#include "PmergeMe.hpp"
#include <list>
#include <iostream>
#include <cstdlib>

class NotANumber : public std::exception
{
public:
    const char *what() const throw()
    {
        return "Error: Not a number.";
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

template<typename T>
typename std::vector<T>::iterator operator+(typename std::vector<T>::iterator it, int n) {
    std::advance(it, n);
    return it;
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

std::list<std::pair<int, int> > pmerge(const std::list<int>& numbers) {
    std::list<std::pair<int, int> > res;

    std::list<int>::const_iterator it = numbers.begin();
    while (it != numbers.end()) {
        std::list<int>::const_iterator next_it = it;
        if (++next_it != numbers.end()) {
            if (*it > *next_it) {
                res.push_back(std::make_pair(*next_it, *it));
            } else {
                res.push_back(std::make_pair(*it, *next_it));
            }
        }
        std::advance(it, 2);
    }

    return res;
}


void recursion_sort_helper(std::list<std::pair<int,int> >& o, std::list<std::pair<int,int> >::iterator it) {
    if (it == std::prev(o.end()))
        return;
    
    if (it->second > std::next(it)->second) 
    {
        std::swap(*it, *std::next(it));
        recursion_sort_helper(o, o.begin()); 
    } 
    else
        recursion_sort_helper(o, std::next(it));

}

void recursion_sort(std::list<std::pair<int,int> >& o) {
    recursion_sort_helper(o, o.begin());
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
        recursion_sort(pairs);
        std::list<std::pair<int, int> >::iterator it3;
        std::list<int> lkbar;
        std::list<int> sghar;
		for(it3 = pairs.begin() ; it3 != pairs.end(); it3++)
        {
            lkbar.push_back(it3->second);
            sghar.push_back(it3->first);
        }
        //now we have two lists of the same size lkbar == sorted numbers and sghar == unsorted numbers
        if(*(lkbar.begin()) >= *(sghar.begin()))
        {
            lkbar.push_front(*(sghar.begin()));
            sghar.pop_front();
        }

        //now generate the jacob number based on sghar 's size
       
        it = lkbar.begin();
        std::cout<<"lkbar : "<<std::endl;
        std::cout << "--------"<<std::endl;
        while(it != lkbar.end())
        {
            std::cout<<*it<<" "<<std::endl;
            it++;
        }

        std::cout<<"sghar : "<<std::endl;
        std::cout << "--------"<<std::endl;
        it = sghar.begin();
        while(it != sghar.end())
        {
            std::cout<<*it<<" ";
            it++;
        }
        
    }
    catch (std::exception &e) 
	{
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}