#include "Parser.h"

//======= Функция реализации приоритета операций =========

int Prior ( int AnotherElemType ){
    switch (AnotherElemType)
    {
    case Ass: case Less: case Greater: case Equal: case NotEqual:
        {
            return 1;
        }

        case LRb:
        {
            return 2;
        }

        case Plus: case Minus:
        {
            return 3;
        }

        case Div: case Mul:
        {
            return 4;
        }
    }
    return 0;
}

map <PS_Type, string> PS_Element :: OperationPSType
{
        {PS_Type::Var, "var"},
        {PS_Type::Const, "const"},
        {PS_Type::In, "in"},
        {PS_Type::Out, "out"},
        {PS_Type::Mass, "mass"},
        {PS_Type::Plus, "+"},
        {PS_Type::Minus, "-"},
        {PS_Type::Div, "/"},
        {PS_Type::Mul, "*"},
        {PS_Type::Ass, "="},
        {PS_Type::Greater, ">"},
        {PS_Type::Less, "<"},
        {PS_Type::Equal, "=="},
        {PS_Type::NotEqual, "!="},
        {PS_Type::Label, "label"},
        {PS_Type::T, "unconditional transition"},
        {PS_Type::F, "conditional transition"},
        {PS_Type::I, "indexing"}

};


PS_Element::PS_Element(Token token)
{
    Token in_token = token;
    Element = token.getToken();
    switch(token.getType()) {
        case Var: {
            Element_Type = PS_Type::Var;
            break;
        }
        case Const: {
            Element_Type = PS_Type::Const;
            break;
        }
        case In: {
            Element_Type = PS_Type::In;
            break;
        }
        case Out: {
            Element_Type = PS_Type::Out;
            break;
        }
        case Mass: {
            Element_Type = PS_Type::Mass;
            break;
        }
        case Plus: {
            Element_Type = PS_Type::Plus;
            break;
        }
        case Minus: {
            Element_Type = PS_Type::Minus;
            break;
        }
        case Div: {
            Element_Type = PS_Type::Div;
            break;
        }
        case Mul: {
            Element_Type = PS_Type::Mul;
            break;
        }
        case Ass: {
            Element_Type = PS_Type::Ass;
            break;
        }
        case Less: {
            Element_Type = PS_Type::Less;
            break;
        }
        case Greater: {
            Element_Type = PS_Type::Greater;
            break;
        }
        case Equal: {
            Element_Type = PS_Type::Equal;
            break;
        }
        case NotEqual: {
            Element_Type = PS_Type::NotEqual;
            break;
        }
        case Empty: {
            Element_Type = PS_Type::Empty;
            break;
        }
    }
}
PS_Element::PS_Element(string element, PS_Type element_type)
{
    Element = element;
    Element_Type = element_type;
}
const string &PS_Element::GetPS_Element() const
{
    return Element;
}

PS_Type PS_Element::GetPS_Element_Type() const
{
    return Element_Type;
}

string PS_Element::Translate_PS_Type(PS_Type elem)
{
    return OperationPSType[elem];
}

void PS_Element::GetPSInfo()
{
    cout << Element << " " << PS_Element::Translate_PS_Type(PS_Element::GetPS_Element_Type()) << endl;
}

void Polish_string::GetPolish_string()
{
    cout<< "Polska strochka:"<< endl;
    for(int i = 0; i<Polish_string.size(); i++)
    {
        Polish_string[i].GetPSInfo();
    }

}

map <string, int> Polish_string::Var_Map
{};
map <string, int*> Polish_string::Mass_Map
{};
map <string, int> Polish_string::Label_Map
{};

void Polish_string::Generate_PS(vector<Token> List)
{
    Input_string = List;
    vector<Token>Stack;
    int* null;
    int check = 0;
    k = 0;
    for (int i=0; i<Input_string.size(); i++)
    {
        k++;
        switch(Input_string[i].getType())
        {
            case Semicolon:
            {
                while(Stack.size()!=0)
                {
                    Polish_string.push_back(Stack.back());
                    Stack.pop_back();
                }
                break;
            }
            case RSb:
            {
                while(Stack.back().getType()!= LSb)
                {
                    Polish_string.push_back(Stack.back());
                    Stack.pop_back();
                }
                Stack.pop_back();
                if(Stack.back().getType()!= Mass)
                {
                    Polish_string.push_back(PS_Element("I", PS_Type::I));
                }
                break;
            }
            case RRb:
            {
                while(Stack.back().getType()!= LRb)
                {
                    Polish_string.push_back(Stack.back());
                    Stack.pop_back();
                }
                Stack.pop_back();
                break;
            }
            case Var:
            {
                //if (check != 0)
                //{
                    //Label_Map.
                //}
                Polish_string.push_back(Input_string[i]);
                if (!Stack.empty())
                {
                    if (Stack.back().getType() == Mass)
                    {
                        if (Mass_Map.find(Input_string[i].getToken()) == Mass_Map.end())
                        {
                            Mass_Map.insert(make_pair(Input_string[i].getToken(), null));
                        }
                    }
                    break;
                }
                if (Var_Map.find(Input_string[i].getToken()) == Var_Map.end())
                {
                    Var_Map.insert(make_pair(Input_string[i].getToken(), -1));
                }
                break;
            }
            case Const:
            {
                Polish_string.push_back(Input_string[i]);
                break;
            }
            case LRb:
            {
                Stack.push_back(Input_string[i]);
                break;
            }
            case LSb:
            {
                Stack.push_back(Input_string[i]);
                break;
            }
            case If:
            {
                Stack.push_back(Input_string[i]);
                break;
            }
            case Then:
            {
                Polish_string.push_back(PS_Element("\"m\"+ to_string(i)", PS_Type::Label));
                Label_Map.insert(make_pair("m"+ to_string(i), k));
                Polish_string.push_back(PS_Element("f", PS_Type::F));
                check++;
                break;
            }
            case Mass:
            {
                Stack.push_back(Input_string[i]);
                break;
            }
            case Plus: case Minus: case Div: case Mul: case  Ass: case Less: case Greater: case Equal: case NotEqual:
            {
                while(Stack.size()!=0 && Prior(Stack.back().getType()) >= Prior(Input_string[i].getType()))
                {
                    Polish_string.push_back(Stack.back());
                    Stack.pop_back();
                }
                Stack.push_back(Input_string[i]);
                break;
            }
        }
    }

    while(Stack.size()!=0)
    {
        Polish_string.push_back(Stack.back());
        Stack.pop_back();
    }
}

