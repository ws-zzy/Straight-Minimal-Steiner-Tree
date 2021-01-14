all: main smt
	g++ -O4 main.o smt.o -o main.out -std=c++11 -I/usr/include/python3.8 -lpython3.8 -w
smt:
	g++ -O4 -c smt.cpp -o smt.o -std=c++11 -w
main:
	g++ -O4 -c main.cpp -o main.o -std=c++11 -I/usr/include/python3.8 -lpython3.8 -w
clean:
	rm *.o *.out
