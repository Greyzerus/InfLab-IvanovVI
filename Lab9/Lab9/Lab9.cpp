// Lab9.cpp: определ€ет точку входа дл€ консольного приложени€.
//
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

/*
* ¬ывести инфоормацию о транспорте, который
* отправл€етс€ из указанного пункта в указанный интервал времени
*
* ¬ывести начальные и конечные пункты дл€ которых
* врем€ в пути больше введенного с клавиатуры.
*/



class transport {
public:
	void set_departure(char* _departure)
	{
		strncpy(departure, _departure, 30);
	}
	void set_arrival(char* _arrival)
	{
		strncpy(arrival, _arrival, 30);
	}
	void set_departure_time(int _departure_time)
	{
		departure_time = _departure_time;
	}
	void set_arrival_time(int _arrival_time)
	{
		arrival_time = _arrival_time;
	}
	void set_number_of_seats(int _number_of_seats)
	{
		number_of_seats = _number_of_seats;
	}

	char* get_departure()
	{
		return departure;
	}
	char* get_arrival()
	{
		return arrival;
	}
	int get_departure_time()
	{
		return departure_time;
	}
	int get_arrival_time()
	{
		return arrival_time;
	}
	int get_number_of_seats()
	{
		return number_of_seats;
	}

	void print()
	{
		printf("%s : %d \n%s : %d\nSeats: %d\n\n"
			, departure
			, departure_time
			, arrival
			, arrival_time
			, number_of_seats);
	}
	int intravel_time()
	{
		return arrival_time - departure_time;
	}
	int all_seats_cost(int cost)
	{
		return cost*number_of_seats;
	}

private:
	char departure[30];
	char arrival[30];
	int departure_time;
	int arrival_time;
	int number_of_seats;
};

int _tmain(int argc, _TCHAR* argv[])
{
	FILE* infile = fopen("f1.txt", "r");
	if (infile == NULL) {
		printf("Can't open file f1.txt\n");
		system("pause");
		return -1;
	}
	int races_count = 0;
	char* departure = new char[20];
	char* arrival = new char[20];
	int arrival_time, departure_time, number_of_seats;
	while (fscanf(infile, "%s %d %s %d %d", departure, &departure_time, arrival, &arrival_time, &number_of_seats) != EOF)
		races_count++;
	rewind(infile);
	transport* transports = new transport[races_count];
	int i = 0;
	for (int i = 0; i<races_count; i++)
	{
		fscanf(infile, "%s %d %s %d %d", departure, &departure_time, arrival, &arrival_time, &number_of_seats);
		transports[i].set_departure(departure);
		transports[i].set_arrival(arrival);
		transports[i].set_departure_time(departure_time);
		transports[i].set_arrival_time(arrival_time);
		transports[i].set_number_of_seats(number_of_seats);
	}
	fclose(infile);
	for (int i = 0; i < races_count; i++)
	{
		transports[i].print();
	}

	printf("Enter departure station departure and arrival time: ");
	char string_buf[30];
	int int1_buf, int2_buf;
	scanf("%s %d %d", string_buf, &int1_buf, &int2_buf);
	for (int i = 0; i < races_count; i++)
	{
		if (!strcmp(transports[i].get_departure(), string_buf) 
			&& transports[i].get_departure_time() >= int1_buf
			&& transports[i].get_arrival_time() <= int2_buf)
		{
			transports[i].print();
		}
	}

	printf("Enter arrival time: ");
	scanf("%d", &int1_buf);
	for (int i = 0; i < races_count; i++)
	{
		if (transports[i].intravel_time() > int1_buf)
		{
			printf("%s %s\n", transports[i].get_arrival(), transports[i].get_departure());
		}
	}

	system("pause");
	return 0;
}
