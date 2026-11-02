/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 18:32:13 by cycolonn          #+#    #+#             */
/*   Updated: 2026/11/02 20:32:53 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RPN.hpp"
#include <sstream>
#include <iostream>
#include <cstdlib>

RPN::RPN()
{
}

RPN::RPN(const RPN& src)
{
    (void)src;
}

RPN& RPN::operator=(const RPN &rhs)
{
    (void)rhs;
    return *this;
}

RPN::~RPN()
{
}


int is_operator(const char c)
{
    return  (c == '+' || c == '-' || c== '*' || c == '/');  
}

int check_token(const std::string &token, std::stack<int , std::list<int> > &stack)
{
    if (token.size() > 1) return 0; 
    if (std::isdigit(token[0]) && token[0] > '9') return 0;
    if (is_operator(token[0]) && stack.size() < 2) return 0; 
    return token[0];
}

int operation(int left, int right, char ope)
{
    if (ope == '/' && right == 0) throw(std::runtime_error("Error"));

    if (ope == '+') return left + right;
    if (ope == '-') return left - right;
    if (ope == '*') return left * right;
    if (ope == '/') return left / right;

    return 0;
}

void compute(std::stack<int , std::list<int> > &stack , char ope)
{
    
    int right = stack.top();
    stack.pop();
    int left = stack.top(); 
    stack.pop();
    stack.push(operation(left, right, ope)); 
}

int RPN::resolve(const std::string &operation)
{
    std::istringstream sstream(operation);
    std::string token;
    std::stack<int , std::list<int> > stack;

    while (sstream >> token)
    { 
        if (!check_token(token, stack))
            throw(std::invalid_argument("Error"));
        if (std::isdigit(token[0]))
            stack.push(token[0] - '0');
        else if (is_operator(token[0])) 
            compute(stack, token[0]); 
    }
    return stack.top();
}



/*
    RPN 
    123 +*
    
    STACK
    [3]
    [2]
    [1]

    operator
    +

    compute
    left | right = res
      2  +  3    = 5

    move
    push [res]


    STACK
    [res]
    [1]

    operator
    *

    compute
    left | right = res
      1  *  5    = 5
    
    move
    push [res]

    STACK
    [res]
    */