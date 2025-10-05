#include <iostream>
#include <stdexcept>

using namespace std;

struct Node {
    string value;
    Node* next;
    Node* previous;

    Node(string v, Node* n = nullptr, Node* p = nullptr)
        : value(v), next(n), previous(p) {}
};

struct DL_list {
    Node* head;
    Node* tail;
    int size;

    DL_list() : head(nullptr), tail(nullptr), size(0) {}

    void clear() {
        Node* current = head;
        while(current != nullptr)
        {
            Node* tmp = current;
            current = current->next;
            delete tmp;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    ~DL_list() {
        clear();
    }
};

void addHead(DL_list& list, string value) {
    Node* newNode = new Node(value, list.head, nullptr);

    if(list.head != nullptr)
    {
        list.head->previous = newNode;
    }
    else 
    {
        list.tail = newNode;
    }

    list.head = newNode;
    list.size++;
}

void addTail(DL_list& list, string value) {
    Node* newNode = new Node(value, nullptr, list.tail);

    if(list.tail != nullptr)
    {
        list.tail->next = newNode;
    }
    else
    {
        list.head = newNode;
    }

    list.tail = newNode;
    list.size++;
}

Node* getNodeByIndex(const DL_list& list, int index) {
    if(index < 0 || index >= list.size) {
        throw out_of_range("Index out of range");
    }
    Node* current = list.head;
    for(int i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}

void addAfter(DL_list& list, int index, string value) {
    if(index < 0 || index >= list.size) {
        cerr << "Error: index out of range in addAfter\n";
        return;
    }

    Node* current = getNodeByIndex(list, index);
    Node* newNode = new Node(value, current->next, current);

    if(current->next != nullptr) {
        current->next->previous = newNode;
    }
    else {
        list.tail = newNode;
    }

    current->next = newNode;
    list.size++;
}

void addBefore(DL_list& list, int index, string value) {
    if(index < 0 || index >= list.size) {
        cerr << "Error: index out of range in addBefore\n";
        return;
    }

    Node* current = getNodeByIndex(list, index);
    Node* newNode = new Node(value, current, current->previous);

    if(current->previous != nullptr) {
        current->previous->next = newNode;
    }
    else {
        list.head = newNode;
    }

    current->previous = newNode;
    list.size++;
}

void removeByValue(DL_list& list, string value) {
    Node* current = list.head;

    while(current != nullptr && current->value != value) {
        current = current->next;
    }

    if(current == nullptr) {
        cerr << "Value not found\n";
        return;
    }

    if(current->previous != nullptr) {
        current->previous->next = current->next;
    }
    else {
        list.head = current->next;
    }

    if(current->next != nullptr) {
        current->next->previous = current->previous;
    }
    else {
        list.tail = current->previous;
    }

    delete current;
    list.size--;
}

int searchByValue(const DL_list& list, string value) {
    Node* current = list.head;
    int index = 0;
    while(current != nullptr) {
        if(current->value == value) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1; // не найдено
}

void print(const DL_list& list) {
    cout << "[";
    Node* current = list.head;
    while(current != nullptr) {
        cout << current->value;
        if(current->next) cout << " <-> ";
        current = current->next;
    }
    cout << "]\n";
}

int main() {
    DL_list list;

    addHead(list, "one");       // [one]
    addTail(list, "two");       // [one <-> two]
    addTail(list, "three");     // [one <-> two <-> three]
    print(list);

    addAfter(list, 1, "2.5");   // после "two"
    print(list);

    addBefore(list, 0, "zero"); // перед "one"
    print(list);

    cout << "Index of 'three': " << searchByValue(list, "three") << endl;

    removeByValue(list, "2.5"); // удалить "2.5"
    print(list);

    removeByValue(list, "zero"); // удалить "zero"
    print(list);

    return 0;
}