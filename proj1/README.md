# **Calculator Project:**
_A command line calculator capable of correctly evaluating infix notation expressions involving addition (+), subtraction (-), multiplication (x), and division (/). Order of operation is observed._

### **calculator.h and calculator.cc:** 
An object that will calculate a given math problem separated into an array of opperators (chars) and a matching array of operands (floats). Both array must be in the order that they were provided (Ex: [1 + 2 - 3] --> [1 2 3] and [+ -])

### **main.cc:**
A function that takes in command line arguments, transforms them into a form that can be calculated by a calculator object, and returns the solution.

### **Usage:**
First type `make` in the terminal of this projects root folder. This will create the executable calculate. Then enter `./calculate 2 + 3` or whatever math formula you want to input. The program will then output the solution.