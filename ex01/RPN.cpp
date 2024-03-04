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


std::vector<std::string> splitString(const std::string& str) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}
RPN::RPN(const std::string &numbers)
{
    this->data = splitString(numbers);
}

void RPN::check_expression()
{
    int number_counter = 0;
    int operator_counter = 0;
    
        std::vector<std::string>::iterator it = this->data.begin();
        while (it != this->data.end())
        {
            if((*it == "+" || *it == "-" || *it == "*" || *it == "/" )&& (it->size() == 1))
                operator_counter++;
            else if(std::isdigit((*it)[0]) || ((*it)[0] == '-' && std::isdigit((*it)[1])))
                number_counter++;
            else
                throw RPN::ExpressionError();
            it++;
        }
        if(number_counter - operator_counter != 1)
            throw RPN::ExpressionError();
    // this->calculate();
}



void RPN::calculate() {
    std::vector<std::string>::iterator it = data.begin();
    while (it != data.end()) {
        const std::string& token = *it;
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            double num = atof(token.c_str());
            stack.push(num);
        } else {
            try {
                pushOperator(token);
            } catch(const std::runtime_error& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                return;
            }
        }
        ++it;
    }
    if (!stack.empty()) {
        double result = stack.top();
        std::cout << "Result: " << result << std::endl;
    } else {
        std::cerr << "Error: Empty expression" << std::endl;
    }
}
