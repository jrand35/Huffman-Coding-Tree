//Test.cpp
//Test driver

#include <fstream>
#include "HuffmanCodingTree.h"
using namespace std;

int main(){
	//User input
	HuffmanCodingTree tree;
	string str;
	cout << "Enter a string without spaces to compress and encode it\nthen the program will repeat the process with the contents of \"Text.txt\"\nOr you can enter -1 to skip directly to Text.txt." << endl;
	cin >> str;
	if (str != "-1"){
		tree.ScanString(str);
		cin.get();
		cout << "Characters and frequencies" << endl;
		tree.PrintList();

		int count = 1;
		cin.get();
		while (!tree.isComplete()){
			tree.BuildTreeOnce();
			cout << "----------" << endl;
			cout << "Building tree step " << count << "..." << endl;
			tree.PrintList();
			count++;
			cin.get();
		}

		tree.EncodeTree();
		cout << "----------" << endl;
		cout << "Character codes" << endl;
		tree.PrintCodes();
		cin.get();
		cout << "----------" << endl;
		cout << "Print encoded message \"" << str << "\"" << endl;
		tree.PrintMessage();

		cout << endl << "Press enter when ready.";
		cin.get();
	}

	//Input file, Text.txt
	ifstream infile;
	ofstream outfile;
	infile.open("Text.txt");
	if (infile.fail()){
		exit(1);
	}
	tree.ClearTree();
	string str2 = "";
	do{
		string tempstr;
		getline(infile, tempstr);
		str2 += tempstr;
		if (!infile.eof()){
			str2 += "\n";
		}
	} while (!infile.eof());
	//cout << str2;

	cout << "Scanning Text.txt..." << endl;
	tree.ScanString(str2);
	cin.get();
	cout << "Characters and frequencies" << endl;
	tree.PrintList();

	int count = 1;
	cin.get();
	while (!tree.isComplete()){
		tree.BuildTreeOnce();
		cout << "----------" << endl;
		cout << "Building tree step " << count << "..." << endl;
		tree.PrintList();
		count++;
		cin.get();
	}
	infile.close();

	tree.EncodeTree();
	cout << "----------" << endl;
	cout << "Character codes" << endl;
	tree.PrintCodes();
	cin.get();
	cout << "----------" << endl;
	cout << "Print encoded message \"" << str2 << "\"" << endl;
	string codedMessage = tree.PrintMessage();
	outfile.open("CodedMessage.txt");
	//tree.PrintMessageToFile(outfile);
	outfile << codedMessage;
	outfile.close();

	//Decode to original file
	cout << endl;
	ifstream encodedFile;
	encodedFile.open("CodedMessage.txt");
	if (encodedFile.fail()){
		exit(1);
	}
	string encodedMessage;
	getline(encodedFile, encodedMessage);
	encodedFile.close();
	string decodedMessage = tree.DecodeMessage(encodedMessage);
	cout << decodedMessage;
	ofstream decodedFile;
	decodedFile.open("DecodedMessage.txt");
	decodedFile << decodedMessage;
	decodedFile.close();

	cin.get();
	return 0;
}