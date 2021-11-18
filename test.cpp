#include"RB_Node.hpp"
#include"RB_Tree.hpp"
#include<iostream>


int main() {
	RB_Tree<int> test;
	test.insert(3);
	test.insert(1);
	test.insert(0);
	test.insert(2);
	test.insert(5);
	test.insert(5);
	test.insert(4);
	test.insert(7);
	test.insert(8);

	return 0;
}