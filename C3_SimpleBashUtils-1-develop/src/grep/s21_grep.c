#include "s21_grep.h"

int main(int argc, char** argv) {
  if (argc == 1) {
    printf(
        "usage: %s [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] "
        "[-C[num]]\n",
        argv[0]);
    printf("\t[-e pattern] [-f file] [--binary-files=value] [--color=when]\n");
    printf(
        "\t[--context[=num]] [--directories=action] [--label] "
        "[--line-buffered]\n");
    printf("\t[--null] [pattern] [file ...]\n");
  } else if (argc > 2) {
    struct options s21_flags;
    initFlags(&s21_flags);
    int len = argc;
    struct template s21_template[len];
    initTemplate(s21_template, argc);
    int countTemplate = 0;
    defineFlags(argc, argv, &s21_flags, s21_template, &countTemplate);
    scanFiles(argc, argv, s21_template, countTemplate, &s21_flags);
  } else {
    printf("Not arguments\n");
  }
  return 0;
}

void initFlags(struct options* s21_flags) {
  s21_flags->e = 0;
  s21_flags->i = 0;
  s21_flags->v = 0;
  s21_flags->c = 0;
  s21_flags->l = 0;
  s21_flags->n = 0;
  s21_flags->h = 0;
  s21_flags->s = 0;
  s21_flags->f = 0;
  s21_flags->o = 0;
}

void initTemplate(struct template* s21_template, int size) {
  int index = 0;
  while (index < size) {
    s21_template[index].name = NULL;
    s21_template[index].isFile = 0;
    s21_template[index].fileName = NULL;
    s21_template[index].isDefault = 0;
    index++;
  }
}

void initStructFiles(struct file* s21_structFiles, int size) {
  int index = 0;
  while (index < size) {
    s21_structFiles[index].fileName = NULL;
    s21_structFiles[index].matched = 0;
    s21_structFiles[index].matchedAll = 0;
    s21_structFiles[index].valid = 0;
    index++;
  }
}

int whatIsFlags(char* arg, struct options* s21_flags) {
  int error = 0;
  char* flag;
  char* e_flag = strchr(arg, 'e');
  char* f_flag = strchr(arg, 'f');
  if (strlen(arg) == 1 || strlen(arg) != strspn(arg, "-eivclnhsfo")) {
    error = 1;
  }
  if (!e_flag) {
    e_flag = arg + strlen(arg);
  }
  if (!f_flag) {
    f_flag = arg + strlen(arg);
  }
  if (e_flag < f_flag) {
    s21_flags->f = 1;
    f_flag = e_flag;
  }
  if (e_flag > f_flag) {
    s21_flags->e = 1;
    e_flag = f_flag;
  }
  if ((flag = strchr(arg, 'i')) && (e_flag == NULL || flag < e_flag) &&
      (f_flag == NULL || flag < f_flag))
    s21_flags->i = 1;
  if ((flag = strchr(arg, 'v')) && (e_flag == NULL || flag < e_flag) &&
      (f_flag == NULL || flag < f_flag))
    s21_flags->v = 1;
  if ((flag = strchr(arg, 'c')) && (e_flag == NULL || flag < e_flag) &&
      (f_flag == NULL || flag < f_flag))
    s21_flags->c = 1;
  if ((flag = strchr(arg, 'l')) && (e_flag == NULL || flag < e_flag) &&
      (f_flag == NULL || flag < f_flag))
    s21_flags->l = 1;
  if ((flag = strchr(arg, 'n')) && (e_flag == NULL || flag < e_flag) &&
      (f_flag == NULL || flag < f_flag))
    s21_flags->n = 1;
  if ((flag = strchr(arg, 'h')) && (e_flag == NULL || flag < e_flag) &&
      (f_flag == NULL || flag < f_flag))
    s21_flags->h = 1;
  if ((flag = strchr(arg, 's')) && (e_flag == NULL || flag < e_flag) &&
      (f_flag == NULL || flag < f_flag))
    s21_flags->s = 1;
  if ((flag = strchr(arg, 'o')) && (e_flag == NULL || flag < e_flag) &&
      (f_flag == NULL || flag < f_flag))
    s21_flags->o = 1;

  return error;
}

