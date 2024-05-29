#include <iostream>
#include <vector>
#include "TreeAVL/TreeAVL.hpp"

void printVector(std::vector<int>& vect) {
	for (int i = 0; i < vect.size(); i++)
		std::cout << vect.at(i) << " ";
	std::cout << "\n\n";
}

int main() {
	TreeAVL::Tree<int, int> arvore;
	std::vector<int> nums = {};
	int tam = 20;
	for (int i = 0; i < tam; i++)
		nums.push_back(rand() % 100);
	for (int i = 0; i < tam; i++)
		arvore.add(nums.at(i), nums.at(i));

	printVector(nums);
	arvore.print();

	std::cout << "\n\n";
	try {
		while (arvore.getNumberElements()) {
			int auxi = arvore.getMinorElement();
			std::cout << arvore.remove(auxi) << " ";
		}
	} catch (std::exception& e) {
		arvore.clear();
	}

	return 0;
}