#include <iostream>
#include"RB_Tree.h"
#include"RB_Node.h"



/* 左旋示意图(对节点x进行左旋)：
 *      px                              px
 *     /                               /
 *    x                               y
 *   /  \      --(左旋)-->           / \
 *  lx   y                          x  ry
 *     /   \                       /  \
 *    ly   ry                     lx  ly
 */
template<class T>
void RB_Tree<T>::left_rotate(RB_Node<T>* x) {

	RB_Node<T>* y = x->right;
	if (x == nullptr || y == nullptr || this->root == nullptr)return;

	x->right = y->left;
	if (y->left != nullptr)y->left->parent = x;

	y->parent = x->parent;
	if (x == this->root)this->root = y;
	else {
		if (x->parent->left == x) x->parent->left = y;
		if (x->parent->right == x)x->parent->right = y;
	}

	x->parent = y;
	y->left = x;
}

/* 右旋示意图(对节点y进行右旋)：
 *            py                               py
 *           /                                /
 *          y                                x
 *         /  \      --(右旋)-->            /  \
 *        x   ry                           lx   y
 *       / \                                   / \
 *      lx  rx                                rx  ry
 */
template<class T>
void RB_Tree<T>::right_rotate(RB_Node<T>* y) {

	RB_Node<T>* x = y->left;
	if (x == nullptr || y == nullptr || this->root == nullptr)return;

	y->left = x->right;
	if (x->right != nullptr)x->right->parent = y;

	x->parent = y->parent;
	if (y == this->root)x = this->root;
	else
	{
		if (y->parent->left == y)y->parent->left = x;
		if (y->parent->right == y)y->parent->right = x;
	}

	y->parent = x;
	x->right = y;
}

template<class T>
void RB_Tree<T>::insert(T new_val) {
	RB_Node<T>* new_node = new RB_Node<T>(new_val, red, nullptr, nullptr, nullptr);
	if (new_node == nullptr) { std::cout << "创建失败"; return;}
	else this->insert(new_node);
	return;
}
template<class T>
void RB_Tree<T>::insert(RB_Node<T>* new_node) {
	if (this->root == nullptr) {
		new_node->color = black;
		this->root = new_node;
		return;
	}
	T new_val = new_node->val;

	RB_Node<T>* x = this->root;
	RB_Node<T>* y = x;
	while (x != nullptr){
		y = x;
		if (new_val < x->val) {
			x = x->left;
		}
		else if(new_val > x->val){
			x = x->right;
		}
		else
		{
			break;
		}
	}

	if (new_val == y->val) {
		new_node->parent = y->parent;
		if (y->parent->left == y)y->parent->left = new_node;
		if (y->parent->right == y)y->parent->right = new_node;
		new_node->color = y->color;
		new_node->left = y->left;
		new_node->right = y->right;
		delete y;
		y == nullptr;
	}//插入值相等时替换原结点
	else
	{
		new_node->color = red;
		new_node->parent = y;
		new_val < y->val ? y->left = new_node : y->right = new_node;
		this->insert_fix(new_node);
	}
	return;
}
