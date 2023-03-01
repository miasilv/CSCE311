// Copyright 2023 Amelia Silver

#include "../inc/text_server.h"
#include "../inc/unix_domain_sock.h"

int main(int argc, char *argv[]) {
    DomainSocketServer dss(argv[1]);
    dss.RunServer();

    return 0;
}
