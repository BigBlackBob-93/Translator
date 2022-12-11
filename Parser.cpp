#include "Parser.h"
#include <stdexcept>
using namespace std;

void Parser::Next_State()
{
    switch (current_state)
    {
        case State::A:
        {
            switch (current_token.getType())
            {
                case TokenType::Begin:
                {
                    Automate_Stack.emplace(TokenType::End);
                    Automate_Stack.emplace(State::S);
                    Automate_Stack.emplace(State::M);
                    Automate_Stack.emplace(TokenType::Begin);

                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    break;
                }
                default:
                {
                    string message = "Parser error, position: " + to_string(current_token.getPosition());
                    throw runtime_error(message);
                }
            }
            break;
        }
        case State::M:
        {
            switch (current_token.getType())
            {
                case TokenType::Mass:
                {
                    Automate_Stack.emplace(State::M);
                    Automate_Stack.emplace(TokenType::Semicolon);
                    Automate_Stack.emplace(TokenType::RSb);
                    Automate_Stack.emplace(TokenType::Const);
                    Automate_Stack.emplace(TokenType::LSb);
                    Automate_Stack.emplace(TokenType::Var);
                    Automate_Stack.emplace(TokenType::Mass);

                    Automate_Generator.emplace(Generator_program::Mass);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Program9);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Program8);
                    Automate_Generator.emplace(Generator_program::Program7);
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        case State::S:
        {
            switch (current_token.getType())
            {
                case TokenType::Var:
                {
                    Automate_Stack.emplace(State::B);
                    Automate_Stack.emplace(TokenType::Semicolon);
                    Automate_Stack.emplace(State::Q);
                    Automate_Stack.emplace(TokenType::Ass);
                    Automate_Stack.emplace(State::H);
                    Automate_Stack.emplace(TokenType::Var);

                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Ass);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Program10);

                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        case State::Q:
        {
            switch (current_token.getType())
            {
                case TokenType::LRb:
                {
                    Automate_Stack.emplace(State::T_tilda);
                    Automate_Stack.emplace(State::F_tilda);
                    Automate_Stack.emplace(TokenType::RRb);
                    Automate_Stack.emplace(State::Q);
                    Automate_Stack.emplace(TokenType::LRb);

                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    break;
                }
                case TokenType::Var:
                {
                    Automate_Stack.emplace(State::T_tilda);
                    Automate_Stack.emplace(State::F_tilda);
                    Automate_Stack.emplace(State::H);
                    Automate_Stack.emplace(TokenType::Var);

                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Var);
                    break;
                }
                case TokenType::Const:
                {
                    Automate_Stack.emplace(State::T_tilda);
                    Automate_Stack.emplace(State::F_tilda);
                    Automate_Stack.emplace(TokenType::Const);

                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Const);
                    break;
                }
                case TokenType::In:
                {
                    Automate_Stack.emplace(State::T_tilda);
                    Automate_Stack.emplace(State::F_tilda);
                    Automate_Stack.emplace(TokenType::RRb);
                    Automate_Stack.emplace(State::H);
                    Automate_Stack.emplace(TokenType::Var);
                    Automate_Stack.emplace(TokenType::LRb);
                    Automate_Stack.emplace(TokenType::In);

                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::In);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Var);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    break;
                }
                default:
                {
                    string message = "Parser error, position: "+ to_string(current_token.getPosition());
                    throw runtime_error(message);
                }
            }
            break;
        }
        case State::T_tilda:
        {
            switch (current_token.getType())
            {
                case TokenType::Plus:
                {
                    Automate_Stack.emplace(State::T_tilda);
                    Automate_Stack.emplace(State::T);
                    Automate_Stack.emplace(TokenType::Plus);

                    Automate_Generator.emplace(Generator_program::Plus);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    break;
                }
                case TokenType::Minus:
                {
                    Automate_Stack.emplace(State::T_tilda);
                    Automate_Stack.emplace(State::T);
                    Automate_Stack.emplace(TokenType::Minus);

                    Automate_Generator.emplace(Generator_program::Minus);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        case State::T:
        {
            switch (current_token.getType())
            {
                case TokenType::LRb:
                {
                    Automate_Stack.emplace(State::F_tilda);
                    Automate_Stack.emplace(TokenType::RRb);
                    Automate_Stack.emplace(State::Q);
                    Automate_Stack.emplace(TokenType::LRb);

                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    break;
                }
                case TokenType::Var:
                {
                    Automate_Stack.emplace(State::F_tilda);
                    Automate_Stack.emplace(State::H);
                    Automate_Stack.emplace(TokenType::Var);

                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Var);
                    break;
                }
                case TokenType::Const:
                {
                    Automate_Stack.emplace(State::F_tilda);
                    Automate_Stack.emplace(TokenType::Const);

                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Const);
                    break;
                }
                case TokenType::In:
                {
                    Automate_Stack.emplace(State::F_tilda);
                    Automate_Stack.emplace(TokenType::RRb);
                    Automate_Stack.emplace(State::H);
                    Automate_Stack.emplace(TokenType::Var);
                    Automate_Stack.emplace(TokenType::LRb);
                    Automate_Stack.emplace(TokenType::In);

                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::In);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Var);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    break;
                }
                default:
                {
                    string message = "Parser error, position: "+ to_string(current_token.getPosition());
                    throw runtime_error(message);
                }
            }
            break;
        }
        case State::F_tilda:
        {
            switch (current_token.getType())
            {
                case TokenType::Mul:
                {
                    Automate_Stack.emplace(State::F_tilda);
                    Automate_Stack.emplace(State::F);
                    Automate_Stack.emplace(TokenType::Mul);

                    Automate_Generator.emplace(Generator_program::Mul);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    break;
                }
                case TokenType::Div:
                {
                    Automate_Stack.emplace(State::F_tilda);
                    Automate_Stack.emplace(State::F);
                    Automate_Stack.emplace(TokenType::Div);

                    Automate_Generator.emplace(Generator_program::Div);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        case State::F:
        {
            switch(current_token.getType())
            {
                case TokenType::LRb:
                {
                    Automate_Stack.emplace(TokenType::RRb);
                    Automate_Stack.emplace(State::Q);
                    Automate_Stack.emplace(TokenType::LRb);

                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    break;
                }
                case TokenType::Var:
                {
                    Automate_Stack.emplace(State::H);
                    Automate_Stack.emplace(TokenType::Var);

                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Var);
                    break;
                }
                case TokenType::Const:
                {
                    Automate_Stack.emplace(TokenType::Var);

                    Automate_Generator.emplace(Generator_program::Const);
                    break;
                }
                case TokenType::In:
                {
                    Automate_Stack.emplace(TokenType::RRb);
                    Automate_Stack.emplace(State::H);
                    Automate_Stack.emplace(TokenType::Var);
                    Automate_Stack.emplace(TokenType::LRb);
                    Automate_Stack.emplace(TokenType::In);

                    Automate_Generator.emplace(Generator_program::In);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Var);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    break;
                }
                default:
                {
                    string message = "Parser error, position: "+ to_string(current_token.getPosition());
                    throw runtime_error(message);
                }
            }
            break;
        }
        case State::H:
        {
            switch(current_token.getType())
            {
                case TokenType::LSb:
                {
                    Automate_Stack.emplace(TokenType::RSb);
                    Automate_Stack.emplace(State::Q);
                    Automate_Stack.emplace(TokenType::LSb);

                    Automate_Generator.emplace(Generator_program::I);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        case State::B:
        {
            switch(current_token.getType())
            {
                case TokenType::Mass:
                {
                    Automate_Stack.emplace(State::B);
                    Automate_Stack.emplace(TokenType::Semicolon);
                    Automate_Stack.emplace(TokenType::RSb);
                    Automate_Stack.emplace(TokenType::Const);
                    Automate_Stack.emplace(TokenType::LSb);
                    Automate_Stack.emplace(TokenType::Var);
                    Automate_Stack.emplace(TokenType::Mass);

                    Automate_Generator.emplace(Generator_program::Mass);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Program9);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Program8);
                    Automate_Generator.emplace(Generator_program::Program7);
                    break;
                }
                case TokenType::Var:
                {
                    Automate_Stack.emplace(State::B);
                    Automate_Stack.emplace(TokenType::Semicolon);
                    Automate_Stack.emplace(State::Q);
                    Automate_Stack.emplace(TokenType::Ass);
                    Automate_Stack.emplace(State::H);
                    Automate_Stack.emplace(TokenType::Var);

                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Ass);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Program10);
                    break;
                }
                case TokenType::If:
                {
                    Automate_Stack.emplace(State::B);
                    Automate_Stack.emplace(State::E);
                    Automate_Stack.emplace(TokenType::RCb);
                    Automate_Stack.emplace(State::B);
                    Automate_Stack.emplace(State::S);
                    Automate_Stack.emplace(TokenType::LCb);
                    Automate_Stack.emplace(TokenType::Then);
                    Automate_Stack.emplace(TokenType::RRb);
                    Automate_Stack.emplace(State::C);
                    Automate_Stack.emplace(TokenType::LRb);
                    Automate_Stack.emplace(TokenType::If);

                    Automate_Generator.emplace(Generator_program::Program3);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Program1);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    break;
                }
                case TokenType::While:
                {
                    Automate_Stack.emplace(State::B);
                    Automate_Stack.emplace(TokenType::RCb);
                    Automate_Stack.emplace(State::B);
                    Automate_Stack.emplace(State::S);
                    Automate_Stack.emplace(TokenType::LCb);
                    Automate_Stack.emplace(TokenType::Do);
                    Automate_Stack.emplace(TokenType::RRb);
                    Automate_Stack.emplace(State::C);
                    Automate_Stack.emplace(TokenType::LRb);
                    Automate_Stack.emplace(TokenType::While);

                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Program5);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Program1);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Program4);
                    break;
                }
                case TokenType::Out:
                {
                    Automate_Stack.emplace(State::B);
                    Automate_Stack.emplace(TokenType::Semicolon);
                    Automate_Stack.emplace(TokenType::RRb);
                    Automate_Stack.emplace(State::H);
                    Automate_Stack.emplace(TokenType::Var);
                    Automate_Stack.emplace(TokenType::LRb);
                    Automate_Stack.emplace(TokenType::Out);

                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Out);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Var);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        case State::E:
        {
            switch (current_token.getType())
            {
                case TokenType::Else:
                {
                    Automate_Stack.emplace(TokenType::RCb);
                    Automate_Stack.emplace(State::S);
                    Automate_Stack.emplace(TokenType::LCb);
                    Automate_Stack.emplace(TokenType::Else);

                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Program2);
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        case State::C:
        {
            switch (current_token.getType())
            {
                case TokenType::Var:
                {
                    Automate_Stack.emplace(State::G);
                    Automate_Stack.emplace(State::H);
                    Automate_Stack.emplace(TokenType::Var);

                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Var);
                    break;
                }
                default:
                {
                    string message = "Parser error, position: "+ to_string(current_token.getPosition());
                    throw runtime_error(message);
                }
            }
            break;
        }
        case State::G:
        {
            switch (current_token.getType())
            {
                case TokenType::Less:
                {
                    Automate_Stack.emplace(State::Z);
                    Automate_Stack.emplace(State::Q);
                    Automate_Stack.emplace(TokenType::Less);

                    Automate_Generator.emplace(Generator_program::Less);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    break;
                }
                case TokenType::Greater:
                {
                    Automate_Stack.emplace(State::Z);
                    Automate_Stack.emplace(State::Q);
                    Automate_Stack.emplace(TokenType::Greater);

                    Automate_Generator.emplace(Generator_program::Greater);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    break;
                }
                case TokenType::Equal:
                {
                    Automate_Stack.emplace(State::Z);
                    Automate_Stack.emplace(State::Q);
                    Automate_Stack.emplace(TokenType::Equal);

                    Automate_Generator.emplace(Generator_program::Equal);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    break;
                }
                case TokenType::NotEqual:
                {
                    Automate_Stack.emplace(State::Z);
                    Automate_Stack.emplace(State::Q);
                    Automate_Stack.emplace(TokenType::NotEqual);

                    Automate_Generator.emplace(Generator_program::NotEqual);
                    Automate_Generator.emplace(Generator_program::Empty);
                    Automate_Generator.emplace(Generator_program::Empty);
                    break;
                }
                default:
                {
                    string message = "Parser error, position: "+ to_string(current_token.getPosition());
                    throw runtime_error(message);
                }
            }
            break;
        }
        case State::Z:
        {
            break;
        }
        case State::Empty:
        {
            default:
                string message = "Parser error, position: "+ to_string(current_token.getPosition());
                throw runtime_error(message);
        }
    }
}

