#include "Parse.h"

Parse::Parse()
{
    i = 0;
    branch = false;
}

bool Parse::nextsym()
{
    if(i < syms.size() - 1)
    {
        i++;
        return true;
    }
    else
    {
        return false;
    }
}

Symbol Parse::peek()
{
    return syms[i];
}

int Parse::match(SymType t)
{
    if(t == syms[i].type) 
    {
        return 1;
    }
    return 0;
}

int Parse::expect(SymType t)
{
    if(match(t)) return 1;
    else throw std::string("Wrong Symbol");
}

void Parse::factor()
{
    if(match(NUM))
    {
        m.push_num(peek());
        nextsym();
    }
    else if(match(VAR))
    {
        m.push_var(peek());
        nextsym();
    }
    else if(match(LPAREN))
    {
        nextsym();
        expression();
        expect(RPAREN);
        nextsym();
    }
    else throw std::string("On line " + std::to_string(pc->first) + ":Expected factor, found " + SymName[peek().type]);
}

void Parse::term()
{
    factor();
    while(match(MUL) || match(DIV))
    {
        if(match(MUL))
        {
            nextsym();
            factor();
            m.mul();
        }
        if(match(DIV))
        {
            nextsym();
            factor();
            m.div(); 
        }
    }

}

void Parse::expression()
{
    term();

    while(match(ADD) || match(SUB))
    {
        if(match(ADD))
        {
            nextsym();
            term();
            m.add();
        }
        if(match(SUB))
        {
            nextsym();
            term();
            m.sub(); 
        }
    }
}

void Parse::print_expression_list()
{
    int a;
    nextsym();
    while(i < syms.size())
    {
        if(match(STRING))
        {
            std::cout << peek().sym << " ";
            nextsym();
            if(!match(COMMA))
            {
                break;
            }
            else
            {
                nextsym();
            }
        }
        else if(match(NUM) || match(VAR))
        {
            expression();
            a = m.top();
            std::cout << a << " ";
            if(!match(COMMA))
            {
                break;
            }
            else
            {
                nextsym();
            }
        }
    }
    std::cout << std::endl;
}

void Parse::input_var_list()
{
    Symbol s;
    
    nextsym();
    while(i < syms.size())
    {
        if(match(VAR))
        {
            std::cin >> s.sym;
            m.push_num(s);
            m.save_var(peek());
            nextsym();
            if(!match(COMMA))
            {
                break;
            }
            else
            {
                nextsym();
            }
        }
        else
        {
            throw std::string("Var expected");
        }
    }
}

void Parse::compare()
{
    expression();
    if(match(G))
    {
        nextsym();
        expression();
        m.g();
    }
    else if(match(GE))
    {
        nextsym();
        expression();
        m.ge();
    }
    else if(match(L))
    {
        nextsym();
        expression();
        m.l();
    }
    else if(match(LE))
    {
        nextsym();
        expression();
        m.le();
    }
    else if(match(EQ))
    {
        nextsym();
        expression();
        m.eq();
    }
    else if(match(NEQ))
    {
        nextsym();
        expression();
        m.neq();
    }
    else
    {
        throw std::string("Comparison expected");
    }
}

void Parse::list()
{
    for(pc = program.begin(); pc != program.end(); pc++)
    {
        std::vector<Symbol> s = pc->second;
        for(int j = 0; j < s.size(); j++)
        {
            if(s[j].type == STRING)
            {
                std::cout << "\"" << s[j].sym << "\"";
            }
            else
            {
                std::cout << s[j].sym << " ";
            }
        }

        std::cout << std::endl;
    } 
}

void Parse::statement()
{
    if(match(IF))
    {
        nextsym();
        compare();
        if(!m.if_statement())
        {
            return;
        }
        expect(THEN);
        nextsym();
        statement();
    }
    else if(match(LET))
    {
        nextsym();
        expect(VAR);
        Symbol s = syms[i];
        nextsym();
        expect(ASSIGN);
        nextsym();
        expression();
        m.save_var(s);
    }
    else if(match(GOTO))
    {
        nextsym();
        expression();
        pc = program.find(m.top());
        branch = true;
    }
    else if(match(PRINT))
    {
        print_expression_list();
    }
    else if(match(RUN))
    {
        run();
    }
    else if(match(END))
    {
        end = true;
    }
    else if(match(LIST))
    {
        list();
    }
    else if(match(INPUT))
    {
        input_var_list();
    }
    else
    {
        throw std::string("Command expected");
    }
}

void Parse::line()
{
    expect(NUM);
    nextsym();
    statement();
}

void Parse::run()
{
    for(pc = program.begin(); pc != program.end(); pc++)
    {
        if(branch)
        {
            pc--;
            branch = false;
        }

        if(end)
        {
            end = false;
            break;
        }
        syms.clear();
        syms = pc->second;
        i = 0;
        line();
    } 
}

void Parse::get_line()
{
    if(match(NUM))
    {
        /*What c++ maps force you to do in order to
        overwrite a value in a map as a key cannot be simply
        overwritten in the form map[key] = newvalue */
        std::pair<std::map<int,std::vector<Symbol>>::iterator,bool> ret;
        ret = program.insert(std::pair<int, std::vector<Symbol>>(std::stoi(peek().sym), syms));
        if(ret.second == false)
        {
            ret.first->second = syms;
        }
    }
    else
    {
        statement();
    }
}

void Parse::parse(std::vector<Symbol> s)
{
    syms = s;
    i = 0;
    if(syms.size() > 0)
    {
        get_line();
    }
    //m.print_stack();
    //m.print_vars();
}

void Parse::print()
{
    std::cout << std::endl;
    for(i = 0; i < syms.size(); i++)
    {
        std::cout << syms[i].sym << " " << SymName[syms[i].type] << std::endl;
    }
}
