/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 18:27:39 by cycolonn          #+#    #+#             */
/*   Updated: 2026/11/02 20:10:40 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RPN.hpp"

#include <iostream>
#include <stdexcept>

int main(int ac, char **av)
{
    if (ac != 2 || !av[1][0])
        return std::cerr << "Error\n", 0;
    try
    {
        std::cout << RPN::resolve(av[1]) << "\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
