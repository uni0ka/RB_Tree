#include"RB_Node.hpp"
#include"RB_Tree.hpp"
#include"test.hpp"
#include<set>
#include <Windows.h>
#include<ctime>

int test_size = 10000;
using namespace std;


void test01() {
	clock_t startTime = clock();
	RB_Tree<int> rbtest;
	for (int i = 0; i <= test_size; ++i) {
		rbtest.insert(i);
		//cout << check_RB_Tree(rbtest) << endl;
	}

	for (int i = 0; i < test_size; ++i) {
		rbtest.remove(i);
		//cout << check_RB_Tree(rbtest) << endl;
	}
	clock_t endTime = clock();
	cout << "ºìºÚÊ÷´æ´¢ÓÃÊ±£º" << double(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	check_RB_Tree(rbtest) ? cout << "1\n" : cout << "0\n";
}

void test02() {
	clock_t startTime = clock();
	set<int> settest;
	for (int i = 0; i <= test_size; ++i) {
		settest.insert(i);
	}

	for (int i = 0; i < test_size; ++i) {
		settest.insert(i);
		//cout << check_RB_Tree(rbtest) << endl;
	}
	settest.erase(10);
	clock_t endTime = clock();
	cout << "set´æ´¢ÓÃÊ±£º" << double(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
}

int main() {
	test01();
	test02();

	return 0;
}

