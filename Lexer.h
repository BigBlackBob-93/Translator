#ifndef TRANSLATOR_LEXER_H
#define TRANSLATOR_LEXER_H

#include <vector>
#include <map>
#include <iostream>
using namespace std;

enum SymbolType {
    Digit,
    Letter,
    Operation,
    Space
};

SymbolType DefineSymbol(char& symbol);

enum TokenType {
    Var = 1,   // a
    Const,     // k
    If,
    Then,
    Else,
    While,
    Do,
    In,
    Out,
    End,
    Begin,
    Mass,
    Plus,      //+
    Minus,     // -
    Div,       // /
    Mul,       // *
    Ass,       // =
    LRb,       // (
    RRb,       // )
    LSb,       // [
    RSb,       // ]
    Less,      // <
    Greater,   // >
    Equal,     // ==
    NotEqual,  // !=
    Semicolon, // ;
    LCb,       // {
    RCb,       // }
    Empty
};

class Token {
    string token;
    TokenType type;
    int position;
public:
    static map <string, TokenType> OperationType;
    Token(string& token, int& position);
    [[nodiscard]] const string &getToken() const;
    [[nodiscard]] TokenType getType() const;
    void GetInfo();
    bool DefineToken(SymbolType& symbol_type);
    bool DefineOperationType();
    void DefineLetterType();
};

class Lexer {
    vector <Token> TokenList;
    int position;
    string code;
public:
    explicit Lexer(string& code);
    vector<Token> Analysis();
};
#endif //TRANSLATOR_LEXER_H