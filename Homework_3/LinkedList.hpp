#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template <typename T> class LinkedList {
protected:
    template <typename U> struct node {
        U value;
        node<U>* nextNode;
    public:
        node(U value) {
            this->value = value;
            nextNode = nullptr;
        }
        node(U value, node<U>* nextNode) {
            this->value = value;
            this->nextNode = nextNode;
        }
    };

    node<T>* firstItem = nullptr;

public:
    LinkedList(T value) {
        firstItem = new node<T>(value);
    }

    LinkedList() {}

    // Add to end
    // Returns pointer to inserted value
    T* Add(T value) {
        if (firstItem == nullptr) {
            firstItem = new node<T>(value);
            return&firstItem->value;
        }

        node<T>* temp = firstItem;
        while (true) {
            if (temp->nextNode == nullptr) {
                temp->nextNode = new node<T>(value);
                return&temp->nextNode->value;
            }
            temp = temp->nextNode;
        }
    }

    // Insert at index n, if value exists at index n then shift it to the right
    // Returns pointer to inserted value or nullptr if insertion failed
    T* Add(T value, int index) {
        if (index < 0) {
            return nullptr;
        }

        node<T>* previousNode = nullptr;
        node<T>* currentNode = firstItem;
        // Iterate through list items, if index is not yet reached but list ends return nullptr
        for (int i = 0; i < index; i++) {
            if (currentNode == nullptr && i < index) {
                return nullptr;
            }
            previousNode = currentNode;
            currentNode = currentNode->nextNode;
        }

        // List empty, initalize first value
        if (previousNode == nullptr && currentNode == nullptr) {
            firstItem = new node<T>(value);
            return&firstItem->value;
        }

        // Insert into first item, shift current right
        if (previousNode == nullptr && currentNode != nullptr) {
            node<T>* temp = firstItem;
            firstItem = new node<T>(value, temp);
            return&firstItem->value;
        }

        // Index points to list length + 1
        if (currentNode == nullptr) {
            previousNode->nextNode = new node<T>(value);
            return&previousNode->nextNode->value;
        }

        // Insert between two elements
        node<T>* nextNode = currentNode->nextNode;
        previousNode->nextNode = new node<T>(value, currentNode);
        return&previousNode->nextNode->value;
    }

    T* Get(int index) const {
        if (index < 0) {
            return nullptr;
        }

        node<T>* previousNode = nullptr;
        node<T>* currentNode = firstItem;
        // Iterate through list items, if index is not yet reached but list ends return nullptr
        for (int i = 0; i < index; i++) {
            if (currentNode == nullptr && i < index) {
                return nullptr;
            }
            previousNode = currentNode;
            currentNode = currentNode->nextNode;
        }

        return& currentNode->value;
    }

    int Size() const {
        if (firstItem == nullptr) {
            return 0;
        }

        int i = 0;
        node<T>* temp = firstItem;
        while (temp != nullptr) {
            i++;
            temp = temp->nextNode;
        }
        return i;
    }

    void PrintAll() const {
        int i = 0;
        node<T>* temp = firstItem;
        while (temp != nullptr) {
            std::cout << i++ << ": " << temp->value << '\n';
            temp = temp->nextNode;
        }
    }

    ~LinkedList() {
        if (firstItem == nullptr) {
            return;
        }
        node<T>* temp1 = firstItem;
        node<T>* temp2 = firstItem->nextNode;
        while (true) {
            if (temp2 == nullptr) {
                delete temp1;
                return;
            }
            delete temp1;
            temp1 = temp2;
            temp2 = temp1->nextNode;
        }
    }
};

#endif