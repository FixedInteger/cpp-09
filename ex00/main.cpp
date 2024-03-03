#include "BitcoinExchange.hpp"
int main(int ac , char **av)
{
    (void)ac;
    (void)av;
    try
    {

        std::cout <<"-----------------------------------" << std::endl;
        std::cout <<"|  Welcome to Bitcoin Exchange     |" << std::endl;
        std::cout <<"-----------------------------------" << std::endl;
        while(1)
        {
            std::cout << "Press enter to continue :" << std::endl;
            std::string date;
            std::string filename;
            std::cout << "Enter the date in the format YYYY-MM-DD" << std::endl;
            std::getline(std::cin, date);
            std::cout << "Enter the filename" << std::endl;
            std::getline(std::cin, filename);
            BitcoinExchange exchange(filename, date);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;   
}