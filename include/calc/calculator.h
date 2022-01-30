#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <math.h>

namespace calc{
    /**
     * Container for expressions input by user.
     */
    class Expression{
        private:
            std::string infixExpr;      ///> Infix expression input by user.
            std::string postfixExpr;    ///> Postfix conversion of 'infixExpr'.
            std::string tmpNumString;   ///> Temporary number stored in string form.
        public:
           bool isIntegerOnly = true;   ///> Whether operands or the operator need only integers.

            /**
             * Initialize infix expression.
             * @param inputExpr the expression input by user.
             */
            Expression(std::string inputExpr);
        private:
            /**
             * Store number starting at specific position in the expression.
             * This method stores in 'tmpNumString' the number starting at a specific position.
             * That position and the return value allows to "skip" numbers in the expression if wanted.
             * The method also changes the bool isIntegerOnly whether a decimal number is stored.
             * @param pos position of the character of the number.
             * @param type either "in" for infix or "post" for postfix.
             * @return position+1 of the last character of the number.
             */
            int StoreNumber(const int pos, std::string type);

            /**
             * Clear current number stored in string form.
             * This method simply clears the string 'tmpNumString'.
             */
            void ClearNumber();

            /**
             * Build string from single character.
             * @param character to build from.
             * @return the string.
             */
            std::string BuildStringFromChar(char character);

            /**
             * Evaluate whether character is an operator.
             * The character has to be a string. Use BuildStringFromChar if needed.
             * @param chr the character.
             * @return true if character is an operetor, false otherwise.
             */
            bool IsOperator(std::string chr);

            /** Evaluate whether operator is left associative.
             * The operator has to be converted to string.
             * @param oper the operator.
             * @return true if left associative, false otherwise.
             */
            bool IsLeftAssociative(std::string oper);

            /**
             * Tokenize expression.
             * This method makes tokens out of an expression. A pair consists of a token value,
             * ('+', '1'...) and a token name ('o' for operator, 'n' for number...).
             * @param inputExpr the expression to tokenize.
             * @param type either "in" for infix or "post" for postfix.
             * @return vector of pairs of strings with their assigned meaning.
             */
            std::vector<std::pair<std::string, char>> Tokenizer(std::string inputExpr, std::string type);
        public:
            /**
             * Tokenize postfix expression.
             * Public version of Tokenizer this time only tokenizing the postfix expression.
             * @return vector of pairs of strings with their assigned meaning.
             */
            std::vector<std::pair<std::string, char>> Tokenizer();
        private:
            /**
             * Evaluate precedence of operators.
             * @param operator1 the first operator.
             * @param operator2 the second operator.
             * @return 1 if operator1 has precendence, -1 if operator2, 0 if same.
             */
            int GetPrecedence(std::string operator1, std::string operator2);
            /**
             * Build postfix mathematical expression from infix expression.
             * @return queue of the converted expression.
             */
            std::queue<std::string> BuildPostfixQueue();
        public:
            /**
             * Build postfix expression from infix expression.
             * BuildPostfixQueue() is used to build a postfix queue that is then converted to
             * a string stored in 'postfixExpr'.
             */
            void BuildPostfixString();
    };

    /**
     * Structure of a tree.
     * Implemented here because the complete Node type is needed in templates.
     */
    struct Node{
        std::string data;
        Node* left;
        Node* right;
    };


    class BinaryTree{
        private:
            Expression* expr;
            std::vector<std::pair<std::string, char>> tokens;   ///> Postfix expression tokens.
            static std::stack<Node*> treeStack;                 ///> Stack of pointers to nodes.
        public:
            BinaryTree(std::string inputExpr);
        private:
            /**
             * Allocate memory for new node.
             * @param newData the data to be stored in the node.
             * @return pointer to the the new node.
             */
            Node* NewNode(std::string newData);

            /**
             * Populate the binary tree from the postfix expression.
             */
            void Populate();

            /**
             * Evaluate (binary) expression tree.
             * @tparam T the type of numbers handled.
             * @param node starting node for evaluation.
             */
            template<typename T> T Evaluate(Node* node = treeStack.top()){
                if (node == NULL){
                    return 0;
                }
                // Leaf nodes are the only nodes with numbers.
                if (node->left == NULL && node->right == NULL){
                    if (expr->isIntegerOnly){
                        return std::stoi(node->data);
                    }
                    else {
                        return std::stof(node->data);
                    }
                }

                T leftOperand;
                T rightOperand;
                if (expr->isIntegerOnly){
                    leftOperand = Evaluate<int>(node->left);
                    rightOperand = Evaluate<int>(node->right);
                }
                else{
                    leftOperand = Evaluate<double>(node->left);
                    rightOperand = Evaluate<double>(node->right);
                }

                if (node->data == std::string {'+'}){
                    return leftOperand + rightOperand;
                }
                else if (node->data == std::string {'-'}){
                    return leftOperand - rightOperand;
                }
                else if (node->data == std::string {'*'}){
                    return leftOperand * rightOperand;
                }
                else if (node->data == std::string {'^'}){
                    return pow(leftOperand, rightOperand);
                }
            };
    };
}
