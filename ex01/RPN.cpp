#include "RPN.hpp"
#include <fstream>
RPN::RPN()
{
    std::cout << "RPN constructor" << std::endl;
}

RPN::~RPN()
{
    std::cout << "RPN destructor" << std::endl;
}

RPN::RPN(const RPN &other)
{
    std::cout << "RPN copy constructor" << std::endl;
    this->data = other.data;
}

RPN &RPN::operator=(const RPN &other)
{
    std::cout << "RPN operator=" << std::endl;
    this->data = other.data;
    return *this;
}

void RPN::check_expression(const std::string &expression)
{
    std::stringstream ss;
    ss << expression;
    std::string token;
    while(ss >> token)
    {
        if(token.size() == 1 && !isdigit(token[0]))
        {
            if(token[0] != '+' && token[0] != '-' && token[0] != '*' && token[0] != '/')
                throw ExpressionError();
        }
        else
        {
            for(size_t i = 0; i < token.size(); i++)
            {
                if(!isdigit(token[i]) && token[i] != '.')
                    throw ExpressionError();
            }
        }
    }
}

RPN::RPN(const std::string &number)
{
    check_expression(number);
    check_file(number);
    std::ifstream file(number);
    std::string line;
    while(std::getline(file, line))
    {
        data.insert(line);
    }
    file.close();
}


//calculate
void RPN::calculate()
{
    std::set<std::string>::iterator it;
    for(it = data.begin(); it != data.end(); it++)
    {
        std::stringstream ss;
        ss << *it;
        std::string token;
        while(ss >> token)
        {
            if(token.size() == 1 && !isdigit(token[0]))
            {
                double a = stack.top();
                stack.pop();
                double b = stack.top();
                stack.pop();
                if(token[0] == '+')
                    stack.push(b + a);
                else if(token[0] == '-')
                    stack.push(b - a);
                else if(token[0] == '*')
                    stack.push(b * a);
                else if(token[0] == '/')
                    stack.push(b / a);
            }
            else
            {
                stack.push(std::stod(token));
            }
        }
        std::cout << stack.top() << std::endl;
        stack.pop();
    }
}


void RPN::check_file(const std::string &filename)
{
    std::ifstream file(filename);
    if(!file.is_open())
        throw FileError();
    file.close();
}