RM = rm -f
CC = g++
CFLAGS = -std=c++11 -g -Wall

run: objects
	@printf "Compiling main\n"
	$(CC) $(CFLAGS) -o main main.o Container.o

objects:
	$(CC) $(CFLAGS) -c main.cpp Container.cpp

bin:
	mkdir -p bin

clean:
	$(RM) main main.o Container.o

.PHONY: run clean