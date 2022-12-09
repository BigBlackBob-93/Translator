#include "Lexer.h"
#include "Parser.h"

int main()
{
    // enter the code
    string code;
    cout << "Enter your code: ";
    getline(cin, code);
    Lexer t(code);

    // submit the code for lexical analysis -> you will have a vector of tokens
    vector<Token>List = t.Analysis();
    for(int i =0; i < List.size(); i++)
    {
        List[i].GetInfo();
    }


    //you can use token methods to get information about it
    // example: List[0].getType(); List[0].getToken();

    Parser test(List);
    test.Run();


    return 0;
}