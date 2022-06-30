/*
 ============================================================================
 Name        : structs.c
 Author      : Добрыдень Яна
 License     : GNU GPL
 Description : Модульная версия
 ============================================================================
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

typedef struct calcEl {
	char c;
	double *x,*y;
	char working_mode;
	double *res;
	int size;
	double result;
	struct calcEl *next;
} calcEl;

typedef struct turn {
	calcEl *headValue;
	calcEl *tlValue;
} turn;

typedef struct node {
	double x;
	struct node *next;
} node;

typedef struct stack {
	node *headValue;
} stack;

typedef struct list {
	calcEl *headValue;
	calcEl *tlValue;
} list;


#endif 
