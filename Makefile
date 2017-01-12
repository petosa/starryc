# Makefile

src=global.c scanner.c parser.c error.c
obj=global.o scanner.o parser.o error.o
inc=global.h scanner.h parser.h error.h
misc=Makefile
cflags=-Wall -g -O0 -Werror -pedantic -std=c11
target=starryc

all: $(target)

$(target) : $(obj) $(misc)
	gcc $(cflags) -o $(target) $(src) $(inc)

clean:
	rm -f $(obj) $(target)
