GCC=gcc
CFLAGS= -Wall -Werror -Wextra -std=c11 -lm -g
LIBS= -lcheck
LFLAGS= -fprofile-arcs -ftest-coverage
LINUX = -lrt -lpthread -lm -lsubunit
OS=$(shell uname -s)

all: clean test

test:
ifeq ($(OS), Darwin)
	$(GCC) $(CFLAGS) s21_tests.c s21_smart_calc.c s21_stack_func.c -o test.out $(LIBS)
	./test.out
else
	$(GCC) $(CFLAGS) s21_tests.c s21_smart_calc.c s21_stack_func.c -o test.out $(LIBS) $(LINUX)
	./test.out
endif

gcov_report: s21_smart_calc.c
ifeq ($(OS), Darwin)
	$(GCC) $(CFLAGS) $(LFLAGS) s21_tests.c s21_smart_calc.c s21_stack_func.c -o test.out $(LIBS)
else
	$(GCC) $(CFLAGS) $(LFLAGS) s21_tests.c s21_smart_calc.c s21_stack_func.c -o test.out $(LIBS) $(LINUX)
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
	rm -rf *.a *.o *.gc* *.out *.info test.out report s21_smart_calc

rebuild: clean all

study: s21_smart_calc.c s21_stack_func.c
	$(GCC) $(CFLAGS) s21_smart_calc.c s21_stack_func.c study.c -o study.o
	./study.o