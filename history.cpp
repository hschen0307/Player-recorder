#include"history.h"
//Hsuan-chih,Chen
//This file defines all functions of the history and list class



//defult constructor
history::history()
{
	event = NULL;
	previous = NULL;
	next = NULL;	
}



//destructor
history::~history()
{
	if(event)
		delete [] event;
}



//copy constructor
history::history(const history & to_add)
{
	if(event)
		delete [] event;
	event = new char[strlen(to_add.event)+1];
    strcpy(event,to_add.event);	
}



//go to the next history
//output:: history pointer by reference
history*& history::go_next()
{
	return next;
}



//go to the previous history
//output:: history pointer by reference
history*& history::go_previous()
{
	return previous;
}



//for coping deeply from another history object 
//input::another history object by reference 
//output:: history object by reference
history& history::operator = (const history & to_add)
{	
    if(this == &to_add) //self check	
        return *this;	//same object directly return
    if(event)			//delete self data member first
        delete [] event;
    event = new char[strlen(to_add.event)+1];	//copy new information 
    strcpy(event,to_add.event);
    return *this;				//return self pointer by dereferecing
}



//for outputing all history's information 
//input:: ostream object by reference, history object by reference 
//output:: ostream object by reference 
ostream& operator << (ostream& print, const history& to_print)
{
	if(to_print.event)
		print<< "event : "<< to_print.event <<endl;
	return print;
}



//delete the event in a history
//output::history object by reference
history& history::operator --()
{
	if(event)
		delete [] event;
	return *this;
}



//check whether a event is in a history or not
//input:: event description
//output:: true, in the history. false, not in the history 
bool history::operator == (char* history_event) const
{	
	if(strcmp(event,history_event)==0)
		return true;
	else
		return false;
}



//read a history information in a history object
//input::a array 
void history::read_a_history(char temp_array[])
{
	if(event)
		delete [] event;
	event = new char[strlen(temp_array)+1];
	strcpy(event, temp_array);
}



//same as  operator =
//input::another history object by reference 
//output:: history object by reference
void history::copy_a_history(const history & to_add)
{
	event = new char[strlen(to_add.event)];
	strcpy(event,to_add.event);
}



//same as operator <<
void history::display()const
{
	cout<< "event : "<< event<<endl;
}



//constructor
list::list()
{
	head = NULL;  
}



//destructor
list::~list()
{
	delete_list(head);
}



//delete all histories in a list
//input::a head pointer of a list by reference 
void list::delete_list(history*& head)
{
	if(!head)
		return;
	delete_list(head->go_next());
	delete head;
	head = NULL;
}



//for outputing all list's information 
//input:: ostream object by reference, list object by reference 
//output:: ostream object by reference 
ostream& operator << (ostream& print,const list& to_print)
{
	print<<"History"<<endl;
	print<<"------------------------"<<endl;
	history* current = to_print.head;
	while(current)
	{
		print<<(*current);	//call history operator << for displaying
		current = current->go_next();
	}
	print<<"-------------------------"<<endl;
    return print;
}



//for inserting a history in a list
//input:: history object by reference 
//output:: list object by reference
list& list::operator += (const history & to_add)
{
        history* temp = new history; //create a new history, use temp points it frist.
		(*temp) = to_add; //call the history operator for copying 
		if(!head)	//head == NULL
		{
			head = temp;
			head->go_next() = NULL;
			head->go_previous() = NULL;
			tail = temp;	//set the tail
		}
		else
		{
        	temp->go_next() = head;     //insert the temp to the beginning of a chain.
			head->go_previous()=temp; //set the previous pointer to point temp
        	head = temp;            //let the temp be the head of that chain.
			head->go_previous() = NULL;
		}
		return *this;
}



//for deleting the event in a history of a list
//input:: event's description  
//output:: list object by reference
list& list::operator -= (char* history_event)
{
	history* current = head;
	while(current)
	{
		if((*current)==history_event) //call history operator == for comparing
		{
			--(*current); //call history operator -- for deleting
		}
		current = current->go_next();
	}
	return *this; //return self pointer by dereferecing
}

