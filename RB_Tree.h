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
	void left_rotate(RB_Node* x, RB_Node<T>*& root);//����
	void right_rotate(RB_Node* y, RB_Node<T>*& root);//����
};

/* ����ʾ��ͼ(�Խڵ�x��������)��
 *      px                              px
 *     /                               /
 *    x                               y
 *   /  \      --(����)-->           / \            
 *  lx   y                          x  ry
 *     /   \                       /  \
 *    ly   ry                     lx  ly
 */
template<class T>
void RB_Tree<T>::left_rotate(RB_Node<T>* x, RB_Node<T>* &root) {

	RB_Node<T>* y = x->right;

	x->right = y->left; 
	y->left->parent = x;

	y->parent = x->parent;
	if (x == root)root = y;
	else {
		if (x->parent->left == x) x->parent->left = y;
		if (x->parent->right == x)x->parent->right = y;
	}

	x->parent = y;
	y->left = x;
}

/* ����ʾ��ͼ(�Խڵ�y��������)��
 *            py                               py
 *           /                                /
 *          y                                x
 *         /  \      --(����)-->            /  \          
 *        x   ry                           lx   y
 *       / \                                   / \          
 *      lx  rx                                rx  ry
 */
template<class T>
void RB_Tree<T>::right_rotate(RB_Node<T>* y, RB_Node<T>*& root) {

	RB_Node<T>* x = y->left;

	y->left = x->right;
	x->right->parent = y;

	x->parent = y->parent;
	if (y == root)x = root;
	else
	{
		if (y->parent->left == y)y->parent->left = x;
		if (y->parent->right == y)y->parent->right = x;
	}

	y->parent = x;
	x->right = y;
}