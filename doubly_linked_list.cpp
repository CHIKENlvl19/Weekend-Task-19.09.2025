#include <iostream>

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

    DL_list() : head(nullptr), tail(nullptr) {}
};

void addHead() {

}

void addTail() {

}

void addAfter() {

}

void addBefore() {

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