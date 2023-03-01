// Copyright 2023 Amelia Silver

#include <cassert>
#include <cerrno>
#include <cstddef>
#include <cstdlib>
#include <cstring>

#include <string>
#include <iostream>

#include "../inc/text_client.h"

void DomainSocketClient::RunClient(std::vector<std::string> info) {
    // (1) open nameless Unix socket
    int socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        std::cerr << strerror(errno) << std::endl;
        exit(-1);
    }

    // (2) connect to an existing socket
    int success = connect(socket_fd,
                reinterpret_cast<const sockaddr*>(&sock_addr_),
                sizeof(sock_addr_));
    if (success < 0) {
        std::cerr << strerror(errno) << std::endl;
        exit(-1);
    }

    std::clog << "SERVER CONNNECTION ACCEPTED" << std::endl;

    const ssize_t kWrite_buffer_size = 128;
    char write_buffer[kWrite_buffer_size];

    // (3) Write information to socket
    int write_buffer_count = 0;
    for (int i = 0; i < info.size(); i++) {
        std::string toAdd(info.at(i));
        for (int i = 0; write_buffer_count < kWrite_buffer_size &&
                    i < toAdd.size(); i++, write_buffer_count++) {
            write_buffer[write_buffer_count] = toAdd.at(i);
        }
        write_buffer[write_buffer_count] = '\t';
        write_buffer_count++;
    }

    if (write_buffer_count > 0) {
        ssize_t bytes_wrote = write(socket_fd, write_buffer,
                                write_buffer_count);
        if (bytes_wrote < 0) {
            std::cerr << strerror(errno) << std::endl;
            exit(-1);
        }

        if (bytes_wrote == 0) {
            std::clog << "SERVER DROPPED CONNECTION" << std::endl;
            exit(-2);
        }
    }

    // (4) Recieve from server
    const size_t kRead_buffer_size = 1024;
    char read_buffer[kRead_buffer_size];
    int bytes_read;

    bytes_read = read(socket_fd, read_buffer, kRead_buffer_size);

    if (bytes_read == 0) {
        std::clog << "SERVER DISCONNECTED" << std::endl;
        close(socket_fd);
    } else if (bytes_read < 0) {
        std::cerr << strerror(errno) << std::endl;
        exit(-1);
    }

    std::string str_read_buffer(read_buffer);
    int data_count = 1;

    if (str_read_buffer.find("INVALID FILE") != std::string::npos) {
        std::clog << "INVALID FILE" << std::endl;
    } else if (bytes_read == 1) {
        std::clog << "BYTES RECIEVED: " << bytes_read << std::endl;
    } else {
        int index = str_read_buffer.find_first_of('\n');
        while (str_read_buffer.size() > 0 && index != std::string::npos) {
            std::cout << data_count << ".\t";
            std::cout << str_read_buffer.substr(0, index);
            std::cout << std::endl;
            str_read_buffer.erase(0, index + 1);
            data_count++;
            index = str_read_buffer.find_first_of('\n');
        }

        std::clog << "BYTES RECIEVED: " << bytes_read << std::endl;
    }
}
