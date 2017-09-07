#include <cstdio>
#include <string>
#include "Tokenise.h"
#include "Parse.h"

#define LINE_LENGTH 80

int main(void)
{
    std::string input;
    Parse parse;
    while(1)
    {
        try
        {
            std::getline(std::cin, input);
            Tokenise t;
            if(input.find("QUIT") != std::string::npos) break;
            t.symbolise(input);
            //t.print();
            parse.parse(t.get_syms());
            std::cout.flush();
        }
        catch(std::string& err){std::cerr << "Error:" << err << std::endl;}
    }

    
}
