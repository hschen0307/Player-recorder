#include "node.h"
#include <algorithm>
using namespace std;
//Hsuan-Chih, Chen
//This file declares all function of the avltree class
//avltree class
//This class manage all player objects in the tree data structure



class avltree
{
	public:
		avltree();	//defult constructor 
		~avltree();	//destructor
		void read_file();	//read my test file
		void delete_tree(node*& root);	//delete all node in a tree
 		int height(node* root);		//calculate height of a tree
		int cal_factor(node *current);	//calculate a factor of a node
		void insert(int num,node*&player);	//weaper insert a node(player) into the tree
		node* insert_(node*& root,int num, node*&player);//insert a node(player) into the tree recursively
		node *rr_rotation(node *&parent);	//right-right rotation
		node *ll_rotation(node *&parent);	//left-left rotation
		node *lr_rotation(node *&parent);	//left-right rotation
		node *rl_rotation(node *&parent);	//right-left rotation
		node *balance(node *&current);		//check the factor and do different rotation
		void display(node *ptr, int level);	
		void display_in();	//display(inorder) wraper
		void display_pre();	//display(preoreder) wraper
		void display_in(node* root); //recursively inorder display
		void display_pre(node* root);//recursively preoreder display
		void find_player(int num);
		int find_player(node* root, int num, node*& find);
		void test();
	private:
		node *root; //store the tree's root
		node *find;//store a current player		
};
