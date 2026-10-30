#include "BST.h"
#include "../common/TreeDisplay.h"

Node::Node(int key)
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
    return find(value) != nullptr;
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
    if (!node) return;
    Node* boundary = node->parent;
    if (!boundary) root = nullptr;
    else if (boundary->left == node) boundary->left = nullptr;
    else boundary->right = nullptr;
    // Walk down to leaves and back through parents without recursion or allocation.
    while (node != boundary) {
        if (node->left) { node = node->left; continue; }
        if (node->right) { node = node->right; continue; }
        Node* parent = node->parent;
        if (parent != boundary) {
            if (parent->left == node) parent->left = nullptr;
            else parent->right = nullptr;
        }
        delete node;
        node = parent;
    }
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
			Node* successor = treeSuccessor(node);
			node->key = successor->key;
			removeNode(successor);
		}

}
Node* BST::treeSuccessor(Node* node)
{
	if (!node) return nullptr;
	if (node->right != nullptr) {
		node = node->right;
		while (node->left != nullptr) {
			node = node->left;
		}
		return node;
	}
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
	this->removeNode(this->find(value));
}

void BST::printTree(Node* node, int space)
{
    tree_ui::draw(node, static_cast<Node*>(nullptr), [](Node* n) {
        return std::to_string(n->key);
    }, space);
}

void BST::print()
{
    std::cout << "BST — binary search tree\n";
    printTree(root, 0);
}
