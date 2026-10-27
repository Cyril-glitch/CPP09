/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 19:06:57 by cycolonn          #+#    #+#             */
/*   Updated: 2026/10/27 20:20:37 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <fstream>


class BitcoinExchange
{
    public :

        BitcoinExchange();
        BitcoinExchange(const std::string &csv);
        BitcoinExchange(const BitcoinExchange &src);
        ~BitcoinExchange();

        BitcoinExchange &operator=(const BitcoinExchange &rhs);

        void get_btc_value(const std::string &input_file);
        
    private :

        std::ifstream   ifs;
        std::string     _buf;
        std::map<std::string, double> _map; 
        void    _parse_csv(const std::string &csv);
        void    _display_value(const std::string &date, const std::string &nbtc);
};
   
#endif