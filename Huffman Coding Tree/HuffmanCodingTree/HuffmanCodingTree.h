//HuffmanCodingTree.h
//HuffmanCodingTree declaration file

#ifndef HUFFMANCODINGTREE_H
#define HUFFMANCODINGTREE_H

#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

const int DEFAULT_SIZE = 20;
const int ADD_SIZE = 5;

struct Node{
	char ch;
	int frequency;
	string code;
	Node *left;
	Node *right;
	bool leafNode;
};

class HuffmanCodingTree{
public:
	HuffmanCodingTree();
	~HuffmanCodingTree();
	void ScanString(string str);
	void BuildTreeOnce();
	void BuildTree();
	void EncodeTree();
	void PrintList() const;
	void PrintCodes();
	string PrintMessage();
	string DecodeMessage(string str);
	void ClearTree();
	bool isComplete() const;
private:
	Node **nodeList;
	Node *root;
	string treeString;
	int maxSize;
	int listSize;
	bool listIsFull() const;
	void ExpandList(int size);
	void Encode(Node *ptr, string code);
	void PrintCode(Node *ptr);
	int SearchCharIndex(char ch) const;
	string getCharCode(char ch, Node *ptr);
	bool GetCharFromCode(string code, char &ch, int index, Node *ptr);
	int LowestFreqIndex() const;
	void RemoveFromList(int index);
	void Destroy(Node *ptr);
};

#endif