#include <iostream>

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
            std::string data;
            class Node* left;
            class Node* right;

            Node(std::string inputData);

        private:
            /**
            * Find target in tree.
            * @param root root of the (sub)tree to search.
            * @param target target to find in (sub)tree.
            * @return true if target found in tree else false.
            */
            int Find(class Node* root, std::string target);
            /* See that root is indeed the whole class and not simply an instance
             * by using 'class Node*' and not simply 'node*'
             */
    };
}
