// Lab9.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>


class transport {
	void set_departure (char* _departure);
	void set_arrival (char* _arrival);
	void set_departure_time (int _departure_time);
	void set_arrival_time (int _arrival_time);
	void set_number_of_seats (int _number_of_seats);

	void print();
	void intravel_time ();
	int all_seats_cost (int cost);
private:
	char* departure;
	char* arrival;
	int departure_time;
	int arrival_time;
	int number_of_seats;
};

int _tmain(int argc, _TCHAR* argv[])
{
	FILE* infile = fopen ("transports.txt", "r");
	if (!infile) {
		printf ("Can't open file f1.txt");
		system("pause");
		return -1;
	}
	int races_count = 0;
	char* departure = new char[20];
	char* arrival = new char[20];
	int arrival_time, departure_time, number_of_seats;
	while (fscanf (infile, "%s %d %s %d %d", departure, departure_time, arrival, arrival_time, number_of_seats) != EOF )
		races_count++;
	transport* transports = new transport[races_count];
	int i=0;
	for (int i=0; i<races_count; i++)
	{
		fscanf (infile, "%s %d %s %d %d", departure, departure_time, arrival, arrival_time, number_of_seats);
		transports[i].set_departure(departure);
		transports[i].set_arrival(arrival);
		transports[i].set_departure_time(departure_time);
		transports[i].set_arrival_time(arrival_time);
		transports[i].set_number_of_seats(number_of_seats);
	}
	/*вывести инф. о транспортах отправл€ющихс€ из указанного места в указанный интервал времени*/
	/*вывести пункты отправлени€ и прибыти€ дл€ каоторых врем€ в пути больше введенного с клавы*/
	system("pause");
	return 0;
}
														    
