
#include "PmergeMe.hpp"

bool PmergeMe::isDigit(const std::string &str) {
    size_t start = (str[0] == '-' && str[1]) ? 1 : 0;
    for (size_t i = start; i < str.length(); ++i) {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}
void print_list2(const std::vector<int>& o);
PmergeMe::PmergeMe(int argc, char *argv[]) {
    if (argc <= 1)
        throw BadParameters();
    
    for (int i = 1; i < argc; ++i) {
        if (!this->isDigit(argv[i]))
            throw NotANumber();
        numList.push_back(std::atoi(argv[i]));
    }
    if (this->check_sorted(numList))
        throw Sorted();
}

PmergeMe::~PmergeMe() {}

const char *PmergeMe::NotANumber::what() const throw() {
    return "Not a number";
}

const char *PmergeMe::BadParameters::what() const throw() {
    return "Bad parameters";
}

const char *PmergeMe::Sorted::what() const throw() {
    return "Already sorted";
}

std::vector<std::pair<int, int> > PmergeMe::pmerge(const std::vector<int>& numbers) 
{
    std::vector<std::pair<int, int> > res;
    std::vector<int>::const_iterator it = numbers.begin();
    while (it != numbers.end()) {
        if (*it > *std::next(it))
            res.push_back(std::make_pair(*std::next(it), *it));
        else
            res.push_back(std::make_pair(*it, *std::next(it)));
        std::advance(it, 2);
    }
    return res;
}

bool PmergeMe::check_sorted(const std::vector<int>& o) 
{
    std::vector<int>::const_iterator it = o.begin();
    while (it != std::prev(o.end())) {
        if (*it > *std::next(it))
            return false;
        it++;
    }
    return true;
}

std::vector<int> generateJacobsthalSequence(int n) {
    std::vector<int> jacob_numbers;
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
    if (n >= 2) 
	{
		std::vector<int>::iterator it = jacob_numbers.begin();
		jacob_numbers.erase(it);
		jacob_numbers.erase(it +1);

    }
    if (b >= n) {
        jacob_numbers.pop_back();
    }
    jacob_numbers.push_back(n);
    return jacob_numbers;
}

void PmergeMe::set_strugler() 
{
    std::vector<int>::iterator it = this->numList.begin();
    if (this->numList.size() % 2 != 0) {
        strugler = *it;
		//pop
		this->numList.erase(it);
    }

}
int PmergeMe::get_strugler()
{
	return this->strugler;
}

std::vector<int> PmergeMe::get_numList() {
    return this->numList;
}

void recursion_sort_helper(std::vector<std::pair<int,int> >& o, std::vector<std::pair<int,int> >::iterator it) {
    if (it == std::prev(o.end()))
        return;

    if (it->second > std::next(it)->second) {
        std::swap(*it, *std::next(it));
        recursion_sort_helper(o, std::next(it));
    }
    else
        recursion_sort_helper(o, std::next(it));
}

void recursion_sort(std::vector<std::pair<int,int> >& o) {
    if (o.size() < 2)
        return;

    recursion_sort_helper(o, o.begin());
}

void print_list2(const std::vector<int>& o) 
{
for (std::vector<int>::const_iterator it = o.begin(); it != o.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}
int main(int argc, char *argv[]) 
{
    try {

        PmergeMe pmergeMe(argc, argv);

        pmergeMe.set_strugler();
        std::vector<std::pair<int, int> > pairs = pmergeMe.pmerge(pmergeMe.get_numList());
        std::vector<int> lkbar;
        std::vector<int> sghar;
		recursion_sort(pairs);

		for (std::vector<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); it++) 
		{
			lkbar.push_back(it->second);
			sghar.push_back(it->first);
		}
		std::sort(lkbar.begin(), lkbar.end());
		if(sghar.front() > lkbar.front())
		{
			lkbar[0] = sghar[0];
			std::vector<int>::iterator it = sghar.begin();
			sghar.erase(it);
		}

        std::sort(lkbar.begin(), lkbar.end());
        std::vector<int> jacob_numbers = generateJacobsthalSequence(sghar.size());
        std::vector<int> index;
        
        for (std::vector<int>::iterator it = jacob_numbers.begin(); it != jacob_numbers.end(); it++) {
            int current = *it;
            index.push_back(current);
            for (int i = current - 1; i > 1; i--) {
                if (std::find(index.begin(), index.end(), i) == index.end()) {
                    index.push_back(i);
                }
            }
        }
		lkbar.insert(std::lower_bound(lkbar.begin(), lkbar.end(), sghar[0]), sghar[0]);
        for (std::vector<int>::iterator it = index.begin(); it != index.end(); it++) {
            if ((size_t)*it < sghar.size()) {
                int sgharIndex = *it;
                int sgharElement = sghar[sgharIndex];
                
                std::vector<int>::iterator insertPos = std::lower_bound(lkbar.begin(), lkbar.end(), sgharElement);
                lkbar.insert(insertPos, sgharElement);
            }
        }
		if(pmergeMe.get_strugler() != 0)
		{
			lkbar.insert(std::lower_bound(lkbar.begin(), lkbar.end(), pmergeMe.get_strugler()), pmergeMe.get_strugler());
		}
		
		print_list2(lkbar);
	
    }
    catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}