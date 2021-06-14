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
    protected:
        std::vector<Node<T>> children;

    protected:
        Node &findChildByData(T data);
        Node &findOrInsertChild(T data);

    private:
        bool searchBySubstitution(const std::list<T> &list, typename::std::list<T>::iterator slice, size_t maxErrors);
        bool searchByRemovedChar(const std::list<T> &list, typename::std::list<T>::iterator slice, size_t maxErrors);
        bool searchByAddedChar(const std::list<T> &list, typename::std::list<T>::iterator slice, size_t maxErrors);

    public:
        T data;

    public:
        Node(T data);
        void insertDataSlice(const std::list<T> &list, typename std::list<T>::iterator slice);
        bool hasDataSlice(const std::list<T> &list, typename::std::list<T>::iterator slice, size_t maxErrors = 0);
};

template<class T>
Node<T>::Node(T data) :
data(data)
{

}

template<class T>
Node<T> &Node<T>::findChildByData(T data)
{
    for (auto &child : this->children) {
        if (child.data == data) {
            return child;
        }
    }
    throw NotFound();
}

template<class T>
Node<T> &Node<T>::findOrInsertChild(T data)
{
    // Check if data isn't already in a child
    try {
        auto &child = this->findChildByData(data);

        // Child already exist
        return child;
    } catch (NotFound &e) {
        // Insert child
        this->children.push_back(Node(data));
        return this->children.back();
    }
}

template<class T>
void Node<T>::insertDataSlice(const std::list<T> &list, typename std::list<T>::iterator slice)
{
    // // Nothing to append
    if (slice == list.end())
        return;

    // // Find or create new child with the first item
    auto &child = this->findOrInsertChild(*slice);

    // Remove first item and send remaining slice part to child
    child.insertDataSlice(list, std::next(slice));
}

template<class T>
bool Node<T>::searchBySubstitution(const std::list<T> &list, typename::std::list<T>::iterator slice, size_t maxErrors)
{
    // Try to find the remaining slice part into the children
    for (auto &child : this->children) {
        // Ignore the substitued character
        // Children has the remaining slice
        if (child.hasDataSlice(list, std::next(slice), maxErrors - 1)) {
            return true;
        }
    }
    return false;
}

template<class T>
bool Node<T>::searchByRemovedChar(const std::list<T> &list, typename::std::list<T>::iterator slice, size_t maxErrors)
{
    // Try to find the same slice into the children
    for (auto &child : this->children) {
        // Children has the remaining slice
        if (child.hasDataSlice(list, slice, maxErrors - 1)) {
            return true;
        }
    }
    return false;
}

template<class T>
bool Node<T>::searchByAddedChar(const std::list<T> &list, typename::std::list<T>::iterator slice, size_t maxErrors)
{
    // Ignore the wrong char and test himself again
    return this->hasDataSlice(list, std::next(slice), maxErrors - 1);
}

template<class T>
bool Node<T>::hasDataSlice(const std::list<T> &list, typename::std::list<T>::iterator slice, size_t maxErrors)
{
    // All children founds
    if (slice == list.end())
        return true;

    try {
        // Try to find the first member of the slice
        auto &child = this->findChildByData(*slice);

        // Send in recursive the other part of the slice
        return child.hasDataSlice(list, std::next(slice), maxErrors);
    } catch (NotFound &e) {
        // Child not found, the word isn't complete
        if (maxErrors == 0) {
            // No errors allowed
            return false;
        }

        // Error handling
        return
            // Character removed test
            this->searchByRemovedChar(list, slice, maxErrors) ||
            // Substitution test
            this->searchBySubstitution(list, slice, maxErrors) ||
            // Character added test
            this->searchByAddedChar(list, slice, maxErrors);
    }
}