void defineFlags(int argc, char** argv, struct options* s21_flags,
                 struct template* s21_template, int* countTemplate) {
  int e = 0, f = 0, i = 1;
  while (i < argc) {
    if (strspn(argv[i], "-")) {
      whatIsFlags(argv[i], s21_flags);
      if (strchr(argv[i], 'e')) {
        e++;
        s21_template[*countTemplate].isDefault = 0;
        s21_template[*countTemplate].isFile = 0;
        s21_template[*countTemplate].name = getNameOfTemplate(argc, argv, i);
        (*countTemplate)++;
      }
      if (strchr(argv[i], 'f')) {
        f++;
        s21_template[*countTemplate].isDefault = 0;
        s21_template[*countTemplate].isFile = 1;
        s21_template[*countTemplate].fileName = getNameOfFile(argc, argv, i);
        (*countTemplate)++;
      }
    }
    i++;
  }
  if (!e && !f) {
    s21_template[*countTemplate].isFile = 0;
    s21_template[*countTemplate].isDefault = 1;
    s21_template[*countTemplate].name = initDefaultPattern(argc, argv);
    (*countTemplate)++;
  }
}

char* getNameOfTemplate(int argc, char** argv, int index) {
  char* res = NULL;
  if (strchr(argv[index], 'e') == argv[index] + strlen(argv[index]) - 1) {
    if (index + 1 < argc)
      res = argv[index + 1];
    else
      res = strchr(argv[index], 'e') + 1;
  }
  return res;
}

char* getNameOfFile(int argc, char** argv, int index) {
  char* res = NULL;
  if (strchr(argv[index], 'f') == argv[index] + strlen(argv[index]) - 1) {
    if (index + 1 < argc)
      res = argv[index + 1];
    else
      res = strchr(argv[index], 'f') + 1;
  }
  return res;
}

char* initDefaultPattern(int argc, char** argv) {
  char* res = NULL;
  int index = 1;
  while (index < argc) {
    if (!strspn(argv[index], "-")) {
      res = argv[index];
      break;
    }
    index++;
  }
  return res;
}

void scanFiles(int argc, char** argv, struct template* s21_template,
               int countTemplate, struct options* s21_flags) {
  int files_cnt = 0;
  int check1 = 0;
  int check2 = 0;
  int index = 1;
  while (index < argc) {
    if (argvIsFile(index, argv, s21_template, &check1, s21_flags)) {
      files_cnt++;
    }
    index++;
  }

  struct file s21_structFiles[files_cnt];
  initStructFiles(s21_structFiles, files_cnt);
  int countGetsFiles = 0;
  for (int i = 1; i < argc; i++)
    if (argvIsFile(i, argv, s21_template, &check2, s21_flags)) {
      s21_structFiles[countGetsFiles].fileName = argv[i];
      countGetsFiles++;
    }

  filesProcessing(s21_template, countTemplate, s21_structFiles, files_cnt,
                  s21_flags);
}

int argvIsFile(int i, char** argv, struct template* s21_template, int* check1,
               const struct options* s21_flags) {
  return (!strspn(argv[i], "-") &&
          !((strchr(argv[i], 'f') && strspn(argv[i], "-")) ||
            (i != 1 && argv[i - 1][strlen(argv[i - 1]) - 1] == 'f' &&
             strspn(argv[i - 1], "-")) ||
            (strchr(argv[i], 'e') && strspn(argv[i], "-")) ||
            (i != 1 && argv[i - 1][strlen(argv[i - 1]) - 1] == 'e' &&
             strspn(argv[i - 1], "-")) ||
            (!(s21_flags->f || s21_flags->e) &&
             !strcmp(argv[i], s21_template[0].name) && ((*check1)--) >= 0)));
}

void filesProcessing(struct template* s21_template, int countTemplate,
                     struct file* s21_structFiles, int files_cnt,
                     struct options* s21_flags) {
  int empty_line = isEmptyLineInPatterns(s21_template, countTemplate);
  int matching_lines = 0;
  for (int i = 0; i < files_cnt; i++) {
    FILE* f = fopen(s21_structFiles[i].fileName, "r");
    if (f) {
      if (empty_line) {
        if (s21_flags->l || s21_flags->c || (s21_flags->o && !s21_flags->v) ||
            !(s21_flags->v && s21_flags->o)) {
          matching_lines =
              printAll(f, s21_flags, s21_structFiles + i, files_cnt);
        }
      } else {
        matching_lines = seekInFile(f, s21_template, countTemplate, s21_flags,
                                    s21_structFiles + i, files_cnt);
      }
      fclose(f);
    }
    if (s21_flags->c) {
      printFileC(s21_structFiles + i, files_cnt, matching_lines, s21_flags);
    }
    if (s21_flags->l) {
      if (matching_lines > 0) printf("%s\n", s21_structFiles->fileName);
    }
  }
}

