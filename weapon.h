#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <fstream>
using namespace std;
//Hsuan-Chih, Chen



//This file declares all functions of the weapon and hash table class
//weapon class
//this class manages all functions and operators of a weapon
class weapon
{
	public:
		weapon(); //constructor
		~weapon();//destructor
		weapon(const weapon & to_add);//copy constructor
		weapon*& go_next();//get next weapon
		weapon& operator = (const weapon & to_add); //copy a weapon
		friend ostream& operator << (ostream& print,const weapon& to_print); //print a weapon's information
		weapon& operator -=(int num); //minus a bullet from a weapon
		bool operator == (char* weapon_name) const; //check wether a weapon in the table or not
		void read_a_weapon(char temp_array[], int num ); //read a weapon information in a weapon object
		char* key_value(); //get a weapon's name for hashing 
		void copy_a_weapon(const weapon & to_add);//same as = operator		
		void display()const; //same as = operator

	protected:
		char* name;	//store weapon's name
		int bullet; //store the number of bullets
		weapon* next; //store next weapon address
};



//table class
//this class manages all functions and operators of a hash table
class table
{
	public:
		table(int size=7); //constructor
		~table();	//destructor
		void delete_table(); //delete all chains of a hash table
		table& operator += (const weapon & to_add);//insert a weapon to a table
		friend ostream& operator << (ostream& print,const table& to_print);	//print whole weapons in a table
		table& operator -= (char* weapon_name); //minus a bullet from a weapon
		int hash_function(char * keyword)const; //get a number from hashing a word
		void display()const;//same as << operator

	protected:
		weapon ** hash_table;//store a pointer to a dynamic table 
		int hash_table_size;//hash table size
};


