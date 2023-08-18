#include "RedBlackTree.h"


//CONSTRUCTORS
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
	//wartownik jest pustym wêz³em, jest u¿ywany zamiast nullptr,
	//	poniewa¿ eliminuje potrzebê specjalnej obs³ugi wszystkich
	//	przypadków naro¿nych, tj.ostatniego wêz³a, pierwszego wêz³a itp

	this->sentinel = new Node(Color::BLACK);
	this->root = sentinel;
}

RedBlackTree::~RedBlackTree()
{
	this->clear(this->root);
}


//INSERT
void RedBlackTree::rotateLeft(Node* node)
{
	std::cout << "LEFT ROTATION\n";
	Node* y = node->right; //inicjacja y
	node->right = y->left; //zamiana lewego poddrzewa y na prawe poddrzewo x
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
	std::cout << "RIGHT ROTATION\n";

	Node* y = node->left;
	node->left = y->right;

	if (node->right != sentinel)
	{
		node->right->parent = node;
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
//Final insert
void RedBlackTree::add(int value)
{
	Node* node = new Node(value, Color::RED, sentinel, sentinel, this->root);
	node->key = value;
	this->RBinsert(node);
	lastNode.push_back(node);
}

bool RedBlackTree::checkIfExist(int value)
{
	Node* r = root;
	while (r != sentinel)
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
// Element nie zosta³ znaleziony w drzewie
	std::cout << "Podana liczba nie istnieje\n";
	Sleep(2000);
return false;

}



//DELETE
Node* RedBlackTree::treeSuccessor(Node* node)
{
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

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
	


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//if (node == sentinel)
	//	return;

	//if (node == root) {
	//	root = sentinel;
	//	return;
	//}

	//if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
	//	Node* child = node->left != sentinel ? node->left : node->right;

	//	if (node == node->parent->left) {
	//		node->parent->left = child;
	//		if (child != sentinel)
	//			child->parent = node->parent;
	//		setColor(child, BLACK);
	//		delete (node);
	//	}
	//	else {
	//		node->parent->right = child;
	//		if (child != sentinel)
	//			child->parent = node->parent;
	//		setColor(child, BLACK);
	//		delete (node);
	//	}
	//}
	//else {
	//	Node* sibling = sentinel;
	//	Node* parent = sentinel;
	//	Node* ptr = node;
	//	setColor(ptr, DOUBLE_BLACK);
	//	while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
	//		parent = ptr->parent;
	//		if (ptr == parent->left) {
	//			sibling = parent->right;
	//			if (getColor(sibling) == RED) {
	//				setColor(sibling, BLACK);
	//				setColor(parent, RED);
	//				rotateLeft(parent);
	//			}
	//			else {
	//				if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
	//					setColor(sibling, RED);
	//					if (getColor(parent) == RED)
	//						setColor(parent, BLACK);
	//					else
	//						setColor(parent, DOUBLE_BLACK);
	//					ptr = parent;
	//				}
	//				else {
	//					if (getColor(sibling->right) == BLACK) {
	//						setColor(sibling->left, BLACK);
	//						setColor(sibling, RED);
	//						rotateRight(sibling);
	//						sibling = parent->right;
	//					}
	//					setColor(sibling, parent->color);
	//					setColor(parent, BLACK);
	//					setColor(sibling->right, BLACK);
	//					rotateLeft(parent);
	//					break;
	//				}
	//			}
	//		}
	//		else {
	//			sibling = parent->left;
	//			if (getColor(sibling) == RED) {
	//				setColor(sibling, BLACK);
	//				setColor(parent, RED);
	//				rotateRight(parent);
	//			}
	//			else {
	//				if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
	//					setColor(sibling, RED);
	//					if (getColor(parent) == RED)
	//						setColor(parent, BLACK);
	//					else
	//						setColor(parent, DOUBLE_BLACK);
	//					ptr = parent;
	//				}
	//				else {
	//					if (getColor(sibling->left) == BLACK) {
	//						setColor(sibling->right, BLACK);
	//						setColor(sibling, RED);
	//						rotateLeft(sibling);
	//						sibling = parent->left;
	//					}
	//					setColor(sibling, parent->color);
	//					setColor(parent, BLACK);
	//					setColor(sibling->left, BLACK);
	//					rotateRight(parent);
	//					break;
	//				}
	//			}
	//		}
	//	}
	//	if (node == node->parent->left)
	//		node->parent->left = sentinel;
	//	else
	//		node->parent->right = sentinel;
	//	delete(node);
	//	setColor(root, BLACK);
	//}
}
void RedBlackTree::clear(Node* node)
{
	if (node == sentinel) {
		return;
	}

	clear(node->left);
	clear(node->right);

	if (node->parent == sentinel) {
		root = sentinel;
	}
	else if (node->parent->left == node) {
		node->parent->left = sentinel;
	}
	else {
		node->parent->right = sentinel;
	}
	delete node;
	
}
void RedBlackTree::RBdelete(Node* node)
{
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
}



//Final remove
void RedBlackTree::remove(int value)
{
	if(checkIfExist(value))
		this->RBdelete(this->find(value));
}

//DISPLAY
void RedBlackTree::printTree(Node* node, int space)
{
	if (node == sentinel)
	{
		return;
	}
	space += 5;
	printTree(node->right, space);
	std::cout << std::endl;
	for (int i = 5; i < space; i++) {
		std::cout << " ";
	}
	std::cout << (node->color == RED ? "\033[1;31m" : "") << node->key << "\033[0m" << std::endl;
	printTree(node->left, space);
}

void RedBlackTree::print()
{
	std::cout << "\t\tDRZEWO CZERWONO CZARNE\n\n";
	this->printTree(this->root, 0);

}