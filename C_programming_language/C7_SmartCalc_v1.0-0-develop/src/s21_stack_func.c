#include "s21_smart_calc.h"

/**
 * @brief вставляет узел в конец списка
 */
void push(t_node **head, double value, t_type type, int priority) {
  t_node *new_node = malloc(sizeof(t_node));

  if (!new_node) {
    exit(1);
  } else {
    new_node->value = value;
    new_node->type = type;
    new_node->priority = priority;
    new_node->next = *head;
    *head = new_node;
  }
}

t_node *rpn_stack(t_node *rpn) {
  t_node *res = NULL;
  while (rpn) {
    push(&res, rpn->value, rpn->type, rpn->priority);
    rpn = rpn->next;
  }
  return res;
}

/**
 * @brief удаляет последний узел
 */

void pop(t_node **head) {
  if (*head == NULL) {
    exit(1);
  } else {
    t_node *out = *head;
    *head = (*head)->next;
    free(out);
  }
}

/**
 * @brief считываем с первого узла и записываем данные
 * value, type, priority
 */
int write_from_first(t_node *head, double *value, t_type *type,
                     int *priority) {
  int error = 0;

  if (head != NULL) {
    t_node *temp_node = head;
    *value = temp_node->value;
    *type = temp_node->type;
    *priority = temp_node->priority;
  } else {
    error = 1;
  }

  return error;
}

/**
 * @brief вставляет узел в начало односвязного списка
 */
void insert_el(t_node **head, double value, t_type type, int priority) {
  t_node *new_node = malloc(sizeof(t_node));

  if (*head != NULL) {
    new_node->value = value;
    new_node->type = type;
    new_node->priority = priority;
    new_node->next = *head;
    *head = new_node;
  } else {
    *head = new_node;
  }
}
