/*
#include "TreeAVL.hpp"

template <typename Data, typename ID>
bool TreeAVL::Tree<Data, ID>::add(Data info) {
    Node<Data>* new_node = new Node<Data>(info);

    if (this->root) {
        return add(&this->root, new_node);
    } else {
        root = new_node;
    }
    return true;
}

template <typename Data, typename ID>
bool TreeAVL::Tree<Data, ID>::add(Node<Data>** root, Node<Data>* new_node) {
    if (new_node->getInfo() < (*root)->getInfo()) {
        if ((*root)->getNodeLeft())
            return add(&(*root)->getNodeLeft(), new_node);
        else
            (*root)->setNodeLeft(new_node);
        return true;
    } else if (new_node->getInfo() > (*root)->getInfo()) {
        if ((*root)->getNodeRight())
            return add(&(*root)->getNodeRight(), new_node);
        else
            (*root)->setNodeRight(new_node);
        return true;
    } else {
        delete new_node;
        return false;
    }
}

template <typename Data, typename ID>
void TreeAVL::Tree<Data, ID>::print() {
    if (this->root)
        print(root);
}

template <typename Data, typename ID>
void TreeAVL::Tree<Data, ID>::print(Node<Data>* root) {
    if (!root)
        return;

    std::cout << root->getInfo() << "\n";
}

*/

// TreeAVL.cpp
