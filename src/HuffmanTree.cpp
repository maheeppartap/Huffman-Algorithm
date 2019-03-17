
#include "HuffmanTree.h"
#include <iostream>

// Constructor with weight and character
HuffmanTree::HuffmanTree(unsigned weight, unsigned char c) {
    root = new Node(c);
    this->weight = weight;
    this->height = 0;
}

// constructor with two trees and joining them together
HuffmanTree::HuffmanTree(const HuffmanTree &a, const HuffmanTree &b) {
    this->weight = a.weight + b.weight;
    this->height = (a.height > b.height) ? a.height:b.height +1;
    this->root = new Node(0);
    this->root->attachNodes(a.root,b.root);
}


//Default constructor
HuffmanTree::HuffmanTree() {
    this->weight = 0;
    this->root = NULL;
}


//Overloading < operator to compare the weights
bool operator<(const HuffmanTree &a, const HuffmanTree &b) {
    return a.weight < b.weight;
}


//overloading the <= operator to compare weights
bool operator<=(const HuffmanTree &a, const HuffmanTree &b) {
    return a.weight <= b.weight;
}


// Node constructor with a value
HuffmanTree::Node::Node(unsigned char val) {
    this->val = val;
    this->left = nullptr;
    this->right = nullptr;
}


//Attaching two nodes given their addresses
void HuffmanTree::Node::attachNodes(HuffmanTree::Node *left, HuffmanTree::Node *right) {
    this->left = left;
    this->right = right;
}


//Returns the value of the node
unsigned char HuffmanTree::Node::getVal() {
    return val;
}


//returns the address of the left node.
HuffmanTree::Node* HuffmanTree::Node::getLeft() {
    return left;
}


//returns the address of the right node
HuffmanTree::Node* HuffmanTree::Node::getRight() {
    return right;
}



void HuffmanTree::populateHuffCodeTable(std::string *table){
    char s[height];
    codeTab(root,s,0,table);
}


char HuffmanTree::getChar(std::ifstream& in, bool* done){
    static char c;
    static short n = 8;

    HuffmanTree::Node* node = root;

    for( ; ; ) {
        if(node->getVal() != 0){ //check if node is not 0
            if(node->getVal() == 128) *done = true; //if get value
            return node->getVal();
        }

        if(n >= 8){
            if(!in.get(c)){
                *done = true;
                return 0;
            }
            n = 0;
        }

        int path = 0x80 & c;
        if (path)
            node = node->getRight();
        else
            node = node->getLeft();
        c <<= 1;

        n++;
    }

}

void HuffmanTree::codeTab(HuffmanTree::Node* root, char* s,unsigned n,std::string table[129]) {
    if(root->getVal() != 0){
        std::string code;
        s[n] = 0;
        code = s;
        table[root->getVal()] = s;
        return;
    }

    s[n]= '0';
    codeTab(root->getLeft(),s,n+1,table);

    s[n] = '1';
    codeTab(root->getRight(),s,n+1,table);

}

