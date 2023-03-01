calculate: main.o calculator.o
	g++ bin/main.o bin/calculator.o -o calculate

main.o: src/main.cc
	g++ -c src/main.cc -o bin/main.o

calculator.o: src/calculator.cc inc/calculator.h
	g++ -c src/calculator.cc -o bin/calculator.o

clean: 
	rm bin/*
	rm calculate