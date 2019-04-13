//
//  main.cpp
//  Project4
//
//  Created by Jacob Courtney on 3/31/19 for CS 2413 at the University of Oklahoma.
//  Copyright © 2019 Jacob Courtney. All rights reserved.
//

#include <iostream>
using namespace std;

/**
 * D E C L A R A T I O N =============================================================================================================== D E C L A R I T I O N
 */
class Tree {
public:
    //Project methods
    Tree(); //default constructor
    Tree(int numberOfNodes); //creates a tree with numberOfNodes number of nodes
    Tree(Tree const &toBeCopied); //copy constructor
    virtual ~Tree(); //destructor
    friend ostream &operator << (ostream&, Tree &M); //ostream operator
    int LCA(int node1, int node2); //finds the least common ancestor and returns that node as an int
    void printParent(int node); //prints the parent of the specified node to the console
    int Parent(int node); //returns the parent of the specified node as an int
    void printChildren(int node); //prints the children of the specified node to the console
    void printSiblings(int node); //prints the siblings of the specified node to the console
    int Root(); //returns the root of the tree as an int
    void setRoot(int rootNode); //sets the root of the tree to the specified node
    void setParent(int node, int parent); //sets the parent of the specified node to the specified parent
    void nodesAtLevel(int level); //prints all of the nodes at the specified level to the console
    int Level(int node); //finds the level of the specified node and returns it as an int
    int height(); //returns the height of the tree as an int
    void Preorder(); //prints the preorder traversal of the tree to the console
    
    //helper methods
    int size(); //returns the number of nodes in the tree, which is equivalent to the size of the data array, as an int
    void preorderOnNode(int node); //helper method for the Preorder method
protected:
    int _size; //stores the number of nodes in the tree
    int* data; //main array that stores the tree
};

/**
 *  C O N S T R U C T O R / D E S T R U C T O R =================================================================== C O N S T R U C T O R / D E S T R U C T O R
 */

//default constructor sets the size of the tree to 0
Tree::Tree() {
    data = new int[0];
    _size = 0;
};

//regular constructor takes in the number of nodes and makes that the size of the tree
Tree::Tree(int numberOfNodes) {
    data = new int[numberOfNodes];
    _size = numberOfNodes;
};

//copy constructor takes in another tree and deep copies it
Tree::Tree(Tree const &toBeCopied) {
    data = new int[toBeCopied._size];
    _size = toBeCopied._size;
    for (int i = 0; i < _size; i++) {
        data[i] = toBeCopied.data[i];
    }
};

//destructor basically just deletes the data array
Tree::~Tree() {
    delete[] data;
};

/**
 * P R O J E C T  M E T H O D S ================================================================================================== P R O J E C T  M E T H O D S
 */

//the ostream operator for a Tree object
ostream& operator << (ostream& output, Tree &M) {
    for (int i = 0; i < M.size(); i++) {
        output << "" << i << ": " << M.data[i] << " ";
    }
    return output;
}

//returns the least common ancestor given two nodes
int Tree::LCA(int node1, int node2) {
    
    //weird for loops, yes. i is set to the higher level node, j is set to the lower level node
    //the condition the loops are checking for is that the parent of the current node isnt the root
    //the increment increments up to the current nodes parent
    for (int i = Level(node1) <= Level(node2) ? node1 : node2; Parent(i) != -1; i = Parent(i)) {
        for (int j = Level(node1) >= Level(node2) ? node1 : node2; Parent(j) != -1; j = Parent(j)) {
            //if the two nodes are equivalent, then the LCA has been found. 
            if (i == j) {
                //this return statement could be set to return either i or j, since they would be equal
                return i;
            } 
        }
    }
    
    //defaults to root if for some reason the LCA wasnt found. but it should be found in all cases
    return Root();
}

//prints the parent of the given node to the console
void Tree::printParent(int node) {
    //just a simple cout statement
    cout << data[node];
}

//returns the parent of the given node as an int
int Tree::Parent(int node) {
    //just gets it from the data array
    return data[node];
}

//prints the children of the given node
void Tree::printChildren(int node) {
    //loops through the data array
    for (int i = 0; i < size() - 1; i++) {
        //if the parent of the current node is the node..
        if (Parent(i) == node) {
            //then cout that guy!
            cout << i << " ";
        }
    }
}

//prints the siblings of the given node
void Tree::printSiblings(int node) {
    //loops through the data array
    for (int i = 0; i < size() - 1; i++) {
        //if the parent of the current node is equal to the parent of node (and they arent the same node)..
        if (Parent(i) == Parent(node) && i != node) {
            //then cout that guy!
            cout << i << " ";
        }
    }
}

//gives the Root of the tree in int format
int Tree::Root() {
    //going to keep track of where we are
    int _root = -1;
    
    //looping through the data array
    for (int i = 0; i < size() -1; i++) {
        //if the parent of the current node is -1..
        if (Parent(i) == -1) {
            //then set that guy equal to _root!
            _root = i;
        }
    }
    //returning _root
    return _root;
}

