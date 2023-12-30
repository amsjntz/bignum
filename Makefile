SOURCES= $(wildcard src/*.c)
OBJECTFILES= $(subst .c,.o,$(SOURCES))

CFLAGS= -Wall -Wextra -std=c99

compile: objs

objs: $(OBJECTFILES)

%.o: %.c
	gcc -c $(CFLAGS) $< -o $@

test: compile
	cd test && gcc $(CFLAGS) test.c $(addprefix ../,$(OBJECTFILES))
	./test/a.out
