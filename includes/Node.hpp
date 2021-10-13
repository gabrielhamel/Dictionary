/**
 * @file Node.hpp
 * @author Gabriel Hamel (gabriel.hamel.pro@gmail.com)
 * @brief
 * @version 1.0
 * @date 2021-06-12
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <functional>
#include <vector>
#include <string>
#include <list>

#include "Exceptions.hpp"

template<class T>
class Node {
    private:
        T data;
        std::vector<Node<T>> children;
        bool isWordEnd;

    protected:
        Node &findChildByData(T data);
        Node &findOrInsertChild(T data, bool isWordEnd);

    private:
        bool searchBySubstitutionOrRemovedChar(typename::std::list<T>::iterator start, typename::std::list<T>::iterator end, size_t maxErrors);
        bool searchByAddedChar(typename::std::list<T>::iterator start, typename::std::list<T>::iterator end, size_t maxErrors);

    public:
        Node();
        Node(T data, bool isWordEnd);
        void insertDataSlice(typename::std::list<T>::iterator start, typename::std::list<T>::iterator end);
        bool hasDataSlice(typename::std::list<T>::iterator start, typename::std::list<T>::iterator end, size_t maxErrors = 0);
};

template<class T>
Node<T>::Node()
{

}

template<class T>
Node<T>::Node(T data, bool isWordEnd) :
data(data), isWordEnd(isWordEnd)
{

}

template<class T>
Node<T> &Node<T>::findChildByData(T data)
{
    for (auto &child : this->children)
        if (child.data == data)
            return child;
    throw NotFound();
}

template<class T>
Node<T> &Node<T>::findOrInsertChild(T data, bool isWordEnd)
{
    // Check if data isn't already in a child
    try {
        auto &child = this->findChildByData(data);

        // Child already exist, set him to end delimiter if isn't already the case
        child.isWordEnd |= isWordEnd;
        return child;
    } catch (const NotFound &e) {
        // Insert child
        this->children.push_back(Node{data, isWordEnd});
        return this->children.back();
    }
}

template<class T>
void Node<T>::insertDataSlice(typename::std::list<T>::iterator start, typename::std::list<T>::iterator end)
{
    // Nothing to append
    if (start == end)
        return;

    // Find or create new child with the first item
    auto &child = this->findOrInsertChild(*start, std::next(start) == end);

    // Remove first item and send remaining slice part to child
    child.insertDataSlice(std::next(start), end);
}

template<class T>
bool Node<T>::searchBySubstitutionOrRemovedChar(typename::std::list<T>::iterator start, typename::std::list<T>::iterator end, size_t maxErrors)
{
    // Try to find the remaining slice part into the children
    for (auto &child : this->children) {
        // Search by substitution
        // Ignore the substitued character
        if (child.hasDataSlice(std::next(start), end, maxErrors - 1))
            return true;

        // Search if there are removed char
        if (child.hasDataSlice(start, end, maxErrors - 1))
            return true;
    }
    return false;
}

template<class T>
bool Node<T>::searchByAddedChar(typename::std::list<T>::iterator start, typename::std::list<T>::iterator end, size_t maxErrors)
{
    // Ignore the wrong char and test himself again
    return this->hasDataSlice(std::next(start), end, maxErrors - 1);
}

template<class T>
bool Node<T>::hasDataSlice(typename::std::list<T>::iterator start, typename::std::list<T>::iterator end, size_t maxErrors)
{
    // All children founds
    if (start == end && this->isWordEnd)
        return true;

    try {
        // Try to find the first member of the slice
        auto &child = this->findChildByData(*start);

        // Send in recursive the other part of the slice
        return child.hasDataSlice(std::next(start), end, maxErrors);
    } catch (const NotFound &e) {
        // Child not found, the word isn't complete
        if (maxErrors == 0)
            // No errors allowed
            return false;

        // Error handling
        return
            // Character removed test
            // Substitution test
            this->searchBySubstitutionOrRemovedChar(start, end, maxErrors) ||
            // Character added test
            this->searchByAddedChar(start, end, maxErrors);
    }
}
