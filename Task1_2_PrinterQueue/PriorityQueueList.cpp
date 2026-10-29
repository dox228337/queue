#include "PriorityQueueList.h"

// Конструктор за замовчуванням
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
        enqueue(current->data);
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
            enqueue(current->data);
            current = current->next;
        }
    }
    return *this;
}

// Додавання завдання з урахуванням пріоритету (чим більше число, тим вищий пріоритет)
void PriorityQueueList::enqueue(const PrintJob& job)
{
    ListNode* newNode = new ListNode(job);

    // 1. Якщо черга порожня
    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
        size++;
        return;
    }

    // 2. Якщо пріоритет вищий, ніж у поточного першого елемента (вставка на початок)
    if (job.priority > head->data.priority)
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        size++;
        return;
    }

    // 3. Якщо пріоритет менший або рівний останньому елементу (вставка в кінець)
    // Для однакових пріоритетів новий елемент стає позаду (принцип FIFO)
    if (job.priority <= tail->data.priority)
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        size++;
        return;
    }

    // 4. Вставка всередину списку
    ListNode* current = head->next;
    while (current != nullptr && current->data.priority >= job.priority)
    {
        current = current->next;
    }

    // Вставляємо newNode перед current
    newNode->next = current;
    newNode->prev = current->prev;
    current->prev->next = newNode;
    current->prev = newNode;

    size++;
}

// Вилучення завдання з найвищим пріоритетом (з голови списку)
PrintJob PriorityQueueList::dequeue()
{
    if (isEmpty())
    {
        std::cout << "[Помилка] Черга порожня!\n";
        return PrintJob();
    }

    ListNode* temp = head;
    PrintJob result = temp->data;

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

// Перегляд елемента з найвищим пріоритетом
PrintJob PriorityQueueList::peek() const
{
    if (isEmpty())
    {
        std::cout << "[Повідомлення] Черга порожня!\n";
        return PrintJob();
    }
    return head->data;
}

// Перевірка на порожнечу
bool PriorityQueueList::isEmpty() const
{
    return head == nullptr;
}

// Отримання розміру черги
int PriorityQueueList::getSize() const
{
    return size;
}

// Виведення елементів черги
void PriorityQueueList::printQueue() const
{
    if (isEmpty())
    {
        std::cout << "Черга на друк порожня.\n";
        return;
    }

    std::cout << "\n================ ПОТОЧНА ЧЕРГА ПРИНТЕРА ================\n";
    std::cout << "№\tПріоритет\tКористувач\t\tДокумент\t\tЧас запиту\n";
    std::cout << "-------------------------------------------------------------------------\n";

    ListNode* current = head;
    int index = 1;
    while (current != nullptr)
    {
        std::cout << index << "\t"
                  << current->data.priority << "\t\t"
                  << current->data.user << "\t\t"
                  << current->data.docName << "\t\t"
                  << current->data.time << "\n";
        current = current->next;
        index++;
    }
    std::cout << "=========================================================================\n";
}

// Очищення черги та звільнення пам'яті
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
