#ifndef TREE_AVL_HPP
#define TREE_AVL_HPP

#include <iostream>
#include "Node/Node.hpp"

namespace TreeAVL {
template <typename Data, typename ID>
int getHeightNode(Node<Data, ID>* node) {
	return node ? node->getHeight() : -1;
}

int maior(int x, int y) {
	return x > y ? x : y;
}

template <typename Data, typename ID>
int calcHeight(Node<Data, ID>* node) {
	return maior(getHeightNode(node->getNodeLeft()), getHeightNode(node->getNodeRight())) + 1;
}

template <typename Data, typename ID>
int getBalancingFactor(Node<Data, ID>* node) {
	return getHeightNode(node->getNodeLeft()) - getHeightNode(node->getNodeRight());
}
}  // namespace TreeAVL

namespace TreeAVL {
template <typename Data, typename ID>
class Tree {
   public:
	Tree()
	    : root(nullptr), numberElements(0) {}
	Tree(Node<Data, ID>* root, int numberElements)
	    : root(root), numberElements(numberElements) {}

	bool add(Data& info, ID& id);
	void print();

	void setNumberElements(int numberElements) { this->numberElements = numberElements; }

	Data& getElement(ID& id);
	Data& getMinorElement();
	int getNumberElements() { return numberElements; }

	Data& remove(ID& id);
	void clear();

   private:
	Node<Data, ID>* root;
	int numberElements;

	bool add(Node<Data, ID>** root, Node<Data, ID>* new_node);
	void print(Node<Data, ID>* root, int depth);

	Node<Data, ID>* seekNode(Node<Data, ID>** root, ID& id);
	Node<Data, ID>* removeRoot(Node<Data, ID>** root);
	Node<Data, ID>* getBiggerLeft(Node<Data, ID>** root, Node<Data, ID>** child);

	void clear(Node<Data, ID>** root);

	void treeBalancer(Node<Data, ID>** root);
	void rotationLeftRight(Node<Data, ID>** root);
	void rotationRightLeft(Node<Data, ID>** root);
	void rotationLeft(Node<Data, ID>** root);
	void rotationRight(Node<Data, ID>** root);
};
}  // namespace TreeAVL

/** It will add the tree according to its id.
 *  If this element already exists, it returns false, and
 *  delete the node.
 */
template <typename Data, typename ID>
bool TreeAVL::Tree<Data, ID>::add(Data& info, ID& id) {
	Node<Data, ID>* new_node = new Node<Data, ID>(info, id);

	if (!this->root) {
		this->numberElements++;
		root = new_node;
		return true;
	}

	if (!add(&(this->root), new_node)) {
		std::cout << id << "\n\n";
		return false;
	} else
		this->numberElements++;
	return true;
}

/** Prints tree data by level.
 *  Following the following format.
 *  Data - Key - Hieght.
 */
template <typename Data, typename ID>
void TreeAVL::Tree<Data, ID>::print() {
	if (this->root)
		print(root, 0);
}

/** It will search for the smallest element in the tree by its id.
 *  If it doesn't find it, it will generate an exception.
 */
template <typename Data, typename ID>
Data& TreeAVL::Tree<Data, ID>::getMinorElement() {
	if (root) {
		Node<Data, ID>* current = root;
		while (current->getNodeLeft())
			current = current->getNodeLeft();
		return current->getInfo();
	}
	throw std::runtime_error("empty tree");
}

/** It will search for a given element in the tree by its id.
 *  If it doesn't find it, it will generate an exception.
 */
template <typename Data, typename ID>
Data& TreeAVL::Tree<Data, ID>::getElement(ID& id) {
	Node<Data, ID>* auxi = root;

	while (auxi) {
		if (*auxi == id)
			return auxi->getInfo();
		if (*auxi > id)
			auxi = auxi->getNodeLeft();
		else
			auxi = auxi->getNodeRight();
	}
	throw std::runtime_error("empty tree");
}

/** Removes in the tree, searching the structure for the ID.
 *  If it doesn't find it, it will generate an exception,
 *  it is recommended to use it within a try-catch.
 */
template <typename Data, typename ID>
Data& TreeAVL::Tree<Data, ID>::remove(ID& id) {
	Node<Data, ID>* auxi = this->seekNode(&this->root, id);
	if (auxi) {
		this->numberElements--;
		Data& info = auxi->getInfo();
		delete auxi;
		return info;
	}
	throw std::runtime_error("Node not found");
}

/** Will clean the entire tree, including its contents.
 */
template <typename Data, typename ID>
void TreeAVL::Tree<Data, ID>::clear() {
	this->numberElements = 0;
	clear(&root);
	root = nullptr;
}

template <typename Data, typename ID>
bool TreeAVL::Tree<Data, ID>::add(Node<Data, ID>** root, Node<Data, ID>* new_node) {
	if (!(*root)) {
		*root = new_node;
		return true;
	}
	if ((*new_node) == (*(*root))) {
		delete new_node;
		return false;
	}
	bool auxi_bool(true);

	if ((*new_node) < (*(*root)))
		auxi_bool = add((*root)->getPointNodeLeft(), new_node);
	else
		auxi_bool = add((*root)->getPointNodeRight(), new_node);
	(*root)->setHeight(calcHeight((*root)));
	treeBalancer(root);
	return auxi_bool;
}

