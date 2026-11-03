/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 17:38:22 by cycolonn          #+#    #+#             */
/*   Updated: 2026/11/03 20:33:23 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/PmergeMe.hpp"
#include <climits>
#include <string>
#include <vector>
#include <stdexcept>

PmergeMe::PmergeMe()
{}

PmergeMe::PmergeMe(const PmergeMe &src)
{}

PmergeMe::~PmergeMe()
{}

PmergeMe& PmergeMe::operator=(const PmergeMe& rhs)
{}

static bool fulldig(const std::string &av)
{
    for(int i = 0; i < av.size(); i++)
        if (std::isdigit(av[i]) == 0) return 0;
    return 1;
}

static int push_integer(const std::string &av, std::vector<int> &vector)
{
    char *end;
    errno = 0;

    if (av.empty()) return 0;
    if (fulldig(av) == false) return 0;
    long cur_int = std::strtol(av.c_str(), &end, 10);
    if (errno == ERANGE || cur_int > INT_MAX || cur_int < 1) return 0;
    vector.push_back(cur_int);
}


static int parser(int ac, char **av, std::vector<int> &vector)
{ 
    if (ac < 2) return 0;

    for(int i = 1; i < ac; i++)
        if (!push_integer(av[i], vector)) return 0;
}

void PmergeMe::sort_vector(int ac, char **av)
{
    std::vector<int> vector;

    if (parser(ac, av, vector) == 0 ) 
        throw(std::invalid_argument("Error"));
}