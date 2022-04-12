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
	~RB_Tree() { delete root; root = nullptr; };
	RB_Node<T>* get_root()const { return this->root; } //��ȡ�����
	void insert(T new_val); //���루ͨ����ֵ��
	void remove(T target_val);//ɾ����ͨ������ֵ��
};


//����
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

//����
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

		if (uncle != nullptr && uncle->color == red) {  //uncleΪ��
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

		if (replace->right != nullptr) { //������Ҷ�ӣ��Һ��ӣ�������1�����ӵ�����ٴ���һ��
			T tmp = replace->val;
			replace->val = replace->right->val;
			replace->right->val = tmp;
			replace = replace->right;
		}
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

	//���ͳһ��ΪɾҶ��
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
	RB_Node<T>* cur = node;
	RB_Node<T>* delete_node = node;
	RB_Node<T>* sil;

	while (cur->color == black && cur != this->root) {
		sil = cur->get_silbling();//�����ֵܽ��

		if (cur->is_left_child()) { //��ɾ���Ϊ����
			if (sil->color == red) {   //�ֵ�Ϊ��
				sil->color = cur->parent->color;
				cur->parent->color = red;
				this->left_rotate(cur->parent);
			}
			else {                      //�ֵ�Ϊ��
				if (sil->right != nullptr && sil->left == nullptr) { //�ֵܽ����Һ���
					sil->color = cur->parent->color;
					sil->right->color = black;
					cur->parent->color = black;
					this->left_rotate(cur->parent);
					break;
				}
				else if (sil->left != nullptr && sil->right == nullptr) { //�ֵܽ�������
					sil->left->color = black;
					sil->color = red;
					this->right_rotate(sil);
				}
				else if (sil->right != nullptr && sil->left != nullptr && sil->right->color == red) { //�ֵ������Һ���
					sil->color = cur->parent->color;
					sil->right->color = black;
					sil->parent->color = black;
					this->left_rotate(cur->parent);
					break;
				}
				else {  //�ֵ��޺���
					if (cur->parent->color == black) {   //�����Ϊ��
						sil->color = red;
						cur = cur->parent;
					}
					else {                             //�����Ϊ��
						cur->parent->color = black;
						sil->color = red;
						break;
					}
				}
			}
		}
		else {        //��ɾ���Ϊ�Һ���
			if (sil->color == red) {   //�ֵ�Ϊ��
				sil->color = cur->parent->color;
				cur->parent->color = red;
				this->right_rotate(cur->parent);
			}
			else {                    //�ֵ�Ϊ��
				if (sil->left != nullptr && sil->right == nullptr) { //�ֵܽ�������
					sil->color = cur->parent->color;
					sil->left->color = black;
					cur->parent->color = black;
					this->right_rotate(cur->parent);
					break;
				}
				else if (sil->right != nullptr && sil->left == nullptr) { //�ֵܽ����Һ���
					sil->right->color = black;
					sil->color = red;
					this->left_rotate(sil);
				}
				else if (sil->left != nullptr && sil->right != nullptr && sil->right->color == red) { //�ֵ������Һ���
					sil->color = cur->parent->color;
					sil->left->color = black;
					cur->parent->color = black;
					this->right_rotate(cur->parent);
					break;
				}
				else {  //�ֵ��޺���
					if (cur->parent->color == black) {  //�����Ϊ��
						sil->color = red;
						cur = cur->parent;
					}
					else {                              //�����Ϊ��
						cur->parent->color = black;
						sil->color = red;
						break;
					}
				}
			}
		}
	}

	delete delete_node;
	delete_node = nullptr;
	return;
}