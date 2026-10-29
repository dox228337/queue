#include "PriorityQueueList.h"

// Конструктор
PriorityQueueList::PriorityQueueList()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

// Деструктор
PriorityQueueList::~PriorityQueueList()
{
    clear();
}

// Конструктор копіювання
PriorityQueueList::PriorityQueueList(const PriorityQueueList& other)
{
    head = nullptr;
    tail = nullptr;
    size = 0;

    ListNode* current = other.head;
    while (current != nullptr)
    {
        enqueue(current->data, current->priority);
        current = current->next;
    }
}

// Оператор присвоєння
PriorityQueueList& PriorityQueueList::operator=(const PriorityQueueList& other)
{
    if (this != &other)
    {
        clear();

        ListNode* current = other.head;
        while (current != nullptr)
        {
            enqueue(current->data, current->priority);
            current = current->next;
        }
    }
    return *this;
}

// Додавання елемента за спаданням пріоритету
void PriorityQueueList::enqueue(const std::string& data, int priority)
{
    ListNode* newNode = new ListNode(data, priority);

    // Якщо черга порожня
    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
        size++;
        return;
    }

    // Якщо новий пріоритет вищий за голову списку
    if (priority > head->priority)
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        size++;
        return;
    }

    // Якщо новий пріоритет менший або рівний за хвіст (FIFO для однакових)
    if (priority <= tail->priority)
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        size++;
        return;
    }

    // Пошук позиції всередині списку
    ListNode* current = head->next;
    while (current != nullptr && current->priority >= priority)
    {
        current = current->next;
    }

    // Вставка перед current
    newNode->next = current;
    newNode->prev = current->prev;
    current->prev->next = newNode;
    current->prev = newNode;

    size++;
}

// Вилучення елемента з найвищим пріоритетом (O(1))
std::string PriorityQueueList::dequeue()
{
    if (isEmpty())
    {
        return "";
    }

    ListNode* temp = head;
    std::string result = temp->data;

    head = head->next;
    if (head != nullptr)
    {
        head->prev = nullptr;
    }
    else
    {
        tail = nullptr;
    }

    delete temp;
    size--;
    return result;
}

// Перегляд значення першого елемента
std::string PriorityQueueList::peek() const
{
    if (isEmpty())
    {
        return "";
    }
    return head->data;
}

// Перевірка на порожнечу
bool PriorityQueueList::isEmpty() const
{
    return head == nullptr;
}

// Кількість елементів
int PriorityQueueList::getSize() const
{
    return size;
}

// Очищення всієї черги
void PriorityQueueList::clear()
{
    ListNode* current = head;
    while (current != nullptr)
    {
        ListNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}
