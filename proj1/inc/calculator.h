/**
 * @file calculator.h
 * @author Mia Silver
 * @brief a program that will calculate a math problem separated into an array of opperators (chars) and a matching array of operands (floats)
 * @version 0.1
 * @date 2023-01-31
 *
 * Copyright (c) 2023 <Mia Silver>
 *
 */

#ifndef PROJ1_INC_CALCULATOR_H_
#define PROJ1_INC_CALCULATOR_H_

#include <iostream>

class Calculator {
// prints the calculator object
friend std::ostream &operator<<(std::ostream &lhs, const Calculator &rhs);

 public:
    // creates an empty calculator object
    Calculator();
    // creates a calculator object with the arrays of _num and _op
    Calculator(float _num[], char _op[], int _numSize);
    // creates a calculator object with the same values as aCalculator
    Calculator(Calculator const &aCalculator);
    // destroys a calculator object
    ~Calculator();

    // increases the size of both num and op arrays by 1
    // if the object is empty, just adds 1 to the num array
    void operator++();
    void operator++(int);

    // returns the size of the num array
    int numLength() const;
    // returns the size of the op array (should be 1 less than num)
    int opLength() const;

    // sets the given index in the num array to _num
    void setNum(int index, float _num);
    // sets the given index in the op array to _op
    void setOp(int index, char _op);

    // returns the int at the given index of num
    float getNum(int index) const;
    // returns the char at the given index of op
    char getOp(int index) const;

    // clears the object and resets it to empty
    void clear();

    // finds the given operation in op and returns the index
    // if not found, will return -1
    int findOp(char operation) const;

    // calculates the math problem by checking for each operator with
    // order of operations then removes the specified operator until
    // there are no more operators in op
    float calculate();

 private:
    // sets the length of num to _numSize and op to _numSize - 1
    bool setLength(int _numSize);

    // removes the operator at opIndex and removes one of the
    // corresponding ints in num and replaces the other with the solution.
    void removeOp(int opIndex, float solution);

    int opSize;
    int numSize;
    char *op;
    float *num;
};

#endif  // PROJ1_INC_CALCULATOR_H_
