// Copyright 2023 Amelia Silver

#include <string>
#include <vector>

#include "../inc/text_client.h"
#include "../inc/unix_domain_sock.h"

int main(int argc, char *argv[]) {
    DomainSocketClient dsc(argv[1]);

    // creating info vector and adding path to it
    std::vector<std::string> info;
    info.push_back(argv[2]);

    // parsing through operation expression to ensure it is all the same
    char op;
    if (argc >= 6) {
      op = *argv[4];
      for (int i = 6; i < argc; i += 2) {
        if (*argv[i] != op) {
          op = '0';
          std::cerr << "Mixed bool_ops not presently supported"
                    << std::endl;
          exit(2);
        }
      }
    }

    // checks to see if the operator is either '+' or 'x' and adds it to info
    if (op != '+' && op != 'x') {
      op = '0';
    }
    if (op == '+') {
      info.push_back("OR");
    } else if (op == 'x') {
      info.push_back("AND");
    } else {
      info.push_back(std::string("n/a"));
    }


    // parsing through terms to search for
    int size = argc / 2 - 1;
    char * terms[size];
    for (int i = 0; i < size; i++) {
      std::string term(argv[(2 * i) + 3]);
      info.push_back(term);
    }

    dsc.RunClient(info);

    return 0;
}
