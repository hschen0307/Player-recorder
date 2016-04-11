#include"node.h"
//Hsuan-chih,Chen
//This file defines all functions of the node class



//default constructor 
node::node()
{
	name = NULL;
	number = 0;
}



//destructor
node::~node()
{
	if(name)
		delete name;
}



//get the left child
//output:: node pointer by reference
node*& node::go_left()
{
	return left;
}



//get the right child
//output:: node pointer by reference
node*& node::go_right()
{
	return right;
}
//get the number in a node
//output::number
int node::get_num()
{
	return number;
}



//for inserting a weapon to the hash table of a node.
//input::weapon object
//output::node object by reference
node& node::operator += (const weapon & to_add)
{
	arsenal += to_add; //call table += operator
	return *this;
}



//for inserting a history to the doubly linked list of a node.
//input::history object
//output::node object by reference
node& node::operator += (const history & to_add)
{
	records += to_add;	//call list += operator 
	return *this;
}



//for minus a bullet from a weapon of a table of a node.
//input:: weapon's name
//output:: node object by reference
node& node::operator -= (char* weapon_name)
{
	arsenal -= weapon_name; //call list -= operator
	return *this;
}



//for outputing all information in a node
//input:: ostream object by reference, node object by reference 
//output:: ostream object by reference
ostream& operator << (ostream& print,const node& to_print)
{
	print<<"Player Number: "<<to_print.number<<endl;
	print<<"Player Name : "<<to_print.name<<endl;
	print<< to_print.arsenal;
	print<< to_print.records;
	return print;
}



//read a player's name in a node object
//input::a array
void node::read_name(char temp[])
{
	name = new char[strlen(temp)+1];
	strcpy(name, temp);
}



//read a number in a node object
//input::number
void node::change_num(int num)
{
	number = num; 
}



//display a node's name, player number, arsenal 
void node::display()
{
	cout<<"Number : " << number<<endl;
	cout<<"name : " << name<<endl;
	cout << arsenal;
}


