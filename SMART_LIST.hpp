//
//  SMART_LIST.h
//
//  A Class implementing a basic singly linked list via the shared_ptr Smart Pointer.
//
//  Created by Christopher Gleeson on 1/2/16.
//  Copyright © 2016 Christopher Gleeson. All rights reserved.
//

#ifndef SMART_LIST_hpp
#define SMART_LIST_hpp

#include <iostream>
#include <memory>

template <typename T>
class LinkedList {
private:
    
    //Definition for Node class
    class Node {
        friend class LinkedList<T>;
    private:
        T _key;
        std::shared_ptr<Node> _next;
    public:
        Node(T k) {
            _key = k;
            _next = nullptr;
        }
        ~Node() = default;
    };
    
    //Instance variables
    int _count = 0; //track the number of nodes
    std::shared_ptr<Node> _head = nullptr;  //head pointer to start of list
    std::shared_ptr<Node> _tail = nullptr;  //tail pointer to the last list element
    
public:
    
    LinkedList() = default;
    ~LinkedList() = default;
    
    //All public methods below return false on error,
    //except for checkEmpty.
    
    //Return true if the list is empty
    bool checkEmpty ();
    
    //Returns true/false on success/fail
    //Assigns the number of nodes in the list to countptr
    bool getCount(int *countptr);
    
    //Returns true/false on success/fail
    //Print the list
    bool print();
    
    //Search for a key and return true if the key exists
    bool searchByKey(T key);
    
    //Returns true/false on success/fail
    //Assigns a successfully found key to T *value
    bool peekFront(T *value);
    
    //Returns true/false on success/fail
    //Assigns the key to T *value on success
    bool peekRear(T *value);
    
    //Returns true/false on success/fail
    //Assigns the key to T *value on success
    bool remFront(T *value);
    
    //Returns true/false on success/fail
    //Assigns the key to T *value on success
    bool remBack(T *value);
    
    //Returns true/false on success/fail
    //Removes the node from the list with the specified key
    bool removeKey(T key);
    
    //Returns true/false on success/fail
    //Removes the node from the list at the specified index
    //Index stars at 0 and goes to _count-1
    bool removeIndex(int index);
    
    //Returns true/false on success/fail
    //Insert a new key into the front of the list
    bool insertFront(T key);
    
    //Returns true/false on success/fail
    //Insert a new key to the rear of the list
    bool insertBack(T key);
    
};

template <typename T>
bool LinkedList<T>::checkEmpty() {
    if(_head == nullptr) {
        return true;
    }else{
        return false;
    }
}

template <typename T>
bool LinkedList<T>::getCount(int *countptr) {
    *countptr = _count;
    return true;
}

template <typename T>
bool LinkedList<T>::print() {
    if(checkEmpty()) {
        std::cout << "List is empty!\n";
        return false;
    }
    
    std::cout << "Printing list...\n";
    auto current = _head;
    while(current->_next) {
        std::cout << current->_key << "\n";
        current = current->_next;
    }
    //print the last item
    std::cout << current->_key << "\n";
    return true;
}


template <typename T>
bool LinkedList<T>::searchByKey(T key) {
    if(checkEmpty()) return false;
    
    auto current = _head;
    while(current->_next) {
        if(current->_key == key) return true;
        current = current->_next;
    }
    
    return false;
}

template <typename T>
bool LinkedList<T>::peekFront(T *value) {
    if(checkEmpty()) return false;
    
    auto current = _head;
    *value = current->_key;
    return true;
}

template <typename T>
bool LinkedList<T>::peekRear(T *value) {
    if(checkEmpty()) return false;
    
    auto current = _tail;
    *value = current->_key;
    return true;
}

template <typename T>
bool LinkedList<T>::remFront(T *value) {
    if(checkEmpty()) return false;
    
    //grab the key
    auto current = _head;
    *value = current->_key;
    
    //handle the singleton list case first
    if(_count == 1) {
        auto removeHead = std::move(_head);
        auto removeTail = std::move(_tail);
    }else{
        //the >= 2 element case
        auto remove = std::move(_head);
        _head = std::move(remove->_next);
    }
    
    //decrement the number of nodes
    _count--;
    
    return true;
}

