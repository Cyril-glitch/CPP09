/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 11:50:37 by cycolonn          #+#    #+#             */
/*   Updated: 2026/10/29 18:49:50 by cycolonn         ###   ########.fr       */
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
    if (buf == "date | value" && first_line)
    {
        first_line = 0;
        return 0;
    }
    if (pos >= (buf.size() - 1) || pos == std::string::npos) 
        return 0; 
    else 
        return 1; 
}

int BitcoinExchange::_check_date(const std::string &date) 
{
   // 0 1 2 3 4 5 6 7 8 9
   // y y y y - m m - d d

    /* check that there is only two '-' and that they are well positioned */
    if (date.size() != 10) return 0;
    if (date.find_first_not_of("012345689-")) return 0;
    if (date.find_first_of('-') != 4 && date.find_last_of('-') != 7) return 0;
    if (!std::isdigit(date[5] || !std::isdigit(date[6]))) return 0;

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(4, 2).c_str());
    int day = std::atoi(date.substr(7, 2).c_str());

    if (month == 0 || month > 12) return 0;
    if (day == 0 || day > 31) return 0;
    if (month == 2 && day > 29) return 0;
    if (!(year % 4) && month == 2 && day > 29) return 0;
    return 1;
}

void BitcoinExchange::_parse_input(const std::string &buf, std::string &date, std::string &sbtc, size_t pos)
{
    _check_format(buf, pos);
    date = buf.substr(0, pos - 1);
    sbtc = buf.substr(pos + 2, (buf.size() - pos));
    _check_date(date);
    _check_sbtc(nbtc);
}

int BitcoinExchange::_check_sbtc(const std::string &sbtc, double &nbtc)
{
    char end*;
    nbtc = std::strtod(sbtc.c_str(), end);
    
    if (*end != '\0') 
        return 0;
    else 
        return 1;
}

void BitcoinExchange::_display_value(const std::string &date, double nbtc)
{
    iterator it = _map.lower_bound(date);
    double exchange = it->second * nbtc;

    if (it->first != date && it != date.begin()) 
        it--;
    if (nbtc > 1000)
        std::cerr << "Error: too large a number.\n"; 
    else if (nbtc < 0)
        std::cerr << "Error: not a positive number.\n"; 
    else 
        std::cout << date << " => " << nbtc << " = " << exchange << "\n";
}


void BitcoinExchange::get_btc_value(const std::string &input_file)
{
    std::ifstream ifs;
    std::string buf;
    std::string date;
    std::string sbtc;
    double nbtc;
    size_t pos;

    ifs.open(input_file.c_str());
    if (!ifs.is_open())
        throw(std::runtime_error("Error: cannot open input_file."));

    while (std::getline(ifs, buf))
    {
        if (_parse_input(buf,date,sbtc, pos))
            _display_value(date , nbtc); 
        else 
            std::cerr << "Error: bad input => " << buf << "\n"; 
    }
}

/*------------------------------------------------------------------------------*/