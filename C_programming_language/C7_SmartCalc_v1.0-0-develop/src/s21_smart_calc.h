#ifndef SRC_S21_SMART_CALC_H_
#define SRC_S21_SMART_CALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum t_type {
  number,
  add,
  sub,
  multiply,
  division,
  my_pow,
  my_mod,
  my_cos,
  my_sin,
  my_tan,
  my_acos,
  my_asin,
  my_atan,
  my_sqrt,
  my_ln,
  my_log,
  open_bracket,
  close_bracket,
  value_x
} t_type;

/**
 * @brief Структура для узла
 */
typedef struct node {
  double value;
  t_type type;
  int priority;
  struct node *next;
} t_node;

// /**
//  * @brief Структура для ссылки на очередь
//  * @param first ссылка на начало очереди
//  * @param last ссылка на конец очереди
//  */
// typedef struct queue {
//   t_node *first;
//   t_node *last;
// } t_queue;

/* функции обработки стэка */

void push(t_node **head, double value, t_type type, int priority);
void pop(t_node **head);
int write_from_first(t_node *head, double *value, t_type *type, int *priority);
int write_from_last(t_node *head, double *value, t_type *type, int *priority);
void delete_first_el(t_node **head);
t_node* rpn_stack(t_node *rpn);
void insert_el(t_node **head, double value, t_type type, int priority);

/* функции smart_calc */

int is_digit(char expression);
int parser(char expression[256], t_node **head, double value_x);
int reverse_polish_notation(t_node **starting_stack, t_node **resulting_stack, t_node **support_stack);
void check_01(t_node **starting_stack, t_node **resulting_stack, t_node *support_stack,
              double starting_value, t_type starting_type,
              int starting_priority);
void closing_bracket(t_node **resulting_stack, t_node *support_stack,
                     int *error, t_type starting_type);
void if_in_starting_no_lexems(t_node **resulting_stack, t_node *support_stack,
                              int *error);
int calculation(t_node **resulting_stack, double *result);
int input_output(char *expression, double value_x, double *result);

/* потом удалить */
int print_node(t_node *test_node, char sometext[100]);

#endif  //  SRC_S21_SMART_CALC_H_
