#include <iostream>
#include <string>
#include "calculator.h"

int main(int argc, char* argv[])
{
    std::ios_base::sync_with_stdio(false);

    calc::BinaryTree expression(argv[1]);
    expression.ComputeAndDisplay();
    return 0;
}
