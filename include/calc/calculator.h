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
