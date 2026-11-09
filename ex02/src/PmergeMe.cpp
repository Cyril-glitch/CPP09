/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 17:38:22 by cycolonn          #+#    #+#             */
/*   Updated: 2026/11/09 20:23:01 by cycolonn         ###   ########.fr       */
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
//display

/*
static void display_main(std::vector<int> &main_chain)
{
    std::vector<int>::iterator it = main_chain.begin();

    while (it != main_chain.end())
        std::cout << *it++ << " "; 
    std::cout << "\n";
}
*/

static void display_pair_vector(std::vector<std::pair<int,int> > &vector)
{
    std::vector<std::pair<int,int> >::iterator it = vector.begin();

    while (it != vector.end())
    {
        std::cout << "[" <<it->first << "|" << it->second << "] "; 
        it++;
    }
    std::cout << "\n";
}

/*-----------------------------------------------------------------------------------------------------*/
//Parser

static bool fulldig(const std::string &av)
{
    for(long unsigned int i = 0; i < av.size(); i++)
        if (std::isdigit(av[i]) == 0) return 0;
    return 1;
}
 
static int push_integer(const std::string &av, std::vector<int> &main_chain)
{
    char *end;
    errno = 0;

    if (av.empty()) return 0;
    if (fulldig(av) == false) return 0;
    long cur_int = std::strtol(av.c_str(), &end, 10);
    if (errno == ERANGE || cur_int > INT_MAX || cur_int < 1) return 0;
    main_chain.push_back(cur_int);
    return 1;
}

static int parser(int ac, char **av, std::vector<int> &main_chain)
{ 
    if (ac < 2) return 0;
    for(int i = 1; i < ac; i++)
        if (!push_integer(av[i], main_chain)) return 0;
    return 1;
}


/*-----------------------------------------------------------------------------------------------------*/
//merge sort

static int divide(std::vector<int> &main_chain, std::vector<std::pair<int,int> > &pair_vector)
{
  std::vector<int>::iterator it = main_chain.begin();
  int orphan = 0;

    while (main_chain.size() >= 2)
    {
            if (*it > *(it+1))
                pair_vector.push_back(std::make_pair(*it, *(it+1)));
            else 
                pair_vector.push_back(std::make_pair(*(it+1), *it));
            main_chain.erase(main_chain.begin(), main_chain.begin() + 2);
    }
    if (!main_chain.empty())
        orphan = *main_chain.begin();
    return orphan;
}

static bool cmp(const std::pair<int, int>& a, const std::pair<int, int>& b)
{
    return a.first < b.first;
}

static void merge(std::vector<std::pair<int, int> >::iterator start, std::vector<std::pair<int, int> >::iterator end)
{ 
    /*on calcule la taille de notre interval de paires*/
    size_t size = end - start;

    if (size <= 1)
        return;

    /*On determine le milieu de cette interval pour le diviser en deux*/
    std::vector<std::pair<int, int> >::iterator center = start + (size / 2);

    /*On divise la premiere moitie de l'interval en deux*/
    merge(start, center);

    /*la 2eme moitie du tableau est diviser en deux*/
    merge(center, end);

    std::inplace_merge(start, center, end, cmp);
}

static void merge_sort(std::vector<int> &main_chain, std::vector<std::pair<int, int> > &pair_vector)
{
    divide(main_chain, pair_vector);
    merge(pair_vector.begin(), pair_vector.end());
}


/*-----------------------------------------------------------------------------------------------------*/
//insert 

static int jacobsthal(int n)
{
    return ((1UL << (n + 1)) + (n % 2 == 0 ? 1 : -1)) / 3;
}

/*
static std::vector<std::pair<int, int> >::iterator find_minor_pos(std::vector<std::pair<int, int> > &pair_vector, int k)
{ 
    return pair_vector.begin() + k; 
}

static std::vector<int>::iterator find_major_pos(std::vector<int> &main_chain, int minor_val)
{
    return std::find(main_chain.begin(), main_chain.end(), minor_val); 
}

static std::vector<int>::iterator binary_search(std::vector<int>::iterator start, std::vector<int>::iterator end, int value)
{

    while (start < end)
    {
        std::vector<int>::iterator mid = start + (end - start) / 2;
        if (value > *mid)
            start = mid + 1;
        else 
            end = mid;
    }
    return start; 
}
*/

static void insert_minor(std::vector<int> &main_chain, std::vector<std::pair<int, int> > &pair_vector)
{
    std::vector<std::pair<int, int> >::iterator minor_pos;
    std::vector<int>::iterator major_pos;
    std::vector<int>::iterator insert_pos;
    int minor_val = pair_vector.begin()->second;
    size_t top = main_chain.size();


    main_chain.push_back(minor_val);
    for (size_t i = 1; i < top; i++)
    {
        size_t k = jacobsthal(i);
        if (k > top)
            break;
        std::cout << k << "\n";
        std::cout << "decre: \n";
        while(i <= k)
        {
            std::cout << k << "\n";
           
            //minor_pos = find_minor_pos(pair_vector,k);
            //minor_val = minor_pos->second;
            //major_pos = find_major_pos(main_chain, minor_val);
            //insert_pos = binary_search(main_chain.begin(), major_pos, minor_val);
            //main_chain.insert(insert_pos, minor_val);
            k--;
        }
        std::cout << "\n\n";
    }
}

static void insert_major(std::vector<int> &main_chain, std::vector<std::pair<int, int> > &pair_vector)
{
    std::vector<std::pair<int, int> >::iterator it = pair_vector.begin();

    while (it < pair_vector.end())
        main_chain.push_back((it++)->first);
}

static void insert_sort(std::vector<int> &main_chain, std::vector<std::pair<int, int> > &pair_vector)
{
    insert_major(main_chain, pair_vector);
    insert_minor(main_chain,pair_vector);
}

/*-----------------------------------------------------------------------------------------------------*/

void PmergeMe::sort_vector(int ac, char **av)
{
    std::vector<int> main_chain;
    std::vector<std::pair<int, int> > pair_vector;

    if (parser(ac, av, main_chain) == 0 ) 
        throw(std::invalid_argument("Error"));   

    merge_sort(main_chain, pair_vector);
    display_pair_vector(pair_vector);

    insert_sort(main_chain, pair_vector);
    //display_main(main_chain);
}

/*
   1/A chaque appel on divise le paquet de paires en deux intervales
   2/Quand on ne peut plus diviser ces intervale on remonte et on les trie entre elles
   3/Le premiere appel qu'on depile compare directement 2 paires
   4/Le deuxieme compare 2 paires tries vs 2 paires tries ainsi de suite
   5/Lors des merges on compare toujours les paires les plus faibles des deux intervales
   6/la plus faible rejoint la suite du trie
   7/On creer des intervales de paires tries de plus en plus grandes jusqu'a devoir tries les deux moities du tableu d'origine
*/

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