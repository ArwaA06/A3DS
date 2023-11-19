// A3DS.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Arwa Ahmed_i222676_SE(C)_A3

#include <iostream>
#include <iomanip>
#include <fstream>
#include "tree.h"
#include "Node.h"
using namespace std;

int main(){
      
    //creating new file for writing
    ofstream  file("myTree.txt");

    if (!file.is_open()){
        cout << "Error opening file" << endl;
        return 1;
    }

    tree myTree;

    //creating root directory
    Node* root = nullptr;

    cout << "Choose amoung following operations:" << endl;
    cout << "1. Creating directory" << endl;
    cout << "2. Creating file" << endl;
    cout << "3. Search by name" << endl;
    cout << "4. Search by content" << endl;
    cout << "5. List directory tree" << endl;
    cout << "6. Merge" << endl;
    cout << "7. Delete File" << endl;
    cout << "8. Delete Folder" << endl;
    cout << "9. Copy file" << endl;
    cout << "10. move file" << endl;
    cout << "11. export tree" << endl;
    cout << "12. import tree" << endl;

    int choice;
    while(true){
        cout << "Enter your choice" << endl;
        cin >> choice;
        cin.ignore();

        switch(choice){
        case 1: {
            myTree.newDir(root);
            //checking creation
            if (root != nullptr) {
                cout << "Directory created successfully" << endl;
            }
            else {
                cout << "root is null" << endl;
            }
            cout << "Tree structure" << endl;
            myTree.displayTree(root);
            //taking left and right child
            break;
        }

        case 2: {
            //function 2 call
            myTree.newFile(root);
            break;
        }
        case 3:
        {
            //function 3 call
            //Calling the search by name
            string nameS;
            cout << "enter the name to search: ";
            cin >> nameS;
            cin.ignore();
            myTree.searchByName(root, nameS);
            break;
        }
        case 4:
        {
            //Calling the search by content
            string FileName;
            cout << "Enter the fileName to search" << endl;
            getline(cin, FileName);
            myTree.searchByContent(root, FileName);
            break;
        }
        case 5: {
            // function 5 call
            myTree.listDirTree();
            break;
        }
        case 6: {
            //function 6 call
            //merging
            myTree.merge();
            break;
        }
        case 7:
        {
            //function 7 call
            string fileName;
            cout << "Enter the name of the file you want to delete" << endl;
            getline(cin, fileName);
            // deleting file
            myTree.del(nullptr, root, fileName);
            break;
        }
        case 8:
        {
            //function 8 call
            string folderN;
            cout << "Enter directory name you want to delete" << endl;
            cin.ignore();
            getline(cin, folderN);

            Node* folder = myTree.searchHelp(root, folderN);

            if (folder != nullptr) {
                myTree.delFolder(folder);
                cout << "Folder deleted successfully" << endl;
            }
            else {
                cout << "Folder not found" << endl;
            }
            break;
        }

        case 9: {
            //function 9 call
            myTree.copy();
            break;
        }
        case 10: {
            //function 10 call
            myTree.move();
            break;
        }
        case 11: {
            //function 11 call
            //export
            break;
        }
        case 12: {
            //function 12 call
            //import
            break;
        }
        default:
            cout << "Invalid choice.Please try again" << endl;
            break;
        }
    }

    //function 8 call
    cout << "open" << endl;
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
