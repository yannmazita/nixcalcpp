#include "calculator.h"
#include <cstdio>

namespace calc{
    Expression::Expression(std::string inputExpr){
        std::string expr = inputExpr;
    }  

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

    struct Node* BinaryTree::NewNode(std::string newData){
        class Node* node = new(struct Node);
        node->data = newData;
        node->left = NULL;
        node->right = NULL;
        return node;
    }

    struct Node* BinaryTree::Insert(struct Node* node, std::string newData){
        // node is empty (NULL pointer)
        if (node == NULL){
            return BinaryTree::NewNode(newData);
        }
        // Left child is empty
        else if (node->left == NULL){
            node->left = BinaryTree::Insert(node->left, newData);
        }
        // Right child is empty
        else if (node->right == NULL){
            node->right = BinaryTree::Insert(node->right, newData);
        }
        return node;
    }
}

