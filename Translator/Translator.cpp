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

SymbolType Define(char& symbol) {
    if (isdigit(symbol)) return Digit;
    if (isalpha(symbol)) return Letter;
    if (isspace(symbol)) return Space;
    return Operation;
}

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
    RCb        // }
};
map <string, TokenType> OperationType{
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
vector <string> ReservedWord = {
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

class Token {
    string token;
    TokenType type;
    int position;

public:
    Token(string& token, int& position) : token(token), position(position)
    {}

    string GetToken() { return token; }
    TokenType GetType() { return type; }
    void GetInfo() { cout << " token: " << token << " type: " << type; }

    bool Define(SymbolType& symbol_type) {
        switch (symbol_type) {
        case Digit: this->type = Const; return true;
        case Letter: this->DefineLetterType(); return true;
        case Operation: if (this->DefineOperationType()) return true; else return false;;
        default: cout << "\n symbol_type is incorrect in Token.Define()"; exit(0);
        }
    }
    bool DefineOperationType() {
        if (OperationType.find(token) != OperationType.end()) {
            type = OperationType[token];
            return true;
        }
        return false;
    }
    void DefineLetterType() {
        for (int i = 0; i < ReservedWord.size(); i++) {
            if (token == ReservedWord[i]) {
                type = Id;
                return;
            }
        }
        type = Var;
    }
};

class Lexer {
    vector <Token> TokenList;
    int position;
    string code;
public:
    Lexer(string& code) : code(code)
    {}

    vector<Token> Analysis() {
        string symbols;
        SymbolType symbol_type;

        while (position < code.length())
        {
            symbol_type = Define(code[position]);
            symbols.push_back(code[position]);
            if (symbol_type == Space) {
                position++;
                symbols.clear();
            }
            else {
                while ((symbol_type == Define(code[position + 1])) && (position < code.length() - 1)) {
                    symbols.push_back(code[position + 1]);
                    position++;
                }
                Token token(symbols, position);
                if (token.Define(symbol_type)) {
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
                        Token token(symbols, position);
                        res = token.Define(symbol_type);
                        if (res)TokenList.push_back(token);
                    }
                    symbols.clear();
                    position++;
                }
            }

        }
        return this->TokenList;
    }
};

int main()
{
    string code = "x++;";
    Lexer t(code);
    vector<Token>List = t.Analysis();
    for (int i = 0; i < List.size(); i++) {
        cout << endl;
        List[i].GetInfo();
    }
    std::cout << "υσι";
    return 0;
}
