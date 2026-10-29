#ifndef PRINTER_H
#define PRINTER_H

#include "PriorityQueueList.h"
#include "StatQueue.h"
#include <string>

// Завдання 2: Клас для симуляції черги друку принтера
class Printer
{
private:
    PriorityQueueList printerQueue; // Поточна черга на друк з пріоритетом (Завдання 1)
    StatQueue requestStats;         // Черга 1: Статистика запитів клієнтів (користувач, час)
    StatQueue printStats;           // Черга 2: Статистика виведення на друк (користувач, час)

    // Допоміжний метод для отримання поточного часу у форматі HH:MM:SS
    std::string getCurrentTime() const;

public:
    Printer();
    ~Printer();

    // Додавання запиту клієнта на друк
    void addRequest(const std::string& user, const std::string& docName, int priority);

    // Друк одного наступного завдання (з найвищим пріоритетом)
    void printNextJob();

    // Друк усіх поточних завдань у черзі
    void printAllJobs();

    // Виведення поточної черги очікування на екран
    void showCurrentQueue() const;

    // Виведення Черги 1: Статистика запитів клієнтів (користувач, час)
    void showRequestStats() const;

    // Виведення Черги 2: Статистика виведення на друк (користувач, час)
    void showPrintStats() const;

    // Перевірка, чи є завдання в черзі
    bool hasPendingJobs() const;
};

#endif // PRINTER_H
