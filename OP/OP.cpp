#include <iostream>
using namespace std;


//структура данных в элементе
struct People
{
    int Number;
    string Surname;
    string Name;
    string Partonimyc;
};
//структура элемента
struct Elem
{
    People data;
    Elem* next, * prev;
};


class List
{
    // Голова, хвост
    Elem* Head, * Tail;
    // Количество элементов
    int Count;

public:

    // Конструктор
    List();
    // Конструктор копирования
    List(const List&);
    // Деструктор
    ~List();

    // Получить количество
    int GetCount();
    // Получить элемент списка
    Elem* GetElem(int);

    // Удалить весь список
    void DelAll();
    // Удаление элемента, если параметр не указывается,
    // то функция его запрашивает
    void Del(int pos = 0);
    // Вставка элемента, если параметр не указывается,
    // то функция его запрашивает
    void Insert(int pos = 0);

    // Добавление в конец списка
    void AddTail(People n);

    // Добавление в начало списка
    void AddHead(People n);

    // Печать списка
    void Print();
    // Печать определенного элемента
    void Print(int pos);
};

List::List()
{
    // Изначально список пуст
    Head = Tail = NULL;
    Count = 0;
}

List::List(const List& L)
{
    Head = Tail = NULL;
    Count = 0;

    // Голова списка, из которого копируем
    Elem* temp = L.Head;
    // Пока не конец списка
    while (temp != 0)
    {
        // Передираем данные
        AddTail(temp->data);
        temp = temp->next;
    }
}

List::~List()
{
    // Удаляем все элементы
    DelAll();
}

void List::AddHead(People n)
{
    // новый элемент
    Elem* temp = new Elem;

    // Предыдущего нет
    temp->prev = 0;
    // Заполняем данные
    temp->data = n;
    // Следующий - бывшая голова
    temp->next = Head;

    // Если элементы есть?
    if (Head != 0)
        Head->prev = temp;

    // Если элемент первый, то он одновременно и голова и хвост
    if (Count == 0)
        Head = Tail = temp;
    else
        // иначе новый элемент - головной
        Head = temp;

    Count++;
}

void List::AddTail(People n)
{
    // Создаем новый элемент
    Elem* temp = new Elem;
    // Следующего нет
    temp->next = 0;
    // Заполняем данные
    temp->data = n;
    // Предыдущий - бывший хвост
    temp->prev = Tail;

    // Если элементы есть?
    if (Tail != 0)
        Tail->next = temp;

    // Если элемент первый, то он одновременно и голова и хвост
    if (Count == 0)
        Head = Tail = temp;
    else
        // иначе новый элемент - хвостовой
        Tail = temp;

    Count++;
}

void List::Insert(int pos)
{
    // если параметр отсутствует или равен 0, то запрашиваем его
    if (pos == 0)
    {
        cout << "Input position: ";
        cin >> pos;
    }

    // Позиция от 1 до Count?
    if (pos < 1 || pos > Count + 1)
    {
        // Неверная позиция
        cout << "Incorrect position !!!\n";
        return;
    }

    // Если вставка в конец списка
    if (pos == Count + 1)
    {
        // Вставляемые данные
        People form;
        cout << "Input new number: ";
        cin >> form.Number;
        cout << "Input new Surname: ";
        cin >> form.Surname;
        cout << "Input new Name: ";
        cin >> form.Name;
        cout << "Input new Partonimyc: ";
        cin >> form.Partonimyc;
        // Добавление в конец списка
        AddTail(form);
        return;
    }
    else if (pos == 1)
    {
        // Вставляемые данные
        People form;
        cout << "Input new number: ";
        cin >> form.Number;
        cout << "Input new Surname: ";
        cin >> form.Surname;
        cout << "Input new Name: ";
        cin >> form.Name;
        cout << "Input new Partonimyc: ";
        cin >> form.Partonimyc;
        // Добавление в начало списка
        AddHead(form);
        return;
    }

    // Счетчик
    int i = 1;

    // Отсчитываем от головы n - 1 элементов
    Elem* Ins = Head;

    while (i < pos)
    {
        // Доходим до элемента, 
        // перед которым вставляемся
        Ins = Ins->next;
        i++;
    }

    // Доходим до элемента, 
    // который предшествует
    Elem* PrevIns = Ins->prev;

    // Создаем новый элемент
    Elem* temp = new Elem;

    // Вводим данные
    People form;
    cout << "Input new number: ";
    cin >> form.Number;
    cout << "Input new Surname: ";
    cin >> form.Surname;
    cout << "Input new Name: ";
    cin >> form.Name;
    cout << "Input new Partonimyc: ";
    cin >> form.Partonimyc;
    temp->data = form;

    // настройка связей
    if (PrevIns != 0 && Count != 1)
        PrevIns->next = temp;

    temp->next = Ins;
    temp->prev = PrevIns;
    Ins->prev = temp;

    Count++;
}

