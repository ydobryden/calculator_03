/*
 ============================================================================
 Name        : stack_modul.h
 Author      : Добрыдень Яна
 License     : GNU GPL
 Description : Модульная версия
 ============================================================================
 */

#ifndef STACK_H_
#define STACK_H_

void init_stack (stack *S);

void push_stack (stack *S, double num);

double pop_stack (stack *S);


#endif
