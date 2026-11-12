/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 17:15:06 by cycolonn          #+#    #+#             */
/*   Updated: 2026/11/12 16:21:34 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <climits>
#include <cstdlib>
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <utility>
#include <algorithm>
#include <functional>
#include <ctime>
#include <cerrno>
#include <deque>
#include <iomanip>
#include <cctype>

template <typename T>
struct PairContainer;

template <>
struct PairContainer<std::vector<int> >
{
    typedef std::vector<std::pair<int, int> > type;
};

template <>
struct PairContainer<std::deque<int> >
{
    typedef std::deque<std::pair<int, int> > type;
};

template <typename C>
class PmergeMe
{
    public:
    
        static int parser(int ac, char **av, C &main_chain);
        static double sort(C &main_chain);
        static void display_main(C &main_chain);  
        static void display_duration(double duration, const size_t &size, const C &main_chain);
        static std::string get_container_name(const std::vector<int> &);
        static std::string get_container_name(const std::deque<int> &);


    private:
        PmergeMe();
        PmergeMe(const PmergeMe &src);
        ~PmergeMe();

        PmergeMe &operator=(const PmergeMe &rhs);
};

template <typename C>
PmergeMe<C>::PmergeMe()
{}

template <typename C>
PmergeMe<C>::PmergeMe(const PmergeMe &src)
{
    (void)src;
}

template <typename C>
PmergeMe<C>::~PmergeMe()
{}

template <typename C>
PmergeMe<C>& PmergeMe<C>::operator=(const PmergeMe<C>& rhs)
{
    (void)rhs;
    return *this;
}

/*-----------------------------------------------------------------------------------------------------*/
//display

template <typename C>
std::string PmergeMe<C>::get_container_name(const std::vector<int> &)
{
    return "std::vector";
}

template <typename C>
std::string PmergeMe<C>::get_container_name(const std::deque<int> &)
{
    return "std::deque";
}

template <typename C>
void PmergeMe<C>::display_main(C &main_chain)
{
    typename C::iterator it = main_chain.begin();

    while (it != main_chain.end())
        std::cout << *it++ << " "; 
    std::cout << "\n";
}

template <typename C>
void PmergeMe<C>::display_duration(double duration ,const size_t &size, const C &main_chain)
{
    std::cout << "Time to process a range of " 
              << size << " elements with " 
              << get_container_name(main_chain) << " : "
              << std::fixed << std::setprecision(5) << duration << " us\n";
}

/*-----------------------------------------------------------------------------------------------------*/
//Parser

static bool fulldig(const std::string &av)
{
    for(long unsigned int i = 0; i < av.size(); i++)
        if (std::isdigit(av[i]) == 0) return 0;
    return 1;
}

template <typename C>
static int push_integer(const std::string &av, C &main_chain)
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

template <typename C>
int PmergeMe<C>::parser(int ac, char **av, C &main_chain)
{ 
    if (ac < 2) return 0;
    for(int i = 1; i < ac; i++)
         if (!push_integer(av[i], main_chain)) return 0;
    return 1;
}

/*-----------------------------------------------------------------------------------------------------*/
//merge sort

template <typename C>
static int handle_orphan(C &main_chain)
{
    int orphan = 0;
    if (!main_chain.empty())
    {
        orphan = *main_chain.begin();
        main_chain.pop_back();
    }
    return orphan;
}

template <typename C, typename PC>
static int divide(C &main_chain, PC &pair_container)
{
    while (main_chain.size() >= 2)
    {
        if (main_chain[0] > main_chain[1])
            pair_container.push_back(std::make_pair(main_chain[0], main_chain[1]));
        else 
            pair_container.push_back(std::make_pair(main_chain[1], main_chain[0]));
        main_chain.erase(main_chain.begin(), main_chain.begin() + 2);
    }
    return handle_orphan(main_chain);
}

static bool cmp(const std::pair<int, int>& a, const std::pair<int, int>& b)
{
    return a.first < b.first;
}

