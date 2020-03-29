RM = rm -f
CC = g++
CFLAGS = -std=c++11 -g -Wall

run: main

bin:
	mkdir -p bin

main:
	@printf "Compiling main\n"
	$(CC) $(CFLAGS) -o main main.cpp

clean:
	# $(RM) -r bin
	$(RM) main

.PHONY: run clean