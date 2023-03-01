// Copyright 2023 Amelia Silver

#ifndef PROJ2_INC_TEXT_CLIENT_H_
#define PROJ2_INC_TEXT_CLIENT_H_

#include <string>
#include <vector>
#include <iostream>

#include "../inc/unix_domain_sock.h"

class DomainSocketClient : public UnixDomainSocket {
 public:
  using UnixDomainSocket::UnixDomainSocket;

  void RunClient(std::vector<std::string> info);
};

#endif  // PROJ2_INC_TEXT_CLIENT_H_