template <typename Iter>
static void merge(Iter start, Iter end)
{ 
    /*on calcule la taille de notre interval de paires*/
    size_t size = end - start;

    if (size <= 1)
        return;

    /*On determine le milieu de cette interval pour le diviser en deux*/
    Iter center = start + (size / 2);

    /*On divise la premiere moitie de l'interval en deux*/
    merge(start, center);

    /*la 2eme moitie du tableau est diviser en deux*/
    merge(center, end);

    std::inplace_merge(start, center, end, cmp);
}

/*-----------------------------------------------------------------------------------------------------*/
//insert 

static size_t jacobsthal(int n)
{
    return ((1UL << (n + 1)) + (n % 2 == 0 ? 1 : -1)) / 3;
}

template <typename PC>
static typename PC::iterator find_minor_pos(PC &pair_container, int idx)
{ 
    return pair_container.begin() + idx; 
}

template <typename C>
static typename C::iterator find_major_pos(C &main_chain, int major_val)
{
    return std::find(main_chain.begin(), main_chain.end(), major_val); 
}

template <typename C>
static typename C::iterator binary_search(typename C::iterator start, typename C::iterator end, int value)
{
    while (start < end)
    {
        typename C::iterator mid = start + (end - start) / 2;
        if (value > *mid)
            start = mid + 1;
        else 
            end = mid;
    }
    return start; 
}

template <typename C, typename PC>
static void insert_main(C &main_chain, PC &pair_container, size_t idx)
{
    typename PC::iterator minor_pos;
    typename C::iterator major_pos;
    typename C::iterator insert_pos;
    int minor_val;
    int major_val;

    minor_pos = find_minor_pos(pair_container, idx);
    minor_val = minor_pos->second;
    major_val = minor_pos->first;
    major_pos = find_major_pos(main_chain, major_val);
    insert_pos = binary_search<C>(main_chain.begin(), major_pos, minor_val);
    main_chain.insert(insert_pos, minor_val);
}

template <typename C>
static void insert_orphan(C &main_chain, int orphan)
{
    typename C::iterator insert_pos;
    insert_pos = binary_search<C>(main_chain.begin(), main_chain.end(), orphan);
    main_chain.insert(insert_pos, orphan);
}

template <typename C, typename PC>
static void insert_minor(C &main_chain, PC &pair_container, int orphan)
{
    size_t rank = 2;
    size_t cur_jacobsthal = jacobsthal(rank);
    size_t prev_jacobsthal = jacobsthal(rank - 1);
    
    main_chain.insert(main_chain.begin(), pair_container[0].second);
    while (main_chain.size() < pair_container.size() * 2)
    {
        for (size_t i = cur_jacobsthal; i > prev_jacobsthal; i--)
        {
            if (i <= pair_container.size())
                insert_main(main_chain, pair_container, i - 1);  
        }
        prev_jacobsthal = cur_jacobsthal;
        cur_jacobsthal = jacobsthal(++rank); 
    }
    if (orphan)
        insert_orphan(main_chain, orphan);
}

template <typename C, typename PC>
static void insert_major(C &main_chain, PC &pair_container)
{
    typename PC::iterator it = pair_container.begin();

    while (it != pair_container.end())
        main_chain.push_back((it++)->first);
}

template <typename C, typename PC>
static void insert_sort(C &main_chain, PC &pair_container, int orphan)
{
    insert_major(main_chain, pair_container);
    insert_minor(main_chain, pair_container, orphan);
}

/*-----------------------------------------------------------------------------------------------------*/

template <typename C>
static bool is_sorted(const C &c)
{
    return std::adjacent_find(c.begin(), c.end(), std::greater<int>()) == c.end();
}

template <typename C, typename PC>
static void ford_johnson(C &main_chain, PC &pair_container)
{
    int orphan = divide(main_chain, pair_container); 
    merge(pair_container.begin(), pair_container.end());
    insert_sort(main_chain, pair_container, orphan);
}

template <typename C>
double PmergeMe<C>::sort(C &main_chain)
{
    typename PairContainer<C>::type pair_container;
    if (main_chain.size() == 1)
        return 0.0;

    clock_t start = clock();
    ford_johnson(main_chain, pair_container);
    clock_t end = clock();

    if (!is_sorted(main_chain))
        throw(std::runtime_error("Error: Unsorted"));
 
    return static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;

}

#endif