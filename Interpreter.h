#ifndef TRANSLATOR_INTERPRETER_H
#define TRANSLATOR_INTERPRETER_H
#include "Parser.h"

class Interpreter{
    vector <Parser::PS_Element> not_stack;
public:
    int index;
    Parser::Data *data;
    explicit Interpreter(Parser::Data Data);
    void Interpretation();
    void ChooseOperation(Parser::PS_Element &operation);
};

int VarOrConst(vector <Parser::PS_Element> &not_stack, Parser::Data *data);
void ChangeToConst(vector <Parser::PS_Element> &not_stack, int &result);
void Shit(int number);

void in(vector <Parser::PS_Element> &not_stack, Parser::Data *data);
void out(vector <Parser::PS_Element> &not_stack, Parser::Data *data);
void solve(vector <Parser::PS_Element> &not_stack, Parser::Data *data, Parser::PS_Operation type);
void ass(vector <Parser::PS_Element> &not_stack, Parser::Data *data);
void compare(vector <Parser::PS_Element> &not_stack, Parser::Data *data, Parser::PS_Operation type);
void t_transition(vector <Parser::PS_Element> &not_stack, Parser::Data *data, int &index);
void f_transition(vector <Parser::PS_Element> &not_stack, Parser::Data *data, int &index);
void indexing(vector <Parser::PS_Element> &not_stack, Parser::Data *data);

#endif //TRANSLATOR_INTERPRETER_H