//sets the root of the tree to the specified node
void Tree::setRoot(int rootNode) {
    //just setting it to the specified index in the array
    data[rootNode] = -1;
}

//sets the parent of the node to the specified node
void Tree::setParent(int node, int parent) {
    //just setting it to the specified index in the array
    data[node] = parent;
}

//prints out all the nodes at the specified level
void Tree::nodesAtLevel(int level) {
    //looping through the data array
    for (int i = 0; i < size() - 1; i++) {
        //if the level of the current node is equal to the level were looking for..
        if (Level(i) == level) {
            //then cout that guy!
            cout << i << " ";
        }
    }
}

//helper method for Preorder
void Tree::preorderOnNode(int node) {
    //printing out the current node
    cout << node << " ";
    //loops through and prints the childrens preorder traversals from smallest to biggest
    for (int i = 0; i < size(); i++) {
        //if this node is the parent of node i
        if (Parent(i) == node) {
            //then recursively call this method
            preorderOnNode(i);
        }
    }
}

//prints out the preorder traversal of the tree
void Tree::Preorder() {
    //simply starts the preorder recursive traversal at the root
    preorderOnNode(Root());
}

//returns the level of the given node. Recursive
int Tree::Level(int node) {
    //if we are at the root node..
    if (Parent(node) == -1) {
        //then the level is equal to 1 so we will return that
        return 1;
    } else {
        //otherwise add 1 to the level of the parent of that node
        return 1 + Level(Parent(node));
    }
}

//returns the height of the tree
int Tree::height() {
    //the height of the current node
    int currentHeight = 1;
    //the tallest height weve found so far
    int tallestHeight = 1;
    //the current node we are on
    int currentNode = 0;
    
    //looping through the data array
    for (int i = 0; i < size(); i++) {
        //so long as we arent past the root
        while (currentNode != -1) {
            //get the parent of the current node
            currentNode = Parent(currentNode);
            //and increment the current height
            currentHeight++;
        }
        //comparing the height from the current node to the tallest one found so far
        if (currentHeight > tallestHeight) {
            //change it if its different
            tallestHeight = currentHeight;
        }
        //reset the current height
        currentHeight = 1;
    }
    //returning the tallest one found
    return tallestHeight;
}

//returns the size of the array, which is also equivalent to the number of nodes in the tree
int Tree::size() {
    //returning the size
    return _size;
}

int main() {
    //instantiating variables
    Tree* myTree;
    int numNodes,node,parent;
    
    //getting the total number of nodes
    cin >> numNodes;
    //creating the tree with that number of nodes
    myTree = new Tree(numNodes);
    
    //this loop gets a parent for each node
    for (int i = 0; i < numNodes; i++) {
        //taking it in
        cin >> node >> parent;
        //setting the parent
        (*myTree).setParent(node, parent);
        if (parent == -1) {
            //using the set root method for the one whos parent is -1
            (*myTree).setRoot(node);
        }
    }
    
    //testing that we read the tree properly
    cout << "The tree that we just read is: " << endl;
    cout << (*myTree) << endl;
    
    //testing that the copy constructor works
    Tree* newTree = new Tree(*myTree);
    cout << "The tree that we just copied is: " << endl;
    cout << (*newTree) << endl;
     
    //testing that the root method works
    cout << "The root of the tree is: " << (*myTree).Root() << endl;
    
    //testing that LCA works
    cout << "The least common ancestor of nodes 3 and 8 is: " << (*myTree).LCA (3,8) << endl;
    cout << "The least common ancestor of nodes is: " << (*myTree).LCA (13,8) << endl;
    cout << "The least common ancestor of nodes is: " << (*myTree).LCA (13,11) << endl;
    
    //testing that the children method works
    cout << "The children of node 12 is/are: " << endl; 
    (*myTree).printChildren(12);
    cout << endl;
    
    cout << "The children of node 10 is/are: " << endl; 
    (*myTree).printChildren(10);
    cout << endl;
    
    //testing that the siblings method works
    cout << "The siblings of node 3 is/are: " << endl; 
    (*myTree).printSiblings(3);
    cout << endl;
    
    cout << "The siblings of node 12 is/are: " << endl; 
    (*myTree).printSiblings(12);
    cout << endl;
    
    //testing that nodesAtLevel works
    cout << "The nodes at level 3 is/are: " << endl; 
    (*myTree).nodesAtLevel(3);
    cout << endl;
    
    //testing that the height method works
    cout << "The height of the tree is: " << (*myTree).height() << endl;
    
    //testing that the Level method works
    cout << "The level of node 3 in the tree is: " << (*myTree).Level(3) << endl;
    cout << "The level of node 12 in the tree is: " << (*myTree).Level(12) << endl;
    
    //testing that preorder works
    cout << "The preorder traversal of the tree is/are" << endl;
    (*myTree).Preorder();
    cout << endl;
     
    //deleting the trees at the end of the program
    delete myTree;
    delete newTree;
    
    //returing 0
    return 0;
}
