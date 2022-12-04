#ifndef TRANSLATOR_PARSER_H
#define TRANSLATOR_PARSER_H
#include "Lexer.h"
using namespace std;

int Prior ( int AnotherElemType );

enum class PS_Type {
    Var = 1, // a
    Const, // k
    In,
    Out,
    Mass,
    Plus, //+
    Minus, // -
    Div, // /
    Mul, // *
    Ass, // =
    Less, // <
    Greater, // >
    Equal, // ==
    NotEqual, // !=
    Label,
    T,
    F,
    I,
    Empty
};

class PS_Element{
    string Element;
    PS_Type Element_Type;
public:
    static map <PS_Type, string> OperationPSType;
    PS_Element(string element, PS_Type element_type);
    PS_Element(Token token);
    const string &GetPS_Element() const;
    PS_Type GetPS_Element_Type() const;
    string Translate_PS_Type(PS_Type elem);
    void GetPSInfo();

};

class Polish_string{
    vector<Token> Input_string;
    vector<PS_Element> Polish_string;
    int k; //счётчик генерируемых элементов ОПС
public:
    void Generate_PS(vector<Token>List);
    void GetPolish_string();
    static map <string, int> Var_Map;
    static map <string, int> Label_Map;
    static map <string, int*> Mass_Map;
};


#endif //TRANSLATOR_PARSER_H
