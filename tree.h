#pragma once
#include "Node.h"
#include <iostream>
#include <iomanip>
using namespace std;

//to implement file and directories
class tree
{
	Node* root;
public:

	tree() {
		root = nullptr;
	}

	tree(Node* r) {
		root = r;
	}

	//function to create new directory
	//specifying only left child of tree for directories
	void newDir(Node*& n) {

		//user should be able to specify directory name
		string Dname;
		cout << "Enter the name of the directory: " << endl;
		getline(cin, Dname);

		//create a new directory node
		Node* Dir = new Node(Dname, "", "directory");

		if (n == nullptr) {
			n = Dir;
		}
		else {
			Node* curr = n;
			while (true) {

				cout << "Enter the position for new dir" << endl;

				string position;
				getline(cin, position);

				if (position == "left") {
					if (curr->getleft() == nullptr) {
						curr->setleft(Dir);
						break;
					}
					else {
						curr = curr->getleft();
					}
				}
				else if (position == "right") {
					if (curr->getright() == nullptr) {
						curr->setright(Dir);
						break;
					}
					else {
						curr = curr->getright();
					}
				}
				else {
					cout << "Invalid position.Please try again" << endl;
				}
			}


			//creating children for new dir
			cout << "Creating children for " << Dir->getName() << ":" << endl;

			//its left child would be a directory but its right child would be a new fil

			//creating new directory as the left child

			if (curr != nullptr) {
				newDir(curr->left);
				//create a new file as the right child
				newFile(curr->right);
			}
			else {
				cout << "Current is null" << endl;
			}
		}
	}


	//display function 
	void displayTree(Node* root) {
		if (root == nullptr) {
			cout << "Tree is empty." << endl;
			return;
		}

		cout << "Root: " << root->getName() << endl;

		if (root->getleft() != nullptr) {
			cout << "Left Child: " << root->getleft()->getName() << endl;
		}
		else {
			cout << "Left Child: None" << endl;
		}

		if (root->getright() != nullptr) {
			cout << "Right Child: " << root->getright()->getName() << endl;
		}
		else {
			cout << "Right Child: None" << endl;
		}
	}


	//function to create new files within the tree, 
	// allowing users to specify the name, type
	//(e.g., txt, pdf), and complete path.

	void newFile(Node*& node) {

		// path
		string filePath;
		cout << "Enter complete path of  file" << endl;
		//cin.ignore();
		getline(cin, filePath);

		//checking if path is already exist treverse through
		//already existed tree and go through each directory mention and
		//check if file area is empty or not
		//Example /PatientsData PatientsHome Report.txt
		//it should check from root / PatientsData node and then PatientsHome node and
		//if PatientsHome left child is empty insert file in it

		Node* curr = node;

		if (curr == nullptr) {
			cout << "Curr node is empty" << endl;
			return;
		}

		size_t startP = 0;
		size_t endP = filePath.find('/');
		while (endP != string::npos) {
			string dir = filePath.substr(startP, endP - startP);
			startP = endP + 1;

			if (curr->getleft() && curr->getleft()->getName() == dir
				&& !curr->getleft()->getright()) {
				curr = curr->getleft();
			}
			else {
				cout << "Error"
			}

		}
	string fileName;
		cout << "Enter the name of the file: " << endl;
		getline(cin, fileName);

		//taking actuall file type
		string fileType;
		cout << "Enter the type of the file (txt/pdf): " << endl;
		getline(cin, fileType);

		Node* fileNode = new Node(fileName, filePath, fileType);
	}


   //function 3
	//listing directory tree in a tree view (level order)
	void listHelper(Node* node, int level) {
		if (node == nullptr) {
			return;
		}
		//printing node info
		cout << "level " << level << "Name: "
			<< node->getName() << "Path: " << node->getPath()
			<< "Type: " << node->getType() << endl;

		listHelper(node->getleft(), level + 1);
		listHelper(node->getright(), level + 1);
	}