template <typename Data, typename ID>
void TreeAVL::Tree<Data, ID>::print(Node<Data, ID>* root, int depth) {
	if (!root)
		return;

	for (int i = depth; i > 0; i--)
		printf("      |");

	std::cout << root->getInfo() << " : " << root->getId() << " - " << root->getHeight() << "\n";
	print(root->getNodeLeft(), depth + 1);
	print(root->getNodeRight(), depth + 1);
}

template <typename Data, typename ID>
TreeAVL::Node<Data, ID>* TreeAVL::Tree<Data, ID>::seekNode(TreeAVL::Node<Data, ID>** root, ID& id) {
	if (!(*root)) {
		// If the Node does not exist, it goes here.
		return nullptr;
	}

	if ((*(*root)) == id) {
		return removeRoot(root);
	}

	Node<Data, ID>* auxi = (*(*root)) > id ? seekNode((*root)->getPointNodeLeft(), id) : seekNode((*root)->getPointNodeRight(), id);

	(*root)->setHeight(calcHeight(*root));
	treeBalancer(root);

	return auxi;
}

template <typename Data, typename ID>
TreeAVL::Node<Data, ID>* TreeAVL::Tree<Data, ID>::removeRoot(TreeAVL::Node<Data, ID>** root) {
	Node<Data, ID>* node = (*root);

	if (!node->getNodeLeft()) {
		*root = node->getNodeRight();
		if (!(*root))
			return node;
	} else {
		Node<Data, ID>* bigLeft = getBiggerLeft((*root)->getPointNodeLeft(), (*root)->getNodeLeft()->getPointNodeRight());
		bigLeft->setNodes(node->getNodeLeft(), node->getNodeRight());
		(*root) = bigLeft;
	}

	(*root)->setHeight(calcHeight(*root));
	treeBalancer(root);
	return node;
}

template <typename Data, typename ID>
TreeAVL::Node<Data, ID>* TreeAVL::Tree<Data, ID>::getBiggerLeft(TreeAVL::Node<Data, ID>** root, TreeAVL::Node<Data, ID>** child) {
	if (!(*child))
		return (*root);

	Node<Data, ID>* auxi = NULL;
	if ((*child)->getNodeRight()) {
		Node<Data, ID>* node_right = (*child)->getNodeRight();
		auxi = getBiggerLeft(child, &node_right);
	} else {
		auxi = (*child);
		(*root)->setNodeRight((*child)->getNodeLeft());
	}
	(*root)->setHeight(calcHeight(*root));
	treeBalancer(root);
	return auxi;
}

template <typename Data, typename ID>
void TreeAVL::Tree<Data, ID>::clear(Node<Data, ID>** root) {
	if (!(*root))
		return;

	clear((*root)->getPointNodeLeft());
	clear((*root)->getPointNodeRight());

	delete (*root)->getPointInfo();
	delete *root;
}

template <typename Data, typename ID>
void TreeAVL::Tree<Data, ID>::treeBalancer(Node<Data, ID>** root) {
	int fator(getBalancingFactor(*root));

	if (fator > 1)
		getBalancingFactor((*root)->getNodeLeft()) < 0 ? rotationLeftRight(root) : rotationLeft(root);
	else if (fator < -1)
		getBalancingFactor((*root)->getNodeRight()) > 0 ? rotationRightLeft(root) : rotationRight(root);
}

template <typename Data, typename ID>
void TreeAVL::Tree<Data, ID>::rotationLeftRight(Node<Data, ID>** root) {
	rotationRight((*root)->getPointNodeLeft());
	rotationLeft(root);
}

template <typename Data, typename ID>
void TreeAVL::Tree<Data, ID>::rotationRightLeft(Node<Data, ID>** root) {
	Node<Data, ID>* auxi = (*root)->getNodeRight();
	rotationLeft(&auxi);
	rotationRight(root);
}

template <typename Data, typename ID>
void TreeAVL::Tree<Data, ID>::rotationLeft(Node<Data, ID>** root) {
	Node<Data, ID>* node = (*root)->getNodeLeft();

	(*root)->setNodeLeft(node->getNodeRight());
	node->setNodeRight(*root);

	(*root)->setHeight(calcHeight(*root));
	node->setHeight(calcHeight(node));

	*root = node;
}

template <typename Data, typename ID>
void TreeAVL::Tree<Data, ID>::rotationRight(Node<Data, ID>** root) {
	Node<Data, ID>* node = (*root)->getNodeRight();

	(*root)->setNodeRight(node->getNodeLeft());
	node->setNodeLeft(*root);

	(*root)->setHeight(calcHeight(*root));
	node->setHeight(calcHeight(node));

	*root = node;
}

#endif