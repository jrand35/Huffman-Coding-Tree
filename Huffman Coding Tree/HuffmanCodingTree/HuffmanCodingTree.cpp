//HuffmanCodingTree.cpp
//HuffmanCodingTree definition file

#include "HuffmanCodingTree.h"

//Constructor
HuffmanCodingTree::HuffmanCodingTree(){
	treeString = "";
	maxSize = DEFAULT_SIZE;
	nodeList = new Node*[DEFAULT_SIZE];
	root = nullptr;
	listSize = 0;
}

//Destructor
HuffmanCodingTree::~HuffmanCodingTree(){
	for (int i = 0; i < listSize; i++){
		Destroy(nodeList[i]);
	}
	delete[] nodeList;
}

//Pre: Tree has been initialized
//Post: Tree has read in a string and divided it into a list of nodes for each character and its frequency
void HuffmanCodingTree::ScanString(string str){
	treeString = str;
	for (int i = 0; i < str.length(); i++){
		char ch = str[i];
		int characterIndex = SearchCharIndex(ch);
		//If character hasn't been added to list
		if (characterIndex == -1){
			if (listIsFull()){
				ExpandList(ADD_SIZE);
			}
			Node *tmp = new Node;
			tmp->ch = ch;
			tmp->frequency = 1;
			tmp->code = "";
			tmp->leafNode = true;
			tmp->left = nullptr;
			tmp->right = nullptr;
			nodeList[listSize] = tmp;
			listSize++;
		}
		//If character exists in list
		else{
			nodeList[characterIndex]->frequency ++;
		}
	}
}

//Pre: Tree has been initialized and there is at least 1 node in the list
//Post: Calls BuildTreeOnce() function until there is only 1 top-level node
void HuffmanCodingTree::BuildTree(){
	while (listSize > 1){
		BuildTreeOnce();
	}
}

//Pre: Tree has been initialized and there is at least 1 node in the list
//Post: Calls recursive function Encode() on all nodes
void HuffmanCodingTree::EncodeTree(){
	string code = "";
	Encode(root, code);
}

//Pre: Tree has been initialized and there is at least 1 node in the list
//Post: Finds the two character nodes with the lowest frequencies, removes them from the list, links them together with a top-level node and adds the node to the list
void HuffmanCodingTree::BuildTreeOnce(){
	int lowestIndex1 = LowestFreqIndex();
	Node *lowestNode1 = nodeList[lowestIndex1];
	RemoveFromList(lowestIndex1);

	int lowestIndex2 = LowestFreqIndex();
	Node *lowestNode2 = nodeList[lowestIndex2];
	RemoveFromList(lowestIndex2);

	Node *tree = new Node;
	tree->ch = '*';
	tree->frequency = (lowestNode1->frequency + lowestNode2->frequency);
	tree->code = "";
	tree->leafNode = false;
	tree->left = lowestNode1;
	tree->right = lowestNode2;
		
	nodeList[listSize] = tree;
	listSize++;

	if (listSize == 1 && nodeList[0]->leafNode == false){
		root = nodeList[0];
	}
}

//Pre: Tree has been initialized
//Post: Prints the characters and frequencies of the characters
void HuffmanCodingTree::PrintList() const{
	for (int i = 0; i < listSize; i++){
		cout << nodeList[i]->ch << "\t" << nodeList[i]->frequency;
		if (nodeList[i]->leafNode == false){
			cout << " internal node";
		}
		cout << endl;
	}
}

//Post: Calls recursive function PrintCode()
void HuffmanCodingTree::PrintCodes(){
	PrintCode(root);
}

//Pre: A string has been read in and the tree has been built
//Post: Prints the encoded message using the tree
string HuffmanCodingTree::PrintMessage() {
	string str;
	for (int i = 0; i < treeString.length(); i++){
		cout << getCharCode(treeString[i], root);
		str += getCharCode(treeString[i], root);
	}
	return str;
}

//Pre: The tree has been built
//Post: Uses the tree built to decode a binary code message
string HuffmanCodingTree::DecodeMessage(string str){
	string test = "";
	string msg = "";
	for (int i = 0; i < str.length(); i++){
		char ch;
		test += str[i];
		//cout << test << endl;
		bool result = GetCharFromCode(test, ch, -1, root);
		if (result == true){
			//exit(1);
			msg += ch;
			test = "";
		}
	}
	return msg;
}

