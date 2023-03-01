// Copyright 2023 Amelia Silver

#include <sys/sysinfo.h>
#include <cassert>
#include <cerrno>
#include <cstddef>
#include <cstdlib>
#include <cstring>

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "../inc/text_server.h"

void DomainSocketServer::RunServer() const {
    int sock_fd;
    int client_req_sock_fd;

    // (1) create a socket
    sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if ( sock_fd < 0 ) {
        std::cerr << strerror(errno) << std::endl;
        exit(-1);
    }

    // (2) bind socket to address for the server
    unlink(socket_path_.c_str());
    int success = bind(sock_fd,
                reinterpret_cast<const sockaddr*>(&sock_addr_),
                sizeof(sock_addr_));
    if (success < 0) {
        std::cerr << strerror(errno) << std::endl;
        exit(-1);
    }

    // (3) Listen for connections from clients
    size_t kMax_client_conns = get_nprocs_conf() - 1;
    success = listen(sock_fd, kMax_client_conns);
    if (success < 0) {
        std::cerr << strerror(errno) << std::endl;
        exit(-1);
    }

    std::clog << "SERVER STARTED" << std::endl <<
            "\tMAX CLIENTS: " << get_nprocs_conf() - 1 << std::endl;

    const size_t kRead_buffer_size = 128;
    char read_buffer[kRead_buffer_size];

    int bytes_read;
    while (true) {
        // (4) Accept connection from a client
        client_req_sock_fd = accept(sock_fd, nullptr, nullptr);
        if (client_req_sock_fd  < 0) {
            std::cerr << strerror(errno) << std::endl;
            continue;
        }

        std::clog << "CLIENT CONNECTED" << std::endl;

        // (5) Receive information from client
        bytes_read = read(client_req_sock_fd, read_buffer, kRead_buffer_size);

        if (bytes_read == 0) {
            std::clog << "CLIENT DISCONNECTED" << std::endl;
            close(client_req_sock_fd);
        } else if (bytes_read < 0) {
            std::cerr << strerror(errno) << std::endl;
            exit(-1);
        }

        std::vector<std::string> info;
        std::string str_read_buffer(read_buffer);

        // reading path
        int index = str_read_buffer.find_first_of('\t');
        std::string path(str_read_buffer.substr(0, index));
        str_read_buffer.erase(0, index + 1);
        std::clog << "\tPATH: \"" << path << "\"" << std::endl;

        // reading operator
        index = str_read_buffer.find_first_of('\t');
        std::string op(str_read_buffer.substr(0, index));
        str_read_buffer.erase(0, index + 1);
        std::clog << "\tOPPERATOR: " << op << std::endl;

        // reading terms
        std::vector<std::string> terms;
        index = str_read_buffer.find_first_of('\t');
        while (str_read_buffer.size() > 0 && index != std::string::npos) {
            std::string term(str_read_buffer.substr(0, index));
            terms.push_back(term);
            str_read_buffer.erase(0, index + 1);
            index = str_read_buffer.find_first_of('\t');
        }
        std::clog << "\tSEEKING: " << terms.at(0);
        for (int i = 1; i < terms.size(); i++) {
            std::clog << ", " << terms.at(i);
        }
        std::clog << std::endl;

        // (6) Find rows in given file that work
        std::fstream file(path, std::ios::in);
        std::vector<std::string> valid_rows;

        if (file.is_open()) {
            std::string line;
            while (getline(file, line)) {
                if (op.compare("AND") == 0) {
                    int count = 0;
                    for (int i = 0; i < terms.size(); i++) {
                        if (line.find(terms.at(i)) != std::string::npos) {
                            count++;
                        }
                    }
                    if (count == terms.size()) {
                        valid_rows.push_back(line + "\n");
                    }
                } else if (op.compare("OR") == 0) {
                    int count = 0;
                    for (int i = 0; i < terms.size(); i++) {
                        if (line.find(terms.at(i)) != std::string::npos) {
                            count++;
                        }
                    }
                    if (count > 0) {
                        valid_rows.push_back(line + "\n");
                    }
                } else {
                    for (int i = 0; i < terms.size(); i++) {
                        if (line.find(terms.at(i)) != std::string::npos) {
                            valid_rows.push_back(line + "\n");
                        }
                    }
                }
            }
        } else {
            valid_rows.push_back("INVALID FILE");
        }

        for (int i = 0; i < valid_rows.size(); i++) {
            std::cout << valid_rows.at(i);
        }

        // (7) Write to Client
        const ssize_t kWrite_buffer_size = 1024;
        int write_buffer_count = 0;
        char write_buffer[kWrite_buffer_size];

        for (int i = 0; i < valid_rows.size(); i++) {
            for (int j = 0; j < valid_rows.at(i).size() &&
                        write_buffer_count < kWrite_buffer_size;
                        j++, write_buffer_count++) {
                write_buffer[write_buffer_count] = valid_rows.at(i).at(j);
            }
        }

        if (valid_rows.size() <= 0) {
            write_buffer[0] = '0';
            write_buffer_count++;
        }

        if (write_buffer_count > 0) {
            ssize_t bytes_wrote = write(client_req_sock_fd, write_buffer,
                                    write_buffer_count);
            std::clog << "BYTES SENT: " << bytes_wrote << std::endl;
            if (bytes_wrote < 0) {
                std::cerr << strerror(errno) << std::endl;
                exit(-1);
            }

            if (bytes_wrote == 0) {
                std::clog << "CLIENT DROPPED CONNECTION" << std::endl;
                exit(-2);
            }
        }

        // (8) Disconnect from client, clear read/write buffers, and valid_rows
        for (int i = 0; i < kRead_buffer_size; i++) {
            read_buffer[i] = '\0';
        }
        for (int i = 0; i < kWrite_buffer_size; i++) {
            write_buffer[i] = '\0';
        }
        valid_rows.clear();
        close(client_req_sock_fd);
    }
}
