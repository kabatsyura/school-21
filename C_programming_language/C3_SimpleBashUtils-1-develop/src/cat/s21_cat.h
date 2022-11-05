#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct options {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
};

void init_struct(struct options* s21_flags);
int whatIsFlags(int argc, char** argv, struct options* s21_flags);
void readFile(char* whatIsfile, struct options s21_flags);

#endif  //  SRC_CAT_S21_CAT_H_
