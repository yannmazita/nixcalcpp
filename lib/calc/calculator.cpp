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
                if (infixExpr[i] == '.'){
                    isIntegerOnly = false;
                }
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

    bool Expression::IsOperator(std::string inputString){
        if (inputString == std::string {'^'} ||
                inputString == std::string {'/'} ||
                inputString == "exp" ||
                inputString == "ln"){
            isIntegerOnly = false;
            return true;
        }
        // Update isIntegerOnly to false when using additional mathematical functions.
        
        if (inputString == std::string {'+'} ||
                inputString == std::string {'-'} ||
                inputString == std::string {'*'}){
            return true;
        }
        else{
            return false;
        }
    }

    bool Expression::IsLeftAssociative(std::string oper){
        if (oper == std::string {'-'} ||
                oper == std::string {'/'} ||
                oper == std::string {'+'} ||
                oper == std::string {'*'}){
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
            if (IsOperator(std::string {inputExpr[i]})){
                tokens.push_back(std::make_pair(std::string {inputExpr[i]}, 'o'));
                // make_pair() template function to make a std::pair with adequate types
            }
            else if (inputExpr[i] == '('){
                tokens.push_back(std::make_pair(std::string {inputExpr[i]}, 'l'));
            }
            else if (inputExpr[i] == ')'){
                tokens.push_back(std::make_pair(std::string {inputExpr[i]}, 'r'));
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

    std::vector<std::pair<std::string, char>> Expression::Tokenizer(){
        std::vector<std::pair<std::string, char>> tokens = Tokenizer(postfixExpr, "post");
        return tokens;
    }

    int Expression::GetPrecedence(std::string operator1, std::string operator2){
        char arr[10] = {'^','1','*','2','/','2','+','3','-','3'};   ///> Precedence array, lowest number means highest precedence.
        char arrGetPrecedence[2];  ///> Precedence of given operators, first value for 'operator1', second value for 'operator2'.
        for (int i = 0; i < 10; i += 2){
            if (operator1 == std::string {arr[i]}){
                arrGetPrecedence[0] = arr[i + 1];
            } else if (operator2 == std::string{arr[i]}){
                arrGetPrecedence[1] = arr[i + 1];
            }
        }
        if (arrGetPrecedence[0] < arrGetPrecedence[1]){
            return 1;
        } else if (arrGetPrecedence[1] < arrGetPrecedence[0]){
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
                while( !(operatorStack.empty()) && (IsOperator(operatorStack.top()) && operatorStack.top() != std::string {'('}) &&
                        (GetPrecedence(operatorStack.top(), tokens[i].first)==1 || ((GetPrecedence(operatorStack.top(), tokens[i].first)==0) &&
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
                while(!operatorStack.empty() && (operatorStack.top() != std::string {'('})){
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                }
                if (!operatorStack.empty() && operatorStack.top() == std::string {'('}){
                    operatorStack.pop();
                }
            }
        }
        while (!operatorStack.empty()){
            if (operatorStack.top() != std::string {'('}){
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

    Node* BinaryTree::BuildExpressionTree(){
        expr->BuildPostfixString();
        tokens = expr->Tokenizer();
        std::stack<Node*> treeStack;                 ///> Stack of pointers to nodes.

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
        return treeStack.top();
    }
    void BinaryTree::ComputeAndDisplay(){
        Node* tree = BuildExpressionTree();
        if (expr->isIntegerOnly){
            std::cout << EvaluateExpressionTree<long long int>(tree);
            std::cout << "\n";
        }
        else {
            std::cout << EvaluateExpressionTree<long double>(tree);
            std::cout << "\n";
        }
    }
}

