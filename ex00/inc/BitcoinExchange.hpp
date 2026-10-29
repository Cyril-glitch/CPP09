/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 19:06:57 by cycolonn          #+#    #+#             */
/*   Updated: 2026/10/29 13:01:28 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include "../inc/colors.hpp"
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <climits>


class BitcoinExchange
{
    public :

        BitcoinExchange();
        BitcoinExchange(const std::string &csv);
        BitcoinExchange(const BitcoinExchange &src);
        ~BitcoinExchange();

        BitcoinExchange &operator=(const BitcoinExchange &rhs);

        void get_btc_value(const std::string &input_file);

        typedef std::map<std::string, double>::iterator iterator;
        
    private :

        std::map<std::string, double> _map; 

        void    _parse_csv(const std::string &csv);        
        int     _check_format(const std::string &buf, size_t &pos);
        double  _check_value(const std::string &date, const std::string &nbtc);
        void    _display_value(const std::string &date, const std::string &nbtc, const std::string &buf);
};
   
#endif