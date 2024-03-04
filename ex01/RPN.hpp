#ifndef RPN_S
#define RPN_S

#include <iostream>
#include <stack>
#include <set>
#include <string>
#include <sstream>
#include <cctype>
#include <stdexcept>

class RPN
{
public:
    RPN();
    ~RPN();
    RPN(const RPN &other);
    RPN &operator=(const RPN &other);
    void check_expression();
    void pushOperand(double num) {
        // Push the operand onto the stack
        stack.push(num);
    }
    void pushOperator(const std::string& op) {
        // Perform operation and push result back to the stack
        double operand2 = stack.top();
        stack.pop();
        double operand1 = stack.top();
        stack.pop();
        double result;
        if (op == "+")
            result = operand1 + operand2;
        else if (op == "-")
            result = operand1 - operand2;
        else if (op == "*")
            result = operand1 * operand2;
        else if (op == "/") {
            if (operand2 == 0)
                throw std::runtime_error("Division by zero");
            result = operand1 / operand2;
        }
        stack.push(result);
    }
    RPN(const std::string &numbers);
    void calculate();
    class FileError : public std::exception
    {
    public:
        virtual const char *what() const throw()
        {
            return "FileError";
        }
    };
    class ExpressionError : public std::exception
    {
    public:
        virtual const char *what() const throw()
        {
            return "ExpressionError";
        }
    };

private:
    std::vector<std::string> data;
    std::stack<double> stack;
};

#endif // RPN_S


