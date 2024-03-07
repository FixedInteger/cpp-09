#include "PmergeMe.hpp"
#include <list>
#include <iostream>
#include <cstdlib>

class NotANumber : public std::exception
{
public:
    const char *what() const throw()
    {
        return "Not a number exception";
    }
};

class BadParamters : public std::exception
{
    public :
    const char *what() const throw()
    {
        return "Bad Parameters : Usage : ./PmergeMe <number1> <number2> ... <numberN>";
    
    }
};

bool isDigit(const std::string &str)
{
    size_t start = (str[0] == '-' && str[1]) ? 1 : 0;
    for (size_t i = start; i < str.length(); ++i)
    {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}


std::list<int> parseArguments(int argc, char *argv[])
{
    std::list<int> numList;

    for (int i = 1; i < argc; ++i)
    {
        if (!isDigit(argv[i]))
            throw NotANumber();
        numList.push_back(atoi(argv[i]));
    }

    return numList;
}
std::list<std::pair<int, int> > pmerge(const std::list<int>& numbers) 
{
    std::list<std::pair<int, int> > res;

    std::list<int>::const_iterator it = numbers.begin();
    while (it != numbers.end())
	{
		if(*it > *std::next(it))
		{
			res.push_back(std::make_pair(*std::next(it),*it));
		}
		else
			res.push_back(std::make_pair(*it,(*std::next(it))));
		std::advance(it,2);

    }

    return res;
}

int main(int argc, char *argv[]) {
    try {
        if (argc <= 1) 
            throw BadParamters();
        
        std::list<int> numbers = parseArguments(argc, argv);
		std::list<int> ::iterator it = numbers.begin();
		if(numbers.size() % 2 != 0)
		{
			int strugller = *it;
			numbers.pop_front();
			std::cout<<"strugller "<<strugller<<std::endl;
		}
        std::list<std::pair<int, int> > pairs = pmerge(numbers);
        std::list<std::pair<int, int> >::iterator it3;
		for(it3 = pairs.begin() ; it3 != pairs.end(); it3++)
        {
            std::cout << it3->first << " | " << it3->second << std::endl;
        }
    }
    catch (std::exception &e) 
	{
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}