int isEmptyLineInPatterns(struct template* s21_template, int countTemplate) {
  int res = 0;
  for (int i = 0; i < countTemplate; i++) {
    if (s21_template[i].isFile) {
      char* line = NULL;
      size_t size = 0;
      FILE* fd = fopen(s21_template[i].fileName, "r");
      if (fd) {
        while (getline(&line, &size, fd) != -1)
          if (line && isEmptyLine(line)) res = 1;
        fclose(fd);
        free(line);
      }
    } else {
      if (isEmptyLine(s21_template[i].name)) res = 1;
    }
  }
  return res;
}

int isEmptyLine(char* name) {
  int res = 0;
  if (strlen(name) == 1 && name[0] == '\n') res = 1;
  return res;
}

int printAll(FILE* fd, struct options* s21_flags, struct file* s21_structFiles,
             int files_cnt) {
  char* line = NULL;
  int line_number = 0;
  size_t size = 0;
  while (getline(&line, &size, fd) != -1) {
    if (line) {
      if (strlen(line) == 1 && line[0] == '\n') line[0] = '.';
      if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
      line_number++;
      if (!s21_flags->c && !s21_flags->l) {
        if (strlen(line) == 1 && line[0] == '.') line[0] = '\0';
        if (!s21_flags->h && files_cnt > 1)
          printf("%s:", s21_structFiles->fileName);
        if (s21_flags->n) printf("%d:", line_number);
        printf("%s\n", line);
      }
    }
  }
  free(line);
  return line_number;
}

int seekInFile(FILE* fd, struct template* s21_template, int countTemplate,
               struct options* s21_flags, struct file* s21_structFiles,
               int files_cnt) {
  int matching_lines = 0;
  int line_number = 0;
  size_t size = 0;
  char* line = NULL;
  while (getline(&line, &size, fd) != -1) {
    if (line) {
      int one_time_print = 1;
      line_number++;
      if (strlen(line) == 1 && line[0] == '\n') line[0] = '.';
      if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
      for (int i = 0; i < countTemplate; i++) {
        int file_name_print = 1;
        seekChoice(line, s21_template + i, s21_structFiles, s21_flags,
                   &matching_lines, files_cnt, line_number, &one_time_print,
                   &file_name_print);
      }
      if (s21_flags->v && one_time_print == 1) {
        printMatch(line, s21_flags, s21_structFiles, files_cnt, line_number,
                   &one_time_print, &matching_lines);
      }
    }
  }
  free(line);
  return matching_lines;
}

void seekChoice(char* line, struct template* s21_template,
                struct file* s21_structFiles, struct options* s21_flags,
                int* matching_lines, int files_cnt, int line_number,
                int* one_time_print, int* file_name_print) {
  if (s21_flags->o && !s21_flags->c && !s21_flags->v) {
    if (s21_template->isFile) {
      seekFilePatterns(line, s21_template, s21_structFiles, s21_flags,
                       matching_lines, files_cnt, line_number, one_time_print,
                       file_name_print);
    } else {
      seekOpattern(line, s21_template, s21_structFiles, s21_flags,
                   matching_lines, files_cnt, line_number, file_name_print);
    }
  } else {
    if (s21_template->isFile) {
      seekFilePatterns(line, s21_template, s21_structFiles, s21_flags,
                       matching_lines, files_cnt, line_number, one_time_print,
                       file_name_print);
    } else {
      seekTemplate(line, *s21_template, s21_structFiles, s21_flags,
                   matching_lines, files_cnt, line_number, one_time_print);
    }
  }
}