template <typename T>
bool LinkedList<T>::remBack(T *value) {
    if(checkEmpty()) return false;
    
    //remFront handles the singleton list case
    if(_count == 1) {
        return remFront(value);
    }
    
    //the >= 2 element case
    auto current = _head;
    auto prev = _head;
    //advance current once
    if(current->_next) {
        current = current->_next;
    }
    //then advance both until the end
    while(current->_next) {
        prev = prev->_next;
        current = current->_next;
    }
    
    //grab the key
    *value = current->_key;
    
    //do the removal
    auto remove = std::move(prev->_next);
    _tail = prev;
    current = nullptr;
    
    //decrement the number of nodes
    _count--;
    
    return true;
}

template <typename T>
bool LinkedList<T>::removeKey(T key) {
    if(checkEmpty()) return false;
    
    //set up pointers
    auto current = _head;
    auto prev = current;
    
    //singleton list case
    if(_count == 1) {
        auto removeHead = std::move(_head);
        auto removeTail = std::move(_tail);
        _count--;
        return true;
    }else if (current->_key == key) {
        //the case where key is at head, non singleton list
        auto remove = std::move(_head);
        _head = std::move(remove->_next);
        _count--;
        return true;
    }
    
    //Key must be somewhere else in the list, get to it
    while(current->_next) {
        if(current->_key == key){
            break;
        }
        prev = current;
        current = current->_next;
    }
    
    //remove the node if the key matches
    if(current->_key == key) {
        prev->_next = std::move(current->_next);
        current.reset();
        _count--;
        return true;
    }
    //The node wasn't in the list
    return false;
}

template <typename T>
bool LinkedList<T>::removeIndex(int index){
    if(checkEmpty()) return false;
    
    //verify index is in bounds
    int count = 0;
    int *countptr = &count;
    getCount(countptr);
    if(index > (*countptr-1)) {
        std::cerr << "removeIndex called with index out of bounds!\n";
        return false;
    }
    
    //set up pointers
    auto current = _head;
    auto prev = current;
    
    //singleton list case / index is 0
    if(_count == 1 && index == 0) {
        auto removeHead = std::move(_head);
        auto removeTail = std::move(_tail);
        _count--;
        return true;
    }else if (index == 0) {
        //the case where index is at head, non singleton list
        auto remove = std::move(_head);
        _head = std::move(remove->_next);
        _count--;
        return true;
    }
    
    //Index is not head, get to it
    int i=0;
    while(current->_next && i < index) {
        prev = current;
        current = current->_next;
        i++;
    }
    
    //remove the node
    prev->_next = std::move(current->_next);
    current.reset();
    _count--;
    return true;
    
}

template <typename T>
bool LinkedList<T>::insertFront(T key) {
    //Create the new node with the value in key
    auto newptr = std::make_shared<Node>(key);
    
    if(!newptr) {
        //if the memory allocation failed, newptr should test false
        return false;
    }
    
    //case 1:  insert into an empty list
    if(checkEmpty()) {
        _head = newptr;
        _tail = newptr;
        _count++;
    }else{
        //case 2: List had at least one element
        auto temp = _head;
        _head = newptr;
        _head->_next = temp;
        _count++;
    }
    return true;
}

template <typename T>
bool LinkedList<T>::insertBack(T key) {
    //Create the new node with the value in key
    auto newptr = std::make_shared<Node>(key);
    
    if(!newptr) {
        //if the memory allocation failed, newptr should test false
        return false;
    }
    
    //case 1:  insert into an empty list
    if(checkEmpty()) {
        _head = newptr;
        _tail = newptr;
        _count++;
    }else{
        //case 2: List had at least one element
        _tail->_next = newptr;
        _tail = newptr;
        _count++;
    }
    return true;
}

#endif /* SMART_LIST_hpp */
