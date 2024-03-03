#ifndef BTC_EXCHANGE_HPP
#define BTC_EXCHANGE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>


#include <fstream>
class BitcoinExchange
{
    private:
        std::map<std::string, std::vector<std::string> > data;
    public:
        BitcoinExchange();
        ~BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        void readData(const std::string &filename);
        
};

#endif