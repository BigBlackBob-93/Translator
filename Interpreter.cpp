#include "Interpreter.h"
#define OPS data->Polish_String
#define VMap data->Var_Map
#define MMap data->Mass_Map

Interpreter::Interpreter(Parser::Data Data) {
    this->data = &Data;
    index = 0;
    this->Interpretation();
}

void Interpreter::Interpretation() {
    for (; index < OPS.size(); ++index) {
        switch (OPS[index].PS_Element_Type) {
            case Parser::PS_Type::Var:
                not_stack.push_back(OPS[index]);
                break;
            case Parser::PS_Type::Const:
                not_stack.push_back(OPS[index]);
                break;
            case Parser::PS_Type::Operation:
                ChooseOperation(OPS[index]);
                break;
            default: Shit(0);
        }
    }
}

void Interpreter::ChooseOperation(Parser::PS_Element &operation) {
    switch (operation.PS_Element_Operation) {
        case Parser::PS_Operation::In: in(not_stack, data); break;
        case Parser::PS_Operation::Out: out(not_stack, data); break;
        case Parser::PS_Operation::Plus: solve(not_stack, data, Parser::PS_Operation::Plus); break;
        case Parser::PS_Operation::Minus: solve(not_stack, data, Parser::PS_Operation::Minus); break;
        case Parser::PS_Operation::Div: solve(not_stack, data, Parser::PS_Operation::Div); break;
        case Parser::PS_Operation::Mul: solve(not_stack, data, Parser::PS_Operation::Mul); break;
        case Parser::PS_Operation::Ass: ass(not_stack, data); break;
        case Parser::PS_Operation::Less: compare(not_stack, data, Parser::PS_Operation::Less); break;
        case Parser::PS_Operation::Greater: compare(not_stack, data, Parser::PS_Operation::Greater); break;
        case Parser::PS_Operation::Equal: compare(not_stack, data, Parser::PS_Operation::Equal); break;
        case Parser::PS_Operation::NotEqual: compare(not_stack, data, Parser::PS_Operation::NotEqual); break;
        case Parser::PS_Operation::T: t_transition(not_stack, data, index); break;
        case Parser::PS_Operation::F: f_transition(not_stack, data, index); break;
        case Parser::PS_Operation::I: indexing(not_stack, data); break;
        case Parser::PS_Operation::Mass: not_stack.pop_back(); break;
        default: Shit(0);
    }
}

int VarOrConst(vector<Parser::PS_Element> &not_stack, Parser::Data *data) {
    if (not_stack.back().PS_Element_Type == Parser::PS_Type::Var) return VMap[not_stack.back().PS_Element_Name];
    else return not_stack.back().num;
}

void ChangeToConst(vector<Parser::PS_Element> &not_stack, int &result) {
    not_stack.back().PS_Element_Type = Parser::PS_Type::Const;
    not_stack.back().num = result;
}

string ShitList[] = { "PS_Type = ???", "indexing: array is out of bounds", "in: PS_Type != Const", "transition: flag > 1"};
void Shit(int number) {
    cout << "\nERROR -- Interpreter: " << ShitList[number] << endl;
    exit(0);
}

void in(vector <Parser::PS_Element> &not_stack, Parser::Data *data) {
    if(not_stack.back().PS_Element_Type != Parser::PS_Type::Var) Shit(2);
    int result;
    cin >> result;
    ChangeToConst(not_stack, result);
}

void out(vector <Parser::PS_Element> &not_stack, Parser::Data *data) {
    cout << VarOrConst(not_stack, data);
    not_stack.pop_back();
}

void solve(vector <Parser::PS_Element> &not_stack, Parser::Data *data, Parser::PS_Operation type) {
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

void ass(vector <Parser::PS_Element> &not_stack, Parser::Data *data) {
    int result = VarOrConst(not_stack, data);
    not_stack.pop_back();
    VMap[not_stack.back().PS_Element_Name] = result;
    not_stack.pop_back();
}

void compare(vector <Parser::PS_Element> &not_stack, Parser::Data *data, Parser::PS_Operation type) {
    int result = VarOrConst(not_stack, data);
    not_stack.pop_back();
    int res = 0;
    switch (type) {
        case Parser::PS_Operation::Less: if(VarOrConst(not_stack, data) < result) res = 1; break;
        case Parser::PS_Operation::Greater: if(VarOrConst(not_stack, data) > result) res = 1; break;
        case Parser::PS_Operation::Equal: if(VarOrConst(not_stack, data) == result) res = 1; break;
        case Parser::PS_Operation::NotEqual: if(VarOrConst(not_stack, data) != result) res = 1; break;
    }
    ChangeToConst(not_stack, res);
}

void t_transition(vector <Parser::PS_Element> &not_stack, Parser::Data *data, int &index) {
    index = not_stack.back().num - 1;
    not_stack.pop_back();
}

void f_transition(vector <Parser::PS_Element> &not_stack, Parser::Data *data, int &index) {
    int num = not_stack.back().num;
    not_stack.pop_back();
    int flag = not_stack.back().num;
    not_stack.pop_back();

    switch (flag) {
        case 0: index = num - 1; break;
        case 1: break;
        default: Shit(3);
    }
}

void indexing(vector <Parser::PS_Element> &not_stack, Parser::Data *data) {
    int result = VarOrConst(not_stack, data);
    not_stack.pop_back();
    int size = MMap[not_stack.back().PS_Element_Name].size();
    if (result < size) ChangeToConst(not_stack, result);
    else Shit(1);
}








