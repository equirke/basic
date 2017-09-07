#include <iostream>
#include <map>

int main(void)
{
    std::map<int, char> m;
    m[2] = '2';
    m[5] = '5';
    m[1] = '1';
    m[3] = '3';
    m[4] = '4';

    for(std::map<int, char>::iterator it = m.begin(); it != m.end(); it++)
    {
        std::cout << it->first << " " << it->second << std::endl;
    }

    std::map<int, char>::iterator i = m[2].begin();
    std::cout << i->first << " " << i->second << std::endl;
}