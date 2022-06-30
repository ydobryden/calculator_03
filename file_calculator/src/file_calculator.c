/*
 ============================================================================
 Name        : file_calculator.c
 Author      : Добрыдень Яна
 License     : GNU GPL
 Description : Обратная польская нотация
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char inputFName[259], outputFName[259];
char inp[256];
char h, L, val_sg;
double d, result_value, numer;
double *result;
FILE *input,*output;

typedef struct polsk {
	int size;
	char working_mode;
	double result;
	double *A,*B;

	char c;
	
	double *result_value;
	
	struct polsk *next;
} 
polsk;

typedef struct ocheredn {
	polsk *hd_val;
	polsk *main_val;
} 
ocheredn;

void init_ochered (ocheredn *O) {
	O->hd_val = NULL;
	O->main_val = NULL;
}

void edit_ochered (ocheredn *O, polsk *data_info) {
	polsk* tmp_information = malloc (sizeof(polsk));
	tmp_information->c = data_info->c;
	tmp_information->A = data_info->A;
	tmp_information->B = data_info->B;

	tmp_information->working_mode = data_info->working_mode;
	tmp_information->result_value = data_info->result_value;

	tmp_information->size = data_info->size;
	tmp_information->next = NULL;

	tmp_information->result = data_info->result;

	if (O->main_val != NULL) 
	{
		O->main_val->next = tmp_information;
	}
	O->main_val = tmp_information;
	if (O->hd_val == NULL) 
	{
		O->hd_val = tmp_information;
	}
}

polsk* del_ochered (ocheredn *O) {
	polsk *result_out;
	result_out = malloc (sizeof (polsk));
	if (O->hd_val == NULL) {
		result_out = NULL;
		return result_out;
	}
	polsk *tmp_information = O->hd_val;
	result_out->c = tmp_information->c;

	result_out->result_value = tmp_information->result_value;

	result_out->result = tmp_information->result;

	result_out->A = tmp_information->A;
	result_out->B = tmp_information->B;

	result_out->size = tmp_information->size;

	result_out->working_mode = tmp_information->working_mode;

	O->hd_val = O->hd_val->next;
	if (O->hd_val == NULL) 
	{
		O->main_val = NULL;
	}
	free (tmp_information);
	return result_out;
}

typedef struct node 
{
	double x;
	struct node *next;
} 
node;

typedef struct stack 
{
	node *hd_val;
} 
stack;

void init_stack (stack *O) 
{
	O->hd_val = NULL;
}

void push (stack *O, double numer) 
{
	node * tmp_information = malloc (sizeof (node));
	tmp_information->x = numer;
	tmp_information->next = O->hd_val;
	O->hd_val = tmp_information;
}

double pop (stack *O) 
{
	node *tmp_information;
	tmp_information = malloc (sizeof (node));
	tmp_information = O->hd_val;
	O->hd_val = O->hd_val->next;
	return tmp_information->x;
}



int main(int argc, char *argv[]) 
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);


	polsk *ochered_value;
	ocheredn pol_cal_1, pol_cal_2;
	stack s;
	
	do {
		printf("P - вычисление обратной польской нотацией, K - классический режим");
		scanf (" %c", &L);
		printf ("Введите название файла, из которого будут взяты данные (формат'.txt'): ");
		scanf ("%s", inputFName);
		printf ("Введите название файла, в который будут записаны результаты вычислений (формат'.txt'): ");
		scanf ("%s", outputFName);


		input = fopen (inputFName, "r");
		switch (L) 
		{
		case 'P':
			init_stack (&s);

			if ((output = fopen(outputFName, "a")) == NULL) 
			{
				output = fopen(outputFName, "w");
			}

			while (feof (input)==0) 
			{
				fscanf (input, "%s", inp);
				if (atof (inp)==0) {
					val_sg=inp[0];
					switch (val_sg) {
						case '-':
							push (&s, pop (&s)-pop(&s));
							break;
						case '+':
							push (&s, pop (&s)+pop(&s));
							break;
						case '*':
							push (&s, pop (&s)*pop(&s));
							break;
						case '/':
							push (&s, pop (&s)/pop(&s));
							break;
						case '!':
							d=1;
							numer=pop (&s);
							if (numer>=0) 
							{
								for (int i=0;i<numer;i++) 
								{
									d=d*(i+1);
								}
							}
							push (&s, d);
							break;
						case '^':
							numer=pop (&s);
							d=numer;
							for (int i=1;i<pop(&s);i++) 
							{
								d=d*numer;
							}
							push(&s,d);
							break;
						case '=':
							fprintf (output, "%lf\n", pop (&s));
							break;
					}
				} 
				else 
				{
					numer=atof(inp);
					push(&s, numer);
				}
			}
			fclose (input);
			break;
		case 'K':
			init_ochered (&pol_cal_1);
			init_ochered (&pol_cal_2);

			ochered_value=malloc (sizeof (polsk));
			while (feof(input) == 0) 
			{
				fscanf (input, " %c %c", &ochered_value->c, &ochered_value->working_mode);
				switch (ochered_value->working_mode) 
				{ 
					case 'v':
						fscanf (input, "%i", &ochered_value->size); 
						ochered_value->A =malloc (ochered_value->size*sizeof(double)); 
						ochered_value->B =malloc (ochered_value->size*sizeof(double));

						for (int i=0;i<ochered_value->size;i++)
						{ 
							fscanf (input, "%lf", &ochered_value->A[i]);
						}
						for (int i=0;i<ochered_value->size;i++)
						{ 
							fscanf (input, "%lf", &ochered_value->B[i]);
						}
						break;
					case 'n':
						ochered_value->size=1;
						if (ochered_value->c=='!') 
						{
							ochered_value->A=malloc (sizeof (double));
							fscanf (input, "%lf", &ochered_value->A[0]);
							ochered_value->B=NULL;
						}
						else 
						{
							ochered_value->A=malloc (sizeof(double));
							ochered_value->B=malloc (sizeof(double));
							fscanf (input, "%lf", &ochered_value->A[0]);
							fscanf (input, "%lf", &ochered_value->B[0]);
						}
						break;
				}
				edit_ochered (&pol_cal_1, ochered_value);
			}
			free (ochered_value);
			fclose (input);
			while ((ochered_value=del_ochered(&pol_cal_1)) != NULL) 
			{
				switch (ochered_value->working_mode) 
				{
				case 'v':
					switch (ochered_value->c) {
					case '+':
						result=malloc (ochered_value->size*sizeof(double));
						for (int i=0;i<ochered_value->size;i++)
						{ 
							result[i]=ochered_value->A[i]+ochered_value->B[i];
						}
						ochered_value->result_value = result;
						break;
					case '-':
						for (int i=0;i<ochered_value->size;i++)
						{ 
							result[i]=ochered_value->A[i]-ochered_value->B[i];
						}
						ochered_value->result_value=result;
						break;
					case '*':
						result_value=0;
						for (int i=0;i<ochered_value->size;i++) 
						{
							result_value+=ochered_value->A[i]*ochered_value->B[i];
						}
						ochered_value->result = result_value;
						break;
					}
					break;
				case 'n':
					switch (ochered_value->c) 
					{
					case '+': 
						ochered_value->result=ochered_value->A[0]+ochered_value->B[0];
						break;
					case '-': 
						ochered_value->result=ochered_value->A[0]-ochered_value->B[0];
						break;
					case '*': 
						ochered_value->result=ochered_value->A[0]*ochered_value->B[0];
						break;
					case '/': 
						ochered_value->result=ochered_value->A[0]/ochered_value->B[0];
						break;
					case '^':
						d = ochered_value->A[0]; 
						for (int i=1;i<ochered_value->B[0];i++) 
						{
							d=d*ochered_value->A[0];
						}
						ochered_value->result=d;
						break;
					case '!': 
						d=1; 
						if(ochered_value->A[0]>=0) 
						{
							for(int i=0;i<ochered_value->A[0];i++) 
							{
								d=d*(i+1);
							}
						}
						ochered_value->result = d;
						break;
					}
					break;
				}
				edit_ochered (&pol_cal_2, ochered_value);
			}
			if((output=fopen(outputFName, "a"))==NULL) 
			{
				output=fopen(outputFName, "w");
			}
			while ((ochered_value=del_ochered(&pol_cal_2)) != NULL) 
			{
				switch (ochered_value->working_mode) 
				{
				case 'v':
					fprintf (output, "( ");
					for (int i=0;i<ochered_value->size;i++) 
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
					for (int i=0; i<ochered_value->size; i++) 
					{
						if (i==ochered_value->size-1) 
						{
							fprintf (output, "%lf", ochered_value->B[i]);
						} 
						else
						{
							fprintf (output, "%lf ", ochered_value->B[i]);
						}
					}

					if (ochered_value->c=='+' || ochered_value->c=='-') 
					{
						fprintf (output, " ) = ( ");
						for (int i=0;i<ochered_value->size;i++) 
						{
							if(i==ochered_value->size-1) 
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
					if (ochered_value->c == '!') 
					{
						fprintf (output, "%lf! = %lf\n", *ochered_value->A, ochered_value->result);
					} 
					else
					{ 
						fprintf (output, "%lf %c %lf = %lf\n", *ochered_value->A, ochered_value->c, *ochered_value->B, ochered_value->result);
					}
					break;
				}
			}
			break;
		}

		fclose (output);
		puts ("\nЧтобы продолжить программу введите любой символ\nДля выхода введите 1\n");
		scanf (" %c", &h);
	}
	while (h!='1');
	return 0;
}
