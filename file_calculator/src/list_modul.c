/*
 ============================================================================
 Name        : list_modul.c
 Author      : Добрыдень Яна
 License     : GNU GPL
 Description : Модульная версия
 ============================================================================
 */
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>

void init_list (list *listCalc) {
	listCalc->headValue = NULL;
	listCalc->tlValue = NULL;
}

void push_list (list *listCalc, calcEl *dataCalc) {
	calcEl* temp = malloc (sizeof(calcEl));
	calcEl *lastVal = listCalc->headValue;
	
	temp->x = dataCalc->x;
	temp->y = dataCalc->y;
	temp->c = dataCalc->c;
	temp->working_mode = dataCalc->working_mode;
	temp->res = dataCalc->res;
	temp->size = dataCalc->size;
	temp->next = NULL;
	temp->result = dataCalc->result;
	if (listCalc->headValue==NULL) {
		listCalc->headValue = temp;
		return;
	}

	while (lastVal->next != NULL) {
		lastVal = lastVal->next;
	} lastVal->next = temp;
	
	return;
}

calcEl* next_list (list *listCalc) {
	listCalc->tlValue = listCalc->tlValue->next;
	return listCalc->tlValue;
}

void del_list (list *listCalc) {
	calcEl *temp;
	if (&listCalc->headValue == NULL) 
		return;
	temp = listCalc->headValue;
	listCalc->headValue = listCalc->headValue->next;

	free (temp);
}


