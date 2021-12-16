#include "calculator.h"
#include <cstdio>
#include <string>

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
}

