#include "PriorityQueueArray.h"

// Конструктор
PriorityQueueArray::PriorityQueueArray(int initialCapacity)
{
    if (initialCapacity <= 0)
    {
        initialCapacity = 10;
    }
    capacity = initialCapacity;
    size = 0;
    arr = new ArrayItem[capacity];
}

// Деструктор
PriorityQueueArray::~PriorityQueueArray()
{
    delete[] arr;
    arr = nullptr;
    size = 0;
    capacity = 0;
}

// Конструктор копіювання
PriorityQueueArray::PriorityQueueArray(const PriorityQueueArray& other)
{
    capacity = other.capacity;
    size = other.size;
    arr = new ArrayItem[capacity];

    for (int i = 0; i < size; i++)
    {
        arr[i] = other.arr[i];
    }
}

// Оператор присвоєння
PriorityQueueArray& PriorityQueueArray::operator=(const PriorityQueueArray& other)
{
    if (this != &other)
    {
        delete[] arr;

        capacity = other.capacity;
        size = other.size;
        arr = new ArrayItem[capacity];

        for (int i = 0; i < size; i++)
        {
            arr[i] = other.arr[i];
        }
    }
    return *this;
}

// Автоматичне розширення динамічного масиву
void PriorityQueueArray::resize(int newCapacity)
{
    ArrayItem* newArr = new ArrayItem[newCapacity];

    for (int i = 0; i < size; i++)
    {
        newArr[i] = arr[i];
    }

    delete[] arr;
    arr = newArr;
    capacity = newCapacity;
}

// Додавання елемента з урахуванням пріоритету (чим більше число, тим вищий пріоритет)
void PriorityQueueArray::enqueue(const std::string& data, int priority)
{
    // Якщо масив заповнений, подвоюємо його місткість
    if (size == capacity)
    {
        resize(capacity * 2);
    }

    // Шукаємо позицію для нового елемента
    // Елементи з більшим пріоритетом розміщуються попереду
    // Для однакових пріоритетів новий стає після існуючих (FIFO)
    int pos = 0;
    while (pos < size && arr[pos].priority >= priority)
    {
        pos++;
    }

    // Зсуваємо елементи праворуч від кінця до знайденої позиції
    for (int i = size; i > pos; i--)
    {
        arr[i] = arr[i - 1];
    }

    // Вставляємо новий елемент у знайдену позицію
    arr[pos] = ArrayItem(data, priority);
    size++;
}

// Вилучення елемента з найвищим пріоритетом (з нульового індексу)
std::string PriorityQueueArray::dequeue()
{
    if (isEmpty())
    {
        std::cout << "[Помилка] Черга порожня!\n";
        return "";
    }

    std::string result = arr[0].data;

    // Зсуваємо всі елементи ліворуч на одну позицію
    for (int i = 0; i < size - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    size--;

    return result;
}

// Перегляд значення першого елемента
std::string PriorityQueueArray::peek() const
{
    if (isEmpty())
    {
        std::cout << "[Повідомлення] Черга порожня!\n";
        return "";
    }
    return arr[0].data;
}

// Перегляд пріоритету першого елемента
int PriorityQueueArray::peekPriority() const
{
    if (isEmpty())
    {
        return -1;
    }
    return arr[0].priority;
}

// Перевірка на порожнечу
bool PriorityQueueArray::isEmpty() const
{
    return size == 0;
}

// Отримання поточної кількості елементів
int PriorityQueueArray::getSize() const
{
    return size;
}

// Отримання поточної місткості масиву
int PriorityQueueArray::getCapacity() const
{
    return capacity;
}

// Виведення елементів черги на екран
void PriorityQueueArray::printQueue() const
{
    if (isEmpty())
    {
        std::cout << "Черга на базі масиву порожня.\n";
        return;
    }

    std::cout << "\n================ ЧЕРГА З ПРІОРИТЕТОМ (МАСИВ) ================\n";
    std::cout << "Місткість: " << capacity << " | Кількість елементів: " << size << "\n";
    std::cout << "Індекс\tПріоритет\tДані (значення)\n";
    std::cout << "-------------------------------------------------------------\n";

    for (int i = 0; i < size; i++)
    {
        std::cout << i << "\t"
                  << arr[i].priority << "\t\t"
                  << arr[i].data << "\n";
    }
    std::cout << "=============================================================\n";
}

// Очищення черги
void PriorityQueueArray::clear()
{
    size = 0;
}
