#ifndef TRANSLATOR_PARSER_H
#define TRANSLATOR_PARSER_H
#include "Lexer.h"
#include <unordered_map>
#include <string>
#include "stack"
using namespace std;

class Parser{
public:
    enum class PS_Type
    {
        Var,
        Const,
        Operation,
        Empty
    };

    enum class PS_Operation
    {
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
        T, // unconditional transition
        F, // conditional transition
        I, // indexing
        Empty
    };

    struct PS_Element{
        string PS_Element_Name;
        PS_Type PS_Element_Type = PS_Type::Empty;
        PS_Operation PS_Element_Operation = PS_Operation::Empty;
        int position = -1; // for errors
        int num = 0;

        PS_Element(string name, const Token& T)
        {
            PS_Element_Type = PS_Type::Var;
            PS_Element_Name = name;
            position = T.getPosition();
        }
        PS_Element(int con, const Token& T)
        {
            PS_Element_Type = PS_Type::Const;
            num = con;
            position = T.getPosition();
        }
        PS_Element(PS_Operation operation, const Token& T)
        {
            PS_Element_Type = PS_Type::Operation;
            PS_Element_Operation = operation;
            position = T.getPosition();
        }
    };

    struct Data{
        vector <PS_Element> Polish_String;
        unordered_map<string, int> Var_Map;
        unordered_map<string, vector<int>> Mass_Map;
    };

    Data Get_data();
    void Run();
    Parser(vector <Token> List);

private:
    void Next_State();
    void Run_Generator_program();

    enum class Maps
    {
        Mass,
        Var
    };

    enum class State
    {
        A, // → beginMS end
        M, // → mass a[k];M | λ
        S, // → aH = Q;B | λ
        Q, // → (Q)F’T’ | aHF’T’ | kF’T’ | in(aH)F’T’
        T_tilda, // → +TT’ | -TT’ | λ
        T, // → (Q)F’ | aHF’ | kF’ | in(aH)F’
        F_tilda, // → *FF’ | \FF’ | λ
        F, // → (Q) | aH | k | in(aH)
        H, // → [Q] | λ
        B, // → mass a[k];B | aH = Q;B | if (C) then {SB}EB | while (C) do {SB}B | out(aH);B | λ
        E, // → else {S} | λ
        C, // → aHG
        G, // → < Q | > Q | == Q |  != Q
        Z, // →  λ
        Empty
    };

    enum class Generator_program
    {
        Empty,
        Var,
        Const,
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
        I, // indexing
        Program1,
        Program2,
        Program3,
        Program4,
        Program5,
        Program6,
        Program7,
        Program8,
        Program9,
        Program10
    };

    struct Stack_item
    {
        bool Is_terminal;
        TokenType token;
        State state;

        Stack_item(TokenType token): Is_terminal(true), token(token), state(State::Empty){};
        Stack_item(State state): Is_terminal(false), token(TokenType::Empty), state(state){};
    };

    Generator_program current_program;
    Token current_token;
    State current_state;
    Maps current_map;
    string current_var_name;
    stack<Stack_item> Automate_Stack;
    stack<Generator_program> Automate_Generator;
    stack<int> Labels;
    Data data;

    vector<Token> input_data;
};


#endif //TRANSLATOR_PARSER_H
