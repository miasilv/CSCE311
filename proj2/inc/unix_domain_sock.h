// Copyright 2023 Amelia Silver

#ifndef PROJ2_INC_UNIX_DOMAIN_SOCK_H_
#define PROJ2_INC_UNIX_DOMAIN_SOCK_H_

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include <string>

class UnixDomainSocket {
 public:
  /// @param socket_path A null-terminated C-string containing the shared path
  ///                    name for socket.
  /// @param abstract Defaults to abstract socket path names, pass false for
  ///                 non-abstract naming.
    explicit UnixDomainSocket(const char *socket_path, bool abstract = true);

 protected:
  ::sockaddr_un sock_addr_;

  std::string socket_path_;
};

#endif  // PROJ2_INC_UNIX_DOMAIN_SOCK_H_
