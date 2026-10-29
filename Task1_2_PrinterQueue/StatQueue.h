#ifndef STATQUEUE_H
#define STATQUEUE_H

#include <string>
#include <iostream>

// Запис для збереження елемента статистики
struct StatRecord
{
    std::string user;       // Користувач
    std::string time;       // Час події
    std::string docName;    // Назва документа
    int priority;           // Пріоритет

    StatRecord()
    {
        user = "";
        time = "";
        docName = "";
        priority = 0;
    }

    StatRecord(const std::string& u, const std::string& t, const std::string& doc = "", int p = 0)
    {
        user = u;
        time = t;
        docName = doc;
        priority = p;
    }
};

// Вузол черги статистики
struct StatNode
{
    StatRecord data;
    StatNode* next;

    StatNode(const StatRecord& record)
    {
        data = record;
        next = nullptr;
    }
};

// Простий клас черги (FIFO) для збереження хронологічної статистики
class StatQueue
{
private:
    StatNode* head;     // Початок черги статистики
    StatNode* tail;     // Кінець черги статистики
    int size;           // Кількість записів

public:
    StatQueue();
    ~StatQueue();

    StatQueue(const StatQueue& other);
    StatQueue& operator=(const StatQueue& other);

    // Додавання нового запису в кінець черги
    void enqueue(const StatRecord& record);

    // Вилучення запису з початку черги
    StatRecord dequeue();

    // Перевірка на порожнечу
    bool isEmpty() const;

    // Отримання кількості записів
    int getSize() const;

    // Виведення списку статистики на екран із заголовком
    void print(const std::string& title) const;

    // Очищення статистики
    void clear();
};

#endif // STATQUEUE_H
