#ifndef _TOKENISE_H_
#define _TOKENISE_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <stack>
#include <queue>
#include "Symbol.h"

class Tokenise
{
    int i;
    std::string input;
    std::vector<Symbol> syms;
    
    SymType command;
    public:
    Tokenise();

    std::vector<Symbol> symbolise(std::string in);

    std::vector<Symbol> get_syms();

    Symbol get_num();

    int isop(char in);

    Symbol get_op();

    void get_command();

    void get_string();

    void print();
};

#endif
