/**
 * @file main.cc
 * @author Mia Silver
 * @brief a function that will take in command line arguments, transforms them into a form that can be calculated by a calculator object, and returns the solution.
 * @version 0.1
 * @date 2023-01-31
 * 
 * Copyright (c) 2023 <Mia Silver>
 * 
 */

#include <iostream>
#include "../inc/calculator.h"

int main(int argc, char *argv[]) {
    Calculator calc;

    // fills number array
    int i, j;
    for (i = j = 1; i < argc; i += 2, j++) {
        calc++;
        float fl = atof(argv[i]);
        calc.setNum(i - j, fl);
    }
    // fills operation array
    for (i = j = 2; i < argc; i += 2, j++) {
        calc.setOp(i - j, *(argv[i]));
    }

    std::cout << calc.calculate() << std::endl;

    return 0;
}
