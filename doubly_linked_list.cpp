#include <iostream>
#include <stdexcept>

using namespace std;

struct Node {
    int value;
    Node* next;
    Node* previous;

    Node(int v, Node* n = nullptr, Node* p = nullptr)
        : value(v), next(n), previous(p) {}
};

struct DL_list {
    Node* head;
    Node* tail;
    int size;

    DL_list() : head(nullptr), tail(nullptr) {}

    ~DL_list() {
        Node* current = head;
        while(current != nullptr)
        {
            Node* tmp = current;
            current = current->next;
            delete tmp;
        }
    }
};

void addHead(DL_list& list, int value) {

}

void addTail(DL_list& list, int value) {

}

void addAfter(DL_list& list, int value, int index) {

}

void addBefore(DL_list& list, int value, int index) {

}

void print() {

}

void removeByValue() {

}

void searchByValue() {
    
}

int main() {

    return 0;
}