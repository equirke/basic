#ifndef _SYMBOL_H_
#define _SYMBOL_H_

enum SymType{UNDEF, MUL, DIV, ADD, SUB, COMMA, NUM, VAR, STRING, LPAREN, RPAREN, LE,
     GE, L, G, EQ, NEQ, ASSIGN, IF, THEN, LET, GOTO, PRINT, INPUT,LIST, RUN, END, CLEAR};

const std::string SymName[] = {"UNDEF", "MUL", "DIV", "ADD", "SUB", "COMMA","NUM", "VAR", "STRING",
"LPAREN", "RPAREN","LE", "GE", "L", "G" , "EQ", "NEQ", "ASSIGN", "IF", "THEN", "LET", "GOTO", 
"PRINT", "INPUT","LIST", "RUN", "END", "CLEAR"};

struct Symbol
{
    std::string sym;
    SymType type;
    int precedence;
};

#endif
