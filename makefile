all: compile link run

compile:
	g++ -c -I "./include" ./src/main.cpp -o ./lib/main.o

link: compile
	g++  ./lib/main.o  -o ./bin/program

run: link
	./bin/program
