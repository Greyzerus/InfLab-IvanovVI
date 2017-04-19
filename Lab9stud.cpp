// Lab9.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
//#include "student.hpp"


class student {
public:
	student ();
	student (char* name, int year, int* grades, size_t grades_number = 0);
	student (student &other);
	~student ();
	student& operator= (student& other);

	size_t get_namesize () { return name_size; };
	size_t get_grades_number () { return grades_number; };
	int get_year () { return year; };

	void set_name (char* i_name) {
		name_size = strlen(i_name)+1;
		name = new char[name_size];
		strncpy (name, i_name, name_size);
	};
	void set_grades (int* i_grades, int i_grades_number) {
	  grades_number = i_grades_number;
	  grades = new int[grades_number];
	  memcpy (grades, i_grades, grades_number * sizeof(int));
	};
	void set_year (int i_year) {year = i_year;};

	const float grades_mean () const;
	void print() const;
private:
	char* name;
	size_t name_size;
	int year; 
	int* grades;
	size_t grades_number;
};

student::student () 
	: name(nullptr), grades(nullptr){}

student::student (char* i_name, int i_year, int* i_grades, size_t i_grades_number) 
	: year (i_year), grades_number (i_grades_number) {
	name_size = strlen(i_name)+1;
	name = new char[name_size];
	strncpy (name, i_name, name_size);
	grades = new int[grades_number];
	memcpy (grades, i_grades, grades_number * sizeof(int));
}

student::student (student &other) 
	: name_size(other.name_size), year(other.year), grades_number(other.grades_number)
{
	name = new char[name_size];
	strncpy (name, other.name, name_size);
	grades = new int[grades_number];
	memcpy (grades, other.grades, grades_number * sizeof(int));
}

student& student::operator= (student &other) 
{
	name_size = other.name_size;
	year = other.year;
	grades_number = other.grades_number;
	name = new char[name_size];
	strncpy (name, other.name, name_size);
	grades = new int[grades_number];
	memcpy (grades, other.grades, grades_number*sizeof(int));
	return *this;
}

student::~student () {
	delete[] name;
	delete[] grades;
}


const float student::grades_mean () const {
	if (grades_number == 0)
		return 0;
	int sum = 0;
	for (int iter = 0; iter < grades_number; iter++) {
		sum+= grades[iter];
	}
	return sum*1.0/grades_number;
}

void student::print() const{
	printf ("Name: %s, year: %d, grades: ", name, year);
	for (int i=0; i<grades_number; i++)
		printf ("%d ", grades[i]);
	putchar('\n');
}


int _tmain(int argc, _TCHAR* argv[])
{
	FILE* infile = fopen ("students.txt", "r");
	if (!infile) {
		printf ("Can't open file f1.txt");
		system("pause");
		return -1;
	}
	char* name = new char[20];
	int year;
	int grades[3];
	student* students;
	size_t entries_num =0;
	while (fscanf (infile, "%s %d %d %d %d", name, &year, &grades[0], &grades[1], &grades[2]) != EOF)
		entries_num++;
	students = new student[entries_num];
	rewind (infile);
	int iter = 0;
	while (fscanf (infile, "%s %d %d %d %d", name, &year, grades, grades+1, grades+2) != EOF) {
		/*students[iter++] = student(name, year, grades, 3);*/
		students[iter].set_name(name);
		students[iter].set_year(year);
		students[iter++].set_grades(grades, 3);
	}
	for (int iter=0; iter<entries_num; iter++)
		students[iter].print();
	system("pause");
	return 0;
}
														    
