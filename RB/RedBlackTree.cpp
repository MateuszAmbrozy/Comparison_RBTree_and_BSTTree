#include "RedBlackTree.h"
#include "../common/TreeDisplay.h"

Node::Node(int color, int key, Node* left,
	Node* right, Node* parent)
{
	this->key = key;
	this->color = color;
	this->left = left;
	this->right = right;
	this->parent = parent;

}

RedBlackTree::RedBlackTree()
{

	this->sentinel = new Node(Color::BLACK);
	sentinel->left = sentinel->right = sentinel->parent = sentinel;
	this->root = sentinel;
}

RedBlackTree::~RedBlackTree()
{
	this->clear(this->root);
	delete sentinel;
}

void RedBlackTree::rotateLeft(Node* node)
{

	Node* y = node->right; // Pivot node.
	node->right = y->left; // Move the pivot's left subtree to the right of the rotated node.
	if (node->right != sentinel)
	{
		node->right->parent = node;
	}
	y->parent = node->parent;
	if (node->parent == sentinel)
	{
		root = y;
	}
	else if (node == node->parent->left)
	{
		node->parent->left = y;
	}
	else
	{
		node->parent->right = y;

	}
	y->left = node;
	node->parent = y;

}
void RedBlackTree::rotateRight(Node* node)
{

	Node* y = node->left;
	node->left = y->right;

	if (node->left != sentinel)
	{
		node->left->parent = node;
	}

	y->parent = node->parent;

	if (node->parent == sentinel)
	{
		this->root = y;
	}
	else if (node == node->parent->left)
	{
		node->parent->left = y;
	}
	else
	{
		node->parent->right = y;

	}
	y->right = node;
	node->parent = y;
}
Node* RedBlackTree::BSTinsert(Node* root, Node*& node)
{
	if (node->parent == sentinel)
		root = node;
	else
		for (;;)
		{
			if (node->key < node->parent->key)
			{
				if (node->parent->left == sentinel)
				{
					node->parent->left = node;
					break;
				}
				node->parent = node->parent->left;
			}
			else
			{
				if (node->parent->right == sentinel)
				{
					node->parent->right = node;
					break;
				}
				node->parent = node->parent->right;
			}

		}
	return root;
}
void RedBlackTree::RBinsert(Node* node)
{
	root = this->BSTinsert(this->root, node);
	Node* uncle;

	this->setColor(node, Color::RED);

	while ((node != root) && getColor(node) == RED && (getColor(node->parent) == Color::RED))
	{
		if (node->parent == node->parent->parent->left)
		{
			uncle = node->parent->parent->right;
			if (getColor(uncle) == RED)
			{
				setColor(uncle, BLACK);
				setColor(node->parent, BLACK);
				setColor(node->parent->parent, RED);
				node = node->parent->parent;
				continue;
			}

			if (node == node->parent->right)
			{
				node = node->parent;
				rotateLeft(node);

			}

			this->setColor(node->parent, Color::BLACK);
			this->setColor(node->parent->parent, Color::RED);
			rotateRight(node->parent->parent);
			break;

		}
		else
		{
			Node* uncle = node->parent->parent->left;

			if (getColor(uncle) == RED)
			{
				setColor(uncle, BLACK);
				setColor(node->parent, BLACK);
				setColor(node->parent->parent, RED);
				node = node->parent->parent;
				continue;
			}
			if (node == node->parent->left)
			{
				node = node->parent;
				rotateRight(node);
			}

			this->setColor(node->parent, Color::BLACK);
			this->setColor(node->parent->parent, Color::RED);
			rotateLeft(node->parent->parent);
			break;

		}
	}
	setColor(root, BLACK);

}
int RedBlackTree::getColor(Node* node)
{
	if (node == nullptr)
		return BLACK;

	return node->color;
}
Node* RedBlackTree::getRoot()
{
	return this->root;
}
void RedBlackTree::setColor(Node* node, int color)
{
	if (node == nullptr)
		return;

	node->color = color;
}
void RedBlackTree::add(int value)
{
	Node* node = new Node(Color::RED, value, sentinel, sentinel, this->root);
	this->RBinsert(node);

}

bool RedBlackTree::checkIfExist(int value)
{
    return find(value) != nullptr;
}

