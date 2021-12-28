#include "calculator.h"
#include <cctype>
#include <cstdio>
#include <queue>
#include <stack>

namespace calc{
    Expression::Expression(std::string inputExpr){
        expr = inputExpr;
    }  

    void Expression::StoreNumber(const int pos){
        tmpNumString.push_back(expr[pos]);
    }

    void Expression::ClearNumber(){
        tmpNumString.clear();
    }

    std::string Expression::CharToString(const char chr){
        std::string str(1, chr);
        return str;
    }

    bool Expression::IsOperator(std::string chr){
        if (chr == CharToString('+') ||
                chr == CharToString('-') ||
                chr == CharToString('*') ||
                chr == CharToString('/')){
            return true;
        }
        return false;
    }

    bool Expression::IsLeftAssociative(std::string oper){
        if (oper == CharToString('-') ||
                oper == CharToString('/') ||
                oper == CharToString('+') ||
                oper == CharToString('*')){
            return true;
        }
        return false;
    }

    int Expression::Precedence(std::string oper1, std::string oper2){

        return 0;
    }

    std::string Expression::PostFixConvert(){
        std::string convertedExpr;              ///> Postfix conversion of the expression.
        std::queue<std::string> outputQueue;    ///> First in, first out container.
        std::stack<std::string> operatorStack;  ///> Last in, first out container.

        for (int i = 0; i < expr.size(); i++){
            if (std::isdigit(expr[i])){
                StoreNumber(expr[i]);
                if (i == expr.size() - 1){
                    outputQueue.push(tmpNumString);
                    ClearNumber();
                }
            }
            else{
                std::string curChar = CharToString(expr[i]);   ///> Conversion of current character to string.
                if (IsOperator(curChar)){
                    /* Push stored number to 'outputQueue' then clear it.
                     * This is done to push numbers that have yet to be pushed when encountering an operator.
                     */
                    if (tmpNumString.size() != 0){
                       outputQueue.push(tmpNumString);
                        ClearNumber();
                    }
                    while ((IsOperator(operatorStack.top()) && operatorStack.top() != CharToString('(')) &&
                            ((Precedence(operatorStack.top(), curChar) == 1 ||
                              (Precedence(operatorStack.top(), curChar) == 0 && IsLeftAssociative(curChar))))){
                        outputQueue.push(operatorStack.top());
                        operatorStack.pop();
                    }
                }
            }

        }

        return convertedExpr;
    }

    struct Node{
        std::string data;
        Node* left;
        Node* right;
    };

    BinaryTree::BinaryTree(){
        root = NULL;
    }

    int BinaryTree::Find(std::string target, Node* &node){
        if (node == NULL){
            return false;
        }
        else if (node->data == target){
                return true;
        }
        if (node->right != NULL){
            return BinaryTree::Find(target, node->right);
        }
        if (root->left != NULL){
            return BinaryTree::Find(target, node->left);
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

    void BinaryTree::Insert(std::string newData, Node* &node){
        // node is empty (NULL pointer)
        if (node == NULL){
            node = BinaryTree::NewNode(newData);
        }
        // Left child is empty
        else if (node->left == NULL){
            BinaryTree::Insert(newData, node->left);
        }
        // Right child is empty
        else if (node->right == NULL){
            BinaryTree::Insert(newData, node->right);
        }
        // 
        else{
            BinaryTree::Insert(newData, node->right);
        }
    }
    // Public acces methods
    int BinaryTree::IsTargetInTree(std::string target){
        return BinaryTree::Find(target, root);
    }

    void BinaryTree::InsertTarget(std::string newData){
        BinaryTree::Insert(newData, root);
    }
}

