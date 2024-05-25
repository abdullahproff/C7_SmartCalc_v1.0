#include "smartcalc.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void push(Node** plist, char c, int prior) {
  Node* p = (Node*)malloc(sizeof(Node));
  p->c = c;
  p->prior = prior;
  p->next = *plist;
  (*plist) = p;
}

int oper_priority(char c) {
  int res = 0;
  int function =
      ((c == 's') || (c == 'c') || (c == 't') || (c == 'S') || (c == 'C') ||
       (c == 'T') || (c == 'q') || (c == 'l') || (c == 'L'));
  if (c == '(' || c == ')') {
    res = 6;
  } else if (c == '+' || c == '-') {
    res = 2;
  } else if (c == '*' || c == '/' || c == 'm') {
    res = 3;
  } else if (c == '^') {
    res = 4;
  } else if (function) {
    res = 5;
  }
  return res;
}

char pop(Node** plist) {
  Node* p = (*plist);
  char res = p->c;
  (*plist) = p->next;
  free(p);
  return res;
}

void pol_add_operator(char* pol_notation, char oper_, size_t* index) {
  pol_notation[*index] = oper_;
  ++(*index);
  pol_notation[*index] = ' ';
  ++(*index);
}

void pol_add_num(char* pol_notation, char* str, size_t* index, size_t i) {
  int next_number = 0;
  pol_notation[*index] = str[i];
  ++(*index);
  next_number =
      (((str[i + 1] >= 48) && (str[i + 1] <= 57)) || (str[i + 1] == 46));
  if (!next_number) {
    pol_notation[*index] = ' ';
    ++(*index);
  }
}

void push_operator(Node** plist, char oper_, char* pol_notation,
                   size_t* index) {
  int priority = 0;
  priority = oper_priority(oper_);
  if ((oper_ != ')') && ((priority > (*plist)->prior) || (*plist)->c == '(')) {
    push(plist, oper_, priority);
  } else if (oper_ == ')') {
    while ((*plist)->c != '(') {
      pol_add_operator(pol_notation, pop(plist), index);
    }
    pop(plist);
  } else {
    while ((priority <= (*plist)->prior) && ((*plist)->c != '(')) {
      pol_add_operator(pol_notation, pop(plist), index);
    }
    push(plist, oper_, priority);
  }
}

void Polish_notation(char* str, char* pol_notation) {
  Node head = {'\0', 0, NULL};
  Node* list = &head;
  size_t index = 0;
  size_t len = strlen(str);
  int num = 0;
  int unary = 0;
  int x = 0;
  for (size_t i = 0; i < len; ++i) {
    num = number(str[i]);
    unary = unary_oper(str, i);
    x = (str[i] == 'x');
    if (num || unary) {
      pol_add_num(pol_notation, str, &index, i);
    } else if (x) {
      pol_add_operator(pol_notation, str[i], &index);
    } else if (str[i] != ' ') {
      push_operator(&list, str[i], pol_notation, &index);
    }
  }
  while (list->prior != 0) {
    pol_add_operator(pol_notation, pop(&list), &index);
  }
  pol_notation[index] = '\0';
}

double compute_function(double operand, char func) {
  double res = 0;
  if (func == 's') {
    res = sin(operand);
  } else if (func == 'c') {
    res = cos(operand);
  } else if (func == 't') {
    res = tan(operand);
  } else if (func == 'S') {
    res = asin(operand);
  } else if (func == 'C') {
    res = acos(operand);
  } else if (func == 'T') {
    res = atan(operand);
  } else if (func == 'q') {
    res = sqrt(operand);
  } else if (func == 'l') {
    res = log(operand);
  } else if (func == 'L') {
    res = log10(operand);
  }
  return res;
}

