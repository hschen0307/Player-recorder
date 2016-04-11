#include"weapon.h"
//Hsuan-chih,Chen
//This file defines all functions of the weapon and table class



//default constructor
weapon::weapon()
{
	name = NULL;
	bullet = 0;	
}



//destructor
weapon::~weapon()
{
	if(name)
		delete [] name;
}



//copy constructor
weapon::weapon(const weapon & to_add)
{
	if(name)
		delete [] name;
	name = new char[strlen(to_add.name)+1];
    strcpy(name,to_add.name);
    bullet = to_add.bullet;	
}



//go to the next weapon
//output:: weapon pointer by reference
weapon*& weapon:: go_next()
{
	return next;
}



//for coping deeply from another weapon object 
//input::another weapon object by reference 
//output:: history object by reference
weapon& weapon::operator = (const weapon & to_add)
{	
    if(this == &to_add)	//self check
        return *this;
    if(name)
        delete [] name;	//delete self data first
    name = new char[strlen(to_add.name)+1];
    strcpy(name,to_add.name);
    bullet = to_add.bullet;
    return *this;	//return self pointer by dereferecing
}



//for outputing all weapon's information 
//input:: ostream object by reference, weapon object by reference 
//output:: ostream object by reference
ostream& operator << (ostream& print, const weapon& to_print)
{
	print<< "name : "<< to_print.name <<endl;
	print<< "bullet: " << to_print.bullet<<endl;
	return print;
}



//minus one bullet in a weapon
//output::weapon object by reference
weapon& weapon::operator -=(int num)
{
	if(bullet > 0)
	{
		bullet = bullet - num;
		cout<<"\nFire!"<<endl;
	}
	else
	{
		cout<<"\nThis weapon has no bullet now."<<endl;
	}
	return *this;
}



//check whether a weapon is in the table or not
//input:: weapon name
//output:: true, the weapon exist. false, otherwise
bool weapon::operator == (char* weapon_name) const
{	
	if(strcmp(name,weapon_name)==0)
		return true;
	else
		return false;
}



//read a weapon information in a weapon object
//input::a array, bullets number	
void weapon::read_a_weapon(char temp_array[], int num)
{
	if(name)
		delete [] name;
	name = new char[strlen(temp_array)+1];
	strcpy(name, temp_array);
	bullet = num;
}



//same as  operator =
//input::another weapon object by reference 
//output::weapon object by reference
void weapon::copy_a_weapon(const weapon & to_add)
{
	name = new char[strlen(to_add.name)];
	strcpy(name,to_add.name);
	bullet = to_add.bullet;
}



//get the weapon's name for hashing
//output:: char* name
char* weapon::key_value()
{
	return name;
}



//constructor
//input::hash table's size
//initialize the hash table size and make all head of chain to be NULL.
table::table(int size)
{
      hash_table = NULL;      
      hash_table_size = size;   //set the hash table size from input arument(size).
      hash_table = new weapon* [hash_table_size];        //create the hash table by using the size
      for(int i=0;i<hash_table_size;++i)                //use for loop to set every head of chains to be NULL.
      {
      	*(hash_table+i)=NULL;
      } 
}



//destructor
//deallocate all dynamic memory.
table::~table()
{
	delete_table(); //delete all chains in hash table
	delete [] hash_table;	//delete the table(array)
}



//delete all chains in a hash table
void table::delete_table()
{
	if(!hash_table)
	{	
		return;
	}
	for(int i=0;i<hash_table_size;++i)	//loop for accessing each chain 
	{
		if(hash_table+i)	//check whether each head pointer of a hash table is not NULL
		{
			weapon* current = *(hash_table+i);
			while(current)		//delete a chain
			{
				weapon* temp = NULL;
				temp = current;
				current = current->go_next();
				delete temp;
			}
		}
	}
}



//hashing a keyword to be a number
//input:: char* a keyword
//output:: number
int table::hash_function(char * keyword)const
{
    int counter = 0;    //for counting the sum
    int len = 0;        //for storing the number of all letters of a keyword.
    if(!keyword)
    {
        return -1;
    }
    len = strlen(keyword);      //get the the number of all letters of a keyword
    for(int i=0; i<len;++i)     //for counting the sum of ASCII codes.
    {
        counter += *(keyword+i);
    }
    counter = counter % hash_table_size;        //hash the sum to the hash table.
    return counter;                             //return a position number of the hash table
}



//for outputing all information in a table.
//input:: ostream object by reference, table object by reference 
//output:: ostream object by reference
ostream& operator << (ostream& print,const table& to_print)
{
	print<<"Arsenal"<<endl;
	print<<"----------------------"<<endl;
    for(int i=0; i< to_print.hash_table_size;++i)	//access each chain
    {
		if(to_print.hash_table[i])
		{	
			weapon* current = to_print.hash_table[i];
			while(current)
			{
				print<<(*current);
				current = current->go_next();
			}
		}
    }
	print<<"------------------------"<<endl;
    return print;
}



//This function is for inserting a weapon to the hash table.
//input::weapon object
//output::table object by reference
table& table::operator += (const weapon & to_add)
{
		int  position = 0;
        weapon* temp = new weapon;      //create a new weapon, use temp points it frist.
		(*temp) = to_add;
        position = hash_function(temp->key_value());    //pass a keyword to the hash function and then get the table position back.
        temp->go_next() = hash_table[position];     //insert the temp to the beginning of a chain.
        hash_table[position] = temp;            //let the temp be the head of that chain.
        return *this;                               //success, return 1.
}



//for minus a bullet from a weapon of a table
//input:: weapon's name
//output:: table object by reference
table& table::operator -= (char* weapon_name)
{
	int position=0;
	position = hash_function(weapon_name);
	weapon* current = *(hash_table+position);
	while(current)
	{
		if((*current)==weapon_name)
		{
			(*current) -= 1;
		}
		current = current->go_next();
	}
	return *this;
}














