// Lab12.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<locale>

using namespace std;


class item
{
protected:
	string name;
	float weight;
	float volume;
	float cost;
	int count;

#pragma region item_constructors
public:
	item(){};
	item(string _name, float _weight, float _volume, float _cost, int _count)
		: name (_name), weight(_weight), volume(_volume), cost(_cost), count(_count) {};
	item(const item& other)
		: name (other.name), weight(other.weight), volume(other.volume), cost(other.cost), count(other.count) {};
#pragma endregion
#pragma region item_methods

public:
	void set_weight (float val) {weight = val;}
	float get_weight () const {return weight;}
	void set_volume (float val) {volume = val;}
	float get_volume () const {return volume;}
	void set_cost (float val) {cost = val;}
	float get_cost () const {return cost;}
	void set_count (int val) {count = val;}
	int get_count () const {return count;}
	void set_name (string _name) {name = _name;}
	string get_name () const {return name;}

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
	friend ostream& operator<< (ostream& os, item& _item)
	{
		os << "Item : "<< _item.name 
			<< "\ncost : " << _item.cost 
			<< "\nweight : " << _item.weight 
			<< "\nvolume : "<< _item.volume 
			<< "\ncost : " << _item.cost 
			<<"\ncount : " << _item.count << endl;
		return os;
	}
	friend istream& operator>> (istream& is, item& _item)
	{
		is >> _item.name >> _item.weight >> _item.volume >> _item.cost >> _item.count;
		return is;
	}
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
	ammo (const ammo &other) : caliber(other.get_caliber()), ap (other.get_ap()),
		item(other.get_item())
	{}
	#pragma endregion
	#pragma region ammo_methods
public:
	void set_caliber (int val) {caliber= val;}
	int get_caliber () const  {return caliber;}
	void set_ap (float val) {ap = val;}
	float get_ap () const  {return ap;}
	item get_item () const  { return item(get_name(), 
									get_weight(),
									get_volume(),
									get_cost(),
									get_count()); }
	float penetrate (float armour_value){ return armour_value*ap;}
	#pragma endregion
	friend ostream& operator<< (ostream& os, ammo& _ammo)
	{
		os << "ammo : " << _ammo.name 
			<<"\ncost : " << _ammo.cost 
			<< "\nweight : " << _ammo.weight 
			<< "\nvolume : " << _ammo.volume 
			<< "\ncost : " << _ammo.cost 
			<<"\ncount : " << _ammo.count 
			<<"\ncaliber : " << _ammo.caliber
			<<"\nap : " << _ammo.ap << endl;
		return os;
	}
	friend istream& operator>> (istream& is, ammo& _ammo)
	{
		is >> _ammo.name >> _ammo.weight >> _ammo.volume >> _ammo.cost >> _ammo.count >> _ammo.caliber >> _ammo.ap;
		return is;
	}
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
	weapon (const weapon &other) : dmg (other.get_dmg()), spd(other.get_spd()), dps(other.get_dps()), item(other.get_item()) {}
	#pragma endregion
	#pragma region weapon_methods
public:
	void set_dmg (int _dmg) {dmg = _dmg; dps = spd * dmg;}
	int get_dmg () const  {return dmg;}
	void set_spd (int _spd) {spd = _spd; dps = spd * dmg;}
	int get_spd () const  {return spd;}
	int get_dps () const  {return dps;}
	//void set_item (item _item) {item (&_item);}
	item get_item () const {return item(get_name(), get_weight(), get_volume(), get_cost(), get_count());}
	float damage_dealt (float seconds = 0, int armour = 0, ammo* _ammo = nullptr) 
	{
		float damage;
		if (seconds == 0)
			damage = dmg - (_ammo ? _ammo->penetrate(armour) : armour);
		else
			damage = (dps - (_ammo ? _ammo->penetrate(armour) : armour) * spd) * seconds;
		return damage>0 ? damage : 0;
	}
	
