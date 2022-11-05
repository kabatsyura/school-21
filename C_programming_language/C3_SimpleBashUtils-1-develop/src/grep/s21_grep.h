#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <errno.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct options {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
};

struct template {
  char* name;
  int isFile;
  char* fileName;
  int isDefault;
};

struct file {
  char* fileName;
  int matched;
  int matchedAll;
  int valid;
};

void initFlags(struct options* s21_flags);
void initTemplate(struct template* s21_template, int size);
void initStructFiles(struct file* s21_structFiles, int size);

int whatIsFlags(char* arg, struct options* s21_flags);
void defineFlags(int argc, char** argv, struct options* s21_flags,
               struct template* s21_template, int* countTemplate);
char* getNameOfTemplate(int argc, char** argv, int index);
char* getNameOfFile(int argc, char** argv, int index);
char* initDefaultPattern(int argc, char** argv);

void scanFiles(int argc, char** argv, struct template* s21_template,
                int countTemplate, struct options* s21_flags);
int argvIsFile(int i, char** argv, struct template* s21_template,
                  int* check1, const struct options* s21_flags);
void filesProcessing(struct template* s21_template, int countTemplate,
                      struct file* s21_structFiles, int files_cnt,
                      struct options* s21_flags);
int isEmptyLineInPatterns(struct template* s21_template,
                              int countTemplate);
int isEmptyLine(char* name);
int printAll(FILE* fd, struct options* s21_flags, struct file* s21_structFiles,
              int files_cnt);
int seekInFile(FILE* fd, struct template* s21_template, int countTemplate,
                 struct options* s21_flags, struct file* s21_structFiles,
                 int files_cnt);
void seekChoice(char* line, struct template* s21_template,
                 struct file* s21_structFiles, struct options* s21_flags,
                 int* matching_lines, int files_cnt, int line_number,
                 int* one_time_print, int* file_name_print);
void seekFilePatterns(char* line, struct template* s21_template,
                        struct file* s21_structFiles, struct options* s21_flags,
                        int* matching_lines, int files_cnt, int line_number,
                        int* one_time_print, int* file_name_print);
void seekOpattern(char* line, struct template* s21_template,
                    struct file* s21_structFiles, struct options* s21_flags,
                    int* matching_lines, int files_cnt, int line_number,
                    int* file_name_print);
void printOmatch(int* file_name_print, struct file* s21_structFiles,
                   size_t offset, regmatch_t match, char* line,
                   struct options* s21_flags, int line_number, int files_cnt);
void seekTemplate(char* line, struct template s21_template,
                  struct file* s21_structFiles, struct options* s21_flags,
                  int* matching_lines, int files_cnt, int line_number,
                  int* one_time_print);
void trimN(char* line);
int doRegcomp(regex_t* regex, struct options* s21_flags, char* pattern);
void printMatch(char* line, struct options* s21_flags,
                 struct file* s21_structFiles, int files_cnt, int line_number,
                 int* one_time_print, int* matching_lines);
void printFileC(struct file* s21_structFiles, int files_cnt,
                   int matching_lines, const struct options* s21_flags);

#endif  // SRC_GREP_S21_GREP_H_
