/*
 ============================================================================
 Name        : calculator.c
 Author      : Добрыдень Яна
 License     : GNU GPL
 Description : Программа калькулятор поддерживает работу с вещественными числами,
 обработку ошибок в арифметических выражениях.
 Поддерживаемые операции - сложение, вычитание, умножение, деление, факториал, возведение в степень
 и работа с векторами. При работе с векторами возможно сложение, вычитание и их скалярное произведение.
 (+ - * / ! ^ v).
 После выполнения одной операции программа выводит запрос на повторение работы, при положительном
 ответе она запускается сначала.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//Добавляем файловый ввод-вывод
FILE *input, *output;
//Добавляем переменные для ввода имени файлов
char inputFName[250], outputFName[250];
int main(int argc, char *argv[])
{
	//Присваиваем переменной r временное значение, для работы цикла while
	char r;
	do
	{
		printf ("Введите название файла, из которого будут взяты данные (формат'.txt'): ");
		scanf ("%s", inputFName);
		printf ("Введите название файла, в который будут записаны результаты вычислений (формат'.txt'): ");
		scanf ("%s", outputFName);
		//Открываем файл для чтения и собираем данные
		input = fopen(inputFName, "r");
		if ((output=fopen(outputFName, "a"))==NULL)
		   {
			//Если файл для записи отсутствует - создаем новый
			output = fopen(outputFName, "w");
		   }
		while (feof(input)==0)
		{
			// Проходим через весь входящий файл
			//*A и *B - первый и второй вектор
			double a,b, d, f, *A, *B;
			char c;
			int size;
			float *res;
			//Выводим подсказку
			fprintf (output, "Введите операцию (+ - * / ! ^ v):");
		    //Вводим операцию
		    fscanf (input, "\n%c", &c);
		    //Создаем блок функций, которые будут выполняться в зависимости от введенной операции
		    switch (c)
		    {
			    //Блок сложения
			    case '+':
				    fprintf (output, "Введите первое число:");
				    fscanf (input, " %lg", &a);
				    fprintf (output, "Введите второе число:");
				    fscanf (input, " %lg", &b);
				    fprintf (output, "%lg + %lg = %lg", a, b, a+b);
				    break;
			    //Блок вычитания
			    case '-':
				    fprintf (output, "Введите первое число:");
				    fscanf (input, " %lg", &a);
				    fprintf (output, "Введите второе число:");
				    fscanf (input, " %lg", &b);
				    fprintf (output, "%lg - %lg = %lg", a, b, a-b);
 		    	    break;
 		    	//Блок умножения
			    case '*':
				    fprintf (output, "Введите первое число:");
				    fscanf (input, " %lg", &a);
				    fprintf (output, "Введите второе число:");
				    fscanf (input, " %lg", &b);
				    fprintf (output, "%lg * %lg = %lg", a, b, a*b);
				    break;
			    //Блок деления
			    case '/':
				    fprintf (output, "Введите первое число:");
				    fscanf (input, "%lg", &a);
				    fprintf (output, "Введите второе число:");
				    fscanf (input, "%lg", &b);
				    if (b==0) fprintf (output, "Ошибка");
				    else fprintf (output, "%lg / %lg = %lg", a, b, a/b);
				    break;
			    //Блок факториала
			    case '!':
				    f=1;
				    fscanf (input, "%lf", &a);
				    if (a>0)
				    {
			    	    for (int i=1; i<=a; i++)
			    	    {
			        	    f=f*i;
			    	    }
			    	    fprintf(output, "\n%.0lf! = %.0lf \n", f,a);
				    }
				    else if (a<0)
				    {
			    	    fprintf (output, "Ошибка");
				    }
				    else fprintf (output, "0! = 1");
				    break;
			    //Блок возведения в степень реализован с помощью библиотеки <math.h>
			    case '^':
				    fprintf (output, "Введите число:");
				    fscanf (input, "%lf", &a);
				    fprintf (output, "Введите степень:");
				    fscanf (input, "%lf",&b);
				    d = pow (a, b);
				    fprintf(output, "%lf ^ %lf = %.1f", a, b, d);
				    break;
			    //Блок работы с векторами
			    case 'v':
				    fprintf (output, "Введите размер векторов: ");
				    fscanf (input, "%i", &size);
				    A = malloc(size*sizeof(int));
				    B = malloc(size*sizeof(int));
				    res = malloc(size*sizeof(int));
				    fprintf (output, "Введите координаты первого вектора: ");
				    for(int i=0;i<size;i++) fscanf(input, "%lf",&A[i]);
				    fprintf (output, "Введите координаты второго вектора: ");
				    for(int i=0;i<size;i++) fscanf(input, "%lf",&B[i]);
				    fprintf (output, "Введите операцию (+ - *): ");
				    fscanf(input, " %c",&c);
				    if (c == '+')
				    {
					     fprintf(output, "(");
					     for(int i=0;i<size;i++) fprintf(output, "%lf ",A[i]);
					     fprintf(output, ") + (");
					     for(int i=0;i<size;i++) fprintf(output, "%lf ",B[i]);
					     fprintf(output, ") = (");
					     for(int i=0;i<size;i++) fprintf(output, "%lf ",A[i]+B[i]);
					     fprintf(output, ")\n");
				    }
				    else if (c == '-')
				    {
					    fprintf(output, "(");
					    for(int i=0;i<size;i++) fprintf(output, "%lf ",A[i]);
					    fprintf(output, ") - (");
					    for(int i=0;i<size;i++) fprintf(output, "%lf ",B[i]);
					    fprintf(output, ") = (");
					    for(int i=0;i<size;i++) fprintf(output, "%lf ",A[i]-B[i]);
					    fprintf(output, ")\n");
				    }
				    else if (c == '*')
				    {
					    fprintf(output, "(");
					    for(int i=0;i<size;i++) fprintf(output, "%lf ",A[i]*B[i]);
					    fprintf(output, ") * (");
					    for(int i=0;i<size;i++) fprintf(output, "%lf ",B[i]);
					    fprintf(output, ") = (");
					    for(int i=0;i<size;i++) fprintf(output, "%lf ",A[i]*B[i]);
					    fprintf(output, ")\n");
				    }
				    else fprintf(output, "Такой операции нет, попробуйте снова");
				    break;
				free(A);
				free(B);
				free(res);
			    default:
				    fprintf (output, "Ошибка");
		    }
		}
		fclose(input);
		fclose(output);
		fprintf (output, "\nЧтобы продолжить программу нажмите 1\nДля выхода нажмите любой другой символ\n");
		fscanf (input, " %c", &r);
	}
	while (r == '1');
	return 0;
}
