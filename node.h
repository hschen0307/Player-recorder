#include "weapon.h"
#include "history.h"
#include <iostream>
#include <cstring>
using namespace std;
//Hsuan-chih,Chen
//This file declares all functions of the node class



//node class
//the class manages all functions in a node.
class node
{
	public:
		node(); //constructor		
		~node();//destructor
		node*& go_left();//get the left child
		node*& go_right();//get the right child
		int get_num(); //get the number in data member	
		node& operator += (const weapon & to_add);
		node& operator += (const history & to_add);
		friend ostream& operator << (ostream& print,const node& to_print);
		node& operator -= (char* weapon_name);
		void change_num(int num);//get the number in data member
		void display();//display a node's name, player number, arsenal 
		void read_name(char temp[]);//read a player's name in a node object
	private:
		char *name;//store player's name
		int number;//store 
		node *left;//store the left child's address 
		node *right;//store the right child's address
		table arsenal;//a table obection for weapons
		list records;//a list object for histories
};
