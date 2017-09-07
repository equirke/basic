#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <stack>
#include <queue>
#include "Symbol.h"

class Machine
{
private:
    std::stack<int> operands;
    int vars[26];
public:

    Machine();
    void push_num(Symbol s);

    void push_var(Symbol s);

    void save_var(Symbol s);

    void add();

    void sub();

    void mul();

    void div();

    void g();

    void l();

    void le();

    void ge();

    void eq();

    void neq();

    bool if_statement();

    int top();

    void print_top();

    void print_stack();

    void print_vars();

};
