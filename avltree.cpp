#include "avltree.h"
//Hsuan-Chih, Chen
//This file defines all function of the avltree class



//defult constructor
avltree::avltree()
{ 
	root = NULL;
	find = NULL;
	read_file(); //read file from weapon.txt
}



//destructor
avltree::~avltree()
{
	delete_tree(root);
}



//delete all nodes in the tree recursively
//input:: root node passed by reference
void avltree::delete_tree(node*& root)
{
	if(!root)
		return;
	delete_tree(root->go_left());
	delete_tree(root->go_right());
	delete root;
	root = NULL;
}



//read file to test whether all my data structures work or not
void avltree::read_file()
{
	int bullet_num = 0;	//store the total bullet number. just for use conveniently 
	char temp_array[30];	//store the array data temporarily.
	int weapons = 0;		//store the total number of weapons 
	int total = 6;			//store total players
	int count = 0;			//store how many weapons are already inserted
	int history_num = 0;	//store the total number of history
	weapon temp;			//store information in a weapon object 
	history temp_his;		//store information in a history object
	ifstream fileIn;	//for geting information from .txt file.
	fileIn.open("weapon.txt");	//open the .txt file
	if(fileIn)
	{
		for(int i =0; i<total; ++i)		//loop for storing every player
		{
			count = 0;				
			node* player = new node;	//create a player node, get name, and store name in it.
	    	fileIn.get(temp_array, 30,':');
        	fileIn.ignore(100,':');
			player->read_name(temp_array);	
			fileIn>>weapons;			//get the total number of weapons first 
			fileIn.ignore(100,':');
			while(count < weapons)	//loop for storing every weapons of one player
			{
				fileIn.get(temp_array, 30,':');
				fileIn.ignore(100,':');
				fileIn>>bullet_num;
				fileIn.ignore(100,':');
				temp.read_a_weapon(temp_array, bullet_num);	//read all information into a temp weapon object
				(*player) += temp;		//using operator overloading to add the weapon to a player's arsenal
				++count;	
			}
			fileIn>>history_num;	//get the total number of histories
			fileIn.ignore(100,':');
			for(int j=0; j<history_num;++j)	//loop for storing every history of one player
			{
				if(j==history_num-1)		//final information of a player. jump to next new line 
				{
					fileIn.get(temp_array, 30,'\n');
					fileIn.ignore(100,'\n');	
				}
				else
				{
					fileIn.get(temp_array, 30,':');
					fileIn.ignore(100,':');	
				}
				temp_his.read_a_history(temp_array);	//read all information into a temp weapon object
				(*player) += temp_his;
			} 
			insert(i,player);	//insert a player into the tree by 1,2,3,4,5...	
		}
	}
}



//calculate the height of the tree(subtrees)
//input::root node passed by value
//output::hieght of a tree 
int avltree::height(node * root)
{
	if(!root)
		return 0;
	return 1+max(height(root->go_left()),height(root->go_right()));
}



//calculate the factor of the current node
//input::current node
//output::factor number
int avltree::cal_factor(node * current)
{
	int left_height = height(current->go_left());
	int right_height = height(current->go_right());
	return(left_height - right_height);
}



//wraper function for inserting a player's information to the tree
//input:: int number, node pointer passed by reference
void avltree::insert(int num,node*& player)
{	
	root = insert_(root,num, player);	
}



//recursively insert function
//input:: data member root, int number, node pointer passed by reference. 
//output:: a pointer which is a new root address after rotation 
node* avltree::insert_(node*&root,int num, node*& player)
{
	if (!root)
	{
		root = player;	//directly set the root pointer to point to the player's address
		root->change_num(num);	//store the player's number
		root->go_left() = NULL;	
		root->go_right() = NULL;
		return root;
	}
	else if (num < root->get_num()) //traverse left
	{
		insert_(root->go_left(), num, player);
		root = balance(root);
	}
	else if (num >= root->get_num()) //traverse right
	{
		insert_(root->go_right(), num, player);
		root = balance(root);
	}
	return root;
}



//right-right rotation. ( if parent < parent's child < the child's child)
//input:a parent node pass by reference
//output:: a temp pointer ( new parent's address)
node* avltree::rr_rotation(node *&parent) 
{
	node *temp;	//set a temp
	temp = parent->go_right(); 	//use temp to hold parent's right child

	parent->go_right() = temp->go_left();	//set the right child's(temp's) left child tp be parent's right child
	temp->go_left() = parent;	//set original parent to be temp's left child
	return temp;	//return new parent's(temp's) address
}



