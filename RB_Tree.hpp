#pragma once
#include"RB_Node.hpp"

template<class T>
class RB_Tree
{
private:
	RB_Node<T>* root;
	void left_rotate(RB_Node<T>* x);//����
	void right_rotate(RB_Node<T>* y);//����
	void insert_fix(RB_Node<T>* new_node);//��������
	void remove_fix(RB_Node<T>* node);//ɾ������

public:
	RB_Tree() { root = nullptr; }
	~RB_Tree() {}; 
	RB_Node<T>* get_root()const {
		return this->root;
	}
	void insert(T new_val); //���루ͨ����ֵ��
	void remove(T target_val);//ɾ����ͨ������ֵ��
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


//����
template<class T>
void RB_Tree<T>::insert(T new_val) {
	if (this->root == nullptr) {   //rootΪ�գ�����
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


//��������
template<class T>
void RB_Tree<T>::insert_fix(RB_Node<T>* new_node) {
	RB_Node<T>* cur = new_node;
	while (cur->parent->color == red) {
		RB_Node<T>* uncle = cur->get_uncle();

		if (uncle!=nullptr && uncle->color == red) {  //uncleΪ��
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
		else if (uncle == nullptr || uncle->color == black) { //uncleΪ�ڻ���nil
			if (cur->parent->is_left_child() && cur->is_left_child()) { //����
				cur->parent->color = black;
				cur->parent->parent->color = red;
				this->right_rotate(cur->parent->parent);
			}
			else if (cur->parent->is_left_child() && cur->is_right_child()) { //����
				this->left_rotate(cur->parent);
				cur = cur->left;
			}
			else if (cur->parent->is_right_child() && cur->is_right_child()) { //����
				cur->parent->color = black;
				cur->parent->parent->color = red;
				this->left_rotate(cur->parent->parent);
			}
			else {     //����
				this->right_rotate(cur->parent);
				cur = cur->right;
			}
		}
	}
	return;
}


//ɾ��
template<class T>
void RB_Tree<T>::remove(T target_val) {
	RB_Node<T>* x = this->root;
	RB_Node<T>* target_node = nullptr;
	while (x != nullptr) {
		if (x->val > target_val)x = x->left;
		else if (x->val < target_val)x = x->right;
		else { target_node = x; break; }
	}
	if (target_node == nullptr) return;//û��Ŀ��ֵ������ɾ����ֱ�ӷ���

	RB_Node<T>* replace = nullptr;
	if (target_node->left != nullptr && target_node->right != nullptr) {  //2������
		//��������̽ڵ㣩
		replace = target_node->get_successor();

		//����ֵ
		T tmp = target_node->val;
		target_node->val = replace->val;
		replace->val = tmp;
	}
	else if (target_node->left != nullptr || target_node->right != nullptr) { //1������
		//���������ӣ�
		replace = target_node->left != nullptr ? target_node->left : target_node->right;

		//����ֵ
		T tmp = target_node->val;
		target_node->val = replace->val;
		replace->val = tmp;
	}
	else if (target_node == this->root) {  //�����޺���
		delete root;
		root = nullptr;
	}
	else replace = target_node; //Ҷ�ӣ�����nil�� ��������Ҫ��ǰ��ͳһ���㴦��

	if (replace != nullptr && replace->color == black) {  //��ɾ���Ϊ�ڣ���������
		this->remove_fix(replace);
	}
	else { //��ɾ���Ϊ�죬ֱ��ɾ��
		delete replace; //RB_Node����������deleteʱ����parent�Ա�����ָ��
		replace = nullptr;
	}

	return;
}

//ɾ������
template<class T>
void RB_Tree<T>::remove_fix(RB_Node<T>* node) {


}