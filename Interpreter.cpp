#include "Interpreter.h"
#define OPS data->Get_data().Polish_String
#define VarMap data->Get_data().Var_Map
#define MassMap data->Get_data().Mass_Map

Interpreter::Interpreter(Parser &data) {
    this->data = &data;
}

void Interpreter::Interpretation() {
    for (int i = 0; i < OPS.size(); ++i) {
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
            default: Err(0);
        }
    }
}

void Interpreter::ChooseOperation(Parser::PS_Element &operation) {
    switch (operation.PS_Element_Operation) {
        //case Parser::PS_Operation::In: in(); break;
        //case Parser::PS_Operation::Out: out(); break;
        case Parser::PS_Operation::Plus: solve(not_stack, data, Parser::PS_Operation::Plus); break;
        case Parser::PS_Operation::Minus: solve(not_stack, data, Parser::PS_Operation::Minus); break;
        case Parser::PS_Operation::Div: solve(not_stack, data, Parser::PS_Operation::Div); break;
        case Parser::PS_Operation::Mul: solve(not_stack, data, Parser::PS_Operation::Mul); break;
        case Parser::PS_Operation::Ass: ass(not_stack, data); break;
        //case Parser::PS_Operation::Less: compare(); break;
        //case Parser::PS_Operation::Greater: compare(); break;
        //case Parser::PS_Operation::Equal: compare(); break;
        //case Parser::PS_Operation::NotEqual: compare(); break;
        //case Parser::PS_Operation::T: t_transition(); break;
        //case Parser::PS_Operation::F: f_transition(); break;
        case Parser::PS_Operation::I: indexing(not_stack, data); break;
        //case Parser::PS_Operation::Mass: break;
        default: Err(0);
    }
}

int VarOrConst(vector<Parser::PS_Element> &not_stack, Parser *data) {
    if (not_stack.back().PS_Element_Type == Parser::PS_Type::Var) return VarMap[not_stack.back().PS_Element_Name];
    else return not_stack.back().num;
}

void ChangeToConst(vector<Parser::PS_Element> &not_stack, int &result) {
    not_stack.back().PS_Element_Type = Parser::PS_Type::Const;
    not_stack.back().num = result;
}

void Err(int number) {
    cout << "\nERROR -- Interpreter: " << Errors[number] << endl;
    exit(0);
}

void in() {

}

void out() {
}

void solve(vector <Parser::PS_Element> &not_stack, Parser *data, Parser::PS_Operation type) {
    int result = 0;
    for (int i = 0; i < 2; ++i) {
        switch (type) {
            case Parser::PS_Operation::Plus:
                result += VarOrConst(not_stack, data);
                break;
            case Parser::PS_Operation::Minus:
                result = VarOrConst(not_stack, data) - result;
                break;
            case Parser::PS_Operation::Div:
                if (i>0) result = VarOrConst(not_stack, data) / result;
                else result = VarOrConst(not_stack, data);
                break;
            case Parser::PS_Operation::Mul:
                if (i>0) result *= VarOrConst(not_stack, data);
                else result = VarOrConst(not_stack, data);
                break;
        }
        if(i<1) not_stack.pop_back();
    }
    ChangeToConst(not_stack, result);
}

void ass(vector <Parser::PS_Element> &not_stack, Parser *data) {
    int result = VarOrConst(not_stack, data);
    not_stack.pop_back();
    VarMap[not_stack.back().PS_Element_Name] = result;
    not_stack.pop_back();
}

void compare() {
}

void t_transition() {
}

void f_transition() {
}

void indexing(vector <Parser::PS_Element> &not_stack, Parser *data) {
    int result = VarOrConst(not_stack, data);
    not_stack.pop_back();
    int size = MassMap[not_stack.back().PS_Element_Name].size();
    if (result < size) ChangeToConst(not_stack, result);
    else Err(1);
}








