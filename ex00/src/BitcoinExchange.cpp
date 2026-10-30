/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 11:50:37 by cycolonn          #+#    #+#             */
/*   Updated: 2026/10/30 17:45:34 by cycolonn         ###   ########.fr       */
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
    ifs.close();
}

/*------------------------------------------------------------------------------*/

//parse_input

static int skip_first_line(const std::string &buf)
{
    static int first_line = 1;
    if (buf == "date | value" && first_line)
    {
        first_line = 0;
        return 1;
    }
    return 0;
}

static int check_format(const std::string &buf, size_t &pos)
{
    // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 
    // y y y y - m m - d d '' |  '' n 

    if (buf.size() < 14) 
        return 0;
    if (buf[10] != ' ' || buf[11] != '|' || buf[12] != ' ') 
        return 0;
    if (!(buf[13] == '+' || buf[13] == '-' || std::isdigit(buf[13])))
        return 0;
    pos = buf.find_first_of('|');
    return 1;
}

int BitcoinExchange::_check_date(const std::string &date)
{
   // 0 1 2 3 4 5 6 7 8 9
   // y y y y - m m - d d

    /* check the date format*/
    if (date.size() != 10) return 0;                                            //the right size
    if (date[4] != '-' || date[7] != '-') return 0;                             //separator position
    for (int i = 0; i < 10; i++)                                                    //digit position
    {
        if (i == 4 || i == 7) continue;
        if (!std::isdigit(date[i])) return 0;
    } 

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());
    int leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));              //handle leap years

    /*check month bounds*/
    if (month < 1 || month > 12) return 0;
    if (day < 1 || day > 31) return 0;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return 0;

    /*handle febrary*/
    if (month == 2 && leap && day > 29) return 0;
    if (month == 2 && !leap && day > 28) return 0;

    /*anterior*/
    iterator it = _map.lower_bound(date);
    if (it == _map.begin() && it->first != date) return 0;

    return 1;
}

static int check_sbtc(const std::string &sbtc, double &nbtc)
{
    char *end;
    nbtc = std::strtod(sbtc.c_str(), &end);

    if (*end != '\0')
        return 0;
    else
        return 1;
}

int BitcoinExchange::_parse_input(t_input_line &line)
{
    if ((!check_format(line.buf, line.pos)))
    {
        std::cerr << "Error: bad input => " << line.buf << "\n"; 
        return 0;
    }
    
    line.date = line.buf.substr(0, line.pos - 1);
    line.sbtc = line.buf.substr(line.pos + 2, (line.buf.size() - (line.pos - 1)));

    if (!_check_date(line.date))
    {
        std::cerr << "Error: bad input => " << line.date << "\n"; 
        return 0;
    }
    else if (!check_sbtc(line.sbtc, line.nbtc))
    {
        std::cerr << "Error: bad input => " << line.sbtc << "\n"; 
        return 0;
    }
    else if (line.nbtc > 1000)
    {
        std::cerr << "Error: too large a number.\n"; 
        return 0;
    }
    else if (line.nbtc < 0)
    {
        std::cerr << "Error: not a positive number.\n"; 
        return 0;
    }

    return 1;
}

/*------------------------------------------------------------------------------*/

//get_btc_value

void BitcoinExchange::_display_value(const std::string &date, double nbtc)
{
    iterator it = _map.lower_bound(date);

    if (it == _map.end() || (it->first != date && it != _map.begin())) it--;
    double exchange = it->second * nbtc;
    std::cout << date << " => " << nbtc << " = " << exchange << "\n";
}

void BitcoinExchange::get_btc_value(const std::string &input_file)
{
    std::ifstream ifs;
    t_input_line line;

    ifs.open(input_file.c_str());
    if (!ifs.is_open())
        throw(std::runtime_error("Error: cannot open input_file."));

    while (std::getline(ifs, line.buf))
    {
        if (skip_first_line(line.buf))
            continue;
        if (_parse_input(line))
            _display_value(line.date , line.nbtc); 
    }
    ifs.close();
}

/*------------------------------------------------------------------------------*/