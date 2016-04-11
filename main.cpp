#include "avltree.h"
//Hsuan-chih,Chen
//2015.8.4
//this file is for testing whether whole program works.



int main()
{
	avltree tree; //create an avltree object(loading file in tree constructor)
	tree.display_pre();	//display preorderly 
	cout<<"\n\n";
	tree.test();	//test the -= operator

	return 0;
}
