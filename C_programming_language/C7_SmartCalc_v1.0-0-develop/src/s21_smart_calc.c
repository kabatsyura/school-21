#include "s21_smart_calc.h"

/**
 * @brief проверка, что лексема - число
 * @param error если 0 - ошибки нет, если 1 - ошибка
 */
int is_digit(char expression) {
  int error = 1;
  if ((expression >= '0' && expression <= '9') || expression == '.') {
    error = 0;
  }
  return error;
}

/**
 * @brief парсер текстовой строки
 * @return error если 0 - ошибки нет, если 1 - ошибка
 */
int parser(char expression[256], t_node **head, double value_x) {
  int error = 0;
  int index = 0;
  int expression_length = (int)strlen(expression);
  int cnt_open_bracket = 0;
  int cnt_close_bracket = 0;
  int cnt_dot = 0;

  if ((expression[0] == '-' || expression[0] == '+') &&
      is_digit(expression[1]) == 0 && expression_length > 2) {
    int i = 0;
    char *start_number = &expression[i];
    while (is_digit(expression[++i]) == 0) {
      if (expression[index] == '.') cnt_dot += 1;
    }
    char *finish_number = &start_number[--i];
    double number = strtod(start_number, &finish_number);
    push(head, number, 0, 0);
    index = i + 1;
  }

  for (; index < expression_length; index++) {
    if (is_digit(expression[index]) == 0) {
      char *start_number = &expression[index];
      cnt_dot = 0;
      while (is_digit(expression[index]) == 0) {
        if (expression[index] == '.') cnt_dot += 1;
        index++;
      }
      char *finish_number = &expression[--index];
      double number = strtod(start_number, &finish_number);
      push(head, number, 0, 0);
    } else if (expression[index] == '+') {
      push(head, 0, 1, 1);
    } else if (expression[index] == '-') {
      push(head, 0, 2, 1);
    } else if (expression[index] == '*') {
      push(head, 0, 3, 2);
    } else if (expression[index] == '/') {
      push(head, 0, 4, 2);
    } else if (expression[index] == '^') {
      push(head, 0, 5, 3);
    } else if (expression[index] == 'm') {
      if (strncmp(&expression[index], "mod", 3) == 0) {
        push(head, 0, 6, 2);
        index += 2;
      }
    } else if (expression[index] == 'c') {
      if (strncmp(&expression[index], "cos", 3) == 0 &&
          expression[index + 3] == '(') {
        push(head, 0, 7, 4);
        index += 2;
      }
    } else if (expression[index] == 's') {
      if (strncmp(&expression[index], "sin", 3) == 0 &&
          expression[index + 3] == '(') {
        push(head, 0, 8, 4);
        index += 2;
      } else if (strncmp(&expression[index], "sqrt", 4) == 0 &&
                 expression[index + 4] == '(') {
        push(head, 0, 13, 4);
        index += 3;
      }
    } else if (expression[index] == 't') {
      if (strncmp(&expression[index], "tan", 3) == 0 &&
          expression[index + 3] == '(') {
        push(head, 0, 9, 4);
        index += 2;
      }
    } else if (expression[index] == 'a') {
      if (strncmp(&expression[index], "acos", 4) == 0 &&
          expression[index + 4] == '(') {
        push(head, 0, 10, 4);
        index += 3;
      } else if (strncmp(&expression[index], "asin", 4) == 0 &&
                 expression[index + 4] == '(') {
        push(head, 0, 11, 4);
        index += 3;
      } else if (strncmp(&expression[index], "atan", 4) == 0 &&
                 expression[index + 4] == '(') {
        push(head, 0, 12, 4);
        index += 3;
      }
    } else if (expression[index] == 'l') {
      if (strncmp(&expression[index], "ln", 2) == 0 &&
          expression[index + 2] == '(') {
        push(head, 0, 14, 4);
        index += 1;
      }
      if (strncmp(&expression[index], "log", 3) == 0 &&
          expression[index + 3] == '(') {
        push(head, 0, 15, 4);
        index += 2;
      }
    } else if ((strncmp(&expression[index], "(+", 2) == 0 ||
                strncmp(&expression[index], "(-", 2) == 0) &&
               is_digit(expression[index + 2]) == 0) {
      int i = index + 1;
      char *start_number = &expression[i];
      while (is_digit(expression[++i]) == 0) {
        if (expression[index] == '.') cnt_dot += 1;
      }
      char *finish_number = &start_number[--i];
      double number = strtod(start_number, &finish_number);
      push(head, number, 0, 0);
      index = i + 1;
    } else if (expression[index] == '(') {
      push(head, 0, 16, -1);
      cnt_open_bracket++;
      switch (expression[index + 1]) {
        case '*':
        case '/':
        case '^':
          error = 1;
          break;
      }
    } else if (expression[index] == ')') {
      push(head, 0, 17, -1);
      cnt_close_bracket++;
    } else if (expression[index] == 'x') {
      push(head, value_x, 18, 0);
    } else if (expression[index] == ' ') {
      continue;
    } else {
      error = 1;
      break;
    }
    if (cnt_dot > 1) {
      error = 1;
      break;
    }
  }

  if (cnt_open_bracket != cnt_close_bracket) {
    error = 1;
  }

  return error;
}

