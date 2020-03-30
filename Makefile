RM = rm -f
CC = g++
CFLAGS = -std=c++11 -g -Wall

run: objects
	@printf "Compiling main\n"
	$(CC) $(CFLAGS) -o main Container.o Test.o

objects:
	$(CC) $(CFLAGS) -c Test.cpp Container.cpp

bin:
	mkdir -p bin

clean:
	$(RM) main Test.o Container.o

.PHONY: run clean