/*
 ============================================================================
 Name        : calculator.c
 Author      : Добрыдень Яна
 License     : GNU GPL
 Description : Работа c очередями
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char inputFName[259], outputFName[259];
char h;

typedef struct ocherednyara 
{
	char c;
	char working_mode;
	double *result_value;

	double result;
	double *A,*B;
	
	int size;
	struct ocherednyara *next;
} 
ocherednyara;

typedef struct ochered {
	ocherednyara *main_val;

	ocherednyara *hd_val;
} ochered;

void init_ochered (ochered *O) {
	O->main_val = NULL;
	O->hd_val = NULL;
	
}

void ochered_main (ochered *O, ocherednyara *data_info) {
	ocherednyara* tmp_information = malloc (sizeof(ocherednyara));
	tmp_information->A = data_info->A;
	tmp_information->B = data_info->B;
	tmp_information->c = data_info->c;

	tmp_information->working_mode = data_info->working_mode;
	
	tmp_information->size = data_info->size;
	tmp_information->next = NULL;
	tmp_information->result_value = data_info->result_value;
	tmp_information->result = data_info->result;
	if (O->main_val != NULL) {
		O->main_val->next = tmp_information;
	}
	O->main_val = tmp_information;
	if (O->hd_val == NULL) {
		O->hd_val = tmp_information;
	}
}

ocherednyara* del_ochered (ochered *O)
{
	ocherednyara *value_out;
	value_out = malloc (sizeof (ocherednyara));
	if (O->hd_val == NULL) {
		value_out = NULL;
		return value_out;
	}
	ocherednyara *tmp_information = O->hd_val;
	value_out->c = tmp_information->c;
	value_out->result_value = tmp_information->result_value;
	value_out->result = tmp_information->result;
	value_out->A = tmp_information->A;
	value_out->B = tmp_information->B;
	value_out->size = tmp_information->size;
	value_out->working_mode = tmp_information->working_mode;

	O->hd_val = O->hd_val->next;
	if (O->hd_val == NULL) {
		O->main_val = NULL;
	}

	free (tmp_information);
	return value_out;
}
double d, result_value;
double *result;
FILE *input,*output;

int main(int argc, char *argv[]) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	
	ocherednyara *ochered_value;
	ochered ocherednyara1, ocherednyara2;
	do {
		init_ochered (&ocherednyara1);
		init_ochered (&ocherednyara2);
		printf ("Введите название файла, из которого будут взяты данные (формат'.txt'): ");
		scanf ("%s", inputFName);
		printf ("Введите название файла, в который будут записаны результаты вычислений (формат'.txt'): ");
		scanf ("%s", outputFName);

		input = fopen (inputFName, "r");
		ochered_value = malloc (sizeof (ocherednyara));
		while (feof(input) == 0) {
			fscanf (input, " %c %c", &ochered_value->c, &ochered_value->working_mode);
			switch (ochered_value->working_mode) { 
				case 'v':
					fscanf (input, "%i", &ochered_value->size); 
					ochered_value->A = malloc (ochered_value->size*sizeof(double));
					ochered_value->B = malloc (ochered_value->size*sizeof(double));
					for (int i=0;i<ochered_value->size;i++) 
					{
						fscanf (input, "%lf", &ochered_value->A[i]);
					}
					for (int i=0; i < ochered_value->size; i++) 
					{
						fscanf (input, "%lf", &ochered_value->B[i]);
					}
					break;
				case 'n':
					ochered_value->size = 1;
					if (ochered_value->c == '!') 
					{
						ochered_value->A = malloc (sizeof (double));
						fscanf (input, "%lf", &ochered_value->A[0]);
						ochered_value->B = NULL;
					} 
					else 
					{
						ochered_value->A = malloc (sizeof(double));
						ochered_value->B = malloc (sizeof(double));
						fscanf (input, "%lf", &ochered_value->A[0]);
						fscanf (input, "%lf", &ochered_value->B[0]);
					}
					break;
			}
			ochered_main (&ocherednyara1, ochered_value);
		}
		free (ochered_value);
		fclose (input);
		while ((ochered_value = del_ochered(&ocherednyara1)) != NULL) 
		{
			switch (ochered_value->working_mode) 
			{
			case 'v':
				switch (ochered_value->c) {
					case '+':
						result = malloc (ochered_value->size*sizeof(double));
						for (int i=0; i < ochered_value->size; i++)
						{ 
						result[i] = ochered_value->A[i] + ochered_value->B[i];
						}
						ochered_value->result_value = result;
						break;
					case '-':
						for (int i=0; i < ochered_value->size; i++) 
						{
						result[i] = ochered_value->A[i] - ochered_value->B[i];
						}
						ochered_value->result_value = result;
						break;
					case '*':
						result_value = 0;
						for (int i=0; i < ochered_value->size; i++) 
						{
							result_value += ochered_value->A[i] * ochered_value->B[i];
						}
						ochered_value->result = result_value;
						break;
				}
				break;
			case 'n':
				switch (ochered_value->c) {
					case '+': 
						ochered_value->result = ochered_value->A[0] + ochered_value->B[0];
						break;
					case '-': 
						ochered_value->result = ochered_value->A[0] - ochered_value->B[0];
						break;
					case '*': 
						ochered_value->result = ochered_value->A[0] * ochered_value->B[0];
						break;
					case '/': 
						ochered_value->result = ochered_value->A[0] / ochered_value->B[0];
						break;
					case '^': 
						d=ochered_value->A[0];
						for (int i=1;i<ochered_value->B[0];i++) 
						{
							d = d * ochered_value->A[0];
						}
						ochered_value->result = d;
						break;
					case '!':
						d=1;
						if (ochered_value->A[0] >= 0) 
						{
							for (int i=0;i<ochered_value->A[0];i++) 
							{
								d=d*(i+1);
							}
						}
						ochered_value->result = d;
						break;
				}
			}
			ochered_main (&ocherednyara2, ochered_value);
		}
		if ((output = fopen(outputFName, "a")) == NULL) 
		{
			output = fopen(outputFName, "w");
		}
		while ((ochered_value = del_ochered(&ocherednyara2)) != NULL) 
		{
			switch (ochered_value->working_mode) 
			{
			case 'v':
				fprintf (output, "( ");
				for (int i=0; i<ochered_value->size;i++) 
				{
					if (i==ochered_value->size-1) 
					{
						fprintf (output, "%lf", ochered_value->A[i]);
					} 
					else
					{ 
						fprintf (output, "%lf ", ochered_value->A[i]);
					}
				}
				fprintf (output, " ) %c ( ", ochered_value->c);
				for (int i=0;i<ochered_value->size;i++) 
				{
					if (i==ochered_value->size-1) {
						fprintf (output, "%lf", ochered_value->B[i]);
					} 
					else 
					{
						fprintf (output, "%lf ", ochered_value->B[i]);
					}
				}
				if (ochered_value->c=='+' || ochered_value->c=='-') {
					fprintf (output, " ) = ( ");

					for (int i = 0; i < ochered_value->size; i++) 
					{
						if (i==ochered_value->size-1) 
						{
							fprintf (output, "%lf", ochered_value->result_value[i]);
						} 
						else
						{ 
							fprintf (output, "%lf ", ochered_value->result_value[i]);
						}
					}
					fprintf (output, " )\n");
				} 
				else
				{ 
					fprintf (output, " ) = %lf\n", ochered_value->result);
				}
				break;
			case 'n':
				if (ochered_value->c=='!') {
					fprintf (output, "%lf! = %lf\n", *ochered_value->A, ochered_value->result);
				} 
				else
				{ 
					fprintf (output, "%lf %c %lf = %lf\n", *ochered_value->A, ochered_value->c, *ochered_value->B, ochered_value->result);
				}
				break;
			}
		}
		fclose (output);
		puts ("\nЧтобы продолжить программу введите любой символ\nДля выхода введите 1\n");
		scanf (" %c", &h);
	}
	while (h!='1');
	return 0;
}