	#pragma endregion
	friend ostream& operator<< (ostream& os, weapon& _weapon)
	{
		os << "weapon : "<< _weapon.name 
			<<"\ncost : " << _weapon.cost 
			<< "\nweight : " << _weapon.weight 
			<< "\nvolume : " << _weapon.volume 
			<< "\ncost : " << _weapon.cost 
			<<"\ncount : " << _weapon.count
			<<"\ndamage : " <<_weapon.dmg 
			<<"\nattack speed : " <<_weapon.spd
			<<" attacks per second\ndps : " <<_weapon.dps
			<< endl;
		return os;
	}
	friend istream& operator>> (istream& is, weapon& _weapon)
	{
		is >> _weapon.name >> _weapon.weight >> _weapon.volume >> _weapon.cost >> _weapon.count >> _weapon.dmg >> _weapon.spd;
		_weapon.dps = _weapon.dmg / _weapon.spd;
		return is;
	}
};
float total_weight (vector<item>& items)
{
	float weight = 0;
	for (vector<item>::iterator iter = items.begin(); iter != items.end() ; iter++)
		weight+=iter->get_weight();
	return weight;						 
}
int best_damage_per_price_weapons_index (vector<weapon>& items)
{
	int damage = items[0].get_dps();
	float cost = items[0].get_cost();
	int index = 0;
	int i=0;
	for (vector<weapon>::iterator iter = items.begin(); iter != items.end() ; iter++, i++)
	{
		if (iter->get_dps() / iter->get_cost() > damage / cost
				|| (iter->get_dps() / iter->get_cost() == damage / cost && iter->get_dps() > damage))
		{
			damage = iter->get_dps();
			cost = iter->get_cost();
			index = i;
		}
	} 
	return index;
}

 
int _tmain(int argc, _TCHAR* argv[])
{ 
	setlocale (LC_ALL, "");
	ifstream infile;
	infile.open ("items.txt");
	if (!infile)
	{
		cout << "Не удалось открыть файл items.txt. " << endl;
		system ("pause");
		return -1;
	}
	string type;
	vector<item> items;
	vector<weapon> weapons;
	vector<ammo> ammos;	
	while (infile.good())
	{
	
		infile >> type;
		if (type == "ammo")
			{
				ammo temp_ammo;
				infile >> temp_ammo;
				ammos.push_back(temp_ammo);
				items.push_back(static_cast <item>(temp_ammo));
				continue;
			} 
		if (type == "weapon")
			{
				weapon temp_weapon;
				infile >> temp_weapon;
				weapons.push_back(temp_weapon);
				items.push_back(static_cast <item>(temp_weapon));  
				continue;
			} 
		item temp_item;
		infile >> temp_item;
		items.push_back(temp_item);
	}

	int i = 0;
	cout << "All items: \n" << endl;
	for (vector<item>::iterator iter = items.begin(); iter != items.end() ; iter++, i++) 
		cout << i << ": "<< *iter;

	i = 0;
	cout << "\n\nRead weapons: \n" << endl;
	for (vector<weapon>::iterator iter = weapons.begin(); iter != weapons.end() ; iter++, i++) 
		cout << i << ": "<< *iter;

	i = 0;
	cout << "\n\nRead ammo: \n" << endl;
	for (vector<ammo>::iterator iter = ammos.begin(); iter != ammos.end() ; iter++, i++) 
		cout << i << ": "<< *iter;	

	cout << "\n\nTotal items weight is :" << total_weight (items) << endl;
	cout <<	"Weapon with the best dps/price coefficient is " << weapons [best_damage_per_price_weapons_index(weapons)] << endl;
	cout << "Enter weapon number, ammo number armour value and time :" << flush;
	int wnum, anum;
	float armour, seconds;
	cin >> wnum >> anum >> armour;
	cout << "\nEach hit will deal " << weapons[wnum].damage_dealt(0,armour, &ammos[anum]) 
		<< " damage.\nTotal dps is " << weapons[wnum].damage_dealt(seconds ,armour, &ammos[anum]) <<endl;
	return 0;
}


/**/
/*Lazyness
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
	friend ostream& operator<< (ostream& os, weapon& _weapon)
	{
		os << "weapon : "<< _ranged.name "\ncost : " _ranged.cost << "\nweight : " << _ranged.weight << "\nvolume : " << _item.volume << "\ncost : " << _ranged.cost <<"\ncount : " << _ranged.count << 
			<<"\ndamage : " <<_weapon.dmg 
			<<"\nattack speed : " <<_weapon.spd
			<<" attacks per second\ndps : " <<_weapon.dps <<endl;
		return os;
	}
	friend istream& operator>> (istream& is, ranged& _ranged)
	{
		is >> _ranged.name >> _ranged.weight >> _ranged.volume >> _ranged.cost >> _ranged.count >> _weapon.dmg >> _weapon.spd;
		_weapon.dps = _weapon.dmg / _weapon.spd;
		return is;
	}
};
*/



