# Copyright 2022 Avram Cristian-Stefan Grupa 311CA

build:
	gcc -Wall -Wextra -std=c99 main.c utils.c utils.h struct.h -o tema1

run:
	./tema1

clean:
	rm -f tema1

.PHONY: pack clean
