// Lab2.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <conio.h>
#include <clocale>
//#include <time.h>
#include <cstdlib>


int** SetC (int*n, int*m)
{
	int** c;
	FILE* f2=fopen("f2.txt", "r");
	if (f2==NULL) 
	{
		puts ("Файл не существует");
		getch();
		exit(1);
	}
	fscanf (f2, "%d %d", n, m);
	c=new int*[*n];
	for (int i=0; i<*n; i++)
	{
		c[i]=new int[*m];
		for (int j=0; j<*m; j++)
			fscanf (f2, "%d",&c[i][j]);
	}
	return (c);
}
void PrintC (int** c, int n, int m)
{
	for (int i=0; i<n; i++)
	{
		putch ('\n');
		for (int j=0; j<m; j++)
			printf ("%d ", c[i][j]);
	}
}
int MaxInStringC (int** c,int n,int m,int* imax,int* jmax)
{
	printf ("\nВыберите строку: ");
	scanf ("%d", imax);
	int max=c[--*imax][*jmax=0]; // -- это сдвиг строки
	for (int j=1; j<m; j++)
		if (c[*imax][*jmax]<c[*imax][j])
			max=c[*imax][*jmax=j];
	 return (max);
}
void ReplaceHigher (int** c, int n, int m, int max)
{
	for (int i=0; i<n; i++)
		for (int j=0; j<m; j++)
			if (c[i][j]>max) c[i][j]=max;
}
int MaxInC (int** c, int n, int m)
{
	int max=c[0][0];
	for (int i=0; i<n; i++)
		for (int j=0; j<m; j++)
			if (c[i][j]>max)
				max=c[i][j];
	return max;
}
//Поменять местами строки с наибольшим и наименьшим количеством максимальных местами
void SwapStringsWithMostMax (int** c, int n, int m)
{	int nmax=1, max=c[0][0], cmax=1, maxsimstr=0, maxi=0;
	int nmin=1, min=c[0][0], cmin=1, minsimstr=0, mini=0;
 char* _t;

	for (int i=0; i<n; i++)
	{	 //Считаем мах в строке, или ищем новые
		for (int j = i ? 0 : 1 ; j<n; j++) // если i != 0, то j=0
		{
			if (c[i][j]>=max){
				if (c[i][j]==max)
					cmax++;
				else
					nmax=0, nmin=1, cmax=1;
			}
		}
		/* обрабатываем максимум */
		if (cmax=>nmax)
		{
			if (cmax==nmax)
			maxsimstr++;
	
		}
		else
		{
			nmax=cmax;
			maxsimstr=0;
			maxi=i;
		}
		else if (cmax<=nmin)
		{
			if (cmax==nmin)
				minsimstr++;
			else 
			{
				nmin = cmax;
				minsimstr=0;
				mini = i;
			}
		}
		/*обрабатываем минимум */	
	}
 if (nmin != nmax && maxi != mini && !maxsimstr && !minsimstr )
 {
	_t=c[mini];
        c[mini]=c[maxi];
	 c[maxi]=_t;
		 PrintC(c, n, m);
 }
 else puts ("Строку вывести невозможно ");
}






	/*
{
	int Max=MaxInC (c, n, m), iMax=0, iMin=0, MaxofMax=0, MinofMax=m, MaxCounter, MaxErrorTag=0, MinErrorTag=0, *t;
	for (int i=0; i<n; i++)
	{
		MaxCounter=0;
		for (int j=0; j<m; j++)
			if (c[i][j]==Max)
				MaxCounter++;
		if (MaxCounter>=MaxofMax)
		{
			if (MaxCounter>MaxofMax)
			{
				MaxofMax=MaxCounter;
				iMax=n;
				MaxErrorTag=0;
			}
			else 
				MaxErrorTag++; //Если уже выбрана строка с таким же количеством максимальных
							   //Выбрать одну из них по условию мы не можем => ошибка
		}
		if (MaxCounter<=MinofMax)
		{
			if (MaxCounter<MinofMax)
			{
				MinofMax=MaxCounter;
				iMin=n;
				MinErrorTag=0;
			}
			else 
				MinErrorTag++;
		}
	}
	if ((MaxofMax==MinofMax)|| MaxErrorTag || MinErrorTag)
		printf ("\nВывести строку невозможно");
	else 
	{
		t=c[iMax];
		c[iMax]=c[iMin];
		c[iMin]=t;
		PrintC;
	}	
}
*/


int main()
{
setlocale (LC_ALL, "");
int **c, n, m, imax, jmax, max;
c=SetC (&n, &m);
PrintC (c, n, m);
max=MaxInStringC (c, n, m, &imax, &jmax);
printf ("c[%d][%d] = %d - max", imax+1, jmax+1, max);
ReplaceHigher (c, n, m, max);
PrintC (c, n, m);
SwapStringsWithMostMax (c, n, m);
PrintC (c, n, m);
getch();
}
