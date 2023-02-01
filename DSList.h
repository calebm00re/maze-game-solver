//
// Created by Caleb Moore on 3/23/21.
//

#ifndef PA04_AMAZING_DSLIST_H
#define PA04_AMAZING_DSLIST_H

//class template for list of nodes
template <class T>
class DSList{
private:
    //create a private node structure for the list to use
    struct DSnode{
        T data;
        DSnode* next{nullptr};
        DSnode* prev{nullptr};
    };

    DSnode* head{nullptr};
    DSnode* tail{nullptr};
    int count = 0;

    //make the functions so class users can manipulate the list
public:
    DSList(); //tested
    DSList(const DSList&); //tested
    DSList& operator= (const DSList&); //tested
    void add (T val); //tested
    void add_front(T val); //tested
    T& get_front(); //tested
    T& get_back(); //tested
    void delete_at(const int&); //tested
    bool empty(); //tested
    void clear(); //tested
    int get_size(); //tested
    ~DSList(); //valgrind will test
};

//default constructor
template<class T>
DSList<T>::DSList() = default;

//add a value to the back of the list
template<class T>
void DSList<T>::add(T val) {
    DSnode* temp = new DSnode;

    temp->data = val;

    if(head == nullptr){
        head = temp;
        tail = temp;
    }

    else{
        temp->prev = tail;
        tail->next = temp;
        tail = temp;
    }
    count++;
}

//add a value to the front of the list
template<class T>
void DSList<T>::add_front(T val) {
    DSnode* temp = new DSnode;

    temp->data = val;

    if(head == nullptr){
        head = temp;
        tail = temp;
    }

    else {
        temp->next = head;
        head->prev = temp;
        head = temp;
    }
    count++;
}

//default constructor? not allocating memory?
template<class T>
DSList<T>::~DSList() {
    this->clear();
}

//check to see if the list is empty
template<class T>
bool DSList<T>::empty() {
    if(head == nullptr){
        return true;
    }
    return false;
}

//clear the entirety of the list
template<class T>
void DSList<T>::clear() {
    DSnode* temp;
    while(head != nullptr){
        temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    count = 0;
}

//delete at an index if it exists
template<class T>
void DSList<T>::delete_at(const int & v) {
    DSnode* temp;
    int curr = 0;
    if (v >= count || v < 0){
        throw std::out_of_range("linked list access out of range");
    }

    temp = head;
    if(this->get_size() == 1){
        temp = head;
        head = nullptr;
        tail = nullptr;
        delete temp;
    }
    else {

        if (v == 0) {
            temp = head;
            head->next->prev = nullptr;
            head = head->next;
            delete temp;
        } else if (v == count - 1) {
            temp = tail;
            tail->prev->next = nullptr;
            tail = tail->prev;
            delete temp;
        } else {

            while (curr < count - 1 && curr != v) {
                temp = temp->next;
                curr++;
            }

            //do deleting after finding where to delete
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
        }
    }
    count--;
}

//get the size of the linked list
template<class T>
int DSList<T>::get_size() {
    return count;
}

//copy constructor
template<class T>
DSList<T>::DSList(const DSList & rhs) {
    DSnode* curr;
    curr = rhs.head;
    //count = rhs.count;

    for(int i = 0; i < rhs.count; i++){
        this->add(curr->data);
        curr = curr->next;
    }
}

//return the front most element if it exists
template<class T>
T &DSList<T>::get_front() {
    if (count == 0){
        throw std::out_of_range("list access out of range");
    }
    else{
        return head->data;
    }
}

//get the last most element if it exists
template<class T>
T &DSList<T>::get_back() {
    if (count == 0){
        throw std::out_of_range("list access out of range");
    }
    else {
        return tail->data;
    }
}

//overload assignment operator
template<class T>
DSList<T> &DSList<T>::operator=(const DSList & rhs) {
    DSnode* curr;
    curr = rhs.head;

    for(int i = 0; i < rhs.count; i++){
        this->add(curr->data);
        curr = curr->next;
    }
    return *this;
}


#endif //PA04_AMAZING_DSLIST_H