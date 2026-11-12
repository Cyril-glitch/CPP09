/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 18:28:46 by cycolonn          #+#    #+#             */
/*   Updated: 2026/11/12 15:01:27 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>
#include <list>


class RPN
{
    public :

        static int resolve(const std::string &operation); 
          
    private :

        RPN();
        RPN(const RPN &src);
        ~RPN();

        RPN& operator=(const RPN &rhs); 
};

#endif