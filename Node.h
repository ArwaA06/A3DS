#pragma once
#include <string>
#include <iomanip>
#include <iostream>
using namespace std;

class Node
{
public:
	string name;
	string path;
	string type;
	//Node* child;
	Node* left;
	Node* right;
	
public:

	Node(){
		name = "";
		path = "";
		type = "";
		//child = nullptr;
		left = nullptr;
		right = nullptr;
	}

	Node(string n,string p ,string t) {
		name = n;
		path = p;
		type = t;
		//child = nullptr;
		left = nullptr;
		right = nullptr;
	}

	//Functions
	string getName(){
		return name;
	}
	string getPath(){
		return path;
	}
	string getType(){
		return type;
	}

	Node* getleft(){
		return left;
	}

	Node* getright() {
		return right;
	}

	void setName(string n) {
		name = n;
	}

	void setType(string t) {
		type = t;
	}
	
	void setleft(Node* l){
		left = l;
	}

	void setright(Node* r) {
	    right = r;
	}

	//adding new child
	void addChild(Node* child){

	}

};

