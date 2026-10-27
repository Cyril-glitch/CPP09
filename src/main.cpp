/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 18:50:29 by cycolonn          #+#    #+#             */
/*   Updated: 2026/10/27 16:34:29 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include <iostream>
#include "../inc/BitcoinExchange.hpp"
#include "../inc/colors.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << BL_RED "WRONG ARGUMENTS" RESET << "\n";
        return 0;
    }

    try
    {
        BitcoinExchange btc(av[1]);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}