Node* RedBlackTree::treeSuccessor(Node* node)
{
	if (!node || node == sentinel) return sentinel;
	if (node->right != sentinel) {
		node = node->right;
		while (node->left != sentinel) {
			node = node->left;
		}
		return node;
	}
	Node* y = node->parent;
	while (y != sentinel && node == y->right) {
		node = y;
		y = y->parent;
	}
	return y;
}
Node* RedBlackTree::find(int value)
{
	Node* x;

	x = root;
	while ((x != sentinel) && (x->key != value))
		if (value < x->key) x = x->left;
		else           x = x->right;
	if (x == sentinel) return NULL;
	return x;
}

void RedBlackTree::RBDeleteFixup(Node* node)
{

		while (node != root && getColor(node) == Color::BLACK) {
			if (node == node->parent->left) {
				Node* sibling = node->parent->right;
				if (getColor(sibling) == Color::RED) {
					setColor(sibling, Color::BLACK);
					setColor(node->parent, Color::RED);
					rotateLeft(node->parent);
					sibling = node->parent->right;
				}
				if (getColor(sibling->left) == Color::BLACK && getColor(sibling->right) == Color::BLACK) {
					setColor(sibling, Color::RED);
					node = node->parent;
				}
				else {
					if (getColor(sibling->right) == Color::BLACK) {
						setColor(sibling->left, Color::BLACK);
						setColor(sibling, Color::RED);
						rotateRight(sibling);
						sibling = node->parent->right;
					}
					setColor(sibling, getColor(node->parent));
					setColor(node->parent, Color::BLACK);
					setColor(sibling->right, Color::BLACK);
					rotateLeft(node->parent);
					node = root;
				}
			}
			else {
				Node* sibling = node->parent->left;
				if (getColor(sibling) == Color::RED) {
					setColor(sibling, Color::BLACK);
					setColor(node->parent, Color::RED);
					rotateRight(node->parent);
					sibling = node->parent->left;
				}
				if (getColor(sibling->right) == Color::BLACK && getColor(sibling->left) == Color::BLACK) {
					setColor(sibling, Color::RED);
					node = node->parent;
				}
				else {
					if (getColor(sibling->left) == Color::BLACK) {
						setColor(sibling->right, Color::BLACK);
						setColor(sibling, Color::RED);
						rotateLeft(sibling);
						sibling = node->parent->left;
					}
					setColor(sibling, getColor(node->parent));
					setColor(node->parent, Color::BLACK);
					setColor(sibling->left, Color::BLACK);
					rotateRight(node->parent);
					node = root;
				}
			}
		}
		setColor(node, Color::BLACK);

}
void RedBlackTree::clear(Node* node)
{
    if (!node || node == sentinel) return;
    Node* boundary = node->parent;
    if (boundary == sentinel) root = sentinel;
    else if (boundary->left == node) boundary->left = sentinel;
    else boundary->right = sentinel;
    while (node != boundary) {
        if (node->left != sentinel) { node = node->left; continue; }
        if (node->right != sentinel) { node = node->right; continue; }
        Node* parent = node->parent;
        if (parent != boundary) {
            if (parent->left == node) parent->left = sentinel;
            else parent->right = sentinel;
        }
        delete node;
        node = parent;
    }
    sentinel->parent = sentinel;
}
void RedBlackTree::RBdelete(Node* node)
{
		if (!node || node == sentinel) return;
		Node* y = sentinel;
		Node* x = sentinel;
		if ((node->left == sentinel) || (node->right == sentinel))
			y = node;
		else
			y = this->treeSuccessor(node);

		if (y->left != sentinel)
		{
			x = y->left;
		}
		else
		{
			x = y->right;
		}
		x->parent = y->parent;

		if (y->parent == sentinel)
			root = x;

		else if (y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;

		if (y != node)
		{
			node->key = y->key;
		}

		if (this->getColor(y) == Color::BLACK)
			this->RBDeleteFixup(x);
		delete y;
		sentinel->parent = sentinel;
}

void RedBlackTree::remove(int value)
{
	this->RBdelete(this->find(value));
}

void RedBlackTree::printTree(Node* node, int space)
{
    tree_ui::draw(node, sentinel, [](Node* n) {
        std::string label = std::to_string(n->key) + (n->color == RED ? " [R]" : " [B]");
        return tree_ui::color(label, n->color == RED ? "31" : "36");
    }, space);
}

void RedBlackTree::print()
{
    std::cout << "RBTree — red-black tree   [R] red / [B] black\n";
    printTree(root, 0);
}
