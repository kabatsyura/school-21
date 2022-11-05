CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11 -D_GNU_SOURCE

all: s21_cat test

s21_cat:
	$(CC) $(CFLAGS) s21_cat.c -o s21_cat

test:
	chmod +x test.sh
	bash test.sh

clean:
	rm -rf *.a *.out *.o log.txt s21_cat *.cfg

check:
	cp ../../materials/linters/CPPLINT.cfg ./
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
	python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h
	make s21_cat
	CK_FORK=no leaks -atExit -- ./s21_cat
	make clean

rebuild:
	make clean
	make all
	rm -rf  *.o *.a