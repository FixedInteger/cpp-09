#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    std::cout << "BitcoinExchange constructor" << std::endl;
}

BitcoinExchange::~BitcoinExchange()
{
    std::cout << "BitcoinExchange destructor" << std::endl;
}

void BitcoinExchange::readData(const std::string &filename)
{
    std::ifstream
    file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return;
    }
    std::string line;

    while (std::getline(file, line))
    {
        std::cout << line << std::endl;
    }
    file.close();
}
