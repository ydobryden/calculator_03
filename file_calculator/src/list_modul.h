/*
 ============================================================================
 Name        : list_modul.h
 Author      : Добрыдень Яна
 License     : GNU GPL
 Description : Модульная версия
 ============================================================================
 */
#include "structs.h"
#ifndef LIST_H_
#define LIST_H_

void init_list (list *listCalc);

void push_list (list *listCalc, calcEl *dataCalc);

void del_list (list *listCalc);

calcEl* next_list (list *listCalc);

#endif
