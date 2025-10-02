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
    list.head->previous = nullptr;
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

void addAfter(DL_list& list, int value, int index) {

}

void addBefore(DL_list& list, int value, int index) {

}

void print(const DL_list& list) {
    cout << "[";
    Node* current = list.head;
    while (current != nullptr) {
        cout << current->value;
        if (current->next) cout << " <-> ";
        current = current->next;
    }
    cout << "]\n";
}

void removeByValue() {

}

void searchByValue() {
    
}

int main() {

    DL_list list;
    addHead(list, "one");
    addTail(list, "two");
    print(list);

    return 0;
}