// Lab10.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

class student {
public:
	student();
	student(char* name, int year, int* grades, size_t grades_number = 0);
	student(student &other);
	~student();
	student& operator= (student& other);

	int get_year() { return year; }
	char* get_name() { return name; }

	void set_name(char* i_name) {
		strncpy(name, i_name, 30);
	}
	void set_grades(int* i_grades) {
		memcpy(grades, i_grades, 3 * sizeof(int));
	}
	void set_year(int i_year) { year = i_year; }
	const float grades_mean()
	{
		return (grades[0] + grades[1] + grades[2]) / 3;
	}
	void print()
	{
		printf("%s %d : %d %d %d\n", name, year
			, grades[0], grades[1], grades[2]);
	}

private:
	char name[30];
	int year;
	int grades[3];
};
class school {
public:
	school();
	school(char* name, int year, int* grades, size_t grades_number = 0);
	school(school &other);
	~school();
	school& operator= (school& other);

	int get_year() { return year; }
	char* get_name() { return name; }

	void set_name(char* i_name) {
		strncpy(name, i_name, 30);
	}
	void set_grades(int* i_grades) {
		memcpy(grades, i_grades, 3 * sizeof(int));
	}
	void set_year(int i_year) { year = i_year; }
	const float grades_mean()
	{
		return (grades[0] + grades[1] + grades[2]) / 3;
	}
	void print()
	{
		printf("%s %d : %d %d %d\n", name, year
			, grades[0], grades[1], grades[2]);
	}

private:
	char name[30];
	int year;
	int grades[3];
};

void print_graduated(school _school, student _student)
{
	if (!strcmp(_school.get_name(), _student.get_name())
		&& _school.get_year() == _student.get_year())
	{
		printf("Graduated : ");
		_school.print();
		_student.print();
	}
}


int main()
{
	char name[30];
	int year;
	int grades[3];
	int students_count = 0;
	int school_count = 0;

	FILE* infile = fopen("f2.txt", "r");
	if (infile == NULL) {
		printf("Can't open file f1.txt\n");
		system("pause");
		return -1;
	}
	while (fscanf(infile, "%s %d %d %d %d", name, &year, grades, grades+1, grades+2) != EOF)
		students_count++;
	rewind(infile);
	student* students= new student[students_count];
	for (int i = 0; i < students_count; i++)
	{
		fscanf(infile, "%s %d %d %d %d", name, &year, grades, grades + 1, grades + 2);
		students[i].set_name(name);
		students[i].set_year(year);
		students[i].set_grades(grades);
	}
	fclose(infile);
	for (int i = 0; i < students_count; i++)
	{
		students[i].print();
	}

	infile = fopen("f3.txt", "r");
	if (infile == NULL) {
		printf("Can't open file f1.txt\n");
		system("pause");
		return -1;
	}
	while (fscanf(infile, "%s %d %d %d %d", name, &year, grades, grades + 1, grades + 2) != EOF)
		school_count++;
	rewind(infile);
	school* schools = new school[school_count];
	for (int i = 0; i < school_count; i++)
	{
		fscanf(infile, "%s %d %d %d %d", name, &year, grades, grades + 1, grades + 2);
		schools[i].set_name(name);
		schools[i].set_year(year);
		schools[i].set_grades(grades);
	}
	fclose(infile);
	for (int i = 0; i < school_count; i++)
	{
		schools[i].print();
	}

	for (int i=0; i<students_count; i++)
		for (int j=0; j<school_count; j++)
			print_graduated(schools[j], students[i]);

	system("pause");
    return 0;
}

