#include "RPN.hpp"

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        std::cerr << "usage: ./rpn filename" << std::endl;
        return 1;
    }
    try
    {
        RPN rpn(argv[1]);
        rpn.check_expression();
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}