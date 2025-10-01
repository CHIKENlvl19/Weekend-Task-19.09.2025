/*Реализовать односвязный список.  
Операции: добавление и удаление элемента (4 способа (до после голова хвост)), 
чтение (разное, несколько способов), 
удаление элемента по значению, поиск элемента по
значению.*/

#include <iostream>
#include <stdexcept>

using namespace std;

struct SL_list;
void addTail(SL_list& list, int value);

struct Node {
    int value;
    Node* next;

    Node(int v, Node* n = nullptr)
        : value(v), next(n) {}
};

struct SL_list {
    Node* head = nullptr;
    int size = 0;

    SL_list() = default;

    SL_list(const SL_list& other) : head(nullptr), size(0) {
        Node* current = other.head;
        while(current != nullptr)
        {
            addTail(*this, current->value);
            current = current->next;
        }
    }

    SL_list& operator=(const SL_list& other) {
        if(this == &other)
        {
            return *this;
        }

        clear();

        Node* current = other.head;
        while(current != nullptr)
        {
            addTail(*this, current->value);
            current = current->next;
        }

        return *this;
    }

    void clear() {
        //clearList(*this); // можно так, но пока рано
        while(head != nullptr)
        {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
        size = 0;
    }

    ~SL_list() { 
        clear();
    }
};

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
    list.size++;
}

void addTail(SL_list& list, int value) {
    Node* newNode = new Node{value};

    if(list.head == nullptr)
    {
        list.head = newNode;
        list.size++;
        return;
    }

    Node* current = list.head;
    while(current->next != nullptr)
    {
        current = current -> next;
    }

    current -> next = newNode;
    list.size++;
}

void addAfter(SL_list& list, int index, int value) {

    if(list.head == nullptr)
    {
        cerr << "Error, list is empty!" << endl;
        return;
    }
    
    try
    {
        Node* current = getNodeByIndex(list, index);
        Node* newNode = new Node(value);
        newNode -> next = current -> next;
        current -> next = newNode;
        list.size++;
    } 
    catch (out_of_range& e)
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
        Node* previous = nullptr;
        int currentIndex = 0;

        while(current != nullptr && currentIndex < index)
        {
            previous = current;
            current = current->next;
            currentIndex++;
        }

        //Node* previous = getNodeByIndex(list, index - 2); // можно еще так

        Node* newNode = new Node{value};
        newNode->next = current;
        previous->next = newNode;
        list.size++;
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
        if(current->next == nullptr)
        {
            cerr << "Error, cannot delete after the last element!";
            return;
        }

        Node* toDelete = current->next;
        current->next = toDelete->next;
        delete toDelete;

        list.size--;
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

    list.size--;
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
        removeHead(list);
    }

    try
    {

        Node* previous = getNodeByIndex(list, index - 2);
        Node* toDelete = previous->next;
        if (toDelete == nullptr) {
            cerr << "Error: no element to delete before index " << index << endl;
            return;
        }

        previous->next = toDelete->next;
        delete toDelete;
        list.size--;
    
    } catch (const out_of_range& e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}

void removeTail(SL_list& list) {

    if(list.head == nullptr)
    {
        return;
    }

    if(list.head -> next == nullptr)
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

    list.size--;
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

int searchByValue(const SL_list& list, int searchKey) {
    
    if(list.head == nullptr)
    {
        throw range_error("Error: list is empty!");
        return -1;
    }

    Node* current = list.head;
    int currentIndex = 0;
    while(current != nullptr)
    {
        if(current->value == searchKey)
        {
            return currentIndex;
        }
        current = current->next;
        currentIndex++;
    }

    return -1;
}

void deleteByValue(SL_list& list, int value) {
    
    if(list.head == nullptr)
    {
        throw logic_error("Erorr: list is empty, nothing to delete!");
        return;
    }

    if(list.head->value == value)
    {
        removeHead(list);
        return;
    }

    Node* current = list.head;
    while(current->next != nullptr && current->next->value != value)
    {
        current = current->next;
    }

    if(current->next != nullptr)
    {
        Node* toDelete = current->next;
        current->next = toDelete->next;
        delete toDelete;
        list.size--;
    }
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

    //list.head = new Node(30);       // [30]
    addHead(list, 10);
    addBefore(list, 0, 10);         // [10, 30] — через addHead
    addBefore(list, 1, 20);         // [10, 20, 30] — перед индексом 1 (перед 30)
    addBefore(list, 2, 25);         // [10, 20, 25, 30] — перед индексом 2 (перед 30)

    print(list); // [10, 20, 25, 30]
    int searchResult = searchByValue(list, 40);
    if(searchResult != -1)
    {
        cout << "Element is present in the list! It's index is " << searchResult << endl;
    }
    else
    {
        cout << "Element is abcent." << endl;
    }

    deleteByValue(list, 10);
    print(list);

    //addBefore(list, 999, 999); // Error: index out of range!

    cout << "Estimated list size is " << list.size << " elements." << endl;

    SL_list list2 = list;
    print(list2);

    SL_list list3;
    list3 = list;
    print(list3);

    // при помощи деструктора список сам очистится при выходе из области видимости

    return 0;
}