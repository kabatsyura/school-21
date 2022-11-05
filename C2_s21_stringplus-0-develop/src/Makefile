.PHONY: all test clean open s21_string.a gcov_report rebuild
CC=gcc
FLAGS=-Wall -Wextra -Werror -std=c11
OS=$(shell uname -s)
LINUX=-lsubunit -lm -lpthread -lrt
LCHECK=-lcheck
CVFLAGS=-fprofile-arcs -ftest-coverage

all: clean s21_string.a test

clean:
	rm -rf report
	rm -rf *.a *.o *.info *.gc* test.out
	rm -rf tester

s21_string.a: s21_string.o
	ar rcs s21_string.a s21_string.o
	cp s21_string.a libs21_string.a
	cp s21_string.a ls21_string.a
	ranlib libs21_string.a
	ranlib ls21_string.a

s21_string.o: s21_string.c
	$(CC) $(FLAGS) -c s21_string.c -o s21_string.o

test: s21_string.a
ifeq ($(OS), Darwin)
	$(CC) $(FLAGS) s21_tests.c s21_string.a -o test.out $(LCHECK)
	./test.out
else
	$(CC) $(FLAGS) s21_tests.c s21_string.a -o test.out $(LCHECK) $(LINUX)
	./test.out
endif

gcov_report: s21_tests.c s21_string.c
ifeq ($(OS), Darwin)
	$(CC) $(FLAGS) $(CVFLAGS) s21_tests.c s21_string.c -o test.out $(LCHECK)
else
	$(CC) $(FLAGS) $(CVFLAGS) s21_tests.c s21_string.c -o test.out $(LCHECK) $(LINUX)
endif
	./test.out
	lcov -t "test.out" -o test.info -c -d .
	genhtml -o report test.info

rebuild: clean all

open:
	open report/index.html

check:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	python3 ../materials/linters/cpplint.py --extensions=c *.c *.h
	make test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./test.out
else
	valgrind ./test.out --leak-check=full
endif
	make clean