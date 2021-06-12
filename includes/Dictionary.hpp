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
        void addWord(const std::basic_string<T> &word);
        void tree(std::function<std::string(T)> toStringMethod) const;
};

template<class T>
Dictionary<T>::Dictionary() : Node<T>('\0')
{

}

template<class T>
void Dictionary<T>::addWord(const std::basic_string<T> &word)
{
    // Convert word to list
    std::list<T> charList(word.begin(), word.end());

    // Insert list into children
    this->insertDataSlice(charList);
}

template<class T>
void Dictionary<T>::tree(std::function<std::string(T)> toStringMethod) const
{
    this->dump(toStringMethod);
}
