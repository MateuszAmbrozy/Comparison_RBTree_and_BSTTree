#include "BST.h"

Node::Node::Node(int key)
{
	this->key = key;
	this->left = this->right = this->parent = nullptr;
}

BST::BST()
{
	this->root = nullptr;
}

BST::~BST()
{
	this->clear(this->root);
}

bool BST::checkIfExist(int value)
{
	Node* r = root;
	while (r != nullptr)
	{
		if (value == r->key)
		{
			return true; // Element zosta³ znaleziony
		}
		else if (value < r->key)
		{
			r = r->left;
		}
		else
		{
			r = r->right;
		}
	}
}

Node* BST::find(int value)
{
	Node* x;

	x = root;
	while ((x != nullptr) && (x->key != value))
		if (value < x->key) x = x->left;
		else           x = x->right;
	if (x == nullptr) return NULL;
	return x;
}

void BST::clear(Node* node)
{
	if (node == nullptr) {
		return;
	}

	// Recursively delete left and right subtrees
	clear(node->left);
	clear(node->right);

	// Update parent pointers and delete current node
	if (node->parent == nullptr) {
		root = nullptr;
	}
	else if (node->parent->left == node) {
		node->parent->left = nullptr;
	}
	else {
		node->parent->right = nullptr;
	}
	delete node;
}

Node* BST::getRoot()
{
	return this->root;
}

Node* BST::insert(Node* root, Node* node)
{
	Node* y = nullptr;
	Node* x = root;

	while (x != nullptr)
	{
		y = x;
		if (node->key < x->key)
		{
			x = x->left;
		}
		else
			x = x->right;
	}
		node->parent = y;
		if (y == nullptr)
			root = node;
		else if (node->key < y->key)
			y->left = node;
		else y->right = node;
		return root;
}

void BST::removeNode(Node* node)
{
		if (node == nullptr)
			return;

		Node* x = nullptr;

		if (node->left == nullptr || node->right == nullptr)
		{
			// Jeœli wêze³ ma co najwy¿ej jedno dziecko
			x = (node->left != nullptr) ? node->left : node->right;

			if (x != nullptr)
				x->parent = node->parent;

			if (node->parent == nullptr)
				root = x;
			else if (node == node->parent->left)
				node->parent->left = x;
			else
				node->parent->right = x;

			delete node;
		}
		else
		{
			// Jeœli wêze³ ma oba dzieci
			Node* successor = treeSuccessor(node);
			node->key = successor->key;
			removeNode(successor);
		}
	

}
Node* BST::treeSuccessor(Node* node)
{
	// Jeœli prawe poddrzewo nie jest puste, to nastêpnik znajduje siê w nim
	if (node->right != nullptr) {
		node = node->right;
		while (node->left != nullptr) {
			node = node->left;
		}
		return node;
	}
	// W przeciwnym razie, nastêpnik jest w pierwszym przodku, którego lewe
	// poddrzewo zawiera wêze³ node.
	Node* y = node->parent;
	while (y != nullptr && node == y->right) {
		node = y;
		y = y->parent;
	}
	return y;
}

void BST::add(int value)
{
	Node* node = new Node(value);
	this->root =this->insert(this->root, node);
}

void BST::remove(int value)
{
	if (checkIfExist(value))
		this->removeNode(this->find(value));
}

void BST::printTree(Node* node, int space)
{
	if (node == nullptr)
	{
		return;
	}
	space += 5;
	printTree(node->right, space);
	std::cout << std::endl;
	for (int i = 5; i < space; i++) {
		std::cout << " ";
	}
	std::cout << node->key << std::endl;
	printTree(node->left, space);
}

void BST::print()
{
	std::cout << "\t\tDRZEWO CZERWONO CZARNE\n\n";
	this->printTree(this->root, 0);
}


