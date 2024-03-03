#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    std::cout << "BitcoinExchange constructor" << std::endl;
}

BitcoinExchange::~BitcoinExchange()
{
    std::cout << "BitcoinExchange destructor" << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    std::cout << "BitcoinExchange copy constructor" << std::endl;
    this->data = other.data;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    std::cout << "BitcoinExchange operator=" << std::endl;
    this->data = other.data;
    return *this;
}

void BitcoinExchange::check_date(const std::string &date)
{
    if(date.size() <= 1)
        throw DateEmpty();
    std::stringstream ss;
    ss << date;
    std::string token;
    std::vector<std::string> tokens;
    while(std::getline(ss, token, '-'))
        tokens.push_back(token);
    if(tokens.size() != 3)
        throw DateError();
    if(tokens[0].size() != 4 || tokens[1].size() != 2 || tokens[2].size() != 2)
        throw DateError();
    std::vector<std::string>::iterator it;
    for(it = tokens.begin(); it != tokens.end(); it++)
    {
        std::string token = *it;
        for(size_t i = 0; i < token.size(); i++)
        {
            if(!isdigit(token[i]))
                throw DateError();
        }
    }
}

BitcoinExchange::BitcoinExchange(const std::string &filename, const std::string &date)
{
    this->check_date(date);
    
    this->filename = filename;
    this->date = date;
    
    
    
}

//exception classes
const char *BitcoinExchange::FileError::what() const throw()
{
    return "FileError: could not open file";
}

const char *BitcoinExchange::DateEmpty::what() const throw()
{
    return "DateError: date is empty";
}
const char *BitcoinExchange::DateError::what() const throw()
{
    return "DateError: date is not in the correct format";
}

const char *BitcoinExchange::DataError::what() const throw()
{
    return "DataError: data is empty";
}

void BitcoinExchange::parseData(const std::string &line)
{
    std::cout << "Parsing data: " << line << std::endl;
    try
    {
        std::string date = line.substr(0, line.find(","));
        std::string price = line.substr(line.find(",") + 1, line.length());
        std::cout << "Date: " << date << " Price: " << price << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
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
        parseData(line);
    }

    file.close();
}
