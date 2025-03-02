#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

// Use inheritance from std::vector (choose public/private) as appropriate
template <typename T>
class Stack : private std::vector<T>
{
public:
    Stack();
    ~Stack();
    bool empty() const;
    size_t size() const;
    void push(const T& item);
    void pop();  // throws std::underflow_error if empty
    const T& top() const; // throws std::underflow_error if empty
    // Add other members only if necessary
};

template <typename T>
Stack<T>::Stack() : std::vector<T>(){

}

template <typename T>
Stack<T>::~Stack(){

}

template <typename T>
bool Stack<T>::empty() const{
    return size() == 0;
}

template <typename T>
size_t Stack<T>::size() const {
    return std::vector<T>::size();
}

template <typename T>
void Stack<T>::push(const T& item){
    std::vector<T>::push_back(item); //Instead of push_front so that it's O(1)
}

template <typename T>
void Stack<T>::pop(){  // throws std::underflow_error if empty
    if(empty())
        throw std::underflow_error("Can't pop if empty.");
    else
        std::vector<T>::pop_back(); //Instead of push_front so that it's O(1)
}

template <typename T>
const T& Stack<T>::top() const { // throws std::underflow_error if empty
    if(empty())
        throw std::underflow_error("Can't access top if empty.");
    return std::vector<T>::back(); // We have this as the order to maintain constant complexity
}

#endif