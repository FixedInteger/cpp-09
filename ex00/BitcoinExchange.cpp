#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::~BitcoinExchange()
{
    this->value = "";
    this->valid_date = "";
    this->data.clear();
    this->filename = "";
    this->btc = false;
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
    {
        std::cout << "Date is empty" << std::endl;
        return;
    }

    std::stringstream ss(date);
    std::string year, month, day;
    
    std::getline(ss, year, '-');
    std::getline(ss, month, '-');
    std::getline(ss, day, '-');

    year = trim(year);
    month = trim(month);
    day = trim(day);
    if (year.empty() || month.empty() || day.empty())
        std::cout << "Invalid Date" <<std::endl;

    else if (year.size() != 4 || month.size() != 2 || day.size() != 2)
        std::cout << "Invalid Date" <<std::endl;

    else if (year.find_first_not_of("0123456789") != std::string::npos || month.find_first_not_of("0123456789") != std::string::npos || day.find_first_not_of("0123456789") != std::string::npos)
        std::cout << "Invalid Date" <<std::endl;

    else if (std::stoi(month) < 1 || std::stoi(month) > 12 || std::stoi(day) < 1 || std::stoi(day) > 31)
        std::cout << "Invalid Date" <<std::endl;
    else
    {
        this->tokens[0] = year;
        this->tokens[1] = month;
        this->tokens[2] = day;
        this->btc = true;
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
    std::string temp = data;
    temp.erase(0, temp.find_first_not_of(" \t\r\n"));
    if(temp.empty())
        std::cout << "Data is empty" << std::endl;
    else if (temp.find_first_not_of("0123456789.") != std::string::npos)
        std::cout << "Error : Not a Number" <<std::endl;
    else if (value < 0.0)
        std::cout << "Error : Not a positive Number" <<std::endl;
    else  if(value > 1000.0)
        std::cout << "Error : Too large A number" <<std::endl;
    else
    {
        this->value = data;
        this->btc = true;
    }
}

void BitcoinExchange::parseData2(const std::string &line)
{
    std::stringstream ss(line); 
    std::string date;
    std::string data;
    while (std::getline(ss, date, ',') && std::getline(ss, data, ','))
    {
        this->data[date] = data;
    }
}


void BitcoinExchange::parseData(std::string &line)
{
    this->btc = false;
    std::stringstream ss(line); 
    std::string date;
    std::string data;
    while (std::getline(ss, date, '|') && std::getline(ss, data, '|'))
    {
        check_date(date);
        check_data(data);
    }
    if(data.empty() || date.empty())
    {
        std::cout << "Error: " <<"bad input:" << " " << line << std::endl;
    }
}

std::string BitcoinExchange::check_first_line(std::string &line, std::ifstream &file)
{
    std::getline(file, line);
    std::string temp = line;

    std::string data;
    std::string date;
    std::stringstream ss(temp);
    std::getline(ss, date, '|');
    std::getline(ss, data, '|');
    data = trim(data);
    date = trim(date);
    if(data != "value" || date != "date")
        throw DataError();
    return temp;
}
void BitcoinExchange::readData(const std::string &filename)
{
    if(filename.empty() || filename.find(".csv") == std::string::npos)
    {
        std::cout << "Error: " << "bad input:" << " " << filename << std::endl;
        return;
    }
    std::ifstream file;
    file.open(filename.c_str(), std::ios::in);
    if (!file.is_open())
        throw std::runtime_error("Failed to open file.");
    std::string line;
    line = check_first_line(line , file);
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
        if (btc == true && !value.empty() && !valid_date.empty() && !data.empty())
        {
            double closestResult = 0.0;
            std::string closestDate;

            std::map<std::string, std::string>::iterator it;
            for (it = data.begin(); it != data.end(); ++it)
            {
                const std::string &date = it->first;
                if (date < valid_date)
                {
                    double result = std::strtod(it->second.c_str(), NULL) * std::strtod(value.c_str(), NULL);
                    if (result <= 1000.0 && (closestDate.empty() || date > closestDate))
                    {
                        closestDate = date;
                        closestResult = result;
                    }
                }
            }

            if (!closestDate.empty())
                std::cout << closestDate << " ===> " << value << " = " << closestResult << std::endl;
            if(this->btc == true && closestDate.empty())
                std::cout << "No data " <<std::endl;
        }
    }

    file.close();
}
