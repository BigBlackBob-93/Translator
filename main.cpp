#include "Lexer.h"
int main()
{
    // enter the code
    string code;
    cout << "Enter your code: ";
    cin >> code;
    Lexer t(code);

    // submit the code for lexical analysis -> you will have a vector of tokens
    vector<Token>List = t.Analysis();

    //you can use token methods to get information about it
    // example: List[0].getType(); List[0].getToken();

    return 0;
}