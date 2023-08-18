#pragma once
#include <iostream>
#include <vector>
#include <iostream>
#include <windows.h>
#include <string>


enum Color { BLACK = 0, RED , DOUBLE_BLACK};

class Node
{
public:
	int key;
	int color; // 0 - black, 1 - red
	Node* left;
	Node* right;
	Node* parent;

	Node(int color = Color::RED, int key = -1, Node* left = nullptr,
		Node* right = nullptr, Node* parent = nullptr);


};

class RedBlackTree
{
private:
	Node* root;
	Node* sentinel;
	std::vector<Node*> lastNode;


public:

	//COLORS MANIPULATE
	int getColor(Node* node);
	Node* getRoot();
	void setColor(Node* node, int color);
	bool checkIfExist(int value);

	//INSERT
	RedBlackTree();
	~RedBlackTree();
	void rotateLeft(Node* ptr);
	void rotateRight(Node* ptr);
	Node* BSTinsert(Node* root, Node*& node);
	void RBinsert(Node* node);
	//Final insert
	void add(int value);

	//DELETE
	Node* find(int value);
	void RBdelete(Node* node);
	Node* treeSuccessor(Node* node);
	void RBDeleteFixup(Node* node);
	void clear(Node* node);
	//Final remove
	void remove(int value);

	//DISPLAY
	void printTree(Node* node, int space);
	void print();



};
