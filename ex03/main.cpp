
#include "PmergeMe.hpp"
int main(int argc, char *argv[]) 
{
    try 
	{

        PmergeMe pmergeMe(argc, argv);
        pmergeMe.set_strugler();
		pmergeMe.sort_using_deque();
		std::cout << "----------------"<<std::endl;
		pmergeMe.sort_using_vector();
        
	
    }
    catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}