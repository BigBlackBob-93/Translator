#include "Lexer.h"
int main()
{
    string code = "x;++e45  while if";
    Lexer t(code);
    vector<Token>List = t.Analysis();
    for (auto& i : List) {
        cout << endl;
        i.GetInfo();
    }
    return 0;
}