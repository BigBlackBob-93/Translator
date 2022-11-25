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
    Var,       // a
    Const,     // k
    Id,        // ReservedWord
    Plus,      //+
    Minus,     // -
    Div,       // /
    Mul,       // *
    Ass,       // =
    LRb,       // (
    RRb,       // )
    LSb,       // [
    RSb,       // ]
    Greater,   // >
    Less,      // <
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
    static vector <string> ReservedWord;
    Token(string& token, int& position);
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