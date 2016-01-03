//
//  smart_list_example.cpp
//  A test and demo for the SMART_LIST.hpp class implementation.
//
//  Created by Christopher Gleeson on 1/1/16.
//  Copyright © 2016 Christopher Gleeson. All rights reserved.
//

#include "SMART_LIST.hpp"

int main(int argc, const char * argv[]) {

    //Create the list object
    LinkedList<int> myList;
    
    //Check the empty list
    bool isEmpty = myList.checkEmpty();
    if(isEmpty) {
        std::cout << "List, post creation is empty.\n";
    }else{
        std::cout << "Something went wrong, the new list should start empty!\n";
    }
    
    //Add the first element
    if(myList.insertFront(6)) {
        int count = 0;
        int *countptr = &count;
        myList.getCount(countptr);
        std::cout << "\nList insertion for key of 6 returned success.\n";
        std::cout << "\nNumber of elements in the list is: " << *countptr << "\n";
    }else{
        std::cout << "\nList insertion returned failure!\n";
    }
    
    //Peek at the first element
    int value = 0;
    int *valptr = &value;
    bool success = myList.peekFront(valptr);
    if(success) {
        std::cout << "\nFirst element in the list has value: " << *valptr << "\n";
    }else{
        std::cout << "\nFailed to peek at the first element in the list!\n";
    }
    
    //Peek at the last element (same as the first)
    success = myList.peekRear(valptr);
    if(success) {
        std::cout << "\nLast element in the list has value: " << *valptr << "\n";
    }else{
        std::cout << "\nFailed to peek at the last element in the list!\n";
    }
    
    //Perform more insertions
    std::cout << "\nPerforming 11 insertions...\n\n";
    myList.insertFront(5);
    myList.insertFront(4);
    myList.insertFront(3);
    myList.insertFront(2);
    myList.insertFront(1);
    myList.insertBack(7);
    myList.insertBack(8);
    myList.insertBack(9);
    myList.insertBack(10);
    myList.insertBack(11);
    myList.insertBack(12);
    
    //Print the list
    myList.print();
    //Print the count of the list, it should be 12
    int count = 0;
    int *countptr = &count;
    myList.getCount(countptr);
    std::cout << "Number of elements in the list is: " << *countptr << "\n";
    
    //Remove the front element of the list
    myList.remFront(valptr);
    std::cout << "Removed front element with value: " << *valptr << "\n";
    
    //Print the list
    myList.print();
    myList.getCount(countptr);
    std::cout << "Number of elements in the list is: " << *countptr << "\n";
    
    //Remove the back element of the list
    myList.remBack(valptr);
    std::cout << "Removed rear element with value: " << *valptr << "\n";
    
    //Print the list
    myList.print();
    myList.getCount(countptr);
    std::cout << "Number of elements in the list is: " << *countptr << "\n";
    
    //Peek at the last element
    success = myList.peekRear(valptr);
    if(success) {
        std::cout << "\nLast element in the list has value: " << *valptr << "\n";
    }else{
        std::cout << "\nFailed to peek at the last element in the list!\n";
    }
    
    //Empty the list via remFront
    std::cout << "Beginning looped front removal...\n";
    while(!myList.checkEmpty()) {
        myList.remFront(valptr);
        std::cout << "Removed front element with value: " << *valptr << "\n";
    }
    
    //Print the list
    myList.print();
    *countptr = 0;
    myList.getCount(countptr);
    std::cout << "Number of elements in the list is: " << *countptr << "\n";

    //Peek again at the first element
    success = myList.peekFront(valptr);
    if(success) {
        std::cout << "\nFirst element in the list has value: " << *valptr << "\n";
    }else{
        std::cout << "\nFailed to peek at the first element in the list!\n";
    }
    
    //Peek again at the last element
    success = myList.peekRear(valptr);
    if(success) {
        std::cout << "\nLast element in the list has value: " << *valptr << "\n";
    }else{
        std::cout << "\nFailed to peek at the last element in the list!\n";
    }

    //Perform more insertions
    std::cout << "\nPerforming 12 insertions...\n\n";
    myList.insertFront(6);
    myList.insertFront(5);
    myList.insertFront(4);
    myList.insertFront(3);
    myList.insertFront(2);
    myList.insertFront(1);
    myList.insertBack(7);
    myList.insertBack(8);
    myList.insertBack(9);
    myList.insertBack(10);
    myList.insertBack(11);
    myList.insertBack(12);
    
    //Print the list
    myList.print();
    myList.getCount(countptr);
    std::cout << "Number of elements in the list is: " << *countptr << "\n";

    //test search
    bool searchresult = myList.searchByKey(1);
    std::cout << "\nSearch for key of 1 returned " << searchresult << "\n";
    searchresult = myList.searchByKey(11);
    std::cout << "\nSearch for key of 11 returned " << searchresult << "\n";
    searchresult = myList.searchByKey(99);
    std::cout << "\nSearch for key of 99 returned " << searchresult << "\n";
    
    //test remove key
    bool remresult = myList.removeKey(8);
    std::cout << "\nRemoval for key of 8 returned " << remresult << "\n";
    myList.print();
    myList.getCount(countptr);
    std::cout << "Number of elements in the list is: " << *countptr << "\n";
    remresult = myList.removeKey(1);
    std::cout << "\nRemoval for key of 1 returned " << remresult << "\n";
    myList.print();
    myList.getCount(countptr);
    std::cout << "Number of elements in the list is: " << *countptr << "\n";
    remresult = myList.removeKey(12);
    std::cout << "\nRemoval for key of 12 returned " << remresult << "\n";
    myList.print();
    myList.getCount(countptr);
    std::cout << "Number of elements in the list is: " << *countptr << "\n";
    
    //test remove index
    remresult = myList.removeIndex(3);
    std::cout << "\nRemoval for index of 3 (value 5) returned " << remresult << "\n";
    myList.print();
    myList.getCount(countptr);
    std::cout << "Number of elements in the list is: " << *countptr << "\n";
    remresult = myList.removeIndex(0);
    std::cout << "\nRemoval for index of 0 (value 2) returned " << remresult << "\n";
    myList.print();
    myList.getCount(countptr);
    std::cout << "Number of elements in the list is: " << *countptr << "\n";
    remresult = myList.removeIndex(6);
    std::cout << "\nRemoval for index of 6 (value 11) returned " << remresult << "\n";
    myList.print();
    myList.getCount(countptr);
    std::cout << "Number of elements in the list is: " << *countptr << "\n";
    
    //Empty the list via remBack
    std::cout << "\nBeginning looped rear removal...\n";
    while(!myList.checkEmpty()) {
        myList.remBack(valptr);
        std::cout << "Removed rear element with value: " << *valptr << "\n";
    }
    
    //Print the list
    myList.print();
    myList.getCount(countptr);
    std::cout << "Number of elements in the list is: " << *countptr << "\n";
    
    //Peek again at the first element
    success = myList.peekFront(valptr);
    if(success) {
        std::cout << "\nFirst element in the list has value: " << *valptr << "\n";
    }else{
        std::cout << "\nFailed to peek at the first element in the list!\n";
    }
    
    //Peek again at the last element
    success = myList.peekRear(valptr);
    if(success) {
        std::cout << "\nLast element in the list has value: " << *valptr << "\n";
    }else{
        std::cout << "\nFailed to peek at the last element in the list!\n";
    }
    
    return 0;
}











