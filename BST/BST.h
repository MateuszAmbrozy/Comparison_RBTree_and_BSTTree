#pragma once
#include <iostream>

class Node
{
public:
	Node* left, * right, * parent;
	int key;
	

	 Node(int key = 0);
};

class BST
{
private:
	Node* root;
public:
	BST();
	~BST();

	bool checkIfExist(int value);
	Node* find(int value);
	void clear(Node* node);
	Node* getRoot();

	Node* insert(Node* root, Node* node);

	void removeNode(Node* node);
	Node* treeSuccessor(Node* node);

	void add(int value);
	void remove(int value);

	void printTree(Node* node, int space);
	void print();
};