/**
 * @brief считываем с последнего узла и записываем данные
 * @param starting_stack стэк куда записаны все первоначальные лексемы
 * @param resulting_stack стэк куда будут записаны лексемы в RPN
 * @return error если 0 - ошибки нет, если 1 - ошибка
 */
int reverse_polish_notation(t_node **starting_stack, t_node **resulting_stack,
                            t_node **support_stack) {
  int error = 0;
  t_node *inverted_stack = rpn_stack(*starting_stack);

  while (1) {
    if (inverted_stack->type == 17) {
      pop(&inverted_stack);
      while ((*support_stack)->type != 16) {
        push(resulting_stack, (*support_stack)->value, (*support_stack)->type,
             (*support_stack)->priority);
        pop(support_stack);
      }
      if ((*support_stack)->type == 16) {
        pop(support_stack);
      }
      if ((*support_stack)->priority == 4) {
        push(resulting_stack, (*support_stack)->value, (*support_stack)->type,
             (*support_stack)->priority);
        pop(support_stack);
      }
    } else {
      if (inverted_stack->type == 0 || inverted_stack->type == 18) {
        push(resulting_stack, inverted_stack->value, inverted_stack->type,
             inverted_stack->priority);
        pop(&inverted_stack);
      } else {
        if (*support_stack) {
          while (*support_stack != NULL) {
            if (inverted_stack->priority != -1 &&
                inverted_stack->priority <= (*support_stack)->priority) {
              push(resulting_stack, (*support_stack)->value,
                   (*support_stack)->type, (*support_stack)->priority);
              pop(support_stack);
            } else {
              break;
            }
          }
        }
        push(support_stack, inverted_stack->value, inverted_stack->type,
             inverted_stack->priority);
        pop(&inverted_stack);
      }
    }
    if (inverted_stack == NULL) break;
  }
  if (*support_stack != NULL) {
    while (*support_stack != NULL) {
      if ((*support_stack)->type == 16) {
        pop(support_stack);
      }
      push(resulting_stack, (*support_stack)->value, (*support_stack)->type,
           (*support_stack)->priority);
      pop(support_stack);
    }
  }
  while (*starting_stack != NULL) {
    pop(starting_stack);
  }
  return error;
}

