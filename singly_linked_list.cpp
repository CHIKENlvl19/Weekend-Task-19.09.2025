/*Реализовать односвязный список.  
Операции: добавление и удаление элемента (4 способа (до после голова хвост)), 
чтение (разное, несколько способов), 
удаление элемента по значению, поиск элемента по
значению.*/

#include <iostream>
#include <stdexcept>

using namespace std;

struct SL_list;
void addTail(SL_list& list, string value);

struct Node {
    string value;
    Node* next;

    Node(string v, Node* n = nullptr)
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

void addHead(SL_list& list, string value) {
    list.head = new Node(value, list.head);
    list.size++;
}

void addTail(SL_list& list, string value) {
    Node* newNode = new Node(value);

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

void addAfter(SL_list& list, int index, string value) {

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

void addBefore(SL_list& list, int index, string value) {

    if(list.head == nullptr)
    {
        cerr << "Error, list is empty!" << endl;
        return;
    }

    if(index < 0)
    {
        cerr << "Error, negative index!" << endl;
        return;
    }

    if(index == 0)
    {
        addHead(list, value);
        return;
    }

    
    Node* current = list.head;
    Node* previous = nullptr;
    int currentIndex = 0;

    while(current != nullptr && currentIndex < index)
    {
        previous = current;
        current = current->next;
        currentIndex++;
    }

    if(currentIndex != index)
    {
        cerr << "Error, index out of range!" << endl;
        return;
    }

    Node* newNode = new Node(value, current);
    previous->next = newNode;
    list.size++;
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
        list.size--;
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

int searchByValue(const SL_list& list, string searchKey) {
    
    if(list.head == nullptr)
    {
        throw range_error("Error: list is empty!");
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

void deleteByValue(SL_list& list, string value) {
    
    if(list.head == nullptr)
    {
        throw logic_error("Erorr: list is empty, nothing to delete!");
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

    cout << "=== ТЕСТ 1: добавление элементов ===" << endl;
    addHead(list, "one");       // [one]
    print(list);
    addTail(list, "two");
    print(list);                // [one -> two]
    addBefore(list, 1, "zero");
    print(list);                // [one -> zero -> two]
    addAfter(list, 1, "three");
    print(list);                // [one -> zero -> three -> two]
    print(list);
    cout << "Размер: " << list.size << endl;

    cout << "\n=== ТЕСТ 2: удаление элементов ===" << endl;
    removeHead(list);           // удаляем "one"
    print(list);
    removeTail(list);           // удаляем "two"
    print(list);
    removeAfter(list, 0);       // удаляем после "zero" (удалится "three")
    print(list);
    cout << "Размер: " << list.size << endl;

    cout << "\n=== ТЕСТ 3: добавление снова ===" << endl;
    addHead(list, "alpha");
    addTail(list, "beta");
    addTail(list, "gamma");
    print(list);
    cout << "Размер: " << list.size << endl;

    cout << "\n=== ТЕСТ 4: поиск и удаление по значению ===" << endl;
    int pos = searchByValue(list, "beta");
    cout << "beta найден на позиции: " << pos << endl;
    deleteByValue(list, "beta");
    print(list);
    deleteByValue(list, "not_found"); // ничего не удалит
    print(list);

    cout << "\n=== ТЕСТ 5: копирование ===" << endl;
    SL_list copy1 = list;   // копирующий конструктор
    cout << "Копия 1: ";
    print(copy1);

    SL_list copy2;
    copy2 = list;           // оператор присваивания
    cout << "Копия 2: ";
    print(copy2);

    cout << "\n=== ТЕСТ 6: очистка ===" << endl;
    list.clear();
    cout << "После очистки: ";
    print(list);
    cout << "Размер: " << list.size << endl;

    return 0;
}
