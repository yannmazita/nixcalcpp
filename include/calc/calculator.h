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
    struct Node{
        std::string data;   ///> Data in node.
        struct Node* left;   ///> Pointer to left child.
        struct Node* right;  ///> Pointer to right child.
    };

    class BinaryTree{
        private:
            static struct Node* root;

        public:
            BinaryTree();

            /**
            * Find target in (sub)tree.
            * @param target target to find in tree.
            * @param node the starting node for the recursion.
            * @return true if target found in tree else false.
            */
            int Find(std::string target, Node* node = root);

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
             * store in it the wanted data using NewNode().
             * @param newData the data to be stored in the node.
             * @param node the starting node.
             * @return pointer to the updated node.
             */
            Node* Insert(std::string newData, Node* node = root);
    };
}
