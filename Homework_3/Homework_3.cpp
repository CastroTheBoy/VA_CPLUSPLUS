#include <iostream>
#include <ctime>
#include <limits>
#include "LinkedList.hpp"

// TASK DESCRIPTION:
// Create a function, that adds a new element in the middle of the list, whose value is equal to the largest value of the list.
// For example, if list is {7;1;4;3} the list will be {7;1;7;4;3}, or if list is {13;7;11;4;3} the list will be {13;7;11;13;4;3}.

int LargestElement(LinkedList<int>* list) {
    if (list->Size() == 0) {
        return (int)NULL;
    }

    int listSize = list->Size();
    int* listElements = new int[listSize];

    for (int i = 0; i < listSize; i++) {
        listElements[i] = *(list->Get(i));
    }
    
    int largestNumber = listElements[0];

    for (int i = 1; i < list->Size(); i++) {
        int* currentNumber = &listElements[i];
        if (largestNumber < *currentNumber) {
            largestNumber = *currentNumber;
        }
    }
    delete[] listElements;

    return largestNumber;
}

int main()
{
    std::srand(std::time({}));

    auto listOdd = new LinkedList<int>();
    auto listEven = new LinkedList<int>();

    for (int i = 0; i < 10; i++) {
        listEven->Add(std::rand() % 20);
    }
    
    for (int i = 0; i < 11; i++) {
        listOdd->Add(std::rand() % 20);
    }

    std::cout << "List with even number of elements" << '\n';
    listEven->PrintAll();
    std::cout << "Largest element: " << LargestElement(listEven) << '\n';
    listEven->Add(LargestElement(listEven), (listEven->Size() % 2 == 0 ? (int)(listEven->Size() / 2): (int)(listEven->Size() / 2)));
    std::cout << '\n' << "List after injecting largest element in the middle: " << '\n';
    listEven->PrintAll();

    std::cout << '\n' << "List with odd number of elements" << '\n';
    listOdd->PrintAll();
    std::cout << "Largest element: " << LargestElement(listOdd) << '\n';
    listOdd->Add(LargestElement(listOdd), (listOdd->Size() % 2 == 0 ? (int)(listOdd->Size() / 2) : (int)(listOdd->Size() / 2)));
    std::cout << '\n' << "List after injecting largest element in the middle: " << '\n';
    listOdd->PrintAll();

    delete listEven;
    delete listOdd;

    std::cout << '\n' << "Press Enter to close the program" << '\n';
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getchar(); // For compiled versions so that console doesn't close immediatelly
}