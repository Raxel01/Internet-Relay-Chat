#include <iostream>
#include <sstream>
#include <fstream>
int main ()
{
    std::string catcher("\n");
    std::stringstream stream(catcher);
    int i = 0;
    std::string holder;

    while (stream >> holder){
        std::cout << i << std::endl;
        i++;
    }
    // std::string hello("Hello World\n");

    // size_t newpos = hello.find("\n");

    //  if (hello.at(newpos - 1) == '\r')
    //         hello.erase(newpos - 1);// this .....\r\n erase it => LimeChat;
    //       else
    //         hello.erase(newpos);

    // // if (hello.at(newpos) != std::string::npos)
    // //     hello.erase(newpos);
    // std::cout << "|" << hello<<"|" << std::endl;
    return (0);
}