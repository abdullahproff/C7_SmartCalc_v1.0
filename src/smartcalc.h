#ifndef SRS_SMARTCALC_H_
#define SRS_SMARTCALC_H_
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 600

typedef struct Node {
  char c;
  int prior;
  struct Node* next;
} Node;

typedef struct stack_n {
  char str_num[256];
  double stack[256];
  double num;
  size_t count_str_num;
  size_t count_stack;
} stack_n;

char pop(Node** plist);
void push(Node** plist, char c, int prior);
int oper_priority(char c);
void pol_add_operator(char* pol_notation, char oper_, size_t* index);
void pol_add_num(char* pol_notation, char* str, size_t* index, size_t i);
void push_operator(Node** plist, char oper_, char* pol_notation, size_t* index);
void Polish_notation(char* str, char* pol_notation);
int unary_oper(char* str, size_t index);
double compute_function(double operand, char func);
double perform_an_arithmetic(double operand_a, double operand_b, char oper_);
double perform_an_operation(stack_n* N, char oper_);
void push_num(stack_n* N, char* str, size_t* i);
double calc(char* str, double x);
void parser(char* str, char* result);
int unary_pars(char* str, size_t index);

void e_notation(char* result, size_t* j, char next_sym);
int change_func(char* str, size_t* i);
int number(char sym);
int Function(char oper_);
int Oper_and_open_par(char oper_);
int Oper_and_closing_par(char oper_);
int Operators(char oper_);
int Plus_or_Minus(char oper_);
int Num_or_Func(char sym);
int validator(char* str);
int calculator(char* str, double* X, double* res);
void Change(char* str, char* result);

#endif  // SRS_SMARTCALC_H_