void List::Del(int pos)
{
    // если параметр отсутствует или равен 0, то запрашиваем его
    if (pos == 0)
    {
        cout << "Input position: ";
        cin >> pos;
    }
    // Позиция от 1 до Count?
    if (pos < 1 || pos > Count)
    {
        // Неверная позиция
        cout << "Incorrect position !!!\n";
        return;
    }

    // Счетчик
    int i = 1;

    Elem* Del = Head;

    while (i < pos)
    {
        // Доходим до элемента, 
        // который удаляется
        Del = Del->next;
        i++;
    }

    // Доходим до элемента, 
    // который предшествует удаляемому
    Elem* PrevDel = Del->prev;
    // Доходим до элемента, который следует за удаляемым
    Elem* AfterDel = Del->next;

    // Если удаляем не голову
    if (PrevDel != 0 && Count != 1)
        PrevDel->next = AfterDel;
    // Если удаляем не хвост
    if (AfterDel != 0 && Count != 1)
        AfterDel->prev = PrevDel;

    // Удаляются крайние?
    if (pos == 1)
        Head = AfterDel;
    if (pos == Count)
        Tail = PrevDel;

    // Удаление элемента
    delete Del;

    Count--;
}

void List::Print(int pos)
{
    // Позиция от 1 до Count?
    if (pos < 1 || pos > Count)
    {
        // Неверная позиция
        cout << "Incorrect position !!!\n";
        return;
    }

    Elem* temp;

    // Определяем с какой стороны 
    // быстрее двигаться
    if (pos <= Count / 2)
    {
        // Отсчет с головы
        temp = Head;
        int i = 1;

        while (i < pos)
        {
            // Двигаемся до нужного элемента
            temp = temp->next;
            i++;
        }
    }
    else
    {
        // Отсчет с хвоста
        temp = Tail;
        int i = 1;

        while (i <= Count - pos)
        {
            // Двигаемся до нужного элемента
            temp = temp->prev;
            i++;
        }
    }
    // Вывод элемента
    cout << pos << " element: ";
    cout << temp->data.Number << ", ";
    cout << temp->data.Surname << ", ";
    cout << temp->data.Name << ", ";
    cout << temp->data.Partonimyc << ", " << endl;
}

void List::Print()
{
    // Если в списке присутствуют элементы, то пробегаем по нему
    // и печатаем элементы, начиная с головного
    if (Count != 0)
    {
        Elem* temp = Head;
        while (temp!= 0)
        {
            cout << temp->data.Number << ", ";
            cout << temp->data.Surname << ", ";
            cout << temp->data.Name << ", ";
            cout << temp->data.Partonimyc;
            temp = temp->next;
            cout << "\n";
        }
    }
}

void List::DelAll()
{
    // Пока остаются элементы, удаляем по одному с головы
    while (Count != 0)
        Del(1);
}

int List::GetCount()
{
    return Count;
}

Elem* List::GetElem(int pos)
{
    Elem* temp = Head;

    // Позиция от 1 до Count?
    if (pos < 1 || pos > Count)
    {
        // Неверная позиция
        cout << "Incorrect position !!!\n";
        return 0;
    }

    int i = 1;
    // Ищем нужный нам элемент
    while (i < pos && temp != 0)
    {
        temp = temp->next;
        i++;
    }

    if (temp == 0)
        return 0;
    else
        return temp;
}

// Тестовый пример
void main()
{
    setlocale(LC_ALL, "rus");
    List L;
    People form;
    form.Number = 123;
    form.Surname = "Efimova";
    form.Name = "Marina";
    form.Partonimyc = "Mikhailovna";
    L.AddHead(form);
    form.Number = 1234;
    form.Surname = "Uba";
    form.Name = "Maria";
    form.Partonimyc = "Victorovna";
    L.AddTail(form);
    // Распечатка списка
    cout << "List L:\n";
    L.Print();

    cout << endl;

    // Вставка элемента в список
    L.Insert();
    // Распечатка списка
    cout << "List L:\n";
    L.Print();

    // Распечатка 2-го и 8-го элементов списка
    L.Print(1);
}
