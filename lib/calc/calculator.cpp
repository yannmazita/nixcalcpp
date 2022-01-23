#include "calculator.h"
#include <cctype>
#include <cstdio>

namespace calc{
    Expression::Expression(std::string inputExpr){
        infixExpr = inputExpr;
    }  

    int Expression::StoreNumber(const int pos){
        int i = pos;
        while (i < (int)infixExpr.size() && (std::isdigit(infixExpr[i]) || infixExpr[i] == '.')){
            tmpNumString.push_back(infixExpr[i]);
            i++;
        }
        return i;
    }

    void Expression::ClearNumber(){
        tmpNumString.clear();
    }

    std::string Expression::CharToString(char chr){
        std::string str{chr};
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
        else{
            return false;
        }
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

    std::vector<std::pair<std::string, char>> Expression::Tokenizer(std::string inputExpr){
        std::vector<std::pair<std::string, char>> tokens;
        int jumpIdx = 0;   ///> Index of next non-digit char to jump to when storing numbers.
        for (int i = 0; i < inputExpr.size(); i++){
            if (i < jumpIdx && i != 0){
                // Jump characters until jumpIdx.
                continue;
            }
            if (IsOperator(CharToString(inputExpr[i]))){
                tokens.push_back(std::make_pair(CharToString(inputExpr[i]), 'o'));
                // make_pair() template function to make a std::pair with adequate types
            }
            else if (inputExpr[i] == '('){
                tokens.push_back(std::make_pair(CharToString(inputExpr[i]), 'l'));
            }
            else if (inputExpr[i] == ')'){
                tokens.push_back(std::make_pair(CharToString(inputExpr[i]), 'r'));
            }
            else if (std::isdigit(inputExpr[i])){
                jumpIdx = StoreNumber(i);
                tokens.push_back(std::make_pair(tmpNumString, 'n'));
                ClearNumber();
            }
            // Implement function tokenization.
        }
        return tokens;
    }

    int Expression::Precedence(std::string oper1, std::string oper2){
        char arr[10] = {'^','1','*','2','/','2','+','3','-','3'};   ///> Precedence array, lowest number means highest precedence.
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

    void Expression::debugPrint(std::queue<std::string> &outputQueue, std::stack<std::string> &operatorStack){
        std::queue<std::string> tmpQueue = outputQueue;
        std::stack<std::string> tmpStack = operatorStack;
        
        std::cout << "outputQueue = ";
        while (!tmpQueue.empty()){
            std::cout << tmpQueue.front();
            tmpQueue.pop();
        }
        std::cout << " ; operatorStack = ";
        while (!tmpStack.empty()){
            std::cout << tmpStack.top();
            tmpStack.pop();
        }
        std::cout << "\n";
    }

    std::queue<std::string> Expression::PostfixQueue(){
        std::queue<std::string> outputQueue;    ///> First in, first out container.
        std::stack<std::string> operatorStack;  ///> Last in, first out container.
        /*
         * Stack should not be evaluated when empty.
         */
        std::vector<std::pair<std::string, char>> tokens = Tokenizer(infixExpr); ///> Infix expression tokens.
        
        for (int i = 0; i < (int)tokens.size(); i++){
            if (tokens[i].second == 'n'){
                outputQueue.push(tokens[i].first);
                //debugPrint(outputQueue, operatorStack);
            }
            else if (tokens[i].second == 'o'){
                while( !(operatorStack.empty()) && (IsOperator(operatorStack.top()) && operatorStack.top() != CharToString('(')) &&
                        (Precedence(operatorStack.top(), tokens[i].first)==1 || ((Precedence(operatorStack.top(), tokens[i].first)==0) &&
                                                                            IsLeftAssociative(tokens[i].first))) ){
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                    //debugPrint(outputQueue, operatorStack);
                }
                operatorStack.push(tokens[i].first);
                //debugPrint(outputQueue, operatorStack);
            }
            else if (tokens[i].second == 'l'){
                operatorStack.push(tokens[i].first);
                //debugPrint(outputQueue, operatorStack);
            }
            else if (tokens[i].second == 'r'){
                while(!operatorStack.empty() && (operatorStack.top() != CharToString('('))){
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                    //debugPrint(outputQueue, operatorStack);
                }
                if (!operatorStack.empty() && operatorStack.top() == CharToString('(')){
                    operatorStack.pop();
                    //debugPrint(outputQueue, operatorStack);
                }
            }
        }
        while (!operatorStack.empty()){
            if (operatorStack.top() != CharToString('(')){
                outputQueue.push(operatorStack.top());
                operatorStack.pop();
                //debugPrint(outputQueue, operatorStack);
            }
        }
        return outputQueue;
    }
    
    void Expression::PostfixStore(){
        std::queue<std::string> que = PostfixQueue();
        while (!que.empty()){
            postfixExpr.append(que.front());
            que.pop();
        }
    }

    void Expression::DisplayPostfix(){
        std::cout << postfixExpr + "\n";
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
        std::stack<Node*> treeStack;    ///> Stack of pointers to nodes.
        expr->PostfixStore();
        tokens = expr->Tokenizer(expr->postfixExpr);
        for (int i = 0; i < (int)tokens.size(); i++){
            if (tokens[i].second == 'n'){
                treeStack.push(NewNode(tokens[i].first));
            }
            else if (tokens[i].second == 'o'){
                Node* tmpArray[2];
                /*
                if (!treeStack.empty()){
                    tmpArray[0] = treeStack.top();
                    treeStack.pop();
                }
                if (!treeStack.empty()){
                    tmpArray[1] = treeStack.top();
                    treeStack.pop();
                }*/
                tmpArray[0] = treeStack.top();
                treeStack.pop();
                tmpArray[1] = treeStack.top();
                treeStack.pop();
                
                treeStack.push(NewNode(tokens[i].first));
                treeStack.top()->left = tmpArray[0];
                treeStack.top()->right = tmpArray[1];
            }
        }
        std::cout << treeStack.top()->data + "\n";
        expr->DisplayPostfix();
    }
}

