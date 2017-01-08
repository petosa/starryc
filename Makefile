# Makefile

src=scanner.c
obj=scanner.o
inc=scanner.h
misc=Makefile
cflags=-Wall -g -O0 -Werror -pedantic -std=c11
target=starryc

all: $(target)

$(target) : $(obj) $(misc)
	gcc $(cflags) -o $(target) $(src) $(inc)

clean:
	rm -f $(obj) $(target)
