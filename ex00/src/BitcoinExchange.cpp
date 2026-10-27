/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 11:50:37 by cycolonn          #+#    #+#             */
/*   Updated: 2026/10/27 20:22:47 by cycolonn         ###   ########.fr       */
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
    /*
    std::map<std::string, double>::iterator it = _map.begin();
    while (it != _map.end())
    {
        std::cout << "["<< it->first << "]" << "= "<< it->second << "\n";
        it++;
    }
    */
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

void BitcoinExchange::_display_value(const std::string &date, const std::string &nbtc)
{ 
    std::map<std::string, double>::iterator it = _map.lower_bound(date);
    if (it == _map.end())
    {
        std::string error = "Error: bad input => " + date;
        return ;
    }
    else if (it->first != date)
    {
        if (it != _map.begin())
            --it;
    }
    double value = _map[it->first] * std::strtod(nbtc.c_str(), NULL);
    if (value >= 0)
        std::cout << date << " => " << nbtc << " = " << value << "\n"; 
    else if (value > __INT_MAX__)
        std::cerr << "Error: too large a number.\n"; 
    else 
        std::cerr << "Error: not a positive number.\n"; 
}


void BitcoinExchange::get_btc_value(const std::string &input_file)
{
    std::ifstream ifs;
    std::string buf;
    size_t pos;

    ifs.open(input_file.c_str());
    if (!ifs.is_open())
        throw(std::runtime_error("Error: cannot open csv."));

    std::getline(ifs, buf);
    while (std::getline(ifs, buf))
    {
        if ((pos = buf.find_first_of('|')) != std::string::npos)
        {
            std::string date = buf.substr(0, pos - 1);
            std::string nbtc = buf.substr(pos + 2, (buf.size() - pos));
            _display_value(date, nbtc);
        }
    }
}