void seekFilePatterns(char* line, struct template* s21_template,
                      struct file* s21_structFiles, struct options* s21_flags,
                      int* matching_lines, int files_cnt, int line_number,
                      int* one_time_print, int* file_name_print) {
  FILE* fd = fopen(s21_template->fileName, "r");
  if (fd) {
    char* file_line = NULL;
    size_t file_line_size = 0;
    while (getline(&file_line, &file_line_size, fd) != -1) {
      if (line) {
        s21_template->name = file_line;
        if (s21_flags->o && !s21_flags->c && !s21_flags->v) {
          seekOpattern(line, s21_template, s21_structFiles, s21_flags,
                       matching_lines, files_cnt, line_number, file_name_print);
        } else {
          seekTemplate(line, *s21_template, s21_structFiles, s21_flags,
                       matching_lines, files_cnt, line_number, one_time_print);
        }
      }
    }
    free(file_line);
    fclose(fd);
  }
}

void seekOpattern(char* line, struct template* s21_template,
                  struct file* s21_structFiles, struct options* s21_flags,
                  int* matching_lines, int files_cnt, int line_number,
                  int* file_name_print) {
  regex_t regex;
  trimN(s21_template->name);
  int comp_val = doRegcomp(&regex, s21_flags, s21_template->name);
  if (!comp_val) {
    regmatch_t match;
    size_t offset = 0;
    size_t len = strlen(line);
    int eflags = 0;
    while (regexec(&regex, line + offset, 1, &match, eflags) == 0) {
      if (*file_name_print) (*matching_lines)++;
      eflags = REG_NOTBOL;
      printOmatch(file_name_print, s21_structFiles, offset, match, line,
                  s21_flags, line_number, files_cnt);
      offset += match.rm_eo;
      if (match.rm_so == match.rm_eo) offset += 1;
      if (offset > len) break;
    }
  }
  regfree(&regex);
}

void printOmatch(int* file_name_print, struct file* s21_structFiles,
                 size_t offset, regmatch_t match, char* line,
                 struct options* s21_flags, int line_number, int files_cnt) {
  if (!s21_flags->c && !s21_flags->l) {
    if (strlen(line) == 1 && line[0] == '.') line[0] = '\0';
    if (*file_name_print) {
      if (!s21_flags->h && files_cnt > 1)
        printf("%s:", s21_structFiles->fileName);
      if (s21_flags->n) printf("%d:", line_number);
    }
    for (size_t i = offset + match.rm_so; i < offset + match.rm_eo; i++)
      printf("%c", line[i]);
    printf("\n");
    *file_name_print = 0;
  }
}

void seekTemplate(char* line, struct template s21_template,
                  struct file* s21_structFiles, struct options* s21_flags,
                  int* matching_lines, int files_cnt, int line_number,
                  int* one_time_print) {
  regex_t regex;
  trimN(s21_template.name);
  int comp_val = doRegcomp(&regex, s21_flags, s21_template.name);
  if (!comp_val) {
    int exec_val = regexec(&regex, line, 0, NULL, 0);
    if (exec_val == 0) {
      if (!s21_flags->v) {
        printMatch(line, s21_flags, s21_structFiles, files_cnt, line_number,
                   one_time_print, matching_lines);
      }
      *one_time_print = 0;
    }
  }
  regfree(&regex);
}

void trimN(char* line) {
  if (strlen(line) == 1 && line[0] == '\n') line[0] = '.';
  if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
}

int doRegcomp(regex_t* regex, struct options* s21_flags, char* pattern) {
  int comp_val;
  if (s21_flags->i)
    comp_val = regcomp(regex, pattern, REG_ICASE);
  else
    comp_val = regcomp(regex, pattern, 0);
  return comp_val;
}

void printMatch(char* line, struct options* s21_flags,
                struct file* s21_structFiles, int files_cnt, int line_number,
                int* one_time_print, int* matching_lines) {
  if (!s21_flags->c && !s21_flags->l && *one_time_print) {
    if (strlen(line) == 1 && line[0] == '.') line[0] = '\0';
    if (!s21_flags->h && files_cnt > 1)
      printf("%s:", s21_structFiles->fileName);
    if (s21_flags->n) printf("%d:", line_number);
    printf("%s\n", line);
  }
  if (*one_time_print) (*matching_lines)++;
}

void printFileC(struct file* s21_structFiles, int files_cnt, int matching_lines,
                const struct options* s21_flags) {
  if (!s21_flags->h && files_cnt > 1) printf("%s:", s21_structFiles->fileName);
  if (!s21_flags->l)
    printf("%d\n", matching_lines);
  else
    printf("%d\n", matching_lines > 0 ? 1 : 0);
}
