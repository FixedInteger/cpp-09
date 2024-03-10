#include <iostream>
#include <list>
#include <cstdlib>

class NotANumber : public std::exception {
public:
    const char *what() const throw() {
        return "Error: Not a number.";
    }
};

class BadParameters : public std::exception {
public:
    const char *what() const throw() {
        return "Bad Parameters: Usage: ./PmergeMe <number1> <number2> ... <numberN>";
    }
};

class Sorted : public std::exception {
public:
    const char *what() const throw() {
        return "The list is already sorted";
    }
};

bool isDigit(const std::string &str) {
    size_t start = (str[0] == '-' && str[1]) ? 1 : 0;
    for (size_t i = start; i < str.length(); ++i) {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

std::list<int> parseArguments(int argc, char *argv[]) {
    std::list<int> numList;

    for (int i = 1; i < argc; ++i) {
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

    if (it->second > std::next(it)->second) {
        std::swap(*it, *std::next(it));
        recursion_sort_helper(o, std::next(it)); // Pass the next iterator
    } else
        recursion_sort_helper(o, std::next(it)); // Pass the next iterator
}

void recursion_sort(std::list<std::pair<int,int> >& o) {
    if (o.size() < 2) // Base case: stop recursion if the list has 0 or 1 elements
        return;

    recursion_sort_helper(o, o.begin());
}

int check_sort(std::list<int> &o) {
    std::list<int>::iterator it = o.begin();
    while(it != std::prev(o.end())) {
        if(*it > *std::next(it))
            return 0;
        it++;
    }
    return 1;
}

std::list<int> generateJacobsthalSequence(int n) {
    std::list<int> jacob_numbers;
    int a = 0;
    int b = 1;
    int c;
    for (int i = 0; i < n; i++) {
        if (i == 0)
            jacob_numbers.push_back(a);
        else if (i == 1)
            jacob_numbers.push_back(b);
        else {
            c = a;
            a = b;
            b = b + 2 * c;
            jacob_numbers.push_back(b);
        }
        if (b >= n)
            break;
    }
    if (n >= 2) {
        jacob_numbers.pop_front();
        jacob_numbers.pop_front();
    }
    if (b >= n) {
        jacob_numbers.pop_back();
    }
    jacob_numbers.push_back(n);
    return jacob_numbers;
}

int main(int argc, char *argv[]) {
    try {
        if (argc <= 1)
            throw BadParameters();

        std::list<int> numbers = parseArguments(argc, argv);
        if (check_sort(numbers) == 1)
            throw Sorted();

        int strugller = 0;
        std::list<int> ::iterator it = numbers.begin();
        if (numbers.size() % 2 != 0) {
            strugller = *it;
            numbers.pop_front();
            std::cout << "strugller " << strugller << std::endl;
        }

        std::list<std::pair<int, int> > pairs = pmerge(numbers);
        recursion_sort(pairs);

        std::list<int> lkbar;
        std::list<int> sghar;
        std::list<std::pair<int, int> >::iterator it3;

        for (it3 = pairs.begin(); it3 != pairs.end(); it3++) {
            lkbar.push_back(it3->second);
            sghar.push_back(it3->first);
        }

        if (sghar.front() <= lkbar.front()) {
            lkbar.push_front(sghar.front());
            sghar.pop_front();
        }

       std::list<int> jacob_numbers = generateJacobsthalSequence(sghar.size());
        std::list<int> index;
    // std::list<int>::iterator it;

    for (it = jacob_numbers.begin(); it != jacob_numbers.end(); it++) {
        int current = *it;
        index.push_back(current);
        for (int i = current - 1; i >= 1; i--) { // Corrected the indexing to start from current - 1
            if (std::find(index.begin(), index.end(), i) == index.end()) { // Check if i is already in the index list
                index.push_back(i);
            }
        }
    }

        for (it = index.begin(); it != index.end(); it++) {
            std::cout << *it << std::endl;
        }
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
