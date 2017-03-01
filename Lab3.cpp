// Lastdents3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <string.h>

#define GRADESNUMBER 3
#define FAMILYLENGTH 30

struct stud {
 char family [FAMILYLENGTH];
 int group;
 int grades [GRADESNUMBER];
};

void FillStud (stud* students)
{
	printf ("\nВведите группу, 3 оценки и фамилию: ");
		scanf ("%d", &((*students).group));
		for (int j=0; j<3; j++)
			scanf ("%d", &((*students).grades[j]));
		gets_s ((*students).family);
}

void PrintStud (stud students)
{
	putch ('\n');
		printf ("\nfamily = %s", students.family);;
		printf ("\ngroup = %d\ngrades:", students.group);
		for (int i=0; i<GRADESNUMBER; i++)
			printf ("%d ", students.grades[i]);
}

void MaxStudGroup (stud *students, stud** maxgroupstudent, int n)
{
	*maxgroupstudent=&(students[0]);
	for (int i=0; i<n; i++)
		if ((**maxgroupstudent).group < students[i].group)
			(*maxgroupstudent)=&(students[i]);
}

void SortStudByGroup (stud* students, int n)
{
	stud _swap;
	for (int i=0; i<n; i++)
		for (int j=i; j<n; j++)
			if ( (students[i].group)>(students[j].group) )
			{
				_swap=students[i];
				students[i]=students[j];
				students[j]=_swap;
			}
}

void SortStudByFamily (stud* students, int n)
{
	stud _swap;
	for (int i=0; i<n; i++)
		for (int j=i; j<n; j++)
			if ( strcmp (students[i].family, students[j].family) > 0 )
			{
				_swap=students[i];
				students[i]=students[j];
				students[j]=_swap;
			}
}


int _tmain(int argc, _TCHAR* argv[]) {
	setlocale (LC_ALL, "");
	int n;
	stud* students;	
	printf ("Введите количество студентов: ");
	scanf ("%d", &n);
	students = new stud[n];
	
	for (int i=0; i<n; i++)	
		FillStud (&(students[i]));			 


	for (int i=0; i<n; i++)
		PrintStud (students[i]);

	printf ("\n\n\t\t Сортируем студентов по группам");
	SortStudByGroup (students, n);
		for (int i=0; i<n; i++)
			PrintStud (students[i]);
	printf ("\n\n\t\t Сортируем студентов по фамилиям ");
	SortStudByFamily (students, n);
		for (int i=0; i<n; i++)
			PrintStud (students[i]);
	stud* maxgroupstudent=NULL;
	MaxStudGroup (students, &maxgroupstudent, n) ;
	printf ("\n\n\t\tСтудент из крайней группы:");
	PrintStud (*maxgroupstudent);
	_getch();
	return 0;
}

