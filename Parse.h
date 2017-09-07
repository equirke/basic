#ifndef _PARSE_H_
#define _PARSE_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <stack>
#include <map>
#include "Symbol.h"
#include "Machine.h"

class Parse
{
    int i;
    std::vector<Symbol> syms;
    std::map<int, std::vector<Symbol>> program;
    std::map<int, std::vector<Symbol>>::iterator pc;
    bool branch;
    bool end;
    Machine m;
    
    public:
    Parse();

    bool nextsym();

    Symbol peek();

    int match(SymType t);

    int expect(SymType t);

    void factor();

    void term();

    void expression();

    void print_expression_list();

    void input_var_list();

    void compare();

    void list();

    void statement();

    void line();

    void run();

    void get_line();

    void parse(std::vector<Symbol> s);

    void print();
};

#endif