//Post: Empties the values of the tree
void HuffmanCodingTree::ClearTree(){
	for (int i = 0; i < listSize; i++){
		Destroy(nodeList[i]);
	}
	delete[] nodeList;

	treeString = "";
	maxSize = DEFAULT_SIZE;
	nodeList = new Node*[DEFAULT_SIZE];
	root = nullptr;
	listSize = 0;
}

//Post: Returns true if the tree is fully built (there is 1 top-level internal node in the list), false otherwise
bool HuffmanCodingTree::isComplete() const{
	return (listSize == 1 && root != nullptr);
}

//Post: Returns true if the array of node pointers is full, false otherwise, used if calling ExpandList() function
bool HuffmanCodingTree::listIsFull() const{
	return (listSize == maxSize);
}

//Post: Expands the size of the node pointer array
void HuffmanCodingTree::ExpandList(int size){
	Node **newNodeList = new Node*[maxSize + size];
	for (int i = 0; i < maxSize + size; i++){
		newNodeList[i] = nodeList[i];
	}
	delete[] nodeList;
	nodeList = newNodeList;
	newNodeList = nullptr;
	maxSize += size;
}

//Pre: Tree contains at least 1 node, called after tree has been fully built
//Post: Assigns each character on each leaf node a binary code based on the position from the root node
void HuffmanCodingTree::Encode(Node *ptr, string code){
	if (ptr == nullptr){
		return;
	}
	ptr->code = code;

	string leftCode = code + "0";
	string rightCode = code + "1";
	
	Encode(ptr->left, leftCode);
	Encode(ptr->right, rightCode);
}

//Pre: Each character node has been assigned a code
//Post: Prints the list of characters and their codes
void HuffmanCodingTree::PrintCode(Node *ptr){
	if (ptr == nullptr){
		return;
	}
	if (ptr->leafNode){
		cout << ptr->ch << " " << ptr->code << endl;
	}
	else{
		PrintCode(ptr->left);
		PrintCode(ptr->right);
	}
}

//Post: Searches for a node containing the specified character, ch, and returns the index of that node pointer in the list
int HuffmanCodingTree::SearchCharIndex(char ch) const{
	for (int i = 0; i < listSize; i++){
		if (nodeList[i]->ch == ch){
			return i;
		}
	}
	return -1;
}

//Post: Searches for a node containing the specified character, ch, and returns the code for that character
string HuffmanCodingTree::getCharCode(char ch, Node *ptr){
	if (ptr == nullptr){
		return "";
	}
	if (ptr->leafNode){
		if (ptr->ch == ch){
			return ptr->code;
		}
		else{
			return "";
		}
	}
	else{
		string result1 = getCharCode(ch, ptr->left);
		string result2 = getCharCode(ch, ptr->right);
		if (result1 != ""){
			return result1;
		}
		else if (result2 != ""){
			return result2;
		}
		else{
			return "";
		}
	}
}

//Post: Returns true if the code parameter matches ptr->code
bool HuffmanCodingTree::GetCharFromCode(string code, char &ch, int index, Node *ptr){
	if (index > -1){
		if (ptr == nullptr){
			return false;
		}
		if (code == ptr->code && ptr->leafNode){
			ch = ptr->ch;
			return true;
		}
	}
	index++;
	if (code[index] == '0'){
		return GetCharFromCode(code, ch, index, ptr->left);
	}
	else if (code[index] == '1'){
		return GetCharFromCode(code, ch, index, ptr->right);
	}
}

//Pre: There is at least 1 node in the list
//Post: Returns the index of the pointer node containing the lowest frequency value in the list
int HuffmanCodingTree::LowestFreqIndex() const{
	assert(nodeList[0] != nullptr);
	int min = nodeList[0]->frequency;
	int index = 0;
	for (int i = 0; i < listSize; i++){
		if (nodeList[i]->frequency < min){
			min = nodeList[i]->frequency;
			index = i;
		}
	}
	return index;
}

//Post: Removes a pointer node from the list and shifts the indexes to the left
void HuffmanCodingTree::RemoveFromList(int index){
	for (int i = index; i < listSize - 1; i++){
		nodeList[i] = nodeList[i + 1];
	//	nodeList[i]->ch = nodeList[i + 1]->ch;
	//	nodeList[i]->frequency = nodeList[i + 1]->frequency;
	}
	nodeList[listSize - 1] = nullptr;
	listSize--;
}

//Post: Called by the Destructor, deallocates the data pointed by ptr
void HuffmanCodingTree::Destroy(Node *ptr){
	if (ptr == nullptr){
		return;
	}
	Node *tmp = ptr;
	ptr = nullptr;
	Destroy(tmp->left);
	Destroy(tmp->right);
	delete ptr;
}