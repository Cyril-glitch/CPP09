/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 17:38:22 by cycolonn          #+#    #+#             */
/*   Updated: 2026/11/04 20:32:08 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/PmergeMe.hpp"


PmergeMe::PmergeMe()
{}

PmergeMe::PmergeMe(const PmergeMe &src)
{
    (void)src;
}

PmergeMe::~PmergeMe()
{}

PmergeMe& PmergeMe::operator=(const PmergeMe& rhs)
{
    (void)rhs;
    return *this;
}

/*-----------------------------------------------------------------------------------------------------*/
//Parser

static void display_vector(std::vector<int> &vector)
{
    std::vector<int>::iterator it = vector.begin();

    while (it != vector.end())
        std::cout << *it++ << " "; 
    std::cout << "\n";
}

static bool fulldig(const std::string &av)
{
    for(long unsigned int i = 0; i < av.size(); i++)
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
    return 1;
}

static int parser(int ac, char **av, std::vector<int> &vector)
{ 
    if (ac < 2) return 0;

    for(int i = 1; i < ac; i++)
        if (!push_integer(av[i], vector)) return 0;
    return 1;
}


/*-----------------------------------------------------------------------------------------------------*/
//divide

static int divide(std::vector<int> &vector, std::vector<std::pair<int,int> > &pair_vector)
{
  std::vector<int>::iterator it = vector.begin();

    while (it != vector.end())
    {
        if ((it + 1 != vector.end()))
        {
            if (*it > *it+1)
                pair_vector.push_back({*it, *it+1});
            else 
                pair_vector.push_back({*it+1, *it});
            vector.erase(it+1, it);
        }
    }
    if (!vector.empty())
        return vector.at(0);
    return 0;
}


bool custom_cmp(const std::pair<int, int>& a, const std::pair<int, int>& b)
{
    return a.first < b.first;
}

void mergeSort(std::vector<std::pair<int, int> >::iterator start, std::vector<std::pair<int, int> >::iterator end)
{ 
    /*
        1/A chaque appel on divise le paquet de paires en deux intervales
        2/Quand on ne peut plus diviser ces intervale on remonte et on les trie entre elles
        3/Le premiere appel qu'on depile compare directement 2 paires
        4/Le deuxieme compare 2 paires tries vs 2 paires tries ainsi de suite 
        5/Lors des merges on compare toujours les paires les plus faibles des deux intervales 
        6/la plus faible rejoint la suite du trie 
        7/On creer des intervales de paires tries de plus en plus grandes jusqu'a devoir tries les deux moities du tableu d'origine
    */

    /*on calcule la taille de notre tableau de paires*/
    size_t size = end - start;

    if (size <= 1)
        return;

    /*On determine le milieu de ce tableau pour le diviser en deux*/
    std::vector<std::pair<int, int> >::iterator center = start + (size / 2);

    /*la 1er moitie du tableau est diviser en deux*/
    mergeSort(start, center);

    /*la 2eme moitie du tableau est diviser en deux*/
    mergeSort(center, end);

    std::inplace_merge(start, center, end, custom_cmp);
}

void PmergeMe::sort_vector(int ac, char **av)
{
    std::vector<int> vector;
    std::vector<std::pair<int, int> > pair_vector;


    if (parser(ac, av, vector) == 0 ) 
        throw(std::invalid_argument("Error")); 
    display_vector(vector);

    int orphan = divide(vector, pair_vector);    
}


/*
=============================================================
FUSION : 2 PAIRES TRIÉES (GAUCHE)  vs  2 PAIRES TRIÉES (DROITE)
=============================================================

--- DUEL 1 ---
GAUCHE :  [ (3,1) , (7,2) ]       DROITE :  [ (2,5) , (8,4) ]
             ^                                 ^
             3          --- VS ---             2
                         2 GAGNE !
                         (il sort)
SORTIE :  [ (2,5) ]


--- DUEL 2 ---
GAUCHE :  [ (3,1) , (7,2) ]       DROITE :  [ (8,4) ]
             ^                                 ^
             3          --- VS ---             8
                         3 GAGNE !
                         (il sort)
SORTIE :  [ (2,5) , (3,1) ]


--- DUEL 3 ---
GAUCHE :  [ (7,2) ]               DROITE :  [ (8,4) ]
             ^                                 ^
             7          --- VS ---             8
                         7 GAGNE !
                         (il sort)
SORTIE :  [ (2,5) , (3,1) , (7,2) ]


--- FIN (Pas de duel) ---
GAUCHE :  [ VIDE ]                DROITE :  [ (8,4) ]
                                               |
                                        On le pose direct
SORTIE :  [ (2,5) , (3,1) , (7,2) , (8,4) ]
*/