#include"RB_Node.hpp"
#include"RB_Tree.hpp"
#include<queue>
#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;

template<class T>
void print_RB_Tree(const RB_Tree<T>& tree); //逐层打印
template<class T>
bool check_RB_Tree(const RB_Tree<T>& tree); //校验红黑树特性
template<class T>
bool dfs(RB_Node<T>* node, int& count, vector<int>& check_count);
template<class T>
int find_max(RB_Node<int>* node);

int main() {
	RB_Tree<int> test;
	for (int i = 0; i < 999; i++) {
		test.insert(i);
		if (!check_RB_Tree(test))cout << "0";
	}
	for (int i = 555; i < 666; i++) {
		test.remove(i);
		if (!check_RB_Tree(test))cout << "0";
	}

	return 0;
}



template<class T>
void print_RB_Tree(const RB_Tree<T>& tree) {
	auto root = tree.get_root();
	queue<RB_Node<T>*> layer;
	queue<RB_Node<T>*> printer;
	layer.push(root);
	int n = 1;

	while (!layer.empty()) {
		while (!layer.empty()) {
			printer.push(layer.front());
			layer.pop();

		}
		cout << "第" << n << "层:";
		while (!printer.empty()) {
			printer.front() == nullptr ? cout << "null" << " " : cout << printer.front()->val << " ";
			if (printer.front() != nullptr)printer.front()->color == red ? cout << "red |" : cout << "black | ";
			else cout << "black | ";
			if (printer.front() != nullptr) {
				layer.push(printer.front()->left);
				layer.push(printer.front()->right);
			}
			printer.pop();
		}
		n++;
		cout << endl;
	}
}

template<class T>
bool check_RB_Tree(const RB_Tree<T>& tree) {
	int count = 0;
	vector<int> check_count = vector<int>();
	if (tree.get_root()->color == red)return false;
	bool dfs_ans = dfs(tree.get_root(),count, check_count);
	for (size_t i = 1; i < check_count.size(); i++) {
		if (check_count[i] != check_count[i - 1])return false;
	}
	return dfs_ans;
}

template<class T>
bool dfs(RB_Node<T>* node, int& count, vector<int>& check_count) {

	if (node == nullptr)return true;
	if (node->color == red && node->parent->color == red)return false;
	if (node->color == black)count++;
	if (node->left==nullptr)check_count.push_back(count);
	if (node->right == nullptr)check_count.push_back(count);

	bool l = dfs(node->left, count, check_count);
	bool r = dfs(node->right, count, check_count);
	if (node->color == black)count--;
	return l && r;
}

