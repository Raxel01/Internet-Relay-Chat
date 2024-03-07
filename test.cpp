#include <iostream>
#include <vector>


int main()
{
    std::vector<int> vec;

    vec.push_back(1);

    std::vector<int>::iterator it  = vec.begin();

    std::cout << *it << std::endl;
    
    std::cout << it.base() << std::endl;

}