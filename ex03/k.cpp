#include <iostream>
#include <list>

#include <list>
#include <algorithm> // Needed for std::max_element

std::list<int> generateJacobsthalSequence(const std::list<int>& sghar) {
    // Find the maximum value in the sghar list
    int max_value = *(std::max_element(sghar.begin(), sghar.end()));


    std::list<int> jacob_numbers;
    int a = 0;
    int b = 1;
    int c;

    for (int i = 0; b <= max_value; ++i) {
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
    }
    if(jacob_numbers.back() != 10)
    {
        jacob_numbers.pop_back();
        jacob_numbers.push_back(max_value);
    }

    return jacob_numbers;
}


#include <list>


std::list<int> merge_sort(std::list<int>& lkbar, std::list<int>& sghar, std::list<int>& jacob_numbers) {
    std::list<int> result;
    std::list<int>::iterator it = sghar.begin();
    std::list<int>::iterator it2 = jacob_numbers.begin();
    while(it2 != jacob_numbers.end())
    {
        while(it != sghar.end() && *it <= *it2)
        {

        }
       it2++;
    }

    return result;
}



int main() {
    std::list<int> lkbar;
    lkbar.push_back(1);
    lkbar.push_back(3);
    lkbar.push_back(5);
    lkbar.push_back(7);
    lkbar.push_back(9);

    std::list<int> sghar;
    sghar.push_back(2);
    sghar.push_back(7);
    sghar.push_back(6);
    sghar.push_back(4);
    sghar.push_back(10);

    std::list<int> jacob_numbers = generateJacobsthalSequence(sghar);

    std::list<int> result = merge_sort(lkbar, sghar, jacob_numbers);

    std::cout << "Merged and sorted list result:" << std::endl;
    for (std::list<int>::iterator it = result.begin(); it != result.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
