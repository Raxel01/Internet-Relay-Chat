#include <string.h>
#include <iostream>

class Solution {
public:
    std::string longestPalindrome(std::string s) {
        std::string Finale;
        std::string temp1;
        std::string temp2;
        
        if (s.length() == 0)
            return (0);
        if (s.length() == 2){
            if (s[0] == s[1])
                return (s);
            return (0);
        }

        int i = -1;
        while (s[++i] && i < 2)
            temp1[i] = s[i];
        temp2 = temp1;
        while (i < temp1.length()){


        }
        




        return Finale;
        
    }
};