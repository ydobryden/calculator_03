/*
 ============================================================================
 Name        : stack_modul.c
 Author      : Добрыдень Яна
 License     : GNU GPL
 Description : Модульная версия
 ============================================================================
 */

#include "structs.h"
#include <stdio.h>
#include <stdlib.h>

void init_stack (stack *S) {
	S->headValue = NULL;
}

void push_stack (stack *S, double num) {
	node * temp = malloc (sizeof (node));
	temp->x = num;
	temp->next = S->headValue;
	S->headValue = temp;
}

double pop_stack (stack *S) {
	node *temp;
	temp = malloc (sizeof (node));
	temp = S->headValue;
	S->headValue = S->headValue->next;
	return temp->x;
}
