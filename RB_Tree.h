#pragma once
#include"RB_Node.h"
template<class T>
class RB_Tree
{
private:
	RB_Node* root;
public:
	RB_Tree() {}; 
	~RB_Tree() {}; 
	void pre_order();
	void in_order();
	void post_order();
};


