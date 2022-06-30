/*
 ============================================================================
 Name        : ochered_modul.h
 Author      : Добрыдень Яна
 License     : GNU GPL
 Description : Модульная версия
 ============================================================================
 */

#include "structs.h"
#ifndef QUEUE_H_
#define QUEUE_H_

void init_turn (turn *T);

void endTurn (turn *T, calcEl *dataCalc);

calcEl* delTurn (turn *T);

#endif 