double perform_an_arithmetic(double operand_a, double operand_b, char oper_) {
  double res = 0;
  if (oper_ == '+') {
    res = operand_a + operand_b;
  } else if (oper_ == '-') {
    res = operand_a - operand_b;
  } else if (oper_ == '*') {
    res = operand_a * operand_b;
  } else if (oper_ == '/') {
    res = operand_a / operand_b;
  } else if (oper_ == 'm') {
    res = fmod(operand_a, operand_b);
  } else if (oper_ == '^') {
    res = pow(operand_a, operand_b);
  }
  return res;
}

int Function(char func) {
  return ((func == 's') || (func == 'c') || (func == 't') || (func == 'S') ||
          (func == 'C') || (func == 'T') || (func == 'q') || (func == 'l') ||
          (func == 'L'));
}

int Oper_and_open_par(char oper_) {
  return (oper_ == '*' || oper_ == '/' || oper_ == 'm' || oper_ == '^' ||
          oper_ == '(');
}

int Oper_and_closing_par(char oper_) {
  return (oper_ == '*' || oper_ == '/' || oper_ == 'm' || oper_ == '^' ||
          oper_ == ')');
}

int Operators(char oper_) {
  return (oper_ == '*' || oper_ == '/' || oper_ == 'm' || oper_ == '^');
}

int Plus_or_Minus(char oper_) { return (oper_ == '+' || oper_ == '-'); }

double perform_an_operation(stack_n* N, char oper_) {
  int function = Function(oper_);
  double a = 0;
  double b = 0;
  double res = 0;
  if (function) {
    a = N->stack[N->count_stack - 1];
    --(N->count_stack);
    res = compute_function(a, oper_);
  } else {
    b = N->stack[N->count_stack - 1];
    --(N->count_stack);
    a = N->stack[N->count_stack - 1];
    --(N->count_stack);
    res = perform_an_arithmetic(a, b, oper_);
  }
  return res;
}

void push_num(stack_n* N, char* str, size_t* i) {
  int num = 1;
  while (num) {
    N->str_num[N->count_str_num] = str[*i];
    ++(N->count_str_num);
    ++(*i);
    num = number(str[*i]);
  }
  N->num = atof(N->str_num);
  N->stack[N->count_stack] = N->num;
  ++(N->count_stack);
  for (size_t j = 0; j < N->count_str_num; ++j) {
    N->str_num[j] = 0;
  }
  N->count_str_num = 0;
}

double calc(char* str, double x) {
  double res = 0;
  stack_n N = {0};
  size_t i = 0;
  size_t len = strlen(str);
  int num = 0;
  int unary = 0;
  while (i < len) {
    num = number(str[i]);
    unary = unary_oper(str, i);
    if (num || unary) {
      push_num(&N, str, &i);
    } else if (str[i] == 'x') {
      N.stack[N.count_stack] = x;
      ++N.count_stack;
      ++i;
    } else if (str[i] != ' ') {
      N.num = perform_an_operation(&N, str[i]);
      N.stack[N.count_stack] = N.num;
      ++N.count_stack;
      ++i;
    } else {
      ++i;
    }
  }
  res = N.stack[N.count_stack - 1];
  return res;
}
void e_notation(char* result, size_t* j, char next_sym) {
  char replase[10] = {"* 10 ^ "};
  replase[7] = next_sym;
  for (int i = 0; i < 8; ++i) {
    result[*j] = replase[i];
    ++(*j);
  }
}

void parser(char* str, char* result) {
  size_t len = strlen(str);
  int num = 0;
  int next_num = 0;
  int unary = 0;
  for (size_t i = 0, j = 0; i < len; ++i) {
    num = number(str[i]);
    next_num = number(str[i + 1]);
    unary = unary_pars(str, i);
    if (str[i] == 'e') {
      e_notation(result, &j, str[i + 1]);
      ++i;
    } else {
      result[j] = str[i];
      ++j;
      if (num && !next_num) {
        result[j] = ' ';
        ++j;
      } else if (!num && !unary) {
        result[j] = ' ';
        ++j;
      }
    }
  }
}

