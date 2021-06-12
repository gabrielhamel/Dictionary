/**
 * @file Exceptions.hpp
 * @author Gabriel Hamel (gabriel.hamel.pro@gmail.com)
 * @brief
 * @version 1.0
 * @date 2021-06-12
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <exception>

class NotFound : public std::exception
{
    public:
        const char *what() const throw() {
            return "Child not found";
        }
};

class DoubleInsertion : public std::exception
{
    public:
        const char *what() const throw() {
            return "There are already existing child";
        }
};