void Parser::Run_Generator_program()
{
    switch (current_program)
    {
        case Generator_program::Empty:
        {
            break;
        }
        case Generator_program::Var:
        {
            data.Polish_String.emplace_back(current_token.getToken(), current_token);
            break;
        }
        case Generator_program::Const:
        {
            data.Polish_String.emplace_back(stoi(current_token.getToken()), current_token);
            break;
        }
        case Generator_program::In:
        {
            data.Polish_String.emplace_back(PS_Operation::In, current_token);
            break;
        }
        case Generator_program::Out:
        {
            data.Polish_String.emplace_back(PS_Operation::Out, current_token);
            break;
        }
        case Generator_program::Mass:
        {
            data.Polish_String.emplace_back(PS_Operation::Mass, current_token);
            break;
        }
        case Generator_program::Plus:
        {
            data.Polish_String.emplace_back(PS_Operation::Plus, current_token);
            break;
        }
        case Generator_program::Minus:
        {
            data.Polish_String.emplace_back(PS_Operation::Minus, current_token);
            break;
        }
        case Generator_program::Div:
        {
            data.Polish_String.emplace_back(PS_Operation::Div, current_token);
            break;
        }
        case Generator_program::Mul:
        {
            data.Polish_String.emplace_back(PS_Operation::Mul, current_token);
            break;
        }
        case Generator_program::Ass:
        {
            data.Polish_String.emplace_back(PS_Operation::Ass, current_token);
            break;
        }
        case Generator_program::Less:
        {
            data.Polish_String.emplace_back(PS_Operation::Less, current_token);
            break;
        }
        case Generator_program::Greater:
        {
            data.Polish_String.emplace_back(PS_Operation::Greater, current_token);
            break;
        }
        case Generator_program::Equal:
        {
            data.Polish_String.emplace_back(PS_Operation::Equal, current_token);
            break;
        }
        case Generator_program::NotEqual:
        {
            data.Polish_String.emplace_back(PS_Operation::NotEqual, current_token);
            break;
        }
        case Generator_program::I:
        {
            data.Polish_String.emplace_back(PS_Operation::I, current_token);
            break;
        }
        case Generator_program::Program1:
        {
            Labels.push(data.Polish_String.size());
            data.Polish_String.emplace_back(0, current_token);
            data.Polish_String.emplace_back(PS_Operation::F, current_token);
            break;
        }
        case Generator_program::Program2:
        {
            int place = Labels.top();
            Labels.pop();
            Labels.push(data.Polish_String.size());
            data.Polish_String.emplace_back(0, current_token);
            data.Polish_String.emplace_back(PS_Operation::T, current_token);
            data.Polish_String[place].num = data.Polish_String.size();
            break;
        }
        case Generator_program::Program3:
        {
            int place = Labels.top();
            Labels.pop();
            data.Polish_String[place].num = data.Polish_String.size();
            break;
        }
        case Generator_program::Program4:
        {
            Labels.push(data.Polish_String.size());
            break;
        }
        case Generator_program::Program5:
        {
            int place = Labels.top();
            Labels.pop();
            data.Polish_String.emplace_back(Labels.top(), current_token);
            Labels.pop();
            data.Polish_String.emplace_back(PS_Operation::T, current_token);
            data.Polish_String[place].num = data.Polish_String.size();
            break;
        }
        case Generator_program::Program6:
        {
            current_map = Maps::Var;
            break;
        }
        case Generator_program::Program7:
        {
            current_map = Maps::Mass;
            break;
        }
        case Generator_program::Program8:
        {
            if(data.Mass_Map.count(current_token.getToken()))
            {
                string message = "A Array with the same name already exists, rename the Array, position: "+ to_string(current_token.getPosition());
                throw runtime_error(message);
            }

            if (current_map == Maps::Mass)
            {
                current_var_name = current_token.getToken();
            }
            data.Polish_String.emplace_back(current_token.getToken(), current_token);
            break;
        }
        case Generator_program::Program9:
        {
            data.Mass_Map.insert({current_var_name, vector<int>(stoi(current_token.getToken()))});
            break;
        }
        case Generator_program::Program10:
        {
            current_map = Maps::Var;
            data.Polish_String.emplace_back(current_token.getToken(), current_token);

                if (data.Var_Map.count(current_token.getToken()))
                {
                    break;
                }
                else
                {
                    data.Var_Map.insert({current_token.getToken(), -1});
                }
            break;
        }
        default:
        {
            string message = "Parser error, position: "+ to_string(current_token.getPosition());
            throw runtime_error(message);
        }
    }
}

