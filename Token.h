#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string>
#include "Symbol.h"

struct Token
{
    std::string str;
    short num;
    SymType type;
    int precedence;
};

#endif