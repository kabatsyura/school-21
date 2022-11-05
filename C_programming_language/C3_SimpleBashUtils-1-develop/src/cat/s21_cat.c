#include "s21_cat.h"

int main(int argc, char** argv) {
  struct options s21_flags;
  int checkFlag;

  init_struct(&s21_flags);

  checkFlag = whatIsFlags(argc, argv, &s21_flags);

  if (checkFlag != -1) {
    for (int i = 1; i < argc; ++i) {
      if (argv[i][0] != '-') readFile(argv[i], s21_flags);
    }
  }

  return 0;
}

void init_struct(struct options* s21_flags) {
  s21_flags->b = 0;
  s21_flags->e = 0;
  s21_flags->n = 0;
  s21_flags->s = 0;
  s21_flags->t = 0;
  s21_flags->v = 0;
}

int whatIsFlags(int argc, char** argv, struct options* s21_flags) {
  int counter = 0;
  char error;
  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-' && argv[i][1] == '-') {
      if (strcmp(argv[i], "--number-nonblank") == 0) {
        s21_flags->b = 1;
        counter++;
      } else if (strcmp(argv[i], "--number") == 0) {
        s21_flags->n = 1;
        counter++;
      } else if (strcmp(argv[i], "--squeeze-blank")) {
        s21_flags->s = 1;
      } else {
        error = argv[i][1];
        printf(
            "cat: illegal option -- %c\n"
            "usage: cat [-benstuv] [file ...]\n",
            error);
        counter = -1;
      }
    }
    if (argv[i][0] == '-' && argv[i][1] != '-' && counter != -1) {
      for (size_t j = 1; j < strlen(argv[i]); ++j) {
        if (argv[i][j] == 'b') {
          s21_flags->b = 1;
          counter++;
        } else if (argv[i][j] == 'e') {
          s21_flags->e = 1;
          s21_flags->v = 1;
          counter++;
        } else if (argv[i][j] == 'n') {
          s21_flags->n = 1;
          counter++;
        } else if (argv[i][j] == 's') {
          s21_flags->s = 1;
          counter++;
        } else if (argv[i][j] == 't') {
          s21_flags->t = 1;
          s21_flags->v = 1;
          counter++;
        } else if (argv[i][j] == 'v') {
          s21_flags->v = 1;
          counter++;
        } else if (argv[i][j] == 'T') {
          s21_flags->t = 1;
          counter++;
        } else if (argv[i][j] == 'E') {
          s21_flags->e = 1;
          counter++;
        } else if (counter != -1) {
          error = argv[i][j];
          printf(
              "cat: illegal option -- %c\n"
              "usage: cat [-benstuv] [file ...]\n",
              error);
          counter = -1;
        }
      }
    }
  }
  return counter;
}

void readFile(char* whatIsfile, struct options s21_flags) {
  FILE* f;
  f = fopen(whatIsfile, "r");
  if (f == NULL) {
    printf("cat: %s: No such file or directory", whatIsfile);
  } else {
    int counter = 1;
    char symb = fgetc(f);
    int stroka_1 = (symb == '\n') ? 1 : 0;
    int enter = (stroka_1 == 1) ? 1 : 0;
    int delete_str = 0;
    int not_printing = 0;
    while (!feof(f)) {
      char temp;
      temp = symb;
      if (s21_flags.b == 1 && (stroka_1 || counter == 1) && symb != '\n') {
        printf("%6d\t", counter);
        counter++;
      }

      if (s21_flags.n == 1 && s21_flags.b != 1 && (stroka_1 || counter == 1)) {
        if (delete_str != -1) {
          printf("%6d\t", counter);
          counter++;
        }
      }
      if (s21_flags.e == 1 && symb == '\n') {
        if (delete_str != -1) printf("$");
      }
      if (s21_flags.t == 1 && symb == '\t') {
        printf("^");
        symb = 'I';
      }
      if (s21_flags.v == 1) {
        int ch = (int)symb;
        if (symb < 0) {
          symb &= 127;
          ch = (int)symb;
          ch += 128;
        }
        if (ch != 9 && ch != 10 && ch < 32) {
          printf("^");
          symb += 64;
        } else if (ch == 127) {
          printf("^");
          symb = '?';
        } else if (ch > 127 && ch < 160) {
          printf("M-^");
          symb = ch - 64;
          if (symb == 'J' && (s21_flags.b || s21_flags.n)) {
            printf("%c", symb);
            printf("%6d\t", counter);
            counter += 1;
            not_printing = 1;
          }
        } else if (ch >= 160 && ch <= 255) {
          symb -= 128;
        }
      }

      if (delete_str != -1 && not_printing != 1) {
        printf("%c", symb);
      }
      stroka_1 = (symb == '\n') ? 1 : 0;
      symb = fgetc(f);
      if (enter == 1 && symb == '\n' && s21_flags.s == 1) {
        delete_str = -1;
      } else {
        delete_str = 0;
      }
      if (temp == '\n' && symb == '\n') {
        enter = 1;
      } else {
        enter = 0;
      }
      not_printing = 0;
    }
    fclose(f);
  }
}
