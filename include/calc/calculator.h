#include <iostream>
#include <string>
#include <map>
#include <queue>

namespace calc{
    
    /**
     * Container for expressions input by user.
     */
    class Expression{
        private:
            std::string expr;           ///> The current infix expression.
            std::string tmpNumString;   ///> Temporary number stored in string form.
        public:
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

            /** Tokenize expression.
             * @return map of tokenized items. Keys are items, values their nature.
             */
            std::multimap<std::string, char> Tokenizer();

            /**
             * Evaluate precedence of operators.
             * @param Oper1 the first operator.
             * @param Oper2 the second operator.
             * @return 1 if oper1 has precendence, -1 if oper2, 0 if same
             */
            int Precedence(std::string oper1, std::string oper2);

            /**
             * Converts infix mathematical expression to postfix notation.
             * @return queue of the converted expression.
             */
            std::queue<std::string> PostfixConvert();

        public:
            void DisplayPostfix();
    };

    /**
     * Structure of a tree.
     */
    struct Node;

    class BinaryTree{
        private:
            Node* root;

        public:
            BinaryTree();

        private:
            /**
            * Find target in (sub)tree.
            * @param target target to find in tree.
            * @param node the starting node for the recursion.
            * @return true if target found in tree else false.
            */
            int Find(std::string target, Node* &node);
            // A reference to a pointer is used so as to keep
            // modifications of the pointer.

            /**
             * Allocate memory for new node.
             * @param newData the data to be stored in the node.
             * @return pointer to the the new node.
             */
            Node* NewNode(std::string newData);

            /**
             * Insert new node with data.
             * Recursively go through the nodes of a tree until the
             * first empty child is found. Then when it's found,
             * store in it the wanted data using NewNode(). If no
             * node is given, the root node will be used.
             * @param newData the data to be stored in the node.
             * @param node the starting node.
             * @return pointer to the updated node.
             */
            void Insert(std::string newData, Node* &node);
            // A reference to a pointer is used so as to keep
            // modifications of the pointer.

        public:
            int IsTargetInTree(std::string target);
            void InsertTarget(std::string newData);
    };
}
