#include "Machine.h"

Machine::Machine()
{
    for(int i = 0; i < 26; i++)
    {
        vars[i] = 0;
    }
}
void Machine::push_num(Symbol s)
{
    operands.push(std::stoi(s.sym));
}

void Machine::push_var(Symbol s)
{
    char var_name = s.sym[0];
    int a = vars[var_name - 'A'];
    operands.push(a);
}

void Machine::save_var(Symbol s)
{
    char var_name = s.sym[0];
    vars[var_name - 'A'] = operands.top();
    operands.pop();
}

void Machine::add()
{
    int a = operands.top();
    operands.pop();
    int b = operands.top();
    operands.pop();
    operands.push(a + b);
}

void Machine::sub()
{
    int a = operands.top();
    operands.pop();
    int b = operands.top();
    operands.pop();
    operands.push(b - a);
}

void Machine::mul()
{
    int a = operands.top();
    operands.pop();
    int b = operands.top();
    operands.pop();
    operands.push(a * b);
}

void Machine::div()
{
    int a = operands.top();
    operands.pop();
    int b = operands.top();
    operands.pop();
    operands.push(b / a);
}

void Machine::g()
{
    int a = operands.top();
    operands.pop();
    int b = operands.top();
    operands.pop();
    if(b > a) 
    {
        operands.push(1);
    }
    else
    {
        operands.push(0);
    }
}

void Machine::l()
{
    int a = operands.top();
    operands.pop();
    int b = operands.top();
    operands.pop();
    if(b < a) 
    {
        operands.push(1);
    }
    else
    {
        operands.push(0);
    }
}

void Machine::le()
{
    int a = operands.top();
    operands.pop();
    int b = operands.top();
    operands.pop();
    if(b <= a) 
    {
        operands.push(1);
    }
    else
    {
        operands.push(0);
    }
}

void Machine::ge()
{
    int a = operands.top();
    operands.pop();
    int b = operands.top();
    operands.pop();
    if(b >= a) 
    {
        operands.push(1);
    }
    else
    {
        operands.push(0);
    }
}

void Machine::eq()
{
    int a = operands.top();
    operands.pop();
    int b = operands.top();
    operands.pop();
    if(b == a) 
    {
        operands.push(1);
    }
    else
    {
        operands.push(0);
    }
}

void Machine::neq()
{
    int a = operands.top();
    operands.pop();
    int b = operands.top();
    operands.pop();
    if(b != a) 
    {
        operands.push(1);
    }
    else
    {
        operands.push(0);
    }
}

bool Machine::if_statement()
{
    if(operands.top() == 1)
    {
        operands.pop();
        return true;
    }
    else
    {
        operands.pop();
        return false;
    }
}

int Machine::top()
{
    int a  = operands.top();
    operands.pop();
    return a;
}

void Machine::print_top()
{
    std::cout << operands.top();
}

void Machine::print_stack()
{
    while(!operands.empty())
    {
        std::cout << operands.top() << std::endl;
        operands.pop();
    }
}

void Machine::print_vars()
{
    for(int i = 0; i < 26; i++)
    {
        std::cout << char('A' + i) << ": "<< vars[i] << std::endl;
    }
}
