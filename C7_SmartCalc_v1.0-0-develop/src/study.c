#include "s21_smart_calc.h"

int print_node(t_node *test_node, char sometext[100]) {
  int error = 0;
  if (test_node != NULL) {
    int counter = 1;
    for (; test_node->next != NULL; counter++) {
      printf("%s_lexem %d has value %f type %d priority %d\n", sometext,
             counter, test_node->value, test_node->type, test_node->priority);
      test_node = test_node->next;
    }
    printf("%s_lexem %d has value %f type %d priority %d\n", sometext, counter,
           test_node->value, test_node->type, test_node->priority);
  } else {
    error = 1;
  }
  return error;
}

int main() {
  char stroka[256] = "-10mod3";
  t_node *test_node = NULL;
  int status = parser(stroka, &test_node, 0);
  if (status == 0) {
    print_node(test_node, "first");
    // t_node *rpn = rpn_stack(test_node);
    // print_node(rpn, "rpn");
    t_node *result_stack = NULL;
    t_node *support_stack = NULL;

    int status_rpn =
        reverse_polish_notation(&test_node, &result_stack, &support_stack);
    if (status_rpn == 0) {
      printf("\n");
      // print_node(result_stack, "result_stack");
      // print_node(support_stack, "support");
      double result = 0;
      int status_calc = calculation(&result_stack, &result);
      if (status_calc == 1) {
        printf("Ошибка calculation");
      } else {
        printf("%f", result);
      }
    } else {
      printf("Ошибка RPN");
    }
  } else {
    printf("Ошибка парсера!");
  }
  printf("\n\n");

  return 0;
}
