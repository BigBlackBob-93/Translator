#ifndef TRANSLATOR_INTERPRETER_H
#define TRANSLATOR_INTERPRETER_H
#include "Parser.h"

class Interpreter{
    Parser *ptr;
    vector <Parser::PS_Element> not_stack;
    int VarOrConst();
    void ChangeToConst(int &result);
    string key;
    int id;
public:

    int index;
    Interpreter(Parser &Data);
    void Interpretation();
    void ChooseOperation(Parser::PS_Element &operation);
    int TakeMassValue(string &s, int &c);
    void ChangeMassValue(int& value);
    void ResetMass();

    void in();
    void out();
    void solve(Parser::PS_Operation type);
    void ass();
    void indexing();
    void compare(Parser::PS_Operation type);
    void t_transition();
    void f_transition();
};

void Shit(int number);


#endif //TRANSLATOR_INTERPRETER_H