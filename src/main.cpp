/**
 * @file main.cpp
 * @author Gabriel Hamel (gabriel.hamel.pro@gmail.com)
 * @brief
 * @version 1.0
 * @date 2021-06-12
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <string>
#include <iostream>
#include <Dictionary.hpp>

int main(int ac, const char **av)
{

    Dictionary<char> dictionary;

    std::string word1 = "Hello";
    std::string word2 = "Bonsoir";
    std::string word3 = "Bonjour";

    dictionary.addWord(word1);
    dictionary.addWord(word2);
    dictionary.addWord(word3);

    std::cout << dictionary.hasWord("Hello") << std::endl;
    std::cout << dictionary.hasWord("Helo") << std::endl;
    std::cout << dictionary.hasWord("Hmllo", 1) << std::endl;
    // std::cout << dictionary.hasWord("Bonjour") << std::endl;
    // std::cout << dictionary.hasWord("Bonsoir") << std::endl;

    // std::cout << dictionary.hasWord("Bonsoir test") << std::endl;
    // std::cout << dictionary.hasWord("Hell") << std::endl;

    //dictionary.tree([](wchar_t c) { return std::string(1, c); });
}
