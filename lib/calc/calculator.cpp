#include "calculator.h"
#include <cstdio>

namespace calc{
    Expression::Expression(std::string inputExpr){
        std::string expr = inputExpr;
    }  

    int Node::Find(class Node* root, std::string target){
        if (root == NULL){
            return false;
        }
        else if (root->data == target){
                return true;
        }
        if (root->right != NULL){
            return Find(root->right, target);
        }
        if (root->left != NULL){
            return Find(root->left, target);
        }
        return -1;
    }

    class Node* Node::NewNode(std::string newData){
        class Node* node = new(class Node);
        node->data = newData;
        node->left = NULL;
        node->right = NULL;
        return node;
    }

    class Node* Node::Insert(class Node* node, std::string newData){
        // node is empty (NULL pointer)
        if (node == NULL){
            return Node::NewNode(newData);
        }
        // Left child is empty
        else if (node->left == NULL){
            node->left = Node::Insert(node->left, newData);
        }
        // Right child is empty
        else if (node->right == NULL){
            node->right = Node::Insert(node->right, newData);
        }
        return node;
    }
}

