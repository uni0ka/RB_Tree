#pragma once
#include"RB_Node.h"
template<class T>
class RB_Tree
{
private:
	RB_Node* root;
	void left_rotate(RB_Node* x);//����
	void right_rotate(RB_Node* y);//����
	void insert_fix(RB_Node<T>* new_node);//��������
public:
	RB_Tree() {root = nullptr}; 
	~RB_Tree() {}; 

	void insert(T new_val); void insert(RB_Node<T>* new_node);//����
};

