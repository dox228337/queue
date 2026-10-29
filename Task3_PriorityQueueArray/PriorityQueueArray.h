#ifndef PRIORITYQUEUEARRAY_H
#define PRIORITYQUEUEARRAY_H

#include <string>
#include <iostream>

// Елемент черги з пріоритетом на масиві
struct ArrayItem
{
    std::string data;   // Дані (значення)
    int priority;       // Пріоритет (чим більше число, тим вищий пріоритет)

    ArrayItem()
    {
        data = "";
        priority = 0;
    }

    ArrayItem(const std::string& d, int p)
    {
        data = d;
        priority = p;
    }
};

// Завдання 3: Клас "Черга з пріоритетом" на базі динамічного масиву
class PriorityQueueArray
{
private:
    ArrayItem* arr;     // Вказівник на динамічний масив елементів
    int capacity;       // Максимальна місткість масиву
    int size;           // Поточна кількість елементів у черзі

    // Метод для автоматичного розширення масиву при заповненні
    void resize(int newCapacity);

public:
    PriorityQueueArray(int initialCapacity = 10);
    ~PriorityQueueArray();

    // Конструктор копіювання та оператор присвоєння (правило трьох)
    PriorityQueueArray(const PriorityQueueArray& other);
    PriorityQueueArray& operator=(const PriorityQueueArray& other);

    // Додавання елемента з урахуванням пріоритету
    void enqueue(const std::string& data, int priority);

    // Вилучення елемента з найвищим пріоритетом
    std::string dequeue();

    // Перегляд значення першого елемента
    std::string peek() const;

    // Перегляд пріоритету першого елемента
    int peekPriority() const;

    // Перевірка, чи порожня черга
    bool isEmpty() const;

    // Отримання поточної кількості елементів
    int getSize() const;

    // Отримання поточної місткості масиву
    int getCapacity() const;

    // Виведення вмісту черги
    void printQueue() const;

    // Очищення черги
    void clear();
};

#endif // PRIORITYQUEUEARRAY_H
