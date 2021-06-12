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

    Dictionary<wchar_t> dictionary;

    std::string word1 = "Hello";
    std::string word2 = "Bonsoir";
    std::string word3 = "Bonjour";

    dictionary.addWord(std::wstring(word1.begin(), word1.end()));
    dictionary.addWord(std::wstring(word2.begin(), word2.end()));
    dictionary.addWord(std::wstring(word3.begin(), word3.end()));

    dictionary.tree([](char c) { return std::string(1, c); });
}
