/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 11:50:37 by cycolonn          #+#    #+#             */
/*   Updated: 2026/10/29 13:11:05 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/BitcoinExchange.hpp"

/*------------------------------------------------------------------------------*/

//class building

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const std::string &csv)
{
    _parse_csv(csv);
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

/*------------------------------------------------------------------------------*/

//parse_csv

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

/*------------------------------------------------------------------------------*/

//get_btc_value

int BitcoinExchange::_check_format(const std::string &buf, size_t &pos)
{
    static int first_line = 1;

    pos = buf.find_first_of('|');
    if (pos >= (buf.size() - 1) || pos == std::string::npos)
        return (std::cerr << "Error: bad input => " + buf + "\n"), 0;
    else if (buf == "date | value" && first_line)
        return (first_line = 0), 0;
    return 1; 
}

double BitcoinExchange::_check_value(const std::string &date, const std::string &nbtc)
{
    char *end;
    double change = std::strtod(nbtc.c_str(), &end);
    iterator it = _map.lower_bound(date);

    if (it == _map.end()) return -1;
    if (it->first != date && it == _map.begin()) return -1;
    if (it->first != date && it != _map.begin()) --it;
    if (*end != '\0') return -1;
    if (change > 1000) return -2;
    if (change < 0) return -3;
    return (it->second * change);
}

void BitcoinExchange::_display_value(const std::string &date, const std::string &nbtc, const std::string &buf)
{  
    double value = _check_value(date, nbtc);

    if (value == -1)
        std::cerr << "Error: bad input => " + buf << "\n";
    if (value == -2)
        std::cerr << "Error: too large a number.\n"; 
    else if (value == -3)
        std::cerr << "Error: not a positive number.\n";  
    else 
        std::cout << date << " => " << nbtc << " = " << value << "\n";  
}

void BitcoinExchange::get_btc_value(const std::string &input_file)
{
    std::ifstream ifs;
    std::string buf;
    size_t pos;

    ifs.open(input_file.c_str());
    if (!ifs.is_open())
        throw(std::runtime_error("Error: cannot open input_file."));

    while (std::getline(ifs, buf))
    {
        if (_check_format(buf, pos))
        { 
                std::string date = buf.substr(0, pos - 1);
                std::string nbtc = buf.substr(pos + 2, (buf.size() - pos));
                _display_value(date, nbtc, buf);
        }
    }
}

/*------------------------------------------------------------------------------*/