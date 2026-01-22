#include<iostream>
#include<ctime>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"

class Element
{
    int Data; //Значение элемента
    Element* pNext; //Адрес следующего элемента
    static int count;//Объявление статической переменной 
public:
    Iterator begin()
    {
        return Head;
    }
    Iterator end()
    {
        return nullptr;
    }

    Element(int Data, Element* pNext = nullptr)
    {
        this->Data = Data;
        this->pNext = pNext;
        count++;
#ifdef DEBUG
        cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

    }
    ~Element()
    {
        count--;
#ifdef DEBUG
        cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

    }
    friend class Iterator;
    friend class ForwardList;
};
int Element::count = 0;//Инициализация статической переменной

class Iterator
{
    Element* Temp;
public:
    Iterator(Element* Temp = nullptr) :Temp(Temp)
    {
        cout << "ItConstructor:\t" << this << endl;
    }
    ~Iterator()
    {
        cout << "ItDestructor:\t" << this << endl;
    }
    Iterator& operator++()
    {
        Temp = Temp->pNext;
    }

    bool operator==(const Iterator& other)const
    {
        return this->Temp != other.Temp;
    }

    bool operator!=(const Iterator& other)const
    {
        return this->Temp != other.Temp;
    }

    const int& operator*()const
    {
        return Temp->Data;
    }

    int& operator*()
    {
        return Temp->Data;
    }
};

class ForwardList
{
    Element* Head;
    int size;
public:
    ForwardList()
    {
        Head = nullptr;
        size = 0;
        cout << "LConstructor:\t" << this << endl;
    }

    ForwardList(const ForwardList& other)
    {
        Head = nullptr;
        size = 0;
        cout << "LCopyConstructor:\t" << this << endl;

        // Копируем все элементы из другого списка
        Element* temp = other.Head;
        while (temp != nullptr)
        {
            push_back(temp->Data);
            temp = temp->pNext;
        }
    }

    ForwardList(const std::initializer_list<int>& il) :ForwardList()
    {
        //initializer_list - это контейнер
        //контейнер - это обЪект который организует хранение других объектов в памяти
        //у любого контейнера есть методы begin() и end()
        //begin() возвращает итератор на начало конейнера
        //end() возвращает итератор на конец конейнера
        for (int const* it = il.begin(); it != il.end(); it++)
            push_back(*it);
    }

    ~ForwardList()
    {
        while (Head != nullptr)
        {
            Element* temp = Head;
            Head = Head->pNext;
            delete temp;
        }
        cout << "LDestructor:\t" << this << endl;
    }

    ForwardList& operator=(const ForwardList& other)
    {
        cout << "Operator:\t" << this << endl;
        if (this == &other)
            return *this;
        while (Head != nullptr)
        {
            Element* temp = Head;
            Head = Head->pNext;
            delete temp;
        }
        reverse();
        size = 0;
        Element* temp = other.Head;
        while (temp != nullptr)
        {
            push_back(temp->Data);
            temp = temp->pNext;
        }

        return *this;
    }

    void Erase(int index)
    {
        if (index < 0 || index >= size)
        {
            return;
        }

        if (index == 0)
        {
            pop_front();
            return;
        }

        Element* current = Head;
        for (int i = 0; i < index - 1; i++)
        {
            current = current->pNext;
        }

        Element* Delete = current->pNext;

        current->pNext = Delete->pNext;
         
        delete Delete;
        size--;
    }

    // Adding elements: 
    void push_front(int Data)
    {
        //ДОбавляет элемент в начало списка.
        //Data - значение добавляемого элемента.
        //1) Создаем добавляемый элемент
        Element* New = new Element(Data);

        //2) Пристыковываем Новый элемент к началу списка
        New->pNext = Head;

        //3) Смещаем Голову на Новый элемент
        Head = New;

        size++;
    }

    void push_back(int Data)
    {
        if (Head == nullptr)return push_front(Data);
        //1) Создаем новый элемент
        Element* New = new Element(Data);

        //2) Доходим до конца списка
        Element* Temp = Head;
        while (Temp->pNext)
            Temp = Temp->pNext;

        //3) присоединяем новый элемент к концу списка
        Temp->pNext = New;
        size++;
    }

