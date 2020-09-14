CC = g++
	FLAGS = -Wall -pedantic -std=c++11

all: obj/matrix.o obj/main.o
	$(CC) $(FLAGS) obj/matrix.o obj/main.o -o main.out

obj:
	mkdir obj

obj/matrix.o: src/matrix.cpp inc/matrix.h
	$(CC) $(FLAGS) src/matrix.cpp -c -o obj/matrix.o

obj/main.o: src/main.cpp
	$(CC) $(FLAGS) src/main.cpp -c -o obj/main.o

clean:
	rm -f obj/*.o