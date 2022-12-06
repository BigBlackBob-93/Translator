#include "Parser.h"

//======= Функция реализации приоритета операций =========

int Prior ( int AnotherElemType ){
    switch (AnotherElemType)
    {
    case Ass:
        {
            return 1;
        }

        case LRb: case LSb:
        {
            return 2;
        }

        case Plus: case Minus: case Less: case Greater: case Equal: case NotEqual:
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

void Polish_string::GetInfoPolish_string()
{
    cout<< "Polska strochka:"<< endl;
    for(int i = 0; i<Polish_string.size(); i++)
    {
        Polish_string[i].GetPSInfo();
    }
}

vector<PS_Element> Polish_string::GetPolish_string()
{
    return Polish_string;
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
    k = 0;
    label_name = 0;
    map <string, int> :: reverse_iterator it;
    for (int i=0; i<Input_string.size(); i++)
    {
        switch(Input_string[i].getType())
        {
            case Semicolon:
            {
                while(Stack.size()!=0)
                {
                    if (Stack.back().getType() != Else)
                    {
                        k++;
                        Polish_string.push_back(Stack.back());
                    }
                    Stack.pop_back();
                }
                break;
            }
            case RSb:
            {
                while(Stack.back().getType()!= LSb)
                {
                    k++;
                    Polish_string.push_back(Stack.back());
                    Stack.pop_back();
                }
                Stack.pop_back();
                if(Stack.back().getType()!= Mass)
                {
                    k++;
                    Polish_string.push_back(PS_Element("I", PS_Type::I));
                }
                break;
            }
            case RRb:
            {
                while(Stack.back().getType()!= LRb)
                {
                    k++;
                    Polish_string.push_back(Stack.back());
                    Stack.pop_back();
                }
                Stack.pop_back();
                break;
            }
            case RCb:
            {
                if (Stack.back().getType() != Else)
                {
                    it = Label_Map.rbegin();
                    it->second = k+2;
                }
                while(Stack.back().getType()!= LCb)
                {
                    if (Stack.back().getType() != Else)
                    {
                        k++;
                        Polish_string.push_back(Stack.back());
                    }
                    Stack.pop_back();
                }
                Stack.pop_back();
                break;
            }
            case Var:
            {
                k++;
                Polish_string.push_back(Input_string[i]);
                if (!Stack.empty())
                {
                    if (Stack.back().getType() == Mass)
                    {
                        if (Mass_Map.find(Input_string[i].getToken()) == Mass_Map.end())
                        {
                            Mass_Map.insert(make_pair(Input_string[i].getToken(), null));
                        }
                        break;
                    }

                }
                if (Var_Map.find(Input_string[i].getToken()) == Var_Map.end())
                {
                    Var_Map.insert(make_pair(Input_string[i].getToken(), -1));
                }
                break;
            }
            case Const:
            {
                k++;
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
            case LCb:
            {
                Stack.push_back(Input_string[i]);
                break;
            }
            case If:
            {
                break;
            }
            case Then:
            {
                k++;
                label_name++;
                Polish_string.push_back(PS_Element("m"+ to_string(label_name ), PS_Type::Label));
                Label_Map.insert(make_pair("m"+ to_string(label_name), 0));
                k++;
                Polish_string.push_back(PS_Element("f", PS_Type::F));
                break;
            }
            case Else:
            {
                Stack.push_back(Input_string[i]);
                it = Label_Map.rbegin();
                it->second = k+3;
                k++;
                label_name++;
                Polish_string.push_back(PS_Element("m"+ to_string(label_name), PS_Type::Label));
                Label_Map.insert(make_pair("m"+ to_string(label_name), 0));
                k++;
                Polish_string.push_back(PS_Element("t", PS_Type::T));
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
                    k++;
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
        k++;
        Polish_string.push_back(Stack.back());
        Stack.pop_back();
    }
}

