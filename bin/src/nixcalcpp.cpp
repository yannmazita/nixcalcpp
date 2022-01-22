#include <iostream>
#include <string>
#include "calculator.h"

int main(int argc, char* argv[])
{
    std::ios_base::sync_with_stdio(false);

    /*
    std::string someString = "1+2.5*(-3.5)*2*(-3+2)+2^(5-1)";
    calc::BinaryTree btree;
    btree.InsertTarget(std::to_string('+'));
    btree.InsertTarget(std::to_string('1'));
    btree.InsertTarget(std::to_string('+'));
    btree.InsertTarget(std::to_string('3'));
    btree.IsTargetInTree(std::to_string('3'));
    */

    calc::Expression newExpr("3+4*2/(1-5)^2^3");
    newExpr.DisplayPostfix();

    return 0;
}
