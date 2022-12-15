#ifndef TRANSLATOR_INTERPRETER_H
#define TRANSLATOR_INTERPRETER_H
#include "Parser.h"

class Interpreter{
    vector <Parser::PS_Element> not_stack;
public:
    Parser *data;
    explicit Interpreter(Parser &data);
    void Interpretation();
    void ChooseOperation(Parser::PS_Element &operation);
};

int VarOrConst(vector <Parser::PS_Element> &not_stack, Parser *data);
void ChangeToConst(vector <Parser::PS_Element> &not_stack, int &result);
string Errors[] = { "PS_Type = ???", "indexing: array is out of bounds"};
void Err(int number);

void in();
void out();
void solve(vector <Parser::PS_Element> &not_stack, Parser *data, Parser::PS_Operation type);
void ass(vector <Parser::PS_Element> &not_stack, Parser *data);
void compare();
void t_transition();
void f_transition();
void indexing(vector <Parser::PS_Element> &not_stack, Parser *data);

#endif //TRANSLATOR_INTERPRETER_H