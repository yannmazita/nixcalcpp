#include <iostream>
#include <string>

namespace calc{
    
    /**
     * Container for expressions input by user.
     */
    class Expression{
        public:
            /**
             * Initialize expression input by user.
             * @param inputExpr the expression input by user.
             */
            Expression(std::string inputExpr);
    };

    /**
     * Structure of a tree.
     */
    class Node{
        public:
            std::string data;   ///> Data in node.
            class Node* left;   ///> Pointer to left child.
            class Node* right;  ///> Pointer to right child.

            Node();

        private:
            /**
            * Find target in tree.
            * @param root root of the (sub)tree to search.
            * @param target target to find in (sub)tree.
            * @return true if target found in tree else false.
            */
            int Find(class Node* root, std::string target);
            /* See that root is indeed the whole class and not simply
             * an instance by using 'class Node*' and not simply 'node*'
             */

            /**
             * Allocate memory for new node.
             * @param newData the data to be stored in the node.
             * @return pointer to the class making up the node.
             */
            class Node* NewNode(std::string newData);

            /**
             * Insert new node with data.
             * Recursively go through the nodes of a tree until the
             * first empty child is found. Then when it's found,
             * store in it the wanted data using NewNode().
             * @param node the starting node.
             * @param newData the data to be stored in the node.
             * @return pointer to the struct making up the node.
             */
            class Node* Insert(class Node* node, std::string newData);
    };
}