	void listDirTree() {
		if (root == nullptr){
			cout << "Tree is empty" << endl;
			return;
		}
		cout << "listing Directory Tree: " << endl;

		int level = 0;
		listHelper(root, level);
	}

	//function 4
	void merge(){
		//Destination directory
		string destination;
		cout << "Enter destination directory" << endl;
		cin >> destination;

		string source;
		//source directory whose content want to merge
		cout << "Enter source directory" << endl;
		cin >> source;


		//searching for nodes 
		Node* destN = searchHelp(root, destination);
		Node* sourceN = searchHelp(root, source);


		//checking both above has ither 1 or zero child
		if (destN != nullptr && sourceN != nullptr
			&& (destN->getleft() == nullptr || destN->getright() == nullptr) &&
			(sourceN->getleft() == nullptr || sourceN->getright() == nullptr))
			{
			cout << "Merge successfully" << endl;

			cout << "Want to rename file or keeping previous" << endl;
			cout << "1. Rename " <<endl;
			cout << "2. Old name" << endl;
			
			int choice;
			cin >> choice;


			if (choice == 1) {
				string NewName;
				cout << "Enter the new name for the desitanation" << endl;
				cin >> NewName;

				//renaming
				destN->name = NewName;
			}

			if (destN->getleft() == nullptr) {
				destN->setleft(sourceN->getleft());
			}
			else {
				destN->setright(sourceN->getleft());
			}

			delete sourceN;
			
		}
		else {
			cout << "Merge failed" << endl;
		}
	}


	//deleting file
	void del(Node*  Parent ,Node* curr, string& fileName){
		if (curr == nullptr) {
			cout << "File not found" << endl;
			return;

		}

		//delete node and assign null to 
		//corresponding reference in parent node
		if (curr->getName() == fileName) {
			//in the right child restricted files as above
			if (Parent == nullptr){
				delete curr;
				curr = nullptr;
			} else {
				if (Parent->getleft() == curr) {
					delete curr;
					Parent->setleft(nullptr);
				}
				else if (Parent->getright() == curr) {
					delete curr;
					Parent->setright(nullptr);
			  }
			}
			cout << "File deleted successfully." << endl;
			return;
		}

		del(curr, curr->getleft(), fileName);
		del(curr, curr->getright(), fileName);
	}


	//deleting folder
	//function 6
	void delFolder(Node* curr){
      //check if  folder is empty
      // delete if empty
		if (curr == nullptr) {
			cout << "Folder not found." << endl;
			return;
		}

		if (curr->getType() != "directory") {
			cout << "This node is not directory" << endl;
			return;
		}
	
		if (curr->getleft() == nullptr && curr->getright() == nullptr) {
			delete curr;
			cout << "Folder deleted successfully." << endl;
			return;
		}

		//if not empty ask if need to merge with any other
			
			if (curr != nullptr) {
				cout << "Do you want to merge ?" << endl;
				cout << "1. Merge" << endl;
				cout << "2. Delete whole subtree" << endl;

				int choice;
				cin >> choice;

				if (choice == 1) {
					merge();
					cout << "Folder merged successfully" << endl;
				}
				else {
					//deleting whole subtree
					delSubtree(curr);
					cout << "Subtree deleted successfully" << endl;
				}
				cout << "not deleted" << endl;
			}
		}


	void delSubtree(Node* curr){
		if (curr == nullptr){
			return;
		}

		//Recursively delete the left and right
		delSubtree(curr->getleft());
		delSubtree(curr->getright());

		delete curr;
	}

	//search
	//take file name and print out path
	//take directory name and print true or false
	Node* searchHelp(Node* curr, string& Cname){
		//for file
		//for directory
		if (curr == nullptr) {
			return nullptr;
		}

		//checking name
		if (curr->getName() == Cname){
			return curr;
		}

		//recursively searching tree left side
		Node* leftC = searchHelp(curr->getleft(), Cname);
		if (leftC != nullptr) {
			return leftC;
		}

		Node* rightC = searchHelp(curr->getright(), Cname);
		if (rightC != nullptr) {
			return rightC;
		}

		return nullptr;
	}

