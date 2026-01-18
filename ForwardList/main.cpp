#include<iostream>
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
	Element(int Data, Element* pNext = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};
int Element::count = 0;//Инициализация статической переменной

class ForwardList
{
	Element* Head;
public:
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
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
		Element* Erased = Head;

		//2) Смещаем Голову на следующий элемент 
		Head = Head->pNext;

		//3) Удаляем элемент из памяти
		delete Erased;
		soze--;
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
		for (int i = 0; i < Index-1; i++)Temp = Temp->pNext;
		
		//3) Выполняем вставку элемента
		New->pNext = Temp->pNext;
		Temp->pNext = New;
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
#define MULTIPLE_LISTS

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	//list.push_back(123);
	//list.print();
	//list.pop_back();

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
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

}