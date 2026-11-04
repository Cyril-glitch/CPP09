/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 17:15:06 by cycolonn          #+#    #+#             */
/*   Updated: 2026/11/04 20:31:22 by cycolonn         ###   ########.fr       */
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

class PmergeMe
{  
    public :

        static  void sort_vector(int ac, char **av);
        //static  void sort_deque(int ac, char **av);
        
    private :

        PmergeMe();
        PmergeMe(const PmergeMe& src);
        ~PmergeMe();

        PmergeMe& operator=(const PmergeMe &rhs);
};

#endif