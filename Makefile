SOURCES= $(wildcard src/*.c)
OBJECTFILES= $(subst .c,.o,$(SOURCES))

CFLAGS= -Wall -Wextra -std=c99

ifdef DEBUG
	CFLAGS+= -g
endif

compile: objs

objs: $(OBJECTFILES)

%.o: %.c
	gcc -c $(CFLAGS) $< -o $@

compiletest: compile
	cd test && gcc $(CFLAGS) test.c $(addprefix ../,$(OBJECTFILES))

test: compiletest
	./test/a.out

test-valgrind: compiletest
	valgrind --leak-check=full -s ./test/a.out

clean:
	find . -type f -name '*.o' -delete
	rm -f ./test/a.out
	rm -f vgcore.*
