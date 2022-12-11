#include "Lexer.h"
#include "Parser.h"

int main()
{
    // enter the code
    string code;
    cout << "Enter your code: ";
    getline(cin, code);
    Lexer t(code);

    // submit the code for lexical analysis -> you will have a vector of tokens
    vector<Token>List = t.Analysis();
    for(int i =0; i < List.size(); i++)
    {
        List[i].GetInfo();
    }


    //you can use token methods to get information about it
    // example: List[0].getType(); List[0].getToken();

    Parser test(List); //creating an instance of a class Parser
    test.Run(); //calling a function that generates OPS

    //You can use method Get_data() to get specified element of Polish string (example: test.Get_data().Polish_String[0])
    //at the Polish string element you have 5 different characteristics: PS_Element_Name (for var and mass),
    // num (for const and label), position of element (from token), PS_Element_Operation (see description of enum class PS_Operation),
    // PS_Element_Type (var, const or operation)

    //You can use method Get_data() to get specified element of Var_Map or Mass_Map (example: test.Get_data().Var_Map["x"])
    // example: you have program: begin x=4; if (x<5) then {x=0;} else {x=2;},
    // after Run() you will have OPS: x4= x5< 13F x0= 16T x2=, where 13 and 16 are labels, that shows what element of OPS you
    // should jump to (the calculation of the elements of OPS is carried out from 0)


    return 0;
}