/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 19:06:57 by cycolonn          #+#    #+#             */
/*   Updated: 2026/10/30 16:17:33 by cycolonn         ###   ########.fr       */
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

        void            get_btc_value(const std::string &input_file);

        typedef std::map<std::string, double>::iterator iterator;
        
    private :

        std::map<std::string, double> _map; 

        struct t_input_line
        {
            std::string buf;
            std::string date;
            std::string sbtc;
            double nbtc;
            size_t pos;
        };

        void    _parse_csv(const std::string &csv);
        int     _check_date(const std::string &date);
        int     _parse_input(t_input_line &line);
        void    _display_value(const std::string &date, double nbtc);
};
   
#endif