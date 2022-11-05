GCC=gcc
CFLAGS= -Wall -Werror -Wextra -std=c11
LIBS= -lcheck
LFLAGS= -fprofile-arcs -ftest-coverage
LINUX = -lrt -lpthread -lm -lsubunit
OS=$(shell uname -s)

all: clean s21_matrix.a test

s21_matrix.o:
	$(GCC) $(CFLAGS) -c s21_matrix.c -o s21_matrix.o

s21_matrix.a: s21_matrix.o
	ar rcs s21_matrix.a s21_matrix.o
	cp s21_matrix.a libs21_matrix.a
	cp s21_matrix.a ls21_matrix.a
	ranlib libs21_matrix.a
	ranlib ls21_matrix.a

test: s21_matrix.a
ifeq ($(OS), Darwin)
	$(GCC) $(CFLAGS) s21_test.c s21_matrix.a -o test.out $(LIBS)
	./test.out
else
	$(GCC) $(CFLAGS) s21_test.c s21_matrix.a -o test.out $(LIBS) $(LINUX)
	./test.out
endif

gcov_report: s21_matrix.c
ifeq ($(OS), Darwin)
	$(GCC) $(CFLAGS) $(LFLAGS) s21_test.c s21_matrix.c -o test.out $(LIBS)
else
	$(GCC) $(CFLAGS) $(LFLAGS) s21_test.c s21_matrix.c -o test.out $(LIBS) $(LINUX)
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

check:
	cp ../materials/linters/CPPLINT.cfg ./
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	python3 ../materials/linters/cpplint.py --extensions=c *.c *.h
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./test.out
else
	valgrind ./test.out --leak-check=full
endif
	make clean

clean:
	rm -rf *.a *.o *.gc* *.out *.info test.out report

rebuild: clean all

study: s21_matrix.c
	$(GCC) $(CFLAGS) s21_matrix.c study.c -o study.o
	./study.o