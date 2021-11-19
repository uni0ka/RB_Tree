#pragma once
enum node_color
{
	black = 0,
	red = 1,
};

template<class T>
class RB_Node
{
public:
	T val;
	node_color color;
	RB_Node<T>* parent;
	RB_Node<T>* left;
	RB_Node<T>* right;

	RB_Node(T v, node_color c, RB_Node* p, RB_Node* l, RB_Node* r) :val(v), color(c), parent(p), left(l), right(r) {};
	~RB_Node();

	RB_Node<T>* get_uncle(); //��ȡuncle���

	bool is_left_child(); //�жϱ�����Ƿ�Ϊ����
	bool is_right_child();//�жϱ�����Ƿ�Ϊ�Һ���

	// RB_Node<T>* get_predecessor();//��ȡǰ�����
	RB_Node<T>* get_successor();//��ȡ��̽�㣨�������Һ��ӵ�����£�
};


template<class T>
RB_Node<T>* RB_Node<T>::get_uncle() {
	if (this->parent == nullptr || this->parent->parent == nullptr)return nullptr;
	if (this->parent->parent->left == this->parent)return this->parent->parent->right;
	if (this->parent->parent->right == this->parent)return this->parent->parent->left;
	return nullptr;
}

template<class T>
bool RB_Node<T>::is_left_child() {
	return this->parent->left == this ? true : false;
}

template<class T>
bool RB_Node<T>::is_right_child() {
	return this->parent->right == this ? true : false;
}

template<class T>
RB_Node<T>* RB_Node<T>::get_successor() {
	if (this->right == nullptr)return nullptr;
	RB_Node<T>* successor = this->right;
	while (successor->left!=nullptr)
	{
		successor = successor->left;
	}
	return successor;
}

template<class T>
RB_Node<T>::~RB_Node() {
	if (this->parent != nullptr) {
		if (this->is_left_child())this->parent->left = nullptr;
		else this->parent->right = nullptr;
	}
}