/*Реализовать односвязный список.  
Операции: добавление и удаление элемента (4 способа (до после голова хвост)), 
чтение (разное, несколько способов), 
удаление элемента по значению, поиск элемента по
значению.*/

#include <iostream>
#include <stdexcept>

using namespace std;

struct Node {
    int value;
    Node* next;
};

struct SL_list {
    Node* head = nullptr;
};

/*void AddNode(Node* ptr,  int key) {
    Node* newNode = new Node{key, nullptr};
    newNode -> next = ptr -> next;
    ptr -> next = newNode;
}*/

void createSL_list(SL_list& list, int keybegin) {
    list.head = new Node{keybegin, nullptr};
}

Node* getNodeByIndex(const SL_list& list, int index) {
    
    if(index < 0)
    {
        return nullptr;
    }

    Node* current = list.head;
    int currentIndex = 0;

    while(current != nullptr && currentIndex < index)
    {
        current = current -> next;
        currentIndex++;
    }

    if(current == nullptr)
    {
        throw out_of_range("Error: index out of range!");
    }

    return current;
}

void addHead(SL_list& list, int value) {
    list.head = new Node{value, list.head};
}

void addTail(SL_list& list, int value) {
    Node* newNode = new Node{value};

    if(list.head == nullptr)
    {
        list.head = newNode;
        return;
    }

    Node* current = list.head;
    while(current->next != nullptr)
    {
        current = current -> next;
    }

    current -> next = newNode;
}

void addAfter(SL_list& list, int index, int value) {

    if(list.head == nullptr)
    {
        cout << "Error, list is empty!" << endl;
    }
    
    try
    {
        Node* current = getNodeByIndex(list, index);

        Node* newNode = new Node{value};
        newNode -> next = current -> next;
        current -> next = newNode;

    } catch (out_of_range& e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}

void addBefore(SL_list& list, int index, int value) {

    if(list.head == nullptr)
    {
        cerr << "Error, list is empty!" << endl;
        return;
    }

    if(index == 0)
    {
        addHead(list, value);
        return;
    }

    try
    {
        Node* current = getNodeByIndex(list, index);
        Node* previous = getNodeByIndex(list, index - 1); // можно за один подход, но пока не знаю, как :(
    
        Node* newNode = new Node{value};
        newNode->next = current;
        previous->next = newNode;
    }
    catch(const out_of_range& e)
    {
        cerr << e.what() << endl;
    }
}

void removeAfter(SL_list& list, int index) {
    if(list.head == nullptr)
    {
        cerr << "Error, list is empty!" << endl;
        return;
    }

    try
    {
        Node* current = getNodeByIndex(list, index);
        if(current == nullptr)
        {
            cerr << "Error, cannot delete after the last element!";
            return;
        }

        Node* toDelete = current->next;
        current->next = toDelete->next;
        delete toDelete;

    } catch (const out_of_range& e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}

void removeBefore(SL_list& list, int index) {
    if(list.head == nullptr)
    {
        cerr << "Error, index is out of range!" << endl;
        return;
    }

    if(index == 0)
    {
        cerr << "Error, cannot delete the element before first!" << endl;
        return;
    }

    if(index == 1)
    {
        Node* oldHead = list.head;
        list.head = list.head->next;
        delete oldHead;
    }

    try
    {

        Node* previous = getNodeByIndex(list, index - 2);

        if (previous == nullptr || previous->next == nullptr) {
            cerr << "Error: no element to delete before index " << index << endl;
            return;
        }

        Node* toDelete = previous->next;
        previous->next = toDelete->next;
        delete toDelete;
    
    } catch (const out_of_range& e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}

void removeHead(SL_list& list) {

    if(list.head == nullptr)
    {
        return;
    }

    Node* oldHead = list.head;
    list.head = list.head -> next;
    delete oldHead;
}

void removeTail(SL_list& list) {

    if(list.head == nullptr)
    {
        return;
    }

    if(list.head -> next =nullptr)
    {
        delete list.head;
        list.head = nullptr;
        return;
    }

    Node* current = list.head;
    while(current -> next -> next != nullptr)
    {
        current = current -> next;
    }

    Node* tail = current -> next;
    current -> next = nullptr;
    delete tail;
}

void print(const SL_list& list) {
    
    Node* head = list.head;
    
    cout << "[";
    while(head != nullptr)
    {
        cout << head -> value;
        head = head -> next;
        if(head != nullptr)
        {
            cout << " -> ";
        }
    }
    cout << " -> nullptr]" << endl;
}

void print() {

}

void searchByValue() {
    
}

void deleteByValue() {

}

int main() {

    SL_list list;
    /*createSL_list(list, 10);

    addHead(list, 20);
    addTail(list, 30);
    print(list);

    removeHead(list);
    print(list);*/

    //addBefore(list, 0, 10); // Error: list is empty!

    list.head = new Node{30};       // [30]
    addBefore(list, 0, 10);         // [10, 30] — через addHead
    addBefore(list, 1, 20);         // [10, 20, 30] — перед индексом 1 (перед 30)
    addBefore(list, 2, 25);         // [10, 20, 25, 30] — перед индексом 2 (перед 30)

    print(list); // [10, 20, 25, 30]

    addBefore(list, 999, 999); // Error: index out of range!

    return 0;
}