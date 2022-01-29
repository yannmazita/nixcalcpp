#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>

namespace calc{
    /**
     * Container for expressions input by user.
     */
    class Expression{
        private:
            std::string tmpNumString;   ///> Temporary number stored in string form.
        public:
            std::string infixExpr;      ///> Infix expression input by user.
            std::string postfixExpr;    ///> Postfix conversion of 'infixExpr'.

            /**
             * Initialize infix expression.
             * @param inputExpr the expression input by user.
             */
            Expression(std::string inputExpr);
        private:
            /**
             * Store number starting at specific position in the expression.
             * @param pos position of the character of the number.
             * @param type either "in" for infix or "post" for postfix.
             * @return position+1 of the last character of the number.
             */
            int StoreNumber(const int pos, std::string type);

            /**
             * Clear current number stored in string form.
             */
            void ClearNumber();

            /**
             * Convert single character to string.
             * @param character to build from.
             * @return the string.
             */
            std::string BuildStringFromChar(char character);

            /**
             * Evaluate whether character is an operator.
             * The character has to be converted to string.
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
        public:
            /**
             * Tokenize expression.
             * @param inputExpr the expression to tokenize.
             * @param type either "in" for infix or "post" for postfix.
             * @return vector of pairs of strings with their assigned meaning.
             */
            std::vector<std::pair<std::string, char>> Tokenizer(std::string inputExpr, std::string type);
        private:
            /**
             * Evaluate precedence of operators.
             * @param operator1 the first operator.
             * @param operator2 the second operator.
             * @return 1 if operator1 has precendence, -1 if operator2, 0 if same.
             */
            int GetPrecedence(std::string operator1, std::string operator2);
        private:
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
     */
    struct Node;

    class BinaryTree{
        private:
            Expression* expr;
            std::vector<std::pair<std::string, char>> tokens;   ///> Postfix expression tokens.
            std::stack<Node*> treeStack;                        ///> Stack of pointers to nodes.
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
    };
}