//left-left rotation. ( if parent > parent's child > the child's child )
//input:a parent node pass by reference
//output:: a temp pointer ( new parent's address)
node* avltree::ll_rotation(node *&parent) 
{
	node *temp;	//set a temp
	temp = parent->go_left();	//use temp to hold parent's left child
	parent->go_left() = temp->go_right(); //set the left child's(temp's) right child to be parent's left child;
	temp->go_right() = parent; //set parent to be temp's right's child
	return temp; //return new parent's(temp's) address
}



//left-right rotation. ( parent > the child's child > parent's child)
//input:a parent node pass by reference
//output:: a pointer from ll_rotation ( new parent's address)
node* avltree::lr_rotation(node *& parent)
{
	node *temp;	
	temp = parent->go_left();	//set temp to be the parent's left child
	parent->go_left() = rr_rotation(temp); //call rr_rotation first for the rotation of the parent's left child 
	return ll_rotation(parent); //do ll_rotation for the parent
}



//right-left rotation. ( parent < the child's child < parent's child)
//input:a parent node pass by reference
//output:: a temp pointer ( new parent's address)
node *avltree::rl_rotation(node *& parent)
{
	node *temp;
	temp = parent->go_right();	//set temp to be the parent's right child
	parent->go_right() = ll_rotation(temp);//call ll_rotation first for the rotation of the parent's right child 	
	return rr_rotation(parent); //do ll_rotation for the parent
}



//check a current node's factor. if it is not -1,0,or 1, it will call certain rotation function to keep the tree balaced. 
//input::a current node pass by reference
//output::a pointer(the new current address)
node *avltree::balance(node *& current)
{
	int factor=0; //store the factor number of current 
	factor = cal_factor(current);	//get factor number from cal_factor
	if (factor > 1)	//left height > right height (subtrees)
	{
		if (cal_factor(current->go_left()) > 0) //check the parent's left child factor, so we can know we need to do ll or lr rotation
			current = ll_rotation(current);
		else
			current = lr_rotation(current);
	}
	else if (factor < -1)//left height < right height (subtrees)
	{
		if (cal_factor(current->go_right()) > 0) //check the current's right child factor, so we can know we need to do rl or rr rotation
			current = rl_rotation(current);	
		else
			current = rr_rotation(current);
	}
	return current; //return the new current address
}


//display tree graph for easily check whether the tree is balaced.
void avltree::display(node *current, int level) 
{

	if (current != NULL)
	{
		display(current->go_right(), level + 1);
		cout << endl;
		if (current == root)
		{
			cout << "Root -> ";
		}
		for (int i = 0; i < level && current != root; i++)
		{
			cout << "        ";
		}
		cout << current->get_num();
		display(current->go_left(), level + 1);
	}
}



//wraper function display inorderly
void avltree::display_in() 
{
	display_in(root);
}



//inorder diplay recursively
////input:: root
void avltree::display_in(node *root) 
{
	if (root == NULL)
		return;
	display_in(root->go_left());
	cout <<(*root);
	display_in(root->go_right());
}



//wraper function display inorderly
void avltree::display_pre() 
{
	display_pre(root);
	display(root,1);
}



//preorder diplay recursively
//input:: root
void avltree::display_pre(node *root) 
{
	if (root == NULL)
		return;
	cout<<(*root); 
	display_pre(root->go_left());
	display_pre(root->go_right());	
}



//find a player node adress by each player number
//input::player number
void avltree::find_player(int num)
{
	if(!find_player(root,num,find))
	{
		cout<<"There is no this player"<<endl; 
	}
}



//find the player by number, set the find point to point the node.
//input::root, number, find node by reference
int avltree::find_player(node* root, int num, node*& find)
{
	if(!root)
	{
		return 0;
	}
	if(num == root->get_num())
	{
		find = root;	//set the find node point to the root
		return 1;
	}
	else if(num < root->get_num())	//traverse
	{
		return find_player(root->go_left(), num, find);
	}
	else
	{
		return find_player(root->go_right(), num, find);
	}
}




//for testing whether -= operator of table and weapon class works
void avltree::test()
{
	char array[30];
	int numb = 0;
	char choice = '0';
	
		cout<<"testing the -= operator in the weapon class"<<endl;
		cout<<"type a player's number : ";
		cin>>numb; cin.ignore(100,'\n');
		find_player(numb);
		cout<<(*find);
	do{
		cout<<"choose a weapon(type name) : ";
		cin.get(array,30,'\n');	cin.ignore(100,'\n');	
		(*find) -= array;
		find->display();
		cout<<"continue to test it ? (y/n): ";
		cin>>choice; cin.ignore(100,'\n');
		}while(choice == 'y');
}


