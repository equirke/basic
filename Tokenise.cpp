#include "Tokenise.h"

Tokenise::Tokenise()
{
    i = 0;
}

std::vector<Symbol> Tokenise::symbolise(std::string in)
{
    input.clear();
    input = in;
    i = 0;
    while(i < input.size())
    {
        if(input[i] == '\"')
        {
            get_string();
        }
        else if(isalpha(input[i]))
        {
            get_command();
        }
        else if(isdigit(input[i]))
        {
            syms.push_back(get_num());
        }

        else if(isop(input[i]))
        {
            syms.push_back(get_op());
        }
        else if(isspace(input[i])) i++;
    }

    return syms;
}

std::vector<Symbol> Tokenise::get_syms()
{
    return syms;
}

Symbol Tokenise::get_num()
{
    Symbol sym;
    std::string buf;
    while(isdigit(input[i]) && i < input.length())
    {
        buf.push_back(input[i++]);
    }

    sym.sym = buf;
    sym.type = NUM;
    return sym;
}

Symbol Tokenise::get_op()
{
    Symbol sym;
    std::string buf;
    while(isop(input[i]) && i < input.length())
    {
        buf.push_back(input[i++]);
    }

    sym.sym = buf;

    if(!buf.compare(0, 1, "*"))
    {
        sym.type = MUL;
        sym.precedence = 1;
    }

    else if(!buf.compare(0, 1, "/"))
    {
        sym.type = DIV;
        sym.precedence = 1;
    }

    else if(!buf.compare(0, 1, "+"))
    {
        sym.type = ADD;
        sym.precedence = 2;
    }

    else if(!buf.compare(0, 1, ","))
    {
        sym.type = COMMA;
        sym.precedence = 6;
    }

    else if(!buf.compare(0, 1, "-"))
    {
        sym.type = SUB;
        sym.precedence = 2;
    }

    else if(!buf.compare(0, 2, "<>"))
    {
        sym.type = NEQ;
        sym.precedence = 3;
    }

    else if(!buf.compare(0, 1, "<"))
    {
        sym.type = L;
        sym.precedence = 3;
    }

    else if(!buf.compare(0, 1, ">"))
    {
        sym.type = G;
        sym.precedence = 3;
    }

    else if(!buf.compare(0, 2, "<="))
    {
        sym.type = LE;
        sym.precedence = 3;
    }

    else if(!buf.compare(0, 2, ">="))
    {
        sym.type = GE;
        sym.precedence = 3;
    }

    else if(!buf.compare(0, 1, "("))
    {
        sym.type = LPAREN;
    }

    else if(!buf.compare(0, 1, ")"))
    {
        sym.type = RPAREN;
    }

    else if(!buf.compare(0, 1, "=") && command == IF)
    {
        sym.type = EQ;
        sym.precedence = 3;
        command = UNDEF;
    }

    else if(!buf.compare(0, 1, "=") && command == LET)
    {
        sym.type = ASSIGN;
        sym.precedence = 4;
        command = UNDEF;
    }

    return sym;

}

void Tokenise::get_command()
{
    std::string buf;
    Symbol sym;

    while(isalpha(input[i]) && i < input.size())
    {
        buf.push_back(input[i++]);
    }

    sym.sym = buf;

    std::string s = "IFTHENLETGOTOPRINTENDRUNLISTINPUT";
    if(s.find(buf) != std::string::npos)
    {
        if(!buf.compare(0, 2, "IF"))
        {
            sym.type = IF;
            sym.precedence = 6;
            syms.push_back(sym);
            command = IF;
        }

        else if(!buf.compare(0, 4, "THEN"))
        {
            sym.type = THEN;
            sym.precedence = 6;
            syms.push_back(sym);
        }

        else if(!buf.compare(0, 3, "LET"))
        {
            sym.type = LET;
            sym.precedence = 6;
            syms.push_back(sym);
            command = LET;
        }

        else if(!buf.compare(0, 4, "GOTO"))
        {
            sym.type = GOTO;
            sym.precedence = 6;
            syms.push_back(sym);
        }

        else if(!buf.compare(0, 4, "LIST"))
        {
            sym.type = LIST;
            sym.precedence = 6;
            syms.push_back(sym);
        }

        else if(!buf.compare(0, 3, "RUN"))
        {
            sym.type = RUN;
            sym.precedence = 6;
            syms.push_back(sym);
        }

        else if(!buf.compare(0, 3, "END"))
        {
            sym.type = END;
            sym.precedence = 6;
            syms.push_back(sym);
        }

        /*else if(!buf.compare(0, 5, "CLEAR"))
        {
            sym.type = CLEAR;
            sym.precedence = 6;
            syms.push_back(sym);
        }*/

        else if(!buf.compare(0, 5, "PRINT"))
        {
            sym.type = PRINT;
            sym.precedence = 6;
            syms.push_back(sym);
        }

        else if(!buf.compare(0, 5, "INPUT"))
        {
            sym.type = INPUT;
            sym.precedence = 6;
            syms.push_back(sym);
        }
        
    }

    if(buf.size() == 1 && isalpha(buf[0]) && isupper(buf[0]))
    {
        sym.sym = buf;
        sym.type = VAR;
        syms.push_back(sym);
    }
}

void Tokenise::get_string()
{
    std::string buf;
    Symbol sym;
    i++;
    while(input[i] != '\"' && i < input.size())
    {
        buf.push_back(input[i++]);
    }
    i++;

    sym.sym = buf;
    sym.type = STRING;
    syms.push_back(sym);
}

void Tokenise::print()
{
    std::cout << std::endl;
    for(i = 0; i < syms.size(); i++)
    {
        std::cout << syms[i].sym << " " << SymName[syms[i].type] << std::endl;
    }
}

int Tokenise::isop(char in)
{
    std::string s = "*/+-<>=,()";
    if(s.find(in) != std::string::npos) return 1;
    return 0;
}
