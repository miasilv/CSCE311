/**
 * @file calculator.cc
 * @author Mia Silver
 * @brief a program that will calculate a math problem separated into an array of opperators (chars) and a matching array of operands (floats)
 * @version 0.1
 * @date 2023-02-01
 * 
 * Copyright (c) 2023 <Mia Silver>
 * 
 */

#include <iostream>
#include "../inc/calculator.h"

Calculator::Calculator() {
    setLength(0);
    num = new float[numLength()];
    op = new char[opLength()];
}

Calculator::Calculator(float _num[], char _op[],  int _numSize) {
    setLength(_numSize);
    num = new float[numLength()];
    op = new char[opLength()];
    for (int i = 0; i < opSize; i++) {
        op[i] = _op[i];
        num[i] = _num[i];
    }
    num[numLength() - 1] = _num[numLength() - 1];
}

Calculator::Calculator(Calculator const &aCalculator) {
    setLength(aCalculator.numLength());
    num = new float[numLength()];
    op = new char[opLength()];
    for (int i = 0; i < opSize; i++) {
        op[i] = aCalculator.getOp(i);
        num[i] = aCalculator.getOp(i);
    }
    num[numLength() - 1] = aCalculator.getNum(numLength() - 1);
}

Calculator::~Calculator() {
    delete [] num;
    delete [] op;
}


void Calculator::operator++() {
    if (numLength() == 0) {
        int kNumLength = numLength();
        float floatArr[kNumLength + 1];
        for (int i = 0; i < numSize; i++) {
            floatArr[i] = num[i];
        }

        Calculator temp(floatArr, op, numLength() + 1);
        delete [] num;
        setLength(numLength() + 1);
        num = new float[numLength()];
        for (int i = 0; i < numSize; i++) {
            num[i] = temp.getNum(i);
        }
        num[numLength() - 1] = 0;
        return;
    }

    int kNumLength = numLength();
    int kOpLength = opLength();
    float floatArr[kNumLength + 1];
    char charArr[kOpLength + 1];
    for (int i = 0; i < opSize; i++) {
        charArr[i] = op[i];
        floatArr[i] = num[i];
    }
    floatArr[numLength() - 1] = num[numLength() - 1];

    Calculator temp(floatArr, charArr, numLength() + 1);
    delete [] num;
    delete [] op;
    setLength(numLength() + 1);
    num = new float[numLength()];
    op = new char[opLength()];
    for (int i = 0; i < opSize; i++) {
        op[i] = temp.getOp(i);
        num[i] = temp.getNum(i);
    }
    op[opLength() - 1] = ' ';
    num[numLength() - 1] = 0;
}

void Calculator::operator++(int) {
    if (numLength() == 0) {
        int kNumLength = numLength();
        float floatArr[kNumLength + 1];
        for (int i = 0; i < numSize; i++) {
            floatArr[i] = num[i];
        }

        Calculator temp(floatArr, op, numLength() + 1);
        delete [] num;
        setLength(numLength() + 1);
        num = new float[numLength()];
        for (int i = 0; i < numSize; i++) {
            num[i] = temp.getNum(i);
        }
        num[numLength() - 1] = 0;
        return;
    }

    int kNumLength = numLength();
    int kOpLength = opLength();
    float floatArr[kNumLength + 1];
    char charArr[kOpLength + 1];
    for (int i = 0; i < opSize; i++) {
        charArr[i] = op[i];
        floatArr[i] = num[i];
    }
    floatArr[numLength() - 1] = num[numLength() - 1];

    Calculator temp(floatArr, charArr, numLength() + 1);
    delete [] num;
    delete [] op;
    setLength(numLength() + 1);
    num = new float[numLength()];
    op = new char[opLength()];
    for (int i = 0; i < opSize; i++) {
        op[i] = temp.getOp(i);
        num[i] = temp.getNum(i);
    }
    op[opLength() - 1] = ' ';
    num[numLength() - 1] = 0;
}


int Calculator::numLength() const {
    return numSize;
}

int Calculator::opLength() const {
    return opSize;
}


void Calculator::setNum(int index, float _num) {
    if (index >= 0 && index < numLength()) {
        num[index] = _num;
    } else {
        std::cout << "Index out of bound error";
        exit(1);
    }
}

void Calculator::setOp(int index, char _op) {
    if (index >= 0 && index < opLength()) {
        op[index] = _op;
    } else {
        std::cout << "Index out of bound error";
        exit(1);
    }
}

float Calculator::getNum(int index) const {
    if (index >= 0 && index < numLength()) {
        return num[index];
    } else {
        std::cout << "Index out of bound error";
        exit(1);
    }
}

char Calculator::getOp(int index) const {
    if (index >= 0 && index < opLength()) {
        return op[index];
    } else {
        std::cout << "Index out of bound error";
        exit(1);
    }
}


void Calculator::clear() {
    delete [] num;
    delete [] op;
    setLength(0);
    num = new float[numLength()];
    op = new char[opLength()];
}

int Calculator::findOp(char operation) const {
    for (int i = 0; i < opSize; i++) {
        if (op[i] == operation) {
            return i;
        }
    }
    return -1;
}

float Calculator::calculate() {
    while (opLength() > 0) {
        int d = findOp('/');
        while (d >= 0) {
            float solution = getNum(d) / getNum(d + 1);
            removeOp(d, solution);
            d = findOp('/');
        }

        int m = findOp('x');
        while (m >= 0) {
            float solution = getNum(m) * getNum(m + 1);
            removeOp(m, solution);
            m = findOp('x');
        }

        int a = findOp('+');
        while (a >= 0) {
            float solution = getNum(a) + getNum(a + 1);
            removeOp(a, solution);
            a = findOp('+');
        }

        int s = findOp('-');
        while (s >= 0) {
            float solution = getNum(s) - getNum(s + 1);
            removeOp(s, solution);
            s = findOp('-');
        }
    }
    return num[0];

    clear();
}


bool Calculator::setLength(int _numSize) {
    if (_numSize >= 1) {
        numSize = _numSize;
        opSize = _numSize - 1;
        return true;
    }
    numSize = 0;
    opSize = 0;
    return false;
}

void Calculator::removeOp(int opIndex, float solution) {
    int kNumLength = numLength();
    int kOpLength = opLength();
    float floatArr[kNumLength - 1];
    char charArr[kOpLength - 1];
    for (int i = 0; i < opIndex; i++) {
        floatArr[i] = num[i];
        charArr[i] = op[i];
    }
    for (int i = opIndex + 1; i < opSize; i++) {
        charArr[i - 1] = op[i];
    }
    floatArr[opIndex] = solution;
    for (int i = opIndex + 2; i < numSize; i++) {
        floatArr[i - 1] = num[i];
    }

    Calculator temp(floatArr, charArr, numLength() - 1);
    delete [] num;
    delete [] op;
    setLength(numLength() - 1);
    num = new float[numLength()];
    op = new char[opLength()];
    for (int i = 0; i < opSize; i++) {
        op[i] = temp.getOp(i);
        num[i] = temp.getNum(i);
    }
    num[numLength() - 1] = temp.getNum(numLength() - 1);
}


std::ostream & operator<<(std::ostream &lhs, const Calculator &rhs) {
    int opSize = rhs.opLength();
    for (int i = 0; i < opSize; i++) {
        lhs << rhs.getNum(i) << " ";
        lhs << rhs.getOp(i) << " ";
    }
    lhs << rhs.getNum(opSize);
    return lhs;
}
