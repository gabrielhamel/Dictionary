/**
 * @file Dictionary.hpp
 * @author Gabriel Hamel (gabriel.hamel.pro@gmail.com)
 * @brief
 * @version 1.0
 * @date 2021-06-12
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <string>
#include <functional>

#include "Node.hpp"

template <class T>
class Dictionary : protected Node<T> {
    public:
        Dictionary();

        /**
         * @brief Insert a new word into the dictionary
         *
         * @param word The word to insert
         */
        void addWord(const std::basic_string<T> &word);

        /**
         * @brief Check the presence of the specified word
         *
         * @param word The word to looking for
         * @param word The number of maximums error allowed during the search
         */
        bool hasWord(const std::basic_string<T> &word, size_t maxErrors = 0);
};

template<class T>
Dictionary<T>::Dictionary() : Node<T>{'\0'}
{

}

template<class T>
void Dictionary<T>::addWord(const std::basic_string<T> &word)
{
    // Convert word to list
    std::list<T> charList(word.begin(), word.end());
    auto iterator = charList.begin();

    // Insert list into children
    this->insertDataSlice(charList, iterator);
}

template<class T>
bool Dictionary<T>::hasWord(const std::basic_string<T> &word, size_t maxErrors)
{
    // Convert word to list
    std::list<T> charList(word.begin(), word.end());

    return this->hasDataSlice(charList, charList.begin(), maxErrors);
}
