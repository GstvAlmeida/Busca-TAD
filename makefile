all:
	g++ -c main.cpp main.o
	g++ main.o -o projeto

run:
	./projeto

dev:
	g++ -c main.cpp main.o
	g++ main.o -o projeto
	./projeto
