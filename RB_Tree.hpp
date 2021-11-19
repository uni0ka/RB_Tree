#pragma once
#include"RB_Node.hpp"

template<class T>
class RB_Tree
{
private:
	RB_Node<T>* root;
	void left_rotate(RB_Node<T>* x);//左旋
	void right_rotate(RB_Node<T>* y);//右旋
	void insert_fix(RB_Node<T>* new_node);//插入修正
	void remove_fix(RB_Node<T>* node);//删除修正

public:
	RB_Tree() { root = nullptr; }
	~RB_Tree() {}; 
	RB_Node<T>* get_root()const {
		return this->root;
	}
	void insert(T new_val); //插入（通过新值）
	void remove(T target_val);//删除（通过查找值）
};



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
		if (x->is_left_child()) x->parent->left = y;
		if (x->is_right_child())x->parent->right = y;
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
	if (y == this->root)this->root = x;
	else
	{
		if (y->is_left_child())y->parent->left = x;
		if (y->is_right_child())y->parent->right = x;
	}

	y->parent = x;
	x->right = y;
}


//插入
template<class T>
void RB_Tree<T>::insert(T new_val) {
	if (this->root == nullptr) {   //root为空，空树
		root = new RB_Node<T>(new_val, black, nullptr, nullptr, nullptr);
		return;
	}

	RB_Node<T>* x = this->root;
	RB_Node<T>* y = x;
	while (x != nullptr) {
		y = x;
		if (new_val < x->val) {
			x = x->left;
		}
		else if (new_val > x->val) {
			x = x->right;
		}
		else
		{
			return;
		}
	}
	RB_Node<T>* new_node = new RB_Node<T>(new_val, red, y, nullptr, nullptr);
	new_val < y->val ? y->left = new_node : y->right = new_node;
	this->insert_fix(new_node);
	return;
}


//插入修正
template<class T>
void RB_Tree<T>::insert_fix(RB_Node<T>* new_node) {
	RB_Node<T>* cur = new_node;
	while (cur->parent->color == red) {
		RB_Node<T>* uncle = cur->get_uncle();

		if (uncle!=nullptr && uncle->color == red) {  //uncle为红
			cur->parent->color = black;
			uncle->color = black;
			cur->parent->parent->color = red;
			cur = cur->parent->parent;
			if (cur == this->root) {
				cur->color = black;
				break;
			}
			if (cur->parent == this->root) { break; }
		}
		else if (uncle == nullptr || uncle->color == black) { //uncle为黑或者nil
			if (cur->parent->is_left_child() && cur->is_left_child()) { //左左
				cur->parent->color = black;
				cur->parent->parent->color = red;
				this->right_rotate(cur->parent->parent);
			}
			else if (cur->parent->is_left_child() && cur->is_right_child()) { //左右
				this->left_rotate(cur->parent);
				cur = cur->left;
			}
			else if (cur->parent->is_right_child() && cur->is_right_child()) { //右右
				cur->parent->color = black;
				cur->parent->parent->color = red;
				this->left_rotate(cur->parent->parent);
			}
			else {     //右左
				this->right_rotate(cur->parent);
				cur = cur->right;
			}
		}
	}
	return;
}


//删除
template<class T>
void RB_Tree<T>::remove(T target_val) {
	RB_Node<T>* x = this->root;
	RB_Node<T>* target_node = nullptr;
	while (x != nullptr) {
		if (x->val > target_val)x = x->left;
		else if (x->val < target_val)x = x->right;
		else { target_node = x; break; }
	}
	if (target_node == nullptr) return;//没有目标值，无需删除，直接返回

	RB_Node<T>* replace = nullptr;
	if (target_node->left != nullptr && target_node->right != nullptr) {  //2个孩子
		//找替身（后继节点）
		replace = target_node->get_successor();

		//交换值
		T tmp = target_node->val;
		target_node->val = replace->val;
		replace->val = tmp;
	}
	else if (target_node->left != nullptr || target_node->right != nullptr) { //1个孩子
		//找替身（孩子）
		replace = target_node->left != nullptr ? target_node->left : target_node->right;

		//交换值
		T tmp = target_node->val;
		target_node->val = replace->val;
		replace->val = tmp;
	}
	else if (target_node == this->root) {  //根且无孩子
		delete root;
		root = nullptr;
	}
	else replace = target_node; //叶子（无视nil） 无替身，但要和前面统一方便处理

	if (replace != nullptr && replace->color == black) {  //待删结点为黑，调用修正
		this->remove_fix(replace);
	}
	else { //待删结点为红，直接删除
		delete replace; //RB_Node类有析构，delete时消除parent对本结点的指向
		replace = nullptr;
	}

	return;
}

//删除修正
template<class T>
void RB_Tree<T>::remove_fix(RB_Node<T>* node) {


}