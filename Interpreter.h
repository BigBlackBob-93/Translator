//
// Created by BigBlackBob on 15.12.2022.
//

#ifndef TRANSLATOR_INTERPRETER_H
#define TRANSLATOR_INTERPRETER_H
#include "Parser.h"

class Interpreter{
    vector <Parser::PS_Element> not_stack;
public:
    Parser *data;
    Interpreter(Parser &data);
    void Interpretation();
    void ChooseOperation(Parser::PS_Element &operation);
};
void in();
void out();
void plus_f(vector <Parser::PS_Element> &not_stack, Parser *data);
void minus_f(vector <Parser::PS_Element> &not_stack);
void div(vector <Parser::PS_Element> &not_stack);
void mul(vector <Parser::PS_Element> &not_stack);
void ass();
void less_f();
void greater_f();
void equal();
void not_equal();
void t_transition();
void f_transition();
void indexing();

//Parser::Maps DefineVar();

#endif //TRANSLATOR_INTERPRETER_H