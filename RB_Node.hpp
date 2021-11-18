#pragma once
enum node_color
{
	black,
	red,
};

template<class T>
class RB_Node
{
public:
	T val;
	node_color color;
	RB_Node* parent;
	RB_Node* left;
	RB_Node* right;

	RB_Node(T v, node_color c, RB_Node* p, RB_Node* l, RB_Node* r) :val(v), color(c), parent(p), left(l), right(r) {};
	~RB_Node() {};

	RB_Node* get_uncle();
	bool is_left_child();
	bool is_right_child();
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


