#include "Lexer.h"

SymbolType DefineSymbol(char& symbol) {
    if (isdigit(symbol)) return Digit;
    if (isalpha(symbol)) return Letter;
    if (isspace(symbol)) return Space;
    return Operation;
}

Token :: Token(string& token, int& position){
    this->token = token;
    this->position = position;
    this->type = Empty;
}
map <string, TokenType> Token :: OperationType{
        {"+", Plus},
        {"-", Minus},
        {"/", Div},
        {"*", Mul},
        {"=", Ass},
        {"(", LRb},
        {")", RRb},
        {"[", LSb},
        {"]", RSb},
        {">", Greater},
        {"<", Less},
        {"==", Equal},
        {"!=", NotEqual},
        {";", Semicolon},
        {"{", LCb},
        {"}", RCb}
};
vector <string> Token:: ReservedWord = {
        "begin",
        "end",
        "mass",
        "if",
        "then",
        "else",
        "while",
        "do",
        "in",
        "out"
};
void Token :: GetInfo() { cout << " token: " << token << " type: " << type; }

bool Token :: DefineToken(SymbolType& symbol_type) {
    switch (symbol_type) {
        case Digit: this->type = Const; return true;
        case Letter: this->DefineLetterType(); return true;
        case Operation: if (this->DefineOperationType()) return true; else return false;;
        default: cout << "\n symbol_type is incorrect in Token.Define()"; exit(0);
    }
}
bool Token :: DefineOperationType() {
    if (OperationType.find(token) != OperationType.end()) {
        type = OperationType[token];
        return true;
    }
    return false;
}
void Token :: DefineLetterType() {
    for (auto & i : ReservedWord)
        if (token == i) {
            type = Id;
            return;
        }
    type = Var;
}

Lexer:: Lexer(string& code){
    this->code = code;
    this->position = 0;
}
vector<Token> Lexer:: Analysis() {
    string symbols;
    SymbolType symbol_type;

    while (position < code.length())
    {
        symbol_type = DefineSymbol(code[position]);
        symbols.push_back(code[position]);
        if (symbol_type == Space) {
            position++;
            symbols.clear();
        }
        else {
            while ((symbol_type == DefineSymbol(code[position + 1])) && (position < code.length() - 1)) {
                symbols.push_back(code[position + 1]);
                position++;
            }
            Token token(symbols, position);
            if (token.DefineToken(symbol_type)) {
                TokenList.push_back(token);
                symbols.clear();
                position++;
            }
            else {
                bool res = false;
                while (!res) {
                    symbols.pop_back();
                    position--;
                    if (symbols.empty()) {
                        cout << "\n token_type is incorrect in position: " << ++position;
                        exit(0);
                    }
                    Token new_token(symbols, position);
                    res = new_token.DefineToken(symbol_type);
                    if (res)TokenList.push_back(new_token);
                }
                symbols.clear();
                position++;
            }
        }
    }
    return this->TokenList;
}