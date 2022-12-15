//
// Created by BigBlackBob on 15.12.2022.
//

#include "Interpreter.h"
#define OPS data->Get_data().Polish_String
#define VarMap data->Get_data().Var_Map
#define MassMap data->Get_data().Mass_Map

Interpreter::Interpreter(Parser &data) {
    this->data = &data;
}

void Interpreter::Interpretation() {
    int i = 0;
    while(!OPS.empty()){
        switch (OPS[i].PS_Element_Type) {
            case Parser::PS_Type::Var:
                not_stack.push_back(OPS[i]);
                break;
            case Parser::PS_Type::Const:
                not_stack.push_back(OPS[i]);
                break;
            case Parser::PS_Type::Operation:
                ChooseOperation(OPS[i]);
                break;
            default:
                cout << "\nERROR -- Interpreter: PS_Type = Empty" << endl;
                exit(0);
        }
        ++i;
    }
}

void Interpreter::ChooseOperation(Parser::PS_Element &operation) {
    switch (operation.PS_Element_Operation) {
        case Parser::PS_Operation::In: in(); break;
        case Parser::PS_Operation::Out: out(); break;
        case Parser::PS_Operation::Plus: plus_f(not_stack, data); break;
        case Parser::PS_Operation::Minus: minus_f(not_stack); break;
        case Parser::PS_Operation::Div: div(not_stack); break;
        case Parser::PS_Operation::Mul: mul(not_stack); break;
        case Parser::PS_Operation::Ass: ass(); break;
        case Parser::PS_Operation::Less: less_f(); break;
        case Parser::PS_Operation::Greater: greater_f(); break;
        case Parser::PS_Operation::Equal: equal(); break;
        case Parser::PS_Operation::NotEqual: not_equal(); break;
        case Parser::PS_Operation::T: t_transition(); break;
        case Parser::PS_Operation::F: f_transition(); break;
        case Parser::PS_Operation::I: indexing(); break;
        case Parser::PS_Operation::Mass:
            break;
        default:
            cout << "\nERROR -- Interpreter: PS_Element_Operation = Empty" << endl;
            exit(0);
    }
}



void in() {

}

void out() {
}

void plus_f(vector <Parser::PS_Element> &not_stack, Parser *data) {
    if(not_stack.back().PS_Element_Type == Parser::PS_Type::Var){
        if(VarMap.find(not_stack.back().PS_Element_Name) != VarMap.end()){

        }
        else{
            if(MassMap.find(not_stack.back().PS_Element_Name) != MassMap.end()){

            }
            else{

            }
        }
    }
}

void minus_f(vector <Parser::PS_Element> &not_stack) {
}

void div(vector <Parser::PS_Element> &not_stack) {
}

void mul(vector <Parser::PS_Element> &not_stack) {
}

void ass() {
}

void less_f() {
}

void greater_f() {
}

void equal() {
}

void not_equal() {
}

void t_transition() {
}

void f_transition() {
}

void indexing() {
}
