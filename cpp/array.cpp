/*Реализовать Массив. Операции: создание, добавление элемента (по индексу и в конец массива), 
получение элемента по индексу, удаление элемента по
индексу, замена элемента по индексу, длина массива, чтение.*/

#include <iostream>
#include <stdexcept>

using namespace std;

struct myArray {
    string* data;
    int size;
    int capacity;

    myArray(int initialCapacity = 4) // конструктор
        : data(nullptr), size(0), capacity(4) 
    {
        if(initialCapacity <= 0)
        {
            initialCapacity = 4;
        }
        data = new string[initialCapacity];
        capacity = initialCapacity;
    }

    myArray(const myArray& other) // копирующий конструктор
        : data(nullptr), size(other.size), capacity(other.capacity)
    {
        for(int i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
    }

    myArray& operator=(const myArray& other) { // копирующий опеатор присваивания
        if(this == &other)
        {
            return *this;
        }

        string* newData = nullptr;
        if(other.capacity > 0)
        {
            newData = new string[other.capacity];
            for(int i = 0; i < other.size; i++)
            {
                newData[i] = other.data[i];
            }

            delete[] data;
            data = newData;
            size = other.size;
            capacity = other.capacity;

            return *this;
        }


    }

    void clean() {
        delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;
    }

    ~myArray() {
        clean();
    }
};

void push_back(myArray& arr, string value) {
    if(arr.size >= arr.capacity)
    {
        int newCapacity = arr.capacity * 2;
        string* newData = new string[newCapacity];

        for(int i = 0; i < arr.size; i++)
        {
            newData[i] = arr.data[i];
        }

        delete[] arr.data;
        arr.data = newData;
        arr.capacity = newCapacity;
    }

    arr.data[arr.size] = value;
    arr.size++;
}

void insert(myArray& arr, int index, string value) {
    if (index < 0 || index > arr.size)
    {
        throw out_of_range("Error: inserting failed due to invalid index.");
    }

    if(arr.size >= arr.capacity) {
        int newCapacity = arr.capacity * 2;
        string* newData = new string[newCapacity];
        
        for(int i = 0; i < arr.size; i++)
        {
            newData[i] = arr.data[i];
        }

        delete[] arr.data;
        arr.data = newData;
        arr.capacity = newCapacity;
    }

    for(int i = arr.size; i > index; --i)
    {
        arr.data[i] = arr.data[i - 1];
    }

    arr.data[index] = value;
    arr.size++;
}

string getElement(const myArray& arr, int index) {
    if(index < 0 || index > arr.size)
    {
        throw out_of_range("Error: getting an element failed due to invalid index.");
    }

    return arr.data[index];
}

void Delete(myArray& arr, int index) {
    if(index < 0 || index > arr.size)
    {
        throw out_of_range("Error: deleting an element failed due to invalid index.");
    }

    for(int i = index; i < arr.size; i++)
    {
        arr.data[i] = arr.data[i + 1];
    }

    arr.size--;
}

void swapElements(myArray& arr, int index, string value) {
    
    if(index < 0 || index > arr.size)
    {
        throw out_of_range("Error: swapping an element failed due to invalid index.");
    }

    arr.data[index] = value;
}

int size(const myArray& arr) {
    return arr.size;
}

void print(const myArray& arr) {
    cout << "[";
    for(int i = 0; i < arr.size; i++)
    {
        cout << arr.data[i];
        if(i < arr.size - 1)
        {
            cout << ", ";
        }
    }

    cout << "]" << endl;
}

int main() {

    try {
        myArray arr;

        push_back(arr, "ten");
        push_back(arr, "20");
        print(arr);

        insert(arr, 1,  "15");
        print(arr);

        cout << "Elemnt [1]: " << getElement(arr, 1) << endl;

        swapElements(arr, 0, "5");
        print(arr);

        Delete(arr, 0);
        print(arr);

        cout << "Massive length: " << size(arr);

    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }

    
    return 0;
}