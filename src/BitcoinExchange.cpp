/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 11:50:37 by cycolonn          #+#    #+#             */
/*   Updated: 2026/10/27 17:14:56 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/BitcoinExchange.hpp"
#include "../inc/colors.hpp"
#include <iostream>
#include <stdexcept>
#include <cstdlib>

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const std::string &csv)
{
    _parse_csv(csv);
    std::map<std::string, double>::iterator it = _map.begin();
    while (it != _map.end())
    {
        std::cout << "["<< it->first << "]" << "= "<< it->second << "\n";
        it++;
    }
}


BitcoinExchange::BitcoinExchange(const BitcoinExchange &src)
{
    _map = src._map;
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
    _map = rhs._map;
    return *this;
}


void BitcoinExchange::get_rate(const std::string &user_file)
{
    std::ifstream ifs;
    std::string buf;
    size_t pos;
    ifs.open(user_file.c_str());
    if (!ifs.is_open())
        throw(std::runtime_error("Error: cannot open csv."));

    std::getline(ifs, buf);

    while (std::getline(ifs, buf))
    {
        if ((pos = buf.find_first_of('|')) != std::string::npos)
        {
            std::string date = buf.substr(0, pos);
            std::string price = buf.substr(pos + 1, (buf.size() - pos));
            std::cout << date << " => " << price << " = " << (_map.at(date) * std::strtod(price,NULL)); 
        }
    }
}

void BitcoinExchange::_parse_csv(const std::string &csv)
{
    std::ifstream ifs;
    std::string buf;
    size_t pos;
    ifs.open(csv.c_str());
    if (!ifs.is_open())
        throw(std::runtime_error("Error: cannot open csv."));

    std::getline(ifs, buf);

    while (std::getline(ifs, buf))
    {
        if ((pos = buf.find_first_of(',')) != std::string::npos)
        {
            std::string date = buf.substr(0, pos);
            std::string rate = buf.substr(pos + 1, (buf.size() - pos));
            _map[date] = std::strtod(rate.c_str(), NULL);
        }
    }
}