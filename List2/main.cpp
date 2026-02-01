#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
//#define BASE_CHECK

#define tab "\t"
#define delimeter "\n------------------------------"

//Global scope - глобальное пространство имен
class List
{
    class Element //Объявлен в пространстве имен класса 'List'
    {
        int Data;
        Element* pNext;
        Element* pPrev;
    public:
        Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
        {
            cout << "EConstructor:\t" << this << endl;
        }
        ~Element()
        {
            cout << "EDestructor:\t" << this << endl;
        }
        friend class List;
    }*Head, * Tail;
    size_t size;
public:
    class Iterator
    {
        Element* Temp;
    public:
        Iterator(Element* Temp = nullptr) :Temp(Temp) {}
        ~Iterator() {}
        Iterator& operator++()//Prefix increment
        {
            Temp = Temp->pNext;
            return *this;
        }
        Iterator operator++(int)//Postfix increment
        {
            Iterator old = *this;
            Temp = Temp->pNext;
            return old;
        }
        bool operator==(const Iterator& other)const
        {
            return this->Temp == other.Temp;
        }
        bool operator!=(const Iterator& other)const
        {
            return this->Temp != other.Temp;
        }
        int operator*()const
        {
            return Temp->Data;
        }
        int& operator*()
        {
            return Temp->Data;
        }
    };

    class ReverseIterator
    {
        Element* Temp;
    public:
        ReverseIterator(Element* Temp = nullptr) :Temp(Temp) {}
        ~ReverseIterator() {}
        ReverseIterator& operator++()//Prefix increment
        {
            Temp = Temp->pPrev;
            return *this;
        }
        ReverseIterator operator++(int)//Postfix increment
        {
            ReverseIterator old = *this;
            Temp = Temp->pPrev;
            return old;
        }
        bool operator==(const ReverseIterator& other)const
        {
            return this->Temp == other.Temp;
        }
        bool operator!=(const ReverseIterator& other)const
        {
            return this->Temp != other.Temp;
        }
        int operator*()const
        {
            return Temp->Data;
        }
        int& operator*()
        {
            return Temp->Data;
        }
    };

    Iterator begin()
    {
        return Head;
    }
    Iterator end()
    {
        return nullptr;
    }

    ReverseIterator rbegin()
    {
        return Tail;
    }
    ReverseIterator rend()
    {
        return nullptr;
    }

    List()
    {
        Head = Tail = nullptr;
        size = 0;
        cout << "LConstructor:\t" << this << endl;
    }
    List(const std::initializer_list<int>& il) :List()
    {
        for (int const* it = il.begin(); it != il.end(); it++)
        {
            push_back(*it);
        }
    }
    ~List()
    {
        while (Head)pop_front();
        cout << "LDestructor:\t" << this << endl;
    }

    void push_front(int Data)
    {
        if (Head == nullptr && Tail == nullptr)
            Head = Tail = new Element(Data);
        else
            Head = Head->pPrev = new Element(Data, Head, nullptr);
        size++;
    }

    void Insert(int Data, size_t Index)
    {
        if (Index > size) return;
        if (Index == 0) return push_front(Data);
        if (Index == size) return push_back(Data);

        Element* Temp;
        if (Index < size / 2)
        {
            Temp = Head;
            for (size_t i = 0; i < Index; i++) Temp = Temp->pNext;
        }
        else
        {
            Temp = Tail;
            for (size_t i = 0; i < size - Index - 1; i++) Temp = Temp->pPrev;
        }
        Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
        size++;
    }

    void Erase(size_t Index)
    {
        if (Index >= size) return;
        if (Index == 0) return pop_front();
        if (Index == size - 1) return pop_back();

        Element* Temp;
        if (Index < size / 2)
        {
            Temp = Head;
            for (size_t i = 0; i < Index; i++) Temp = Temp->pNext;
        }
        else
        {
            Temp = Tail;
            for (size_t i = 0; i < size - Index - 1; i++) Temp = Temp->pPrev;
        }

        Temp->pPrev->pNext = Temp->pNext;
        Temp->pNext->pPrev = Temp->pPrev;
        delete Temp;
        size--;
    }

    void push_back(int Data)
    {
        if (Head == nullptr && Tail == nullptr)
            Head = Tail = new Element(Data);
        else
            Tail = Tail->pNext = new Element(Data, nullptr, Tail);
        size++;
    }

    void pop_front()
    {
        if (Head == nullptr && Tail == nullptr) return;
        if (Head == Tail)
        {
            delete Head;
            Head = Tail = nullptr;
        }
        else
        {
            Head = Head->pNext;
            delete Head->pPrev;
            Head->pPrev = nullptr;
        }
        size--;
    }

    void pop_back()
    {
        if (Head == nullptr && Tail == nullptr) return;
        if (Head == Tail)
        {
            delete Tail;
            Head = Tail = nullptr;
        }
        else
        {
            Tail = Tail->pPrev;
            delete Tail->pNext;
            Tail->pNext = nullptr;
        }
        size--;
    }

    void print()const
    {
        cout << delimeter << endl;
        for (Element* Temp = Head; Temp; Temp = Temp->pNext)
            cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
        cout << "Количество элементов списка: " << size << endl;
        cout << delimeter << endl;
    }

    void reverse_print()const
    {
        cout << delimeter << endl;
        for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
            cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
        cout << "Количество элементов списка: " << size << endl;
        cout << delimeter << endl;
    }
};

void main()
{
    setlocale(LC_ALL, "");
#ifdef BASE_CHECK
    int n;
    cout << "Введите количество элементов списка: "; cin >> n;
    List list;
    for (int i = 0; i < n; i++)
    {
        list.push_front(rand() % 100);
    }

    list.print();
    list.reverse_print();

    
    int erase_index;
    cout << "Введите индекс удаляемого элемента: "; cin >> erase_index;
    list.Erase(erase_index);
    list.print();
    list.reverse_print();

    int index;
    int value;
    cout << "Введите индекс добавляемого элемента: "; cin >> index;
    cout << "Введите значение добавляемого элемента: "; cin >> value;
    list.Insert(value, index);
    list.print();
    list.reverse_print();
#endif // BASE_CHECK

    List list = { 3, 5, 8, 13, 21 };
    for (List::Iterator it = list.begin(); it != list.end(); it++)
        cout << *it << tab;
    cout << endl;
    for (List::ReverseIterator it = list.rbegin(); it != list.rend(); it++)
        cout << *it << tab;
    cout << endl;
    int value1;
    cout << "Введите значение элемента: "; cin >> value1;
    int a;
    cout << "Введите индекс куда вставить элемент: "; cin >> a;
    list.Insert(value1, a);
    for (int i : list) cout << i << tab; cout << endl;
    int d;
    cout << "Введите индекс элемента чтобы удалить его: "; cin >> d;
    list.Erase(d);
    for (int i : list) cout << i << tab; cout << endl;
}