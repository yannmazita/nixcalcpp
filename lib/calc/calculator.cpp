#include "calculator.h"
#include <cctype>
#include <cstdio>

namespace calc{
    Expression::Expression(std::string inputExpr){
        infixExpr = inputExpr;
    }  

    int Expression::StoreNumber(const int pos, std::string type){
        int i = pos;
        if (type == "in"){
            while (i < (int)infixExpr.size() && (std::isdigit(infixExpr[i]) || infixExpr[i] == '.')){
                tmpNumString.push_back(infixExpr[i]);
                i++;
            }
        } else if (type == "post"){
            while (i < (int)postfixExpr.size() && (std::isdigit(postfixExpr[i]) || postfixExpr[i] == '.')){
                tmpNumString.push_back(postfixExpr[i]);
                i++;
            }
        }
        return i;
    }

    void Expression::ClearNumber(){
        tmpNumString.clear();
    }

    std::string Expression::BuildStringFromChar(char character){
        std::string str{character};
        return str;
    }

    bool Expression::IsOperator(std::string chr){
        if (chr == BuildStringFromChar('+') ||
                chr == BuildStringFromChar('-') ||
                chr == BuildStringFromChar('*') ||
                chr == BuildStringFromChar('/') ||
                chr == BuildStringFromChar('^')){
            return true;
        }
        else{
            return false;
        }
    }

    bool Expression::IsLeftAssociative(std::string oper){
        if (oper == BuildStringFromChar('-') ||
                oper == BuildStringFromChar('/') ||
                oper == BuildStringFromChar('+') ||
                oper == BuildStringFromChar('*')){
            return true;
        }
        return false;
    }

    std::vector<std::pair<std::string, char>> Expression::Tokenizer(std::string inputExpr, std::string type){
        std::vector<std::pair<std::string, char>> tokens;
        int jumpIdx = 0;   ///> Index of next non-digit char to jump to when storing numbers.
        for (int i = 0; i < inputExpr.size(); i++){
            if (i < jumpIdx && i != 0){
                // Jump characters until jumpIdx.
                continue;
            }
            if (IsOperator(BuildStringFromChar(inputExpr[i]))){
                tokens.push_back(std::make_pair(BuildStringFromChar(inputExpr[i]), 'o'));
                // make_pair() template function to make a std::pair with adequate types
            }
            else if (inputExpr[i] == '('){
                tokens.push_back(std::make_pair(BuildStringFromChar(inputExpr[i]), 'l'));
            }
            else if (inputExpr[i] == ')'){
                tokens.push_back(std::make_pair(BuildStringFromChar(inputExpr[i]), 'r'));
            }
            else if (std::isdigit(inputExpr[i])){
                jumpIdx = StoreNumber(i, type);
                tokens.push_back(std::make_pair(tmpNumString, 'n'));
                ClearNumber();
            }
            // Implement function tokenization.
        }
        return tokens;
    }

    int Expression::Precedence(std::string operator1, std::string operator2){
        char arr[10] = {'^','1','*','2','/','2','+','3','-','3'};   ///> Precedence array, lowest number means highest precedence.
        char arrPrecedence[2];  ///> Precedence of given operators, first value for 'operator1', second value for 'operator2'.
        for (int i = 0; i < 10; i += 2){
            if (operator1 == BuildStringFromChar(arr[i])){
                arrPrecedence[0] = arr[i + 1];
            } else if (operator2 == BuildStringFromChar(arr[i])){
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

    std::queue<std::string> Expression::BuildPostfixQueue(){
        std::queue<std::string> outputQueue;    ///> First in, first out container.
        std::stack<std::string> operatorStack;  ///> Last in, first out container.
        //Stack should not be evaluated when empty. 

        std::vector<std::pair<std::string, char>> tokens = Tokenizer(infixExpr, "in"); ///> Infix expression tokens.
        
        for (int i = 0; i < (int)tokens.size(); i++){
            if (tokens[i].second == 'n'){
                outputQueue.push(tokens[i].first);
            }
            else if (tokens[i].second == 'o'){
                while( !(operatorStack.empty()) && (IsOperator(operatorStack.top()) && operatorStack.top() != BuildStringFromChar('(')) &&
                        (Precedence(operatorStack.top(), tokens[i].first)==1 || ((Precedence(operatorStack.top(), tokens[i].first)==0) &&
                                                                            IsLeftAssociative(tokens[i].first))) ){
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                }
                operatorStack.push(tokens[i].first);
            }
            else if (tokens[i].second == 'l'){
                operatorStack.push(tokens[i].first);
            }
            else if (tokens[i].second == 'r'){
                while(!operatorStack.empty() && (operatorStack.top() != BuildStringFromChar('('))){
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                }
                if (!operatorStack.empty() && operatorStack.top() == BuildStringFromChar('(')){
                    operatorStack.pop();
                }
            }
        }
        while (!operatorStack.empty()){
            if (operatorStack.top() != BuildStringFromChar('(')){
                outputQueue.push(operatorStack.top());
                operatorStack.pop();
            }
        }
        return outputQueue;
    }
    
    void Expression::BuildPostfixString(){
        std::queue<std::string> que = BuildPostfixQueue();
        while (!que.empty()){
            postfixExpr.append(que.front());
            postfixExpr.append(" ");
            // Appending spaces because operands are no longer separated by operators.
            que.pop();
        }
        if (postfixExpr.size() > 1){
            postfixExpr.replace(postfixExpr.begin(), postfixExpr.end(), postfixExpr.begin(), postfixExpr.end()-1);
        }
        // Removing the trailing space might be pointless.
    }

    struct Node{
        std::string data;
        Node* left;
        Node* right;
    };

    BinaryTree::BinaryTree(std::string inputExpr){
        expr = new Expression (inputExpr);
    }

    Node* BinaryTree::NewNode(std::string newData){
        Node* node = new Node;
        node->data = newData;
        node->left = NULL;
        node->right = NULL;
        return node;
    }

    void BinaryTree::Populate(){
        expr->BuildPostfixString();
        tokens = expr->Tokenizer(expr->postfixExpr, "post");

        Node* tmpArray[2];
        for (int i = 0; i < (int)tokens.size(); i++){
            if (tokens[i].second == 'n'){
                treeStack.push(NewNode(tokens[i].first));
            }
            else if (tokens[i].second == 'o'){
                tmpArray[1] = treeStack.top();
                treeStack.pop();
                tmpArray[0] = treeStack.top();
                treeStack.pop();

                treeStack.push(NewNode(tokens[i].first));
                treeStack.top()->left = tmpArray[0];
                treeStack.top()->right = tmpArray[1];
            }
        }
        std::cout << "nice\n";
    }
}

