#include <iostream>
using namespace std;

class Element {
public:
    Element* pPrev;
    int Data;
    Element* pNext;

    Element(int value) {
        this->pPrev = nullptr;
        this->Data = value;
        this->pNext = nullptr;
    }
};

class List {
private:
    Element* Head;
    Element* Tail;

public:
    List() {
        this->Head = nullptr;
        this->Tail = nullptr;
    }

    void Add(int value) {
        Element* newElement = new Element(value);

        if (this->Head == nullptr) {
            this->Head = newElement;
            this->Tail = newElement;
        }
        else {
            newElement->pPrev = this->Tail;
            this->Tail->pNext = newElement;
            this->Tail = newElement;
        }
    }

    void Print() {
        Element* current = this->Head;
        while (current != nullptr) {
            cout << current->Data << " ";
            current = current->pNext;
        }
        cout << endl;
    }
};

int main() {
    List list;
    list.Add(3);
    list.Add(5);
    list.Add(8);
    list.Add(13);
    list.Add(21);
    list.Print();
}