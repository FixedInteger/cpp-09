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


RPN::RPN(const std::string &numbers)
{
    std::stringstream ss;
    ss << numbers;
    std::string token;
    while(std::getline(ss, token, ' '))
    {
        if(token.size() == 0)
            continue;
        std::stringstream ss2;
        ss2 << token;
        double number;
        ss2 >> number;
        this->data.insert(token);
    }

}

void RPN::check_expression()
{
    std::set<std::string>::iterator it;
    int number_count = 0;
    int operator_count = 0;
    for(it = this->data.begin(); it != this->data.end(); it++)
    {
        std::string token = *it;
        if(token.size() == 0)
            continue;
        if(token.size() == 1 && !isdigit(token[0]))
        {
            if(token[0] != '+' && token[0] != '-' && token[0] != '*' && token[0] != '/')
                throw ExpressionError();
            operator_count++;
        }
        else
        {
            std::stringstream ss;
            ss << token;
            double number;
            ss >> number;
            if(ss.fail())
                throw ExpressionError();
            number_count++;
        }
    }
    if(number_count - operator_count != 1)
        throw ExpressionError();
   
}
