//
// Created by Caleb Moore on 3/26/21.
//

#ifndef PA04_AMAZING_DSSTACK_H
#define PA04_AMAZING_DSSTACK_H
#include "DSList.h"

template <class T>
class DSStack{
private:
    //private variable
    DSList<T> data;
public:
    //functions to use the stack correctly
    DSStack(); //tested
    DSStack(const DSStack&); //tested
    DSStack& operator= (const DSStack&); //tested
    void push(T& val); //tested
    void pop(); //tested
    T& top(); //tested with pop for double checking
    bool is_empty(); //tested
    ~DSStack(); //valgrind will test hopefully
};

//this adds an element to the top of the stack
template<class T>
void DSStack<T>::push(T &val) {
    data.add_front(val);
}

//this removes the element at the top of the stack
template<class T>
void DSStack<T>::pop() {
    data.delete_at(0);
}

//this returns a reference to the top of the stack
template<class T>
T &DSStack<T>::top() {
    return data.get_front();
}

//this returns true if the stack is empty
template<class T>
bool DSStack<T>::is_empty() {
    return data.empty();
}

//this is the copy constructor
template<class T>
DSStack<T>::DSStack(const DSStack & rhs) {
    data = rhs.data;
}

//this is the assignment operator overloaded
template<class T>
DSStack<T> &DSStack<T>::operator=(const DSStack & rhs) {
    data = rhs.data;
    return *this;
}

//destructor? no dynamic memory?
template<class T>
DSStack<T>::~DSStack() {
    data.clear();
}

//default constructor
template<class T>
DSStack<T>::DSStack() = default;

#endif //PA04_AMAZING_DSSTACK_H
