// Copyright 2023 Amelia  Silver

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include <string>

#include "../inc/unix_domain_sock.h"

UnixDomainSocket::UnixDomainSocket(const char *socket_path,
                                            bool abstract) {
    socket_path_ = std::string(socket_path);

    sock_addr_ = {};
    sock_addr_.sun_family = AF_UNIX;

    if (abstract)
      strncpy(sock_addr_.sun_path + 1,
              socket_path,
              sizeof(sock_addr_.sun_path) - 1);
    else
      strncpy(sock_addr_.sun_path,
              socket_path,
              sizeof(sock_addr_.sun_path));
}