	  bool searchByName(Node* node ,string& name){
		Node* res = searchHelp(node, name);
		return res != nullptr;
	  }


	  //searching
	  void searchByContent(Node* curr, string& name, string path = "") {
		  //getting name odf the file along with type (extension)
		  //and returning path of the file

		  if (curr == nullptr) {
			  return;
		  }

		  //as files are restricted to the right child
		  if (curr->getName() == name) {
			  cout << path + curr->getName() << endl;
			  return;
		  }

		  //recursively seraching right subtree
		  searchByContent(curr->getright(), name, path + curr->getName() + "/");

		  searchByContent(curr->getleft(), name, path);
	  }

	//for copying and moving
	void copy(){
		//-take file name and destination directory from user
		string fileName;
		cout << "Enter file name you want to copy" << endl;
		cin >> fileName;

		string des;
		cout << "Enter destination directory in which you want to copy" << endl;
		cin >> des;

		Node* findFile = searchHelp(root, fileName);
		Node* desFolder = searchHelp(root, des);

		if (findFile == nullptr) {
			cout << "File not found" << endl;
			return;
		}

		//checking if directory is not full
		if (desFolder == nullptr || desFolder->getType() != "directory") {
			cout << "Invalid destination" << endl;
			return;
		}

		if (desFolder->getright() != nullptr) {
			cout << "Destination directory is full" << endl;
			return;
		}

		//creating copy
		Node* copy = new Node();
		copy->setName(findFile->getName());
		copy->setType("file");

		//- copy file if space available
		if (desFolder->getright() == nullptr){
			//copy if space is available
			desFolder->setleft(copy);
		}
		else {
			cout << "File should not be copied in"
				<< "left child as restriced for directories" << endl;
		}
		cout << "File copied successfully" << endl;
	}


	void move(){
		//-take file name and destination directory from user
		string fileName;
		cout << "Enter file name you want to copy" << endl;
		cin >> fileName;

		string des;
		cout << "Enter destination directory in which you want to copy" << endl;
		cin >> des;

		Node* findFile = searchHelp(root, fileName);
		Node* desFolder = searchHelp(root, des);

		if (findFile == nullptr){
			cout << "File not found" << endl;
			return;
		}

		//checking if directory is not full
		if (desFolder == nullptr || desFolder->getType() != "directory") {
			cout << "Invalid destination" << endl;
			return;
		}

		if (desFolder->getright() != nullptr) {
			cout << "Destination directory is full" << endl;
			return;
		}

		//removing file node from its current location 
		removeFile(findFile);

		//Add the file node to des directory
		desFolder->right = findFile;

		cout << "File moved successfully" << endl;

		//chcking source directory
		Node* sourceD = nullptr;
		if (sourceD != nullptr && sourceD->getType() == "directory") {
			if (sourceD->getleft() == nullptr && sourceD->getright() == nullptr) {
				cout << "source directory is nowempty" << endl;
				cout << "1. Yes" << endl;
				cout << "2. No" << endl;

				int choice;
				cin >> choice;

				if (choice == 1) {
					delFolder(sourceD);
					cout << "Source directory deleted successfully" << endl;

				}
			}
		}
	}

	void removeFile(Node* fileNode){
		if (fileNode == nullptr){
			return;
		}

		Node* curr = root;
		//Node that pointed to file node
		Node* file = nullptr;
		while (curr != nullptr){
			if (curr->getleft() == fileNode || curr->getright() == fileNode) {
				file = curr;
				break;
			}

			if (fileNode < curr) {
				curr = curr->getleft();
			}
			else {
				curr = curr->getright();
			}
		}
		//removing
		if (file != nullptr) {
			if (file->getleft() == fileNode) {
				file->setleft(nullptr);

			}else if (file->getright() == fileNode) {
				file->setright(nullptr);
			}
		}
	}

	//import and export
	void importTree(){

	}
	void exportTree(){

	}
};
