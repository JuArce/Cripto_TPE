.PHONY : all clean test cleanTest

COMPILER = ${CC}

CFLAGS = -fsanitize=address -pedantic -pedantic-errors -Wall -Wextra -g

LIBS = -lcrypto	

all: stegobmp;

clean:
	- rm -f *.o src/**/*.o stegobmp

COMMON = ./src/algorithms/decrypt.o ./src/algorithms/embed.o ./src/algorithms/encrypt.o ./src/algorithms/extract.o ./src/algorithms/stego_algorithms.o ./src/cli_parser/cli_parser.o ./src/crypto_cfg/crypto_cfg.o  ./src/files/bmp.o ./src/files/file.o ./src/files/files.o ./src/logger/logger.o ./src/stego_cfg/stego_cfg.o

stegobmp: $(COMMON)
	$(COMPILER) $(CFLAGS) -o stegobmp ./src/stegobmp.c $(COMMON) $(LIBS)
		rm -f src/**/*.o

test: clean all
	mkdir tests; valgrind --leak-check=full -v ./src/stegobmp 2>> tests/results.valgrind; cppcheck --quiet --enable=all --force --inconclusive ./src/stegobmp.c 2>> tests/output.cppOut

cleanTest:
	rm -rf tests/output.cppOut ./tests/report.tasks tests/results.valgrind tests