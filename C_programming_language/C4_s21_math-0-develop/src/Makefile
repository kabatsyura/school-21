CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11
LINUX = -lrt -lpthread -lm -lsubunit
LIBS=-lcheck
LFLAGS=-fprofile-arcs -ftest-coverage
OS = $(shell uname -s)

all: clean s21_math.a test

s21_math.a: s21_math.o
	ar rcs s21_math.a s21_math.o
	cp s21_math.a libs21_math.a
	cp s21_math.a ls21_math.a
	ranlib libs21_math.a
	ranlib ls21_math.a

s21_math.o: s21_math.c
	$(CC) $(CFLAGS) -c s21_math.c -o s21_math.o

test: s21_math.a
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) s21_test.c s21_math.a -o test.out $(LIBS)
	./test.out
else
	$(CC) $(CFLAGS) s21_test.c s21_math.a -o test.out $(LIBS) $(LINUX)
	./test.out
endif

gcov_report: s21_math.c
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(LFLAGS) s21_test.c s21_math.c -o test.out $(LIBS)
else
	$(CC) $(CFLAGS) $(LFLAGS) s21_test.c s21_math.c -o test.out $(LIBS) $(LINUX)
endif
	./test.out
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info

open:
ifeq ($(OS), Darwin)
	open report/index.html
else
	xdg-open report/index.html
endif

rebuild: clean all

check:
	cp ../materials/linters/CPPLINT.cfg ./
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	python3 ../materials/linters/cpplint.py --extensions=c *.c *.h
	make test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./test.out
else
	valgrind ./test.out --leak-check=full
endif
	make clean

clean:
	rm -rf *.gc* *.o *.a *.out *.info test.out
	rm -rf report
