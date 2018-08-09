CC=clang
CFLAGS=-Wall
DEPS=-ledit

FILES=main.c

build:
	$(CC) $(CFLAGS) $(DEPS) $(FILES) -o byol

debug:
	$(CC) $(CFLAGS) $(DEPS) -g $(FILES)
