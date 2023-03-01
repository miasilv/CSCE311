// Copyright 2023 Amelia Silver

#ifndef PROJ2_INC_TEXT_SERVER_H_
#define PROJ2_INC_TEXT_SERVER_H_

#include <string>
#include <iostream>

#include "../inc/unix_domain_sock.h"

class DomainSocketServer : public UnixDomainSocket {
 public:
  using ::UnixDomainSocket::UnixDomainSocket;

  void RunServer() const;
};

#endif  // PROJ2_INC_TEXT_SERVER_H_
