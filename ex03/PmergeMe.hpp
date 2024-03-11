#ifndef PMERGE_ME_S
#define PMERGE_ME_S

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <exception>
#include <deque>

class PmergeMe {

    private:
        std::vector<int> numList;
        std::deque<int> numQueue;
        std::vector<std::pair<int, int> > res;
        int strugler;
    public:
        PmergeMe(int argc, char *argv[]);
        bool isDigit(const std::string &str);
        bool check_sorted( const std::vector<int>& o);

        std::vector<std::pair<int, int> > pmerge( const std::vector<int>& numbers);
        std::deque<std::pair<int, int> > pmergew(const std::deque<int>& numbers);
        //getters
        std::vector<int> get_numList();
        void set_strugler();
        int get_strugler();
        
        class NotANumber : public std::exception
        {
            public:
                const char *what() const throw();
        };
        class BadParameters : public std::exception
        {
            public:
                const char *what() const throw();
        };
        class Sorted : public std::exception
        {
            public:
                const char *what() const throw();
        };
        
        ~PmergeMe();
};
#endif