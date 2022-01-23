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
            std::string infixExpr;      ///> Infix expression input by user.
            std::string tmpNumString;   ///> Temporary number stored in string form.
        public:
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
             * @return position+1 of the last character of the number.
             */
            int StoreNumber(const int pos);

            /**
             * Clear current number stored in string form.
             */
            void ClearNumber();

            /**
             * Convert single character to string.
             * @param chr the character to convert.
             * @return the converted character.
             */
            std::string CharToString(char chr);

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
             * @return vector of pairs of strings with their assigned meaning.
             */
            std::vector<std::pair<std::string, char>> Tokenizer(std::string inputExpr);
        private:
            /**
             * Evaluate precedence of operators.
             * @param Oper1 the first operator.
             * @param Oper2 the second operator.
             * @return 1 if oper1 has precendence, -1 if oper2, 0 if same.
             */
            int Precedence(std::string oper1, std::string oper2);

            /**
             * Print content of outputQueue and operatorStack.
             */
            void debugPrint(std::queue<std::string> &outputQueue, std::stack<std::string> &operatorStack);

            /**
             * Build postfix mathematical expression from infix expression.
             * @return queue of the converted expression.
             */
            std::queue<std::string> PostfixQueue();
        public:
            /**
             * Store postfix conversion of infix expression.
             * PostfixQueue() is used to build a postfix queue that is then converted to
             * a string stored in 'postfixExpr'.
             */
            void PostfixStore();
        public:
            void DisplayPostfix();
    };

    /**
     * Structure of a tree.
     */
    struct Node;

    class BinaryTree{
        private:
            Expression* expr;
            std::vector<std::pair<std::string, char>> tokens;   ///> Postfix expression tokens.
        public:
            BinaryTree(std::string inputExpr);
        private:
            /**
             * Allocate memory for new node.
             * @param newData the data to be stored in the node.
             * @return pointer to the the new node.
             */
            Node* NewNode(std::string newData);
        public:
            /**
             * Populate the binary tree from the postfix expression.
             */
            void Populate();
    };
}
