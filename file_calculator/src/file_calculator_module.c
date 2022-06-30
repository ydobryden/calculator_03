/*
 ============================================================================
 Name        : file_calculator_module.c
 Author      : Добрыдень Яна
 License     : GNU GPL
 Description : Модульная версия
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include "ochered_modul.h"
#include "list_modul.h"
#include "structs.h"
#include "stack_modul.h"

FILE *input,*output;

int main(int argc, char *argv[]) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	char in[256]; 
	char inputFName[259], outputFName[259];

	char h, working_mode, sign, r;
	double d, num;
	double *result;
	double res; 

	calcEl *var_value;
	
	stack s;
	
	turn tCalc1,tCalc2;
	
	list lCalc1,lCalc2;
	do {
		puts ("b - Обратная польская, n - обычная");
		scanf (" %c", &working_mode);

		puts ("Имя входного файла");
		scanf ("%s", inputFName);

		puts ("Имя выходного файла");
		scanf ("%s", outputFName);

		input = fopen (inputFName, "r");
		switch (working_mode) {
			case 'b':
				init_stack (&s);
				if ((output=fopen(outputFName, "a")) == NULL) {
					output=fopen(outputFName, "w");
				}

				while (feof (input) == 0) {
					fscanf (input, "%s", in);
					if (atof(in) == 0) {
						sign = in[0];

						switch (sign) {
							case '+':
								push_stack (&s, pop_stack (&s) + pop_stack(&s));
								break;
							case '-':
								push_stack (&s, pop_stack (&s) - pop_stack(&s));
								break;
							case '*':
								push_stack (&s, pop_stack (&s) * pop_stack(&s));
								break;
							case '/':
								push_stack (&s, pop_stack (&s) / pop_stack(&s));
								break;
							case '!':
								d = 1; 
								num = pop_stack (&s);
								if (num >= 0) {
									for (int i = 0; i < num; i++) {
										d = d * (i + 1);
									}
								}
								push_stack (&s, d);
								break;
							case '^':
								num = pop_stack (&s);
								d = num; 
								for (int i = 1; i < pop_stack (&s); i++) {
									d = d * num;
								}
								push_stack (&s, d);
								break;
							case '=':
								fprintf (output, "%lf\n", pop_stack (&s));
								break;
						}
					} else {
						num = atof (in);
						push_stack (&s, num);
					}
				}
				fclose (input);
				break;
			case 'n':
				puts ("s - работаем со списком, t - работаем с очередями");
				scanf (" %c", &r);
				switch(r) {
					case 't':
						init_turn (&tCalc1);
						init_turn (&tCalc2);
						var_value = malloc (sizeof (calcEl));
						while (feof(input) == 0) {
							fscanf (input, " %c %c", &var_value->c, &var_value->working_mode);
							switch (var_value->working_mode) { 
								case 'v':

									fscanf (input, "%i", &var_value->size); 
									var_value->x = malloc (var_value->size*sizeof(double)); 
									var_value->y = malloc (var_value->size*sizeof(double)); 
									for (int i = 0; i < var_value->size; i++) 
										fscanf (input, "%lf", &var_value->x[i]);
									for (int i = 0; i < var_value->size; i++) 
										fscanf (input, "%lf", &var_value->y[i]);
									break;
								case 'n':
									var_value->size = 1;
									if (var_value->c == '!') {
										var_value->x = malloc (sizeof (double));
										fscanf (input, "%lf", &var_value->x[0]);
										var_value->y = NULL;
									} else {
										var_value->x = malloc (sizeof(double));
										var_value->y = malloc (sizeof(double));
										fscanf (input, "%lf", &var_value->x[0]);
										fscanf (input, "%lf", &var_value->y[0]);
									}
									break;
							}
							endTurn (&tCalc1, var_value);
						}
						free (var_value);
						fclose (input);
						while ((var_value = delTurn(&tCalc1)) != NULL) {
							switch (var_value->working_mode) {
								case 'v':
									switch (var_value->c) {
										case '+':
											result = malloc (var_value->size*sizeof(double));
											for (int i = 0; i < var_value->size; i++) 
												result[i] = var_value->x[i] + var_value->y[i];
											var_value->res = result;
											break;
										case '-':
											for (int i = 0; i < var_value->size; i++) 
												result[i] = var_value->x[i] - var_value->y[i];
											var_value->res = result;
											break;
										case '*':
											res = 0;
											for (int i = 0; i < var_value->size; i++)
												res+=var_value->x[i] * var_value->y[i];
											var_value->result = res;
											break;
									}
									break;
								case 'n':
									switch (var_value->c) {
										case '+': 
											var_value->result = var_value->x[0] + var_value->y[0];
											break;
										case '-': 
											var_value->result = var_value->x[0] - var_value->y[0];
											break;
										case '*': 
											var_value->result = var_value->x[0] * var_value->y[0];
											break;
										case '/': 
											var_value->result = var_value->x[0] / var_value->y[0];
											break;
										case '^': 
											d = var_value->x[0]; 
											for (int i = 1; i < var_value->y[0]; i++)
												d = d * var_value->x[0];
											var_value->result = d;
											break;
										case '!':
											d = 1;
											if (var_value->x[0] >= 0)
												for (int i = 0; i < var_value->x[0]; i++)
													d = d * (i + 1);
											var_value->result = d;
											break;
									}
							}
							endTurn (&tCalc2, var_value);
						}
						if ((output=fopen(outputFName, "a")) == NULL)
							output=fopen(outputFName, "w");
						while ((var_value = delTurn(&tCalc2)) != NULL) {
							switch (var_value->working_mode) {
								case 'v':
									fprintf (output, "( ");
									for (int i = 0; i < var_value->size; i++) {
										if (i == var_value->size-1) {
											fprintf (output, "%lf", var_value->x[i]);
										} else 
											fprintf (output, "%lf ", var_value->x[i]);
									}

									fprintf (output, " ) %c ( ", var_value->c);
									
									for (int i = 0; i < var_value->size; i++) {
										if (i == var_value->size-1) {
											fprintf (output, "%lf", var_value->y[i]);
										} else 
											fprintf (output, "%lf ", var_value->y[i]);
									}
									if (var_value->c == '+' || var_value->c == '-') {
										fprintf (output, " ) = ( ");
										for (int i = 0; i < var_value->size; i++) {
											if (i == var_value->size-1) {
												fprintf (output, "%lf", var_value->res[i]);
											} else 
												fprintf (output, "%lf ", var_value->res[i]);
										}
										fprintf (output, " )\n");
									} else 
										fprintf (output, " ) = %lf\n", var_value->result);
									break;

								case 'n':
									if (var_value->c == '!') {
										fprintf (output, "%lf! = %lf\n", *var_value->x, var_value->result);
									} else 
										fprintf (output, "%lf %c %lf = %lf\n", *var_value->x, var_value->c, *var_value->y, var_value->result);
									break;
							}
						}
						fclose (output);
						break;
					case 's':
						init_list (&lCalc1);
						init_list (&lCalc2);
						
						var_value = malloc (sizeof (calcEl));
						while (feof(input) == 0) {
							fscanf (input, " %c %c", &var_value->c, &var_value->working_mode);
							switch (var_value->working_mode) {
								case 'v':
									fscanf (input, "%i", &var_value->size); 
									var_value->x = malloc (var_value->size * sizeof(double));
									var_value->y = malloc (var_value->size * sizeof(double));
									for (int i = 0; i < var_value->size; i++) 
										fscanf (input, "%lf", &var_value->x[i]);
									for (int i = 0; i < var_value->size; i++) 
										fscanf (input, "%lf", &var_value->y[i]);
									break;
								case 'n':
									// Информация по числам
									var_value->size = 1;
									if (var_value->c == '!') {
										var_value->x = malloc (sizeof (double));
										fscanf (input, "%lf", &var_value->x[0]);
										var_value->y = NULL;
									} else {
										var_value->x = malloc (sizeof(double));
										var_value->y = malloc (sizeof(double));
										fscanf (input, "%lf", &var_value->x[0]);
										fscanf (input, "%lf", &var_value->y[0]);
									}
									break;
							}
							push_list (&lCalc1, var_value);
						}
						fclose (input);
						lCalc1.tlValue = lCalc1.headValue;
						while (lCalc1.tlValue != NULL) {
							var_value->working_mode = lCalc1.tlValue->working_mode;
							var_value->c = lCalc1.tlValue->c;
							var_value->x = lCalc1.tlValue->x;
							var_value->y = lCalc1.tlValue->y;
							var_value->result = lCalc1.tlValue->result;
							var_value->res = lCalc1.tlValue->res;
							var_value->size = lCalc1.tlValue->size;
							switch (var_value->working_mode) {
								case 'v':
									switch (var_value->c) {
										case '+':
											result = malloc (var_value->size * sizeof(double));
											for (int i = 0; i < var_value->size; i++) 
												result[i] = var_value->x[i] + var_value->y[i];
											var_value->res = result;
											break;
										case '-':
											for (int i = 0; i < var_value->size; i++) 
												result[i] = var_value->x[i] - var_value->y[i];
											var_value->res = result;
											break;
										case '*':
											for (int i = 0; i < var_value->size; i++)
												res += var_value->x[i] * var_value->y[i];
											var_value->result = res;
											break;
									}
									break;
								case 'n':
									switch (var_value->c) {
										case '+': 
											var_value->result = var_value->x[0] + var_value->y[0];
											break;
										case '-': 
											var_value->result = var_value->x[0] - var_value->y[0];
											break;
										case '*':
											var_value->result = var_value->x[0] * var_value->y[0];
											break;
										case '/': 
											var_value->result = var_value->x[0] / var_value->y[0];
											break;
										case '^':
											d = var_value->x[0];
											for (int i = 1; i < var_value->y[0]; i++)
												d = d * var_value->x[0];
											var_value->result = d;
											break;
										case '!':
											d = 1; 
											if (var_value->x[0] >= 0)
												for (int i = 0; i < var_value->x[0]; i++)
													d = d * (i + 1);
											var_value->result = d;
											break;
									}
							}
							push_list (&lCalc2, var_value);
							next_list (&lCalc1);
						}
						if ((output=fopen(outputFName, "a"))==NULL)
								output=fopen(outputFName, "w");
						free (var_value);
						lCalc1.tlValue = lCalc1.headValue;
						lCalc2.tlValue = lCalc2.headValue;

						while (lCalc2.tlValue != NULL) {
							switch (lCalc2.tlValue->working_mode) {
								case 'v':
									fprintf (output, "( ");
									for (int i = 0; i < lCalc2.tlValue->size; i++) {
										if (i == lCalc2.tlValue->size-1) {
											fprintf (output, "%lf", lCalc2.tlValue->x[i]);
										} else 
											fprintf (output, "%lf ", lCalc2.tlValue->x[i]);
									}
									fprintf (output, " ) %c ( ", lCalc2.tlValue->c);
									
									for (int i = 0; i < lCalc2.tlValue->size; i++) {
										if (i == lCalc2.tlValue->size-1) {
											fprintf (output, "%lf", lCalc2.tlValue->y[i]);
										} else 
											fprintf (output, "%lf ", lCalc2.tlValue->y[i]);
									}

									if (lCalc2.tlValue->c == '+' || lCalc2.tlValue->c == '-') {
										fprintf (output, " ) = ( ");
										for (int i = 0; i < lCalc2.tlValue->size; i++) {
											if (i == lCalc2.tlValue->size-1) {
												fprintf (output, "%lf", lCalc2.tlValue->res[i]);
											} else 
												fprintf (output, "%lf ", lCalc2.tlValue->res[i]);
										}
										fprintf (output, " )\n");
									} else 
										fprintf (output, " ) = %lf\n", lCalc2.tlValue->result);
									break;
								case 'n':
									if (lCalc2.tlValue->c == '!') {
										fprintf (output, "%lf! = %lf\n", *lCalc2.tlValue->x, lCalc2.tlValue->result);
									} else 
										fprintf (output, "%lf %c %lf = %lf\n", *lCalc2.tlValue->x, lCalc2.tlValue->c, *lCalc2.tlValue->y, lCalc2.tlValue->result);
									break;
							}
							next_list (&lCalc2);
						}
						fclose (output);

						while (lCalc1.headValue != NULL) {
							del_list (&lCalc1);
						}
						while (lCalc2.headValue != NULL) {
							del_list (&lCalc2);
						}
						break;
				}
				break;
		}
		puts ("\nЧтобы продолжить программу введите любой символ\nДля выхода введите 1\n");
		scanf (" %c", &h);
	}
	while (h!='1');
	return 0;
}
