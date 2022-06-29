/*
 ============================================================================
 Name        : calculator.c
 Author      : Добрыдень Яна
 License     : GNU GPL
 Description : Работа со списками
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char inputFName[259], outputFName[259];
char h;

// Структура списка
typedef struct spisochek
{
	char c;
	double result;
	// Для векторов
	double *A,*B;
	// Режим работы
	char working_mode;
	// Для результата
	double *result_value;
	// Для размерности вектора
	int size;
	struct spisochek *next_value;
} 
spisochek;


typedef struct spisochek_calculate
{
	spisochek *main_val;
	spisochek *hd_val;
} 
spisochek_calculate;


void init_spisochek (spisochek_calculate *value)
{
	value->main_val = NULL;
	value->hd_val = NULL;
}

void add_in_spisochek (spisochek_calculate *value, spisochek *data_info)
{
	spisochek* tmp_information = malloc (sizeof(spisochek));
	spisochek *last_val = value->hd_val;
	tmp_information->next_value = NULL;

	tmp_information->A = data_info->A;
	tmp_information->B = data_info->B;
	
	tmp_information->c = data_info->c;
	
	tmp_information->working_mode = data_info->working_mode;
	
	tmp_information->size = data_info->size;
	
	tmp_information->result_value = data_info->result_value;
	
	tmp_information->result = data_info->result;
	
	if (value->hd_val == NULL)
	{
		value->hd_val = tmp_information;
		return;
	}
	
	while (last_val->next_value != NULL)
	{
		last_val = last_val->next_value;
	}
	last_val->next_value = tmp_information;
	return;
}

void del_spisochek (spisochek_calculate *S)
{
	spisochek *tmp_info;
	if (&S->hd_val==NULL) 
		return;
	tmp_info = S->hd_val;
	S->hd_val = S->hd_val->next_value;
	free (tmp_info);
}

spisochek* next_val_spisochek (spisochek_calculate *S)
{
	S->main_val = S->main_val->next_value;
	return S->main_val;
}


char inputFName[259], outputFName[259];
char h; double d, result_val_calc;
double *result;

FILE *input,*output;

int main(int argc, char *argv[])
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	
	spisochek *spisok_calc;
	spisochek_calculate spisochek1, spisochek2;
	
	do
	{
		init_spisochek (&spisochek1);
		init_spisochek (&spisochek2);
		printf ("Введите название файла, из которого будут взяты данные (формат'.txt'): ");
		scanf ("%s", inputFName);
		printf ("Введите название файла, в который будут записаны результаты вычислений (формат'.txt'): ");
		scanf ("%s", outputFName);

		input = fopen (inputFName, "r");
		spisok_calc = malloc (sizeof (spisochek));
		// Считав файл, идем до его конца
		while (feof(input) == 0) 
		{
			fscanf (input, " %c %c", &spisok_calc->c, &spisok_calc->working_mode);
			switch (spisok_calc->working_mode)
			// Режим работы 
			{ 
			case 'v':
				fscanf (input, "%i", &spisok_calc->size); 
				spisok_calc->A = malloc (spisok_calc->size*sizeof(double));
				spisok_calc->B = malloc (spisok_calc->size*sizeof(double));
				// Выделив память для векторов - заполняем их
				for (int i=0;i<spisok_calc->size;i++)
				{ 
				fscanf (input, "%lf", &spisok_calc->A[i]);
				}
				for (int i=0;i<spisok_calc->size;i++) 
				{
				fscanf (input, "%lf", &spisok_calc->B[i]);
				}
				break;
			case 'n':
				spisok_calc->size = 1;
				if (spisok_calc->c == '!')
				{
				spisok_calc->A = malloc (sizeof (double));
				fscanf (input, "%lf", &spisok_calc->A[0]);
				spisok_calc->B = NULL;
				} 
				else 
				{
				spisok_calc->A = malloc (sizeof(double));
				spisok_calc->B = malloc (sizeof(double));
				fscanf (input, "%lf", &spisok_calc->A[0]);
				fscanf (input, "%lf", &spisok_calc->B[0]);
				}
				break;
			}
			add_in_spisochek (&spisochek1, spisok_calc);
		}
		fclose (input);
		spisochek1.main_val = spisochek1.hd_val;
		while (spisochek1.main_val != NULL) 
		{
			spisok_calc->working_mode = spisochek1.main_val->working_mode;
			
			spisok_calc->A = spisochek1.main_val->A;
			spisok_calc->B = spisochek1.main_val->B;
			spisok_calc->c = spisochek1.main_val->c;

			spisok_calc->result = spisochek1.main_val->result;
			spisok_calc->result_value = spisochek1.main_val->result_value;
			
			spisok_calc->size = spisochek1.main_val->size;
			switch (spisok_calc->working_mode) 
			{
			case 'v':
				switch (spisok_calc->c) 
				{
				case '+':
					result = malloc (spisok_calc->size*sizeof(double));
					for (int i=0;i<spisok_calc->size;i++)
					{ 
					result[i] = spisok_calc->A[i]+spisok_calc->B[i];
					}
					spisok_calc->result_value=result;
					break;
				case '-':
					for (int i=0;i<spisok_calc->size;i++) 
					{
					result[i] = spisok_calc->A[i]-spisok_calc->B[i];
					}
					spisok_calc->result_value = result;
					break;
				case '*':
					for (int i=0;i<spisok_calc->size;i++) 
					{
					result_val_calc += spisok_calc->A[i] * spisok_calc->B[i];
					}
					spisok_calc->result = result_val_calc;
					break;
				}
				break;
			case 'n':
				switch (spisok_calc->c) 
				{
				case '+': 
					spisok_calc->result = spisok_calc->A[0]+spisok_calc->B[0];
					break;
				case '-': 
					spisok_calc->result = spisok_calc->A[0]-spisok_calc->B[0];
					break;
				case '*': 
					spisok_calc->result = spisok_calc->A[0]*spisok_calc->B[0];
					break;
				case '/': 
					spisok_calc->result = spisok_calc->A[0]/spisok_calc->B[0];
					break;
				case '^': 
					d=spisok_calc->A[0]; 
					for (int i=1; i < spisok_calc->B[0]; i++)
					{
					d=d*spisok_calc->A[0];
					}
					spisok_calc->result = d;
					break;
				case '!': 
					d=1; 
					if (spisok_calc->A[0]>=0)
					{
					for (int i=0;i<spisok_calc->A[0];i++)
					{
					d=d*(i+1);
					}
					}
					spisok_calc->result = d;
					break;
				}
				break;
			}
			add_in_spisochek (&spisochek2, spisok_calc);
			next_val_spisochek (&spisochek1);
		}
		if ((output = fopen(outputFName, "a")) == NULL) 
		{
		output = fopen(outputFName, "w");
		}
		free (spisok_calc);

		spisochek1.main_val = spisochek1.hd_val;
		spisochek2.main_val = spisochek2.hd_val;
		
		while (spisochek2.main_val != NULL) 
		{
			switch (spisochek2.main_val->working_mode) 
			{
			case 'v':
				fprintf (output, "( ");
				for (int i = 0; i < spisochek2.main_val->size; i++) 
				{
				if (i == spisochek2.main_val->size-1) 
				{
				fprintf (output, "%lf", spisochek2.main_val->A[i]);
				}
				else
				{ 
				fprintf (output, "%lf ", spisochek2.main_val->A[i]);
				}
				}
				fprintf (output, " ) %c ( ", spisochek2.main_val->c);
				for (int i=0;i<spisochek2.main_val->size;i++) 
				{
				if (i == spisochek2.main_val->size-1) 
				{
				fprintf (output, "%lf", spisochek2.main_val->B[i]);
				}
				else
				{ 
				fprintf (output, "%lf ", spisochek2.main_val->B[i]);
				}
				}
				if (spisochek2.main_val->c == '+' || spisochek2.main_val->c == '-') 
				{
					fprintf (output, " ) = ( ");
					for (int i=0;i<spisochek2.main_val->size;i++) {
						if (i == spisochek2.main_val->size-1) {
							fprintf (output, "%lf", spisochek2.main_val->result_value[i]);
						}
						else
						{ 
							fprintf (output, "%lf ", spisochek2.main_val->result_value[i]);
						}
					}
					fprintf (output, " )\n");
				}
				else
				{ 
					fprintf (output, " ) = %lf\n", spisochek2.main_val->result);
				}
				break;
			case 'n':
				if (spisochek2.main_val->c == '!') 
				{
					fprintf (output, "%lf! = %lf\n", *spisochek2.main_val->A, spisochek2.main_val->result);
				}
				else
				{ 
					fprintf (output, "%lf %c %lf = %lf\n", *spisochek2.main_val->A, spisochek2.main_val->c, *spisochek2.main_val->B, spisochek2.main_val->result);
				}
				break;
			}
			next_val_spisochek (&spisochek2);
		}
		fclose (output);
		while (spisochek1.hd_val != NULL) 
		{
			del_spisochek (&spisochek1);
		}

		while (spisochek2.hd_val != NULL) 
		{
			del_spisochek (&spisochek2);
		}

		puts ("\nЧтобы продолжить программу введите любой символ\nДля выхода введите 1\n");
		scanf (" %c", &h);
	}
	while (h!='1');
	return 0;
}
