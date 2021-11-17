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

};


