// Lab12.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class item
{
private:
	string name;
	float weight;
	float volume;
	float cost;
	int count;

#pragma region item_constructors
public:

	item();
	item(string _name, float _weight, float _volume, float _cost, int _count)
		: name (_name), weight(_weight), volume(_volume), cost(_cost), count(_count) {};
	item(item& other)
		: name (other.name), weight(other.weight), volume(other.volume), cost(other.cost), count(other.count) {};
#pragma endregion
#pragma region item_methods

public:
	void set_weight (float val) {weight = val;}
	float get_weight () {return weight;}
	void set_volume (float val) {volume = val;}
	float get_volume () {return volume;}
	void set_cost (float val) {cost = val;}
	float get_cost () {return cost;}
	void set_count (int val) {count = val;}
	int get_count () {return count;}
	void set_name (string _name) {name = _name;}
	string get_name () {return name;}

	float get_cost_weight_ratio () {return cost/weight; }
	float get_total_cost () {return cost*count; }

	item& operator++ (int junk) {
		this->count --;
		return *this;
	}

	item& operator-- (int junk) {
		this->count --;
		return *this;
	}
#pragma endregion	
};
class ammo: public item
{
	int caliber;
	float ap; //armour penetraton coefficient ( 0.01 reduces 100 armour to 1)

	#pragma region ammo_constructors
public:
	ammo () : item() {}
	ammo (int _caliber, float _ap, item item_data)
		: caliber (_caliber), ap (_ap), item(item_data) {}
	ammo (ammo &other) : caliber(other.get_caliber()), ap (other.get_ap()),
		item(other.get_item())
	{}
	#pragma endregion
	#pragma region ammo_methods
public:
	void set_caliber (int val) {caliber= val;}
	int get_caliber () {return caliber;}
	void set_ap (float val) {ap = val;}
	float get_ap () {return ap;}
	item get_item () { return item(get_name(), 
									get_weight(),
									get_volume(),
									get_cost(),
									get_count()); }
	float reduced_armour (float armour_value){ return armour_value*ap;}
	#pragma endregion
};
class weapon : public item
{
	int dmg;  //damage
	float spd; //attacks per second
	float dps; //damage per second

	#pragma region weapon_constructors
public:
	weapon () : item() {}
	weapon (int _dmg, float _spd, item _item)
		: dmg (_dmg), spd(_spd), dps(_dmg*_spd), item(_item) {}
	weapon (weapon &other) : dmg (other.get_dmg()), spd(other.get_spd()), dps(other.get_dps()), item(other.get_item()) {}
	#pragma endregion
	#pragma region weapon_methods
public:
	void set_dmg (int _dmg) {dmg = _dmg; dps = spd * dmg;}
	int get_dmg () {return dmg;}
	void set_spd (int _spd) {spd = _spd; dps = spd * dmg;}
	int get_spd () {return spd;}
	int get_dps () {return dps;}
	//void set_item (item _item) {item (&_item);}
	item get_item () {return item(get_name(), get_weight(), get_volume(), get_cost(), get_count());}

	virtual float damage_dealt (float seconds, int armour = 0) 
	{
		float _dmg = dps * seconds - armour * spd;
		return _dmg>0 ? _dmg : 0;
	}
	
	#pragma endregion
};
class ranged : public weapon
{
	float range;
	ammo ammo_type;

	#pragma region ranged_constructors
public:
	ranged() : weapon(), ammo_type() {}
	ranged (ranged &other) : 
		range (other.get_range()), ammo_type (other.get_ammo_type()), weapon (other.get_weapon()) {}
	ranged(float _range, ammo &_ammo_type, weapon &_weapon) :
		range (_range), weapon (_weapon), ammo_type (_ammo_type){}
	#pragma endregion
	#pragma region ranged_methods
public:
		float get_range() {return range;}
		void set_range(float val) {range = val;}
		ammo get_ammo_type() {return ammo_type;}
		void set_ammo_type (ammo &new_ammo_type) { ammo_type = new_ammo_type;}
		weapon get_weapon() {return weapon(get_dmg(), get_spd(), get_item());};
public:
	bool is_in_range (float _range) {return range>_range;}
	float damage_dealt (float seconds , int armour = 0) 
	{
		float _dmg = get_dps() * seconds - ammo_type.reduced_armour(armour)*get_spd();
		return _dmg>0 ? _dmg : 0;
	}
	#pragma endregion
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

