#include "calculator.h"
#include <cstdio>

namespace calc{
    Expression::Expression(std::string inputExpr){
        std::string expr = inputExpr;
    }  

    struct Node;

    BinaryTree::BinaryTree(){
                root = NULL;
    }

    int BinaryTree::Find(std::string target, Node* node){
        if (node == NULL){
            return false;
        }
        else if (node->data == target){
                return true;
        }
        if (node->right != NULL){
            return Find(target, node->right);
        }
        if (root->left != NULL){
            return Find(target, node->left);
        }
        return -1;
    }

    Node* BinaryTree::NewNode(std::string newData){
        Node* node = new Node;
        node->data = newData;
        node->left = NULL;
        node->right = NULL;
        return node;
    }

    void BinaryTree::Insert(std::string newData, Node* node){
        // node is empty (NULL pointer)
        if (node == NULL){
            *node = *BinaryTree::NewNode(newData);
        }
        // Left child is empty
        else if (node->left == NULL){
            Insert(newData, node->left);
        }
        // Right child is empty
        else if (node->right == NULL){
            Insert(newData, node->right);
        }
    }
}