int number(char sym) { return (((sym >= 48) && (sym <= 57)) || (sym == 46)); }

void Change(char* str, char* result) {
  size_t len = strlen(str);
  int changed = 0;
  for (size_t i = 0, j = 0; i < len; ++i) {
    changed = change_func(str, &i);
    if (!changed) {
      result[j] = str[i];
      ++j;
    } else {
      result[j] = changed;
      ++j;
    }
  }
}

int change_func(char* str, size_t* i) {
  int res = 0;
  char sym = str[*i];
  char next_sym = str[*i + 1];
  if (sym == 'm') {
    res = 'm';
    *i += 2;
  } else if (sym == 's' && next_sym == 'i') {
    res = 's';
    *i += 2;
  } else if (sym == 'c') {
    res = 'c';
    *i += 2;
  } else if (sym == 't') {
    res = 't';
    *i += 2;
  } else if (sym == 's' && next_sym == 'q') {
    res = 'q';
    *i += 3;
  } else if (sym == 'a' && next_sym == 's') {
    res = 'S';
    *i += 3;
  } else if (sym == 'a' && next_sym == 'c') {
    res = 'C';
    *i += 3;
  } else if (sym == 'a' && next_sym == 't') {
    res = 'T';
    *i += 3;
  } else if (sym == 'l' && next_sym == 'n') {
    res = 'l';
    *i += 1;
  } else if (sym == 'l' && next_sym == 'o') {
    res = 'L';
    *i += 2;
  }
  return res;
}

int unary_oper(char* str, size_t index) {
  size_t i = index;
  int unary = (str[i] == '-' || str[i] == '+');
  int next_number = ((str[i + 1] >= 48) && (str[i + 1] <= 57));
  return (unary && next_number);
}

int unary_pars(char* str, size_t index) {
  size_t i = index;
  int oper_ = (Oper_and_open_par(str[i - 1]) || Plus_or_Minus(str[i - 1]));
  int function = Function(str[i - 1]);
  int prev_oper = (function || oper_);
  int at_first = (!i && Plus_or_Minus(str[i]));
  int after_oper = (i && prev_oper && Plus_or_Minus(str[i]));
  return (at_first || after_oper);
}

int Num_or_Func(char sym) { return (number(sym) || Function(sym)); }

int validator(char* str) {
  int return_code = 0;
  size_t len = strlen(str);
  for (size_t i = 0; i < len; ++i) {
    if (!i && Oper_and_closing_par(str[i])) {
      return_code = 1;
    } else if (!i && Plus_or_Minus(str[i]) && !Num_or_Func(str[i + 1])) {
      return_code = 1;
    } else if (Operators(str[i]) && Operators(str[i + 1])) {
      return_code = 1;
    } else if (Operators(str[i]) && Plus_or_Minus(str[i + 1]) &&
               !Num_or_Func(str[i + 2])) {
      return_code = 1;
    } else if (number(str[i]) && str[i + 1] == '(') {
      return_code = 1;
    } else if (Plus_or_Minus(str[i]) && Oper_and_closing_par(str[i + 1])) {
      return_code = 1;
    } else if (str[i] == '.' && str[i + 1] == '.') {
      return_code = 1;
    } else if (str[i] == 'f') {
      return_code = 1;
    } else if ((str[i] == 'n') && (str[i + 1] == 'a')) {
      return_code = 1;
    }
  }
  return return_code;
}

int calculator(char* str, double* X, double* res) {
  double x = 0;
  if (X) {
    x = *X;
  }
  int return_code = 0;
  if (validator(str)) {
    return_code = 1;
  } else {
    char change_func[MAX_SIZE] = {0};
    char str_pars[MAX_SIZE] = {0};
    char pol_notation[MAX_SIZE] = {0};
    Change(str, change_func);
    parser(change_func, str_pars);
    Polish_notation(str_pars, pol_notation);
    *res = calc(pol_notation, x);
  }
  return return_code;
}
