#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::~BitcoinExchange()
{
    this->value = "";
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    this->filename = other.filename;
    this->tokens = other.tokens;
    this->valid_date = other.valid_date;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    this->filename = other.filename;
    return *this;
}

// Trim whitespace from the beginning and end of a string
std::string trim(const std::string &str)
{
    size_t first = str.find_first_not_of(" \t\r\n");
    if (std::string::npos == first)
        return "";

    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

void BitcoinExchange::check_date(const std::string &date)
{
    if (date.empty())
        std::cout << "Date is empty" << std::endl;

    std::stringstream ss(date);
    trim(date);

    std::string token;
    size_t index = 0;
    while (std::getline(ss, token, '-'))
    {
        token = trim(token);
        if (!token.empty() && index < this->tokens.size())
        {
            this->tokens[index] = token;
            index++;
        }
    }
    
   

    
}

void BitcoinExchange::check_file(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw FileError();
    file.close();
}

BitcoinExchange::BitcoinExchange(const std::string &filename)
{
    this->filename = filename;
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

void BitcoinExchange::check_data(const std::string &data)
{
    std::stringstream ss;
    ss << data;
    float value;
    ss >> value;
    if (ss.fail())
        std::cout << "Error: " << "Not a number" << std::endl;
    if(value < 0.0)
        std::cout << "Error: " << "Not a positive number" << std::endl;
    if(value > 1000.0)
        std::cout << "Error: " << "Too large a number" << std::endl;
    else
        this->value = data;
}

void BitcoinExchange::parseData2(const std::string &line)
{
    // std::cout << "Parsing data: " << line << std::endl;
    std::stringstream ss(line); 
    std::string date;
    std::string data;
    while (std::getline(ss, date, ',') && std::getline(ss, data, ','))
    {
        this->data[date] = data;
    }
}

void BitcoinExchange::parseData(const std::string &line)
{
    std::stringstream ss(line); 
    std::string date;
    std::string data;
    while (std::getline(ss, date, '|') && std::getline(ss, data, '|'))
    {
        check_date(date);
        check_data(data);
    }
    if(line.find_first_not_of(date) == std::string::npos || line.find_first_not_of(data) == std::string::npos || line.find_first_not_of("| ") == std::string::npos)
    {
        std::cout << "Error: " <<"bad input:" << " " << line << std::endl;
    }
}

void BitcoinExchange::readData(const std::string &filename)
{
    std::ifstream file;
    file.open(filename, std::ios::in);
    if (!file.is_open())
    {
        file.clear();
        file.open(filename, std::ios::out | std::ios::app);
        if (!file.is_open())
        {
            throw std::runtime_error("Failed to create or open file.");
        }
    }
    std::string line;
    while (std::getline(file, line))
    {
        parseData(line);
        std::ifstream another_file;
        another_file.open("data.csv", std::ios::in);

        std::string line2;
        valid_date = tokens[0] + "-" + tokens[1] + "-" + tokens[2];
        while (std::getline(another_file, line2))
        {
            parseData2(line2);
        }
        another_file.close();
        if(this->value.empty() || this->valid_date.empty() || this->data.empty())
            return;
        else
        {
            std::map<std::string, std::string>::iterator it = data.lower_bound(valid_date);
            double result  = std::stod(it->second) * std::stod(value);
            if(result > 1000.0)
                std::cout << "Error: " << "Too large a number" << std::endl;
            else
                std::cout << it->first << "===> " << value  << " = " << result << std::endl;
        }
    }

    file.close();
}