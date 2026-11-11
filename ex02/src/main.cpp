/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 12:33:03 by cycolonn          #+#    #+#             */
/*   Updated: 2026/11/11 16:44:22 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/PmergeMe.hpp"

int main(int ac, char **av)
{
    try
    {
        std::vector<int> vector;
        std::deque<int> deque;
        if (!PmergeMe<std::vector<int> >::parser(ac, av,vector)) throw(std::invalid_argument("Error"));
        if (!PmergeMe<std::deque<int> >::parser(ac, av,deque)) throw(std::invalid_argument("Error"));

        std::cout << "Before: \n";
        PmergeMe<std::vector<int> >::display_main(vector);
         
        double v_time = PmergeMe<std::vector<int> >::sort(vector);
        double d_time = PmergeMe<std::deque<int> >::sort(deque);

        std::cout << "After: \n";
        PmergeMe<std::vector<int> >::display_main(vector);

        PmergeMe<std::vector<int> >::display_duration(v_time, vector.size(), vector);
        PmergeMe<std::deque<int> >::display_duration(d_time, deque.size(), deque);
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << "\n";
    }
}