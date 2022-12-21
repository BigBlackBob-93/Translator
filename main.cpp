#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include <fstream>

int main()
{
    string code;
    ifstream file("tests.txt");
    if (file.is_open())
    {
        while (getline(file, code))
        {
            cout << "\nCode: " << code;
            Lexer program(code);
            vector<Token>List = program.Analysis();
            Parser ops(List);
            ops.Run();
            Interpreter play(ops);
        }
    }
    file.close();
    return 0;
}