int calculation(t_node **resulting_stack, double *result) {
  int error = 0;

  t_node *inverted_stack = rpn_stack(*resulting_stack);

  while (inverted_stack->next != NULL) {
    t_node *temp = NULL;
    t_node operator= {0, 0, 0, NULL};
    t_node argument_1 = {0, 0, 0, NULL};
    t_node argument_2 = {0, 0, 0, NULL};
    t_node result_stack = {0, 0, 0, NULL};

    int status_of_peek = write_from_first(inverted_stack, &operator.value,
                                          &operator.type, &operator.priority);

    while ((operator.type == 0 || operator.type == 18) && status_of_peek == 0) {
      push(&temp, operator.value, operator.type, operator.priority);
      pop(&inverted_stack);
      status_of_peek = write_from_first(inverted_stack, &operator.value,
                                        &operator.type, &operator.priority);
    }

    if (status_of_peek == 0) {
      if (operator.type >= 1 && operator.type <= 6) {
        write_from_first(temp, &argument_1.value, &argument_1.type,
                         &argument_1.priority);
        pop(&temp);
        write_from_first(temp, &argument_2.value, &argument_2.type,
                         &argument_2.priority);
        pop(&temp);
      } else {
        write_from_first(temp, &argument_1.value, &argument_1.type,
                         &argument_1.priority);
        pop(&temp);
      }
    }
    switch (inverted_stack->type) {
      case 1:
        result_stack.value = argument_2.value + argument_1.value;
        break;
      case 2:
        result_stack.value = argument_2.value - argument_1.value;
        break;
      case 3:
        result_stack.value = argument_2.value * argument_1.value;
        break;
      case 4:
        result_stack.value = argument_2.value / argument_1.value;
        break;
      case 5:
        result_stack.value = pow(argument_2.value, argument_1.value);
        break;
      case 6:
        result_stack.value = fmod(argument_2.value, argument_1.value);
        break;
      case 7:
        result_stack.value = cos(argument_1.value);
        break;
      case 8:
        result_stack.value = sin(argument_1.value);
        break;
      case 9:
        result_stack.value = tan(argument_1.value);
        break;
      case 10:
        result_stack.value = acos(argument_1.value);
        break;
      case 11:
        result_stack.value = asin(argument_1.value);
        break;
      case 12:
        result_stack.value = atan(argument_1.value);
        break;
      case 13:
        result_stack.value = sqrt(argument_1.value);
        break;
      case 14:
        result_stack.value = log(argument_1.value);
        break;
      case 15:
        result_stack.value = log10(argument_1.value);
        break;
      default:
        error = 1;
        break;
    }

    pop(&inverted_stack);
    result_stack.type = argument_1.type;
    if (inverted_stack == NULL) {
      *result = result_stack.value;
      while (temp != NULL) {
        pop(&temp);
      }
      while (*resulting_stack != NULL) {
        pop(resulting_stack);
      }
      break;
    } else {
      insert_el(&inverted_stack, result_stack.value, result_stack.type,
                result_stack.priority);
    }
    while (temp != NULL) {
      double temp_value = 0;
      t_type temp_type = 0;
      int temp_priority = 0;
      if (write_from_first(temp, &temp_value, &temp_type, &temp_priority) ==
          0) {
        insert_el(&inverted_stack, temp_value, temp_type, temp_priority);
        pop(&temp);
      }
    }
  }
  return error;
}

int input_output(char *expression, double value_x, double *result) {
  int error = 0;

  char expression_for_node[256] = "";
  int sum_of_chars = snprintf(expression_for_node, sizeof(expression_for_node),
                              "%s", expression);

  if (sum_of_chars > 0 && sum_of_chars <= 256) {
    t_node *starting_stack = NULL;
    int status_parser = parser(expression_for_node, &starting_stack, value_x);
    if (status_parser == 0) {
      t_node *result_stack = NULL;
      t_node *support_stack = NULL;

      int status_rpn = reverse_polish_notation(&starting_stack, &result_stack,
                                               &support_stack);
      if (status_rpn == 0) {
        double temp_result = 0.0;
        int status_calc = calculation(&result_stack, &temp_result);

        if (status_calc == 0)
          *result = temp_result;
        else
          error = status_calc;
      } else {
        while (result_stack != NULL) {
          pop(&result_stack);
        }
        error = status_rpn;
      }
    } else {
      error = status_parser;
      while (starting_stack != NULL) {
        pop(&starting_stack);
      }
    }
  } else {
    printf("Сократи выражение до 256 знаков. Cейчас %d знаков\n", sum_of_chars);
    error = 1;
  }

  return error;
}
