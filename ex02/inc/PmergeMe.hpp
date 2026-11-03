/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 17:15:06 by cycolonn          #+#    #+#             */
/*   Updated: 2026/11/03 17:38:12 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

class PmergeMe
{  
    public :

        static  void sort(int ac, char **av);

    private :

        PmergeMe();
        PmergeMe(const PmergeMe& src);
        ~PmergeMe();

        PmergeMe& operator=(const PmergeMe &rhs);
};

#endif