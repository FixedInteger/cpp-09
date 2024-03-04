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
        void check_expression(const std::string &expression);
        void check_file(const std::string &filename);
        RPN(const std::string &filename);
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
        std::set<std::string> data;
        std::stack<double> stack;
};


#endif