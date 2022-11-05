CC= gcc
CFLAGS=-Wall -Wextra -Werror -std=c11 -D_GNU_SOURCE

all: s21_grep test

s21_grep:
	$(CC) $(CFLAGS) s21_grep.c -o s21_grep

test:
	chmod +x test.sh
	bash test.sh

check:
	cp ../../materials/linters/CPPLINT.cfg ./
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
	python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h
	make s21_grep
	CK_FORK=no leaks -atExit -- ./s21_grep
	make clean

clean:
	rm -rf *.a *.out *.o log.txt *.cfg s21_grep

rebuild:
	make clean
	make all