void Parser::Run()
{
    Automate_Stack.emplace(State::A);
    Automate_Generator.push(Generator_program::Empty);
    current_map = Maps::Var;
    int current_token_index = 0;
    current_token = input_data[current_token_index];

    while (!Automate_Stack.empty() && !Automate_Generator.empty())
    {
        Stack_item current_stack_item = Automate_Stack.top();
        Automate_Stack.pop();
        current_state = current_stack_item.state;
        current_program = Automate_Generator.top();
        Automate_Generator.pop();

        Run_Generator_program();

        if (current_token.getType() != End)
        {
            if (current_stack_item.Is_terminal)
            {
                if(current_stack_item.token == current_token.getType())
                {
                    current_token_index++;
                    current_token = input_data[current_token_index];
                }
                else
                {
                    string message = "Parser error, unexpected token: "+ to_string(current_token.getPosition());
                    throw runtime_error(message);
                }
            }
            else
            {
                Next_State();
            }
        }
    }

    if(current_token.getType() != TokenType::End)
    {
        string message = "Parser error, unrecognized token: "+ to_string(current_token.getPosition());
        throw runtime_error(message);
    }
}

Parser::Parser(vector<Token> List) : current_token(current_token)
{
    input_data = List;
}

Parser::Data Parser::Get_data() {
    return data;
}




