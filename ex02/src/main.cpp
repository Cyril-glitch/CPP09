/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 12:33:03 by cycolonn          #+#    #+#             */
/*   Updated: 2026/11/04 12:36:17 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/PmergeMe.hpp"

int main(int ac, char **av)
{
    try
    {
        PmergeMe::sort_vector(ac, av);
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << "\n";
    }
}