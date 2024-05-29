#ifndef NODE_HPP
#define NODE_HPP

namespace TreeAVL {
template <typename Data, typename ID>
class Node {
   private:
	Data* info;
	ID id;
	Node<Data, ID>*left, *right;
	int height;

   public:
	Node(Data& info, ID& id)
	    : info(&info), left(nullptr), right(nullptr), height(0), id(id) {}
	Node(Data* info, ID& id)
	    : info(info), left(nullptr), right(nullptr), height(0), id(id) {}

	Data& getInfo() { return (*info); }
	Data* getPointInfo() { return info; }
	ID& getId() { return id; }
	int getHeight() const { return height; }
	Node* getNodeLeft() const { return left; }
	Node* getNodeRight() const { return right; }
	Node** getPointNodeLeft() { return &left; }
	Node** getPointNodeRight() { return &right; }

	void setHeight(int height) { this->height = height; }
	void setId(ID id) { this->id = id; }
	void setNodes(Node<Data, ID>* nodeLeft, Node<Data, ID>* nodeRight) {
		this->left = nodeLeft;
		this->right = nodeRight;
	}
	void setNodeLeft(Node<Data, ID>* node) { this->left = node; }
	void setNodeRight(Node<Data, ID>* node) { this->right = node; }

	bool operator==(Node<Data, ID>& other) const {
		return this->id == other.getId();
	}

	bool operator<(Node<Data, ID>& other) const {
		return this->id < other.getId();
	}

	bool operator>(Node<Data, ID>& other) const {
		return this->id > other.getId();
	}

	bool operator==(const ID& id) const {
		return this->id == id;
	}

	bool operator<(const ID& id) const {
		return this->id < id;
	}

	bool operator>(const ID& id) const {
		return this->id > id;
	}
	~Node() {}
};
}  // namespace TreeAVL

#endif