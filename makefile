main.o: main.c
	g++ -c main.c main.o

all:
	g++ main.o -o projeto

run:
	./projeto

dev: 
	g++ main.o -o projeto
	./projeto
