#ifndef PRIORITYQUEUELIST_H
#define PRIORITYQUEUELIST_H

#include "PrintJob.h"
#include <iostream>

// Вузол двозв'язного списку
struct ListNode
{
    PrintJob data;      // Дані завдання
    ListNode* prev;     // Вказівник на попередній вузол
    ListNode* next;     // Вказівник на наступний вузол

    ListNode(const PrintJob& job)
    {
        data = job;
        prev = nullptr;
        next = nullptr;
    }
};

// Завдання 1: Клас "Черга з пріоритетом" на базі двозв'язного списку
class PriorityQueueList
{
private:
    ListNode* head;     // Вказівник на перший елемент (найвищий пріоритет)
    ListNode* tail;     // Вказівник на останній елемент
    int size;           // Поточна кількість елементів у черзі

public:
    PriorityQueueList();
    ~PriorityQueueList();

    // Конструктор копіювання та оператор присвоєння (правило трьох)
    PriorityQueueList(const PriorityQueueList& other);
    PriorityQueueList& operator=(const PriorityQueueList& other);

    // Додавання завдання з урахуванням пріоритету
    void enqueue(const PrintJob& job);

    // Вилучення завдання з найвищим пріоритетом
    PrintJob dequeue();

    // Перегляд першого завдання без вилучення
    PrintJob peek() const;

    // Перевірка, чи порожня черга
    bool isEmpty() const;

    // Отримання поточної кількості елементів
    int getSize() const;

    // Виведення вмісту черги на екран
    void printQueue() const;

    // Очищення всієї черги
    void clear();
};

#endif // PRIORITYQUEUELIST_H
