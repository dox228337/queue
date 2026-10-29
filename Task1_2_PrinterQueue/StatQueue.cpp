#include "StatQueue.h"

// Конструктор за замовчуванням
StatQueue::StatQueue()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

// Деструктор
StatQueue::~StatQueue()
{
    clear();
}

// Конструктор копіювання
StatQueue::StatQueue(const StatQueue& other)
{
    head = nullptr;
    tail = nullptr;
    size = 0;

    StatNode* current = other.head;
    while (current != nullptr)
    {
        enqueue(current->data);
        current = current->next;
    }
}

// Оператор присвоєння
StatQueue& StatQueue::operator=(const StatQueue& other)
{
    if (this != &other)
    {
        clear();

        StatNode* current = other.head;
        while (current != nullptr)
        {
            enqueue(current->data);
            current = current->next;
        }
    }
    return *this;
}

// Додавання нового запису в кінець черги (FIFO)
void StatQueue::enqueue(const StatRecord& record)
{
    StatNode* newNode = new StatNode(record);

    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }

    size++;
}

// Вилучення запису з початку черги
StatRecord StatQueue::dequeue()
{
    if (isEmpty())
    {
        return StatRecord();
    }

    StatNode* temp = head;
    StatRecord result = temp->data;

    head = head->next;
    if (head == nullptr)
    {
        tail = nullptr;
    }

    delete temp;
    size--;
    return result;
}

// Перевірка на порожнечу
bool StatQueue::isEmpty() const
{
    return head == nullptr;
}

// Отримання кількості елементів
int StatQueue::getSize() const
{
    return size;
}

// Виведення списку статистики на екран
void StatQueue::print(const std::string& title) const
{
    std::cout << "\n================ " << title << " ================\n";
    if (isEmpty())
    {
        std::cout << "Записів немає.\n";
        std::cout << "=========================================================================\n";
        return;
    }

    std::cout << "№\tКористувач\t\tЧас\t\tДокумент\t\tПріоритет\n";
    std::cout << "-------------------------------------------------------------------------\n";

    StatNode* current = head;
    int index = 1;
    while (current != nullptr)
    {
        std::cout << index << "\t"
                  << current->data.user << "\t\t"
                  << current->data.time << "\t"
                  << current->data.docName << "\t\t"
                  << current->data.priority << "\n";
        current = current->next;
        index++;
    }
    std::cout << "=========================================================================\n";
}

// Очищення черги статистики
void StatQueue::clear()
{
    StatNode* current = head;
    while (current != nullptr)
    {
        StatNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}
