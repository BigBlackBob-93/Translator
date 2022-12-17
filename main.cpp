#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"

int main()
{
    string code;
    //code = "begin x = 5; mass A[x]; end";
    cout << "Enter your code: ";
    getline(cin, code);
    Lexer program(code);

    vector<Token>List = program.Analysis();
    Parser ops(List);
    ops.Run();

    Interpreter play(ops);

    return 0;
}