// Lab11.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <vector>

#pragma region transport
class transport {
protected:			 
	char departure[30];
	int departure_time;
	char arrival[30];
	int arrival_time;
public:
	transport(){};
	transport(char* _departure, int _departure_time, char* _arrival, int _arrival_time)
	: departure_time(_departure_time), arrival_time(_arrival_time)
	{
		strncpy (departure, _departure, 30);
		strncpy (arrival, _arrival, 30);
	};
	void set_departure(char* _departure, int _departure_time){
		strncpy (departure, _departure, 30);
		departure_time = _departure_time;
	}
	void set_arrival(char* _arrival, int _arrival_time){
		strncpy (arrival, _arrival, 30);
		arrival_time = _arrival_time;
	}
	char* get_departure () { return departure;}
	int get_departure_time () { return departure_time; }
	char* get_arrival () { return arrival;}
	int get_arrival_time () { return arrival_time; }
	virtual void print() { 
		printf ("Departure %s : %d", departure, departure_time);
		printf ("Arrival %s : %d", arrival, arrival_time);	
	}
};

 #pragma endregion 
#pragma region bus
class bus : public transport {
private: 
	int seats;
	int cost;
public:
	bus(){};
	bus(char* _departure, int _departure_time, char* _arrival, int _arrival_time, int _seats, int _cost)
		: transport(_departure, _departure_time, _arrival, _arrival_time), seats(_seats), cost(_cost) 
	{};
	void set_seats (int _seats) { seats = _seats; }
	int get_seats (int _seats) { return seats; }
	void set_cost (int _cost) { cost = _cost; }
	int get_cost (int _cost) { return cost; }
	int total_cost () { return seats*cost; }
	void print() {
		transport::print();
		printf ("There is %d seats with total cost %d", seats, this->total_cost());
	}
	friend std::ostream& operator<< (std::ostream &os, bus& _bus);
	friend std::istream& operator>> (std::istream &is, bus& _bus);
};

std::ostream& operator<< (std::ostream &os, bus& _bus)
{
	os << _bus.departure << " : " << _bus.departure_time << "\n"
		<< _bus.arrival << " : " << _bus.arrival_time << "\n"
		<< "There is "<< _bus.seats << " seats with total cost " << _bus.total_cost() << std::endl;
	return os;
}
std::istream& operator>> (std::istream &is, bus& _bus)
{
	is >> _bus.departure >> _bus.departure_time
		>> _bus.arrival >> _bus.arrival_time
		>> _bus.seats >> _bus.cost;
	return is;
}

#pragma endregion
#pragma region taxi

class taxi: public transport {
private:
	int seats;
	int cost;
public:
	taxi(){};
	taxi (char* _departure, int _departure_time, char* _arrival, int _arrival_time, int _seats, int _cost)
		: transport(_departure, _departure_time, _arrival, _arrival_time), seats(_seats), cost(_cost) 
	{};
	void set_seats (int _seats) { seats = _seats; }
	int get_seats (int _seats) { return seats; }
	void set_cost (int _cost) { cost = _cost; }
	int get_cost (int _cost) { return cost; }
	int total_cost() { return seats * cost; }
	void print() {
		transport::print();
		printf ("There is %d seats with cost %d", seats, total_cost());
	}	
	friend std::ostream& operator<< (std::ostream &os, taxi& _taxi);
	friend std::istream& operator>> (std::istream &is, taxi& _taxi);
};

std::ostream& operator<< (std::ostream &os, taxi& _taxi)
{
		os << _taxi.departure << " : " << _taxi.departure_time << "\n"
		<< _taxi.arrival << " : " << _taxi.arrival_time << "\n"
		<< "There is "<< _taxi.seats << " seats with cost " << _taxi.cost 
		<< " and total "<< _taxi.total_cost() << std::endl << std::endl;
	return os;
}

std::istream& operator>> (std::istream &is, taxi& _taxi)
{
	is >> _taxi.departure >> _taxi.departure_time
		>> _taxi.arrival >> _taxi.arrival_time
		>> _taxi.seats >> _taxi.cost;
	return is;
}

#pragma endregion

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	ifstream infile;
	infile.open("f1.txt", ios_base::in);
	if (!infile) {
		cout << "Can't open file f1.txt" << endl;
		system("pause");
		return -1;
	}
	vector<bus> Buses;
	int buses_count = 0;
	while (infile.good()) {
		bus buf;
		infile >> buf;
		Buses.push_back(buf);
		cout << Buses[buses_count++];
	}
	infile.close();

	infile.open("f2.txt", ios_base::in);
	if (!infile) {
		cout << "Can't open file f2.txt" << endl;
		system("pause");
		return -1;
	}
	vector<taxi> Taxis;
	int taxis_count = 0;
	while (infile.good()) {
		taxi buf;
		infile >> buf;
		Taxis.push_back(buf);
		cout << Taxis[taxis_count++];
	}
	infile.close();
	
	system ("pause");
	return 0;
}

