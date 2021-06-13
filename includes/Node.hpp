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
        void dump(std::function<std::string(T)> toStringMethod, size_t deep = 0) const;

    private:
        bool searchBySubstitution(std::list<T> &slice, size_t maxErrors);
        bool searchByRemovedChar(std::list<T> &slice, size_t maxErrors);
        bool searchByAddedChar(std::list<T> &slice, size_t maxErrors);

    public:
        T data;

    public:
        Node(T data);
        void insertDataSlice(std::list<T> &slice);
        bool hasDataSlice(std::list<T> &slice, size_t maxErrors = 0);
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
void Node<T>::insertDataSlice(std::list<T> &slice)
{
    // Nothing to append
    if (slice.size() == 0)
        return;

    // Find or create new child with the first item
    auto &child = this->findOrInsertChild(slice.front());

    // Remove first item and send remaining slice part to child
    slice.pop_front();
    child.insertDataSlice(slice);
}

template<class T>
bool Node<T>::searchBySubstitution(std::list<T> &slice, size_t maxErrors)
{
    // Ignore the substitued character
    auto copySlice = std::list<T>(std::next(slice.begin()), slice.end());

    // Try to find the remaining slice part into the children
    for (auto &child : this->children) {
        // Children has the remaining slice
        if (child.hasDataSlice(copySlice, maxErrors)) {
            return true;
        }
    }
    return false;
}

template<class T>
bool Node<T>::searchByRemovedChar(std::list<T> &slice, size_t maxErrors)
{
    auto copySlice = std::list<T>(slice.begin(), slice.end());

    // Try to find the same slice into the children
    for (auto &child : this->children) {
        // Children has the remaining slice
        if (child.hasDataSlice(copySlice, maxErrors)) {
            return true;
        }
    }
    return false;
}

template<class T>
bool Node<T>::searchByAddedChar(std::list<T> &slice, size_t maxErrors)
{
    // Ignore the wrong char
    auto copySlice = std::list<T>(std::next(slice.begin()), slice.end());

    // Test himself again
    return this->hasDataSlice(copySlice, maxErrors);
}

template<class T>
bool Node<T>::hasDataSlice(std::list<T> &slice, size_t maxErrors)
{
    // All children founds
    if (slice.size() == 0)
        return true;

    try {
        // Try to find the first member of the slice
        auto &child = this->findChildByData(slice.front());

        // Send in recursive the other part of the slice
        auto copySlice = std::list<T>(std::next(slice.begin()), slice.end());
        return child.hasDataSlice(copySlice, maxErrors);
    } catch (NotFound &e) {
        // Child not found, the word isn't complete
        if (maxErrors == 0) {
            // No errors allowed
            return false;
        }

        // Error handling
        return
            // Character removed test
            this->searchByRemovedChar(slice, maxErrors - 1) ||
            // Substitution test
            this->searchBySubstitution(slice, maxErrors - 1) ||
            // Character added test
            this->searchByAddedChar(slice, maxErrors - 1);
    }
}
