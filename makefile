.PHONY : all clean test cleanTest

COMPILER = ${CC}

CFLAGS = -fsanitize=address -pedantic -pedantic-errors -Wall -Wextra -Werror -g

LIBS = 

all: stegobmp;

clean:
	- rm -f *.o src/*.o stegobmp

COMMON = ./src/algorithms/*.o ./src/cli_parser/*.o ./src/files/*.o ./src/stego_cfg/*.o

stegobmp: $(COMMON)
	$(COMPILER) $(CFLAGS) -o stegobmp ./src/stegobmp.c $(COMMON) $(LIBS)
		rm -f src/*.o

test: clean all
	mkdir tests; valgrind --leak-check=full -v ./src/stegobmp 2>> tests/results.valgrind; cppcheck --quiet --enable=all --force --inconclusive ./src/stegobmp.c 2>> tests/output.cppOut

cleanTest:
	rm -rf tests/output.cppOut ./tests/report.tasks tests/results.valgrind tests