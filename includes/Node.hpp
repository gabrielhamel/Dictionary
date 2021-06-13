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

    public:
        T data;

    public:
        Node(T data);
        void insertDataSlice(std::list<T> &slice);
        bool hasDataSlice(std::list<T> &slice);
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
bool Node<T>::hasDataSlice(std::list<T> &slice)
{
    // All children founds
    if (slice.size() == 0)
        return true;

    try {
        // Try to find the first member of the slice
        auto &child = this->findChildByData(slice.front());

        // Send in recursive the other part of the slice
        slice.pop_front();
        return child.hasDataSlice(slice);
    } catch (NotFound &e) {
        // Child not found, the word isn't complete
        return false;
    }
}

template<class T>
void Node<T>::dump(std::function<std::string(T)> toStringMethod, size_t deep) const
{
    for (auto &child : this->children) {
        std::cout << std::string(deep, ' ') << toStringMethod(child.data) << std::endl;
        child.dump(toStringMethod, deep + 1);
    }
}
