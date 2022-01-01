#include "calculator.h"
#include <cctype>
#include <cstdio>
#include <queue>
#include <stack>
#include <utility>

namespace calc{
    Expression::Expression(std::string inputExpr){
        expr = inputExpr;
    }  

    int Expression::StoreNumber(const int pos){
        int i = pos;
        while (i < (int)expr.size() && (std::isdigit(expr[i]) || expr[i] == '.')){
            tmpNumString.push_back(expr[i]);
            i++;
        }
        return i;
    }

    void Expression::ClearNumber(){
        tmpNumString.clear();
    }

    std::string Expression::CharToString(char chr){
        std::string str(1, chr);
        return str;
    }

    bool Expression::IsOperator(std::string chr){
        if (chr == CharToString('+') ||
                chr == CharToString('-') ||
                chr == CharToString('*') ||
                chr == CharToString('/') ||
                chr == CharToString('^')){
            return true;
        }
        return false;
    }

    bool Expression::IsLeftAssociative(std::string oper){
        if (oper == CharToString('-') ||
                oper == CharToString('/') ||
                oper == CharToString('+') ||
                oper == CharToString('*') ||
                oper == CharToString('^')){
            return true;
        }
        return false;
    }

    std::multimap<std::string, char> Expression::Tokenizer(){
        std::multimap<std::string, char> tokenMap;
        int loopJump = -1;   ///> Position to jump to when tokenizing a number.
        for (int i = 0; i < expr.size(); i++){
            if (IsOperator(CharToString(expr[i]))){
                tokenMap.insert(std::make_pair(CharToString(expr[i]), 'o'));
                loopJump = -1;
            }
            else if (expr[i] == '('){
                tokenMap.insert(std::make_pair(CharToString(expr[i]), 'l'));
                loopJump = -1;
            }
            else if (expr[i] == ')'){
                tokenMap.insert(std::make_pair(CharToString(expr[i]), 'r'));
                loopJump = -1;
            }
            else if (std::isdigit(expr[i]) && loopJump < i){
                loopJump = StoreNumber(i);
                tokenMap.insert(std::make_pair(CharToString(expr[i]), 'n'));
            }
            // implement function tokenization
        }
        return tokenMap;
    }

    int Expression::Precedence(std::string oper1, std::string oper2){
        char arr[10] = {'^','1','+','2','-','2','*','3','/','3'};   ///> Precedence array, lowest number means highest precedence.
        char arrPrecedence[2];  ///> Precedence of given operators, first value for 'oper1', second value for 'oper2'.
        for (int i = 0; i < 10; i += 2){
            if (oper1 == CharToString(arr[i])){
                arrPrecedence[0] = arr[i + 1];
            } else if (oper2 == CharToString(arr[i])){
                arrPrecedence[1] = arr[i + 1];
            }
        }
        if (arrPrecedence[0] < arrPrecedence[1]){
            return 1;
        } else if (arrPrecedence[1] < arrPrecedence[0]){
            return -1;
        } else {
            return 0;
        }
    }

    std::string Expression::PostfixConvert(){
        std::string convertedExpr;              ///> Postfix conversion of the expression.
        std::queue<std::string> outputQueue;    ///> First in, first out container.
        std::stack<std::string> operatorStack;  ///> Last in, first out container.
        std::multimap<std::string, char> tokens = Tokenizer();          ///> Tokens of items in the expression.

        for (const auto &pair : tokens){
            if (pair.second == 'n'){
                outputQueue.push(pair.first);
            }
            else if (pair.second == 'o'){
                while((IsOperator(operatorStack.top()) && operatorStack.top() != CharToString('(')) ){
                }
            }
        }
        return convertedExpr;
    }
    
    void Expression::DisplayPostfix(){
        std::string str = PostfixConvert();
        for (auto chr : str){
            std::cout << chr;
        }
        std::cout << '\n';
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

