//
// Created by Caleb Moore on 2/23/21.
//

#ifndef INC_21S_PA02_DSVECTOR_H
#define INC_21S_PA02_DSVECTOR_H
#include <iostream>

//template vector class
template <class T>
class DSVector{
private:
    //pointer to array of things of type T
    T* data;
    //size of vector - num of elements
    //this does not get a value assigned yet until one is made
    int size;
    //capacity of vector - number of fillable spaces
    //this does not get a value assigned yet until one is made
    int capacity;
    //make iterator value
    T* it{nullptr};
    int itIndex;
    //function to increase total capacity
    void grow_vector();
public:
    DSVector();
    DSVector(const DSVector&);
    DSVector& operator= (const DSVector&);
    T& operator[] (int l) const;
    void insert (const T& k, int w);
    void erase_at(const int& w);
    void push_back(const T& val);
    T& get_back();
    T& get_front();
    int get_size();
    int get_capacity();
    void pop_back();
    void sort();
    void elim_dupes();
    void move_it_next();
    T& get_it();
    int& getItIndex();
    void reset_it();
    bool checkIter(int &);
    ~DSVector();
};

//default constructor for making a new, empty DSVector
template <class T>
DSVector<T>::DSVector(){
    data = new T[10];
    capacity = 10;
    size = 0;
    it = &data[0];
    itIndex = 0;
}

//overload the [] operator to get an element at the specified index passed to this function
template <class T>
T& DSVector<T>::operator[] (int l) const{
    if(l >= size || l < 0){
        throw std::out_of_range("vector access out of range");
    }
    return data[l];
}

//insert an element of type T wherever is passed as the second argument
template <class T>
void DSVector<T>::insert(const T& k, int w){
    if(size == capacity){
        grow_vector();
    }

    for(int i = size; i >= w; i--){
        data[i] = data[i - 1];
    }

    data[w - 1] = k;
    size++;
}

//add elements to the end of the DSVector
template <class T>
void DSVector<T>::push_back(const T& val){
    if(size == capacity){
        grow_vector();
    }
    data[size++] = val;
}

//make sure the vector grows when this is called and the vector is out of room
template <class T>
void DSVector<T>::grow_vector(){
    T* temp = new T[2*capacity];

    for(int i = 0; i < size; i++){
        temp[i] = data[i];
    }

    capacity *= 2;
    delete[] data;

    data = temp;
}

//return the first element in the DSVector
template<class T>
T& DSVector<T>::get_front() {
    return data[0];
}

//return the last element in the DSVector
template<class T>
T &DSVector<T>::get_back() {
    return data[size - 1];
}

//return the size of the DSVector i.e. the num of total elements
template<class T>
int DSVector<T>::get_size() {
    return size;
}

//return the capacity
template<class T>
int DSVector<T>::get_capacity() {
    return capacity;
}

//delete the vector
template<class T>
DSVector<T>::~DSVector() {
    delete[] data;
}

//overload the assignment operator to make sure one vector can be cloned
template<class T>
DSVector<T>& DSVector<T>::operator=(const DSVector<T>& rhs) {
    delete[] data;

    data = new T[rhs.capacity];
    capacity = rhs.capacity;
    size = rhs.size;
    for(int i = 0; i < size; i++){
        data[i] = rhs.data[i];
    }
    it = rhs.it;
    itIndex = rhs.itIndex;
    return *this;
}

//erase function to delete an element my shifting everything down by one until the spot
// the erasing takes place and decrement the size
template<class T>
void DSVector<T>::erase_at(const int &w) {

    for(int i = w; i < this->get_size() - 1; i++){
        data[i] = data[i + 1];
    }
    size--;
}

//copy constructor to make one DSVector from another
template<class T>
DSVector<T>::DSVector(const DSVector & rhs) {
    delete[] data;

    data = new T[rhs.capacity];
    capacity = rhs.capacity;
    size = rhs.size;
    for(int i = 0; i < size; i++){
        data[i] = rhs.data[i];
    }
    it = rhs.it;
    itIndex = rhs.itIndex;
}

//delete the last element in a DSVector
template<class T>
void DSVector<T>::pop_back() {
    erase_at(size - 1);
}

// quick bubble sort from http://www.cplusplus.com/forum/general/160434/
// used in sorting DSVectors of smaller sizes
template<class T>
void DSVector<T>::sort() {
    T temp;
    for (int k = 0; k < size; k++)
    {
        for (int i = 0; i < size - 1; i++){
            if (data[i] > data[i + 1])
            {
                temp = data[i];
                data[i] = data[i + 1];
                data[i + 1] = temp;
            }
        }
    }
}

//function to get rid of any duplicate elements in a DSVector object
template<class T>
void DSVector<T>::elim_dupes() {
    for(int i = 0; i < get_size() - 1; i++){
        for(int j = i + 1; j < get_size(); j++){
            if(data[i] == data[j]){
                erase_at(j);
            }
        }
    }
}

//this moves the iterator to the next place if it can go there otherwise it makes it nullptr
template<class T>
void DSVector<T>::move_it_next() {
    if(itIndex >= size){
        it = nullptr;
    }
    else {
        it = &data[++itIndex];
    }
}

//this function will return the iterator value it is pointing to
template<class T>
T &DSVector<T>::get_it() {
    return *it;
}

//this resets the iterator to point to the first element
template<class T>
void DSVector<T>::reset_it() {
    it = &data[0];
    itIndex = 0;
}

//this is useful in knowing where the iterator is currently in the vector
template<class T>
int &DSVector<T>::getItIndex() {
    return itIndex;
}

//this function is useful in checking to see if the iterator value is valid
template<class T>
bool DSVector<T>::checkIter(int& t) {
    if(t >= size){
        return false;
    }
    return true;
}


#endif //INC_21S_PA02_DSVECTOR_H
