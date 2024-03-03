#include <iostream>
#include <stack>
#include <algorithm>



int main ()
{
    std::string test("({)}[}");
    std::cout << isValid(test)<< std::endl;
    return 0;
}