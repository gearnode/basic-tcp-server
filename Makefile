CC = gcc
FLAGS = -Wall -Wextra -Werror
SRCFILES = main.c

.DEFAULT: all

.PHONY: all
all: bin bin/server

bin:
	mkdir -p bin

bin/server: bin $(SRCFILES)
	$(CC) $(FLAGS) $(SRCFILES) -o bin/server

.PHONY: clean
clean:
	rm bin/server
	rmdir bin
