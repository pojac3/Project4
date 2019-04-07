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

Tree::Tree(Tree const &toBeCopied) {
    data = new int[toBeCopied._size];
    _size = toBeCopied._size;
    for (int i = 0; i < _size; i++) {
        data[i] = toBeCopied.data[i];
    }
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
    
    for (int i = Level(node1) <= Level(node2) ? node1 : node2; Parent(i) != -1; i = Parent(i)) {
        for (int j = Level(node1) >= Level(node2) ? node1 : node2; Parent(j) != -1; j = Parent(j)) {
            if (i == j) {
                return i;
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
            cout << i << " ";
        }
    }
}

//prints the siblings of the given node
void Tree::printSiblings(int node) {
    for (int i = 0; i < size() - 1; i++) {
        if (Parent(i) == Parent(node)) {
            cout << i << " ";
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
            cout << i << " ";
        }
    }
}

//returns the level of the given node. Recursive
int Tree::Level(int node) {
    if (Parent(node) == -1) {
        return 1;
    } else {
        return 1 + Level(Parent(node));
    }
}

//returns the height of the tree
int Tree::height() {
    int currentHeight = 1;
    int tallestHeight = 1;
    int currentNode = 0;
    for (int i = 0; i < size(); i++) {
        while (currentNode != -1) {
            currentNode = Parent(currentNode);
            currentHeight++;
        }
        if (currentHeight > tallestHeight) {
            tallestHeight = currentHeight;
        }
        currentHeight = 1;
    }
    return tallestHeight;
}

//returns the size of the array, which is also equivalent to the number of nodes in the tree
int Tree::size() {
    return _size;
}

int main() {
    Tree* myTree;
    int numNodes,node,parent;
    
    cin >> numNodes;
    myTree = new Tree(numNodes);
    
    for (int i = 0; i < numNodes; i++) {
        cin >> node >> parent;
        (*myTree).setParent(node, parent);
        if (parent == -1) {
            (*myTree).setRoot(node);
        }
    }
    
    cout << "The tree that we just read is: " << endl;
    cout << (*myTree) << endl;
    
    Tree* newTree = new Tree(*myTree);
    cout << "The tree that we just copied is: " << endl;
    cout << (*newTree) << endl;
     
    cout << "The root of the tree is: " << (*myTree).Root() << endl;
    
    cout << "The least common ancestor of nodes 3 and 8 is: " << (*myTree).LCA (3,8) << endl;
    cout << "The least common ancestor of nodes is: " << (*myTree).LCA (13,8) << endl;
    cout << "The least common ancestor of nodes is: " << (*myTree).LCA (13,11) << endl;
    
    cout << "The children of node 12 is/are: " << endl; 
    (*myTree).printChildren(12);
    cout << endl;
    
    cout << "The children of node 10 is/are: " << endl; 
    (*myTree).printChildren(10);
    cout << endl;
    
    cout << "The siblings of node 3 is/are: " << endl; 
    (*myTree).printSiblings(3);
    cout << endl;
    
    cout << "The siblings of node 12 is/are: " << endl; 
    (*myTree).printSiblings(12);
    cout << endl;

    cout << "The nodes at level 3 is/are: " << endl; 
    (*myTree).nodesAtLevel(3);
    cout << endl;
    
    cout << "The height of the tree is: " << (*myTree).height() << endl;
    
    cout << "The level of node 3 in the tree is: " << (*myTree).Level(3) << endl;
    cout << "The level of node 12 in the tree is: " << (*myTree).Level(12) << endl;
    
    /*
    cout << "The preorder traversal of the tree is/are" << endl;
    (*myTree).Preorder();
    cout << endl;
    */
     
    delete myTree;
    delete newTree;
    
    return 0;
}
