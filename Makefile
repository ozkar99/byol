CC=clang
CFLAGS=-Wall
DEPS=-lreadline -lm

FILES=main.c mpc/mpc.c

build:
	$(CC) $(CFLAGS) $(DEPS) $(FILES) -o lispy

debug:
	$(CC) $(CFLAGS) $(DEPS) -g $(FILES)

clean:
	rm -r a.out* lispy*
