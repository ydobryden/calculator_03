/*
 ============================================================================
 Name        : calculator.c
 Author      : Добрыдень Яна
 License     : GNU GPL
 Description : Переработала работу с файлами
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char inputFName[259], outputFName[259];
char h;
//*A и *B - первый и второй вектор
double a,b, d, f, *A, *B;
char c, r;
int size;
float *res;
double resultVec; //задаем переменную для хранения промежуточного результата действий с векторами
//Добавляем файловый ввод-вывод
FILE *input, *output;
int main(int argc, char *argv[])
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	do
	{
		printf ("Введите название файла, из которого будут взяты данные (формат'.txt'): ");
		scanf ("%s", inputFName);
		printf ("Введите название файла, в который будут записаны результаты вычислений (формат'.txt'): ");
		scanf ("%s", outputFName);
        //Открываем файл для чтения и собираем данные
		input = fopen (inputFName, "r");
		if ((output=fopen(outputFName, "a"))==NULL)
		   {
			//Если файл для записи отсутствует - создаем новый
			output = fopen(outputFName, "w");
		   }
		while (feof(input) == 0)
		{
            //Режим работы калькулятора
			fscanf (input, " %c %c", &c, &r);
			switch (r)
			{
                case 'v':
                {
                    fscanf (input, "%i", &size);
                    switch (c){
                        case '+':
                            A=malloc(size*sizeof(double)); 
                            B=malloc(size*sizeof(double));
                            fprintf (output, "(");
                            for (int i=0; i<size; i++) 
                            {
                                fscanf (input, "%lf", &A[i]);
                                fprintf (output, "%lf ", A[i]);
                            }
                            fprintf (output, ") + (");
                            for (int i=0; i<size; i++)
                            {
                                fscanf (input, "%lf", &B[i]);
                                fprintf (output, "%lf ", B[i]);
                            }
                            fprintf (output, ") = (");
                            for (int i=0; i<size; i++)
                            {
                                fprintf (output, "%lf ", A[i]+B[i]);
                            }
                            fprintf (output, ")\n");
                            free (A);
                            free (B);
                            break;
                        case '-':
                            A=malloc(size*sizeof(double));
                            B=malloc(size*sizeof(double));
                            fprintf (output, "(");
                            for (int i = 0; i<size; i++) //считываем вектор
                            {
                                fscanf (input, "%lf", &A[i]);
                                fprintf (output, "%lf ", A[i]);
                            }
                            fprintf (output, ") - (");
                            for (int i = 0; i<size; i++)
                            {
                                fscanf (input, "%lf", &B[i]);
                                fprintf (output, "%lf ", B[i]);
                            }
                            fprintf (output, ") = (");
                            for (int i=0;i<size;i++)
                            {
                                fprintf (output, "%lf ", A[i]-B[i]);
                            }
                            fprintf (output, ")\n");
                            free (A);
                            free (B);
                            break;
                        case '*':
                            // умножение векторов
                            A=malloc(size*sizeof(double));
                            B=malloc(size*sizeof(double));
                            fprintf (output, "(");
                            for (int i=0;i<size;i++)
                            {
                                fscanf (input, "%lf", &A[i]);
                                fprintf (output, "%lf ", A[i]);
                            }
                            fprintf (output, ") * (");
                            for (int i=0;i<size;i++)
                            {
                                fscanf (input, "%lf", &B[i]);
                                fprintf (output, "%lf ", B[i]);
                            }
                            fprintf (output, ") = ");
                            
                            for (int i=0;i<size;i++)
                            {
                                resultVec += A[i] * B[i];
                            }
                            fprintf (output, "%lf\n", resultVec);
                            resultVec = 0;
                            free (A);
                            free (B);
                            break;
                    }
                    break;
                }
                case 'n':
                {
                    switch (c) 
                    {
                        case '+': 
                            fscanf (input, "%lg %lg", &a, &b);
                            fprintf (output, "%lg + %lg = %lg\n", a,b,a+b);
                            break;
                        case '-': 
                            fscanf (input, "%lg %lg", &a, &b);
                            fprintf (output, "%lg - %lg = %lg\n", a,b,a-b);
                            break;
                        case '*': 
                            fscanf (input, "%lg %lg", &a, &b);
                            fprintf (output, "%lg * %lg = %lg\n", a,b,a*b);
                            break;
                        case '/': 
                            fscanf (input, "%lg %lg", &a, &b);
                            fprintf (output, "%lg / %lg = %lg\n", a,b,a/b);
                            break;
                        case '^': 
                        //Возведение в степень
                            fscanf (input, "%lg %lg", &a, &b);
                            d=a; 
                            for (int i=1;i<b;i++)
                            {
                                d=d*a;
                            }
                            fprintf (output, "%lg ^ %lg = %lg\n", a, b, d);
                            break;
                        case '!': 
                        //Расчет факториала
                            d=1; 
                            fscanf (input, "%lg", &a);
                            if (a>= 0) 
                            {
                                for (int i=0;i<a;i++)
                                {
                                    d=d*(i+1);
                                }
                                fprintf (output, "%lg! = %lg\n", a,d);
                            }
                            break;
                    }
                    break;
			    }
			}
		}
		fclose (input);
		fclose (output);
		puts ("\nЧтобы продолжить программу нажмите 1\nДля выхода нажмите любой другой символ\n");
		scanf (" %c", &h);
	}
	while (h!='1');
	return 0;
}
