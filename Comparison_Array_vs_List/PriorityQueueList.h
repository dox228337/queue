#ifndef PRIORITYQUEUELIST_H
#define PRIORITYQUEUELIST_H

#include <string>
#include <iostream>

// Вузол двозв'язного списку
struct ListNode
{
    std::string data;   // Значення елемента
    int priority;       // Пріоритет
    ListNode* prev;     // Вказівник на попередній вузол
    ListNode* next;     // Вказівник на наступний вузол

    ListNode(const std::string& d, int p)
    {
        data = d;
        priority = p;
        prev = nullptr;
        next = nullptr;
    }
};

// Клас черги з пріоритетом на базі двозв'язного списку для порівняння
class PriorityQueueList
{
private:
    ListNode* head;     // Вказівник на перший елемент
    ListNode* tail;     // Вказівник на останній елемент
    int size;           // Поточна кількість елементів

public:
    PriorityQueueList();
    ~PriorityQueueList();

    PriorityQueueList(const PriorityQueueList& other);
    PriorityQueueList& operator=(const PriorityQueueList& other);

    // Додавання елемента
    void enqueue(const std::string& data, int priority);

    // Вилучення елемента з найвищим пріоритетом
    std::string dequeue();

    // Перегляд першого елемента
    std::string peek() const;

    // Перевірка на порожнечу
    bool isEmpty() const;

    // Отримання розміру
    int getSize() const;

    // Очищення черги
    void clear();
};

#endif // PRIORITYQUEUELIST_H
