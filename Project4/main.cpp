//
//  main.cpp
//  Project4
//
//  Created by Jacob Courtney on 3/31/19.
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
    Tree();
    Tree(int numberOfNodes);
    Tree(Tree const &toBeCopied);
    virtual ~Tree();
    friend ostream &operator << (ostream&, Tree &M);
    int LCA(int node1,int node2);
    void printParent(int node);
    int Parent(int node);
    void printChildren(int node);
    void printSiblings(int node);
    int Root();
    void setRoot(int rootNode);
    void setParent(int node, int parent);
    void nodesAtLevel(int level);
    int Level(int node);
    int height();
    //void Preorder();
    
    //helper methods
    int size();
protected:
    int _size;
    int* data;
};

/**
 *  C O N S T R U C T O R / D E S T R U C T O R =================================================================== C O N S T R U C T O R / D E S T R U C T O R
 */
Tree::Tree() {
    data = new int[0];
};

Tree::Tree(int numberOfNodes) {
    data = new int[numberOfNodes];
    _size = numberOfNodes;
};

Tree::~Tree() {
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
    int levelOfLCA, currentParent1, currentParent2;
    currentParent1 = node1;
    currentParent2 = node2;
    
    levelOfLCA = Level(node1) <= Level(node2) ? node1 - 1:node2 - 1; //DEPRECATED
    
    for (int i = Level(currentParent1) <= Level(currentParent2) ? currentParent1 : currentParent2; Parent(i) != -1; i = Parent(i)) {
        for (int j = Level(currentParent1) >= Level(currentParent2) ? currentParent1 : currentParent2; Parent(j) != -1; j = Parent(j)) {
            if (currentParent1 == currentParent2){
                return currentParent1;
            } 
        }
    }
    
    return Root();
}

//prints the parent of the given node to the console
void Tree::printParent(int node) {
    cout << data[node];
}

//returns the parent of the given node as an int
int Tree::Parent(int node) {
    return data[node];
}

//prints the children of the given node
void Tree::printChildren(int node) {
    for (int i = 0; i < size() - 1; i++) {
        if (Parent(i) == node) {
            cout << node << " ";
        }
    }
}

//prints the siblings of the given node
void Tree::printSiblings(int node) {
    for (int i = 0; i < size() - 1; i++) {
        if (Parent(i) == Parent(node)) {
            cout << node << " ";
        }
    }
}

//gives the Root of the tree in int format
int Tree::Root() {
    int _root = -1;
    
    for (int i = 0; i < size() -1; i++) {
        if (data[i] == -1) {
            _root = i;
        }
    }
    
    return _root;
}

//sets the root of the tree to the specified node
void Tree::setRoot(int rootNode) {
    data[rootNode] = -1;
}

//sets the parent of the node to the specified node
void Tree::setParent(int node, int parent) {
    data[node] = parent;
}

//prints out all the nodes at the specified level
void Tree::nodesAtLevel(int level) {
    for (int i = 0; i < size() - 1; i++) {
        if (Level(i) == level) {
            cout << data[i] << " ";
        }
    }
}

int main() {
    
    
    return 0;
}
