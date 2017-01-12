# Makefile

src="src/global.c" "src/scanner.c" "src/parser.c" "src/error.c"
obj=global.o scanner.o parser.o error.o
misc=Makefile
cflags=-Wall -g -O0 -Werror -pedantic -std=c11
target=starryc

all: $(target)

$(target):
	gcc $(cflags) -I include/ -o $(target) $(src)

clean:
	rm -f $(obj) $(target)
