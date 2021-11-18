#pragma once
#include"RB_Node.h"
template<class T>
class RB_Tree
{
private:
	RB_Node* root;
	void left_rotate(RB_Node* x);//左旋
	void right_rotate(RB_Node* y);//右旋
	void insert_fix(RB_Node<T>* new_node);//插入修正
public:
	RB_Tree() {root = nullptr}; 
	~RB_Tree() {}; 

	void insert(T new_val); //插入（通过新值）
	void insert(RB_Node<T>* new_node);//插入（通过新结点）
};

