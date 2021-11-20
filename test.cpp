#include"RB_Node.hpp"
#include"RB_Tree.hpp"
#include<queue>
#include<algorithm>
#include<iostream>
using namespace std;

template<class T>
void print_RB_Tree(const RB_Tree<T>& tree); 
template<class T>
bool check_RB_Tree(const RB_Tree<T>& tree);

int main() {
	RB_Tree<int> test;
	for (int i = 0; i < 9; i++) {
		test.insert(i);
	}
	print_RB_Tree<int>(test);
	test.remove(7);
	cout << endl;
	print_RB_Tree<int>(test);
	test.remove(8);
	cout << endl;
	print_RB_Tree<int>(test);
	test.remove(3);
	cout << endl;
	print_RB_Tree<int>(test);
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
		cout << "µÚ" << n << "²ã:";
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

}