#include <iostream>
#include <string>

std::string CharToString(char chr){
    std::string str{chr};
    return str;
}

int Precedence(std::string oper1, std::string oper2){
    char arr[10] = {'^','1','+','2','-','2','*','3','/','3'};   ///> Precedence array, lowest number means highest precedence.
    char arrPrecedence[2];  ///> Precedence of given operators, first value for 'oper1', second value for 'oper2'.
    for (int i = 0; i < 10; i += 2){
        if (oper1 == CharToString(arr[i])){
            arrPrecedence[0] = arr[i + 1];
        } else if (oper2 == CharToString(arr[i])){
            arrPrecedence[1] = arr[i + 1];
        }
    }
    if (arrPrecedence[0] < arrPrecedence[1]){
        return 1;
    } else if (arrPrecedence[1] < arrPrecedence[0]){
        return -1;
    } else {
        return 0;
    }
}

int main()
{
    std::cout << Precedence(CharToString('+'), CharToString('*'));
}

