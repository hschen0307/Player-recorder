#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <fstream>
using namespace std;
//Hsuan-Chih, Chen
//This file declares all functions of the history and list class



//history class
//this class manages all functions and operators of history
class history
{
	public:
		history(); //constructor
		~history(); //destructor 
		history(const history & to_add); //copy constructor
		history*& go_next();	//get the next history
		history*& go_previous();	//get the previous history
		history& operator = (const history & to_add); //copy a history object 
		friend ostream& operator << (ostream& print,const history& to_print);//cout a history content
		history& operator --();//delete the event in a history
		bool operator == (char* history_event)const;//check whether a event is in a history or not
		void read_a_history(char temp_array[]);//read a event ina history 
		void copy_a_history(const history & to_add);//same as operator =		
		void display()const;//same as operator <<

	protected:
		char* event;	//store a event
		history* previous;	//store previous history address
		history* next;	//store next history address
};



//list class
//this class manages all functions and operators of doubly linked list
class list
{
	public:
		list();//constructor	
		~list();//destructor	
		void delete_list(history*& head);//delete all histories in a list	
		list& operator += (const history & to_add);//insert a history object in a list
		friend ostream& operator << (ostream& print,const list& to_print); //print all information(histories) in a list
		list& operator -= (char* history_name); //delete a event in a history of a list
		void display()const; //same as operator <<
	protected:
		history * head; //store the first history address
		history * tail;	//store the last history address
};