    void pop_front()
    {
        //1) Запоминаем адрес удаляемого элемента
        Element* Erased = Head;//2) Смещаем Голову на следующий элемент 
        Head = Head->pNext;

        //3) Удаляем элемент из памяти
        delete Erased;
        size--;
    }

    void pop_back()
    {
        //1) Доходим до конца списка
        Element* Temp = Head;
        while (Temp->pNext->pNext)Temp = Temp->pNext;

        //2) Удаляем элемент из списка
        delete Temp->pNext;

        //3) Зануляем указатель на следующий элемент
        Temp->pNext = nullptr;
        size--;
    }

    void insert(int Data, int Index)//Вставляет элемент в список по заданному элементу
    {
        if (Index > size)return;
        //1) Создаем добавляемый элемент
        Element* New = new Element(Data);

        //2) Доходим до нужного элемента списка
        Element* Temp = Head;
        for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

        //3) Выполняем вставку элемента
        New->pNext = Temp->pNext;
        Temp->pNext = New;
        size++;
    }

    void reverse()
    {
        ForwardList buffer;
        while (Head)
        {
            buffer.push_front(Head->Data);
            pop_front();

        }
        Head = buffer.Head;
        buffer.Head = nullptr;
    }

    void print()const
    {
        Element* Temp = Head; //Temp - это итератор
        //Итератор - это указатель, при помощи которого можно получить доступ к элементам структуры данных
        while (Temp)
        {
            cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
            Temp = Temp->pNext;
        }
        cout << "Количество элементов списка: " << size << endl;
        cout << "Общее количество элементов: " << Element::count << endl;
    }
};



//#define BASE_CHECK
//#define MULTIPLE_LISTS
//#define NEW_FEATURES
//#define RANGE_BASED_FOR_ARRAY

void main()
{
    setlocale(LC_ALL, "");

#ifdef BASE_CHECK
    int n;
    cout << "Введите размер списка: "; cin >> n;
    clock_t start = clock();
    ForwardList list;
    for (int i = 0; i < n; i++)
    {
        list.push_back(rand() % 100);
    }
    clock_t end = clock();

    //list.print();
    cout << "Список создан, за" << double(end-start)/CLOCKS_PER_SEC << endl;
    system("PAUSE");
    //list.push_back(123);
    //list.print();
    //list.pop_back();

    int index;
    int value;
    cout << "Введите индекс добавляемого элемента: "; cin >> index;
    cout << "Введите значение добавляемого элемента: "; cin >> value;
    list.insert(value, index);
    //list.print();
#endif BASE_CHECK

#ifdef MULTIPLE_LISTS
    ForwardList list1;
    list1.push_back(3);
    list1.push_back(5);
    list1.push_back(8);
    list1.push_back(13);
    list1.push_back(21);
    list1.print();

    ForwardList list2;
    list2.push_back(34);
    list2.push_back(55);
    list2.push_back(89);
    list2.print();
#endif

#ifdef NEW_FEATURES
    ForwardList list_erase;
    list_erase.push_back(10);
    list_erase.push_back(20);
    list_erase.push_back(30);
    list_erase.push_back(40);
    list_erase.push_back(50);
    list_erase.print();
    list_erase.Erase(2);
    list_erase.print();
    list_erase.Erase(0);
    list_erase.print();

    ForwardList list_copy1;
    list_copy1.push_back(100);
    list_copy1.push_back(200);
    list_copy1.push_back(300);
    list_copy1.print();

    ForwardList list_copy2 = list_copy1;
    list_copy2.print();

    ForwardList list_assign1;
    list_assign1.push_back(5);
    list_assign1.push_back(10);

    ForwardList list_assign2;
    list_assign2 = list_assign1;
    list_assign1.print();
    list_assign2.print();
    {
        ForwardList temp_list;
        temp_list.push_back(1);
        temp_list.push_back(2);
    }
#endif NEW_FEATURES

#ifdef RANGE_BASED_FOR_ARRAY
    int arr[] = { 3, 5, 8, 13, 21 };
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        cout << arr[i] << tab;
    }
    cout << endl;
    for (int i : arr)
    {
        cout << i << tab;
    }
    cout << endl;
#endif 

    ForwardList list = { 3,5,8,13,21 };
    list.print();
    for (int : list)
    {
        cout << i << tab;
    }
    cout << endl;
    int a = 2;
}   