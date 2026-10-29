#include "Printer.h"
#include <iostream>
#include <ctime>

// Конструктор
Printer::Printer()
{
}

// Деструктор
Printer::~Printer()
{
}

// Допоміжний метод: отримання поточного системного часу у форматі HH:MM:SS
std::string Printer::getCurrentTime() const
{
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    char buffer[32];
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S", localTime);
    return std::string(buffer);
}

// Додавання запиту клієнта на друк
void Printer::addRequest(const std::string& user, const std::string& docName, int priority)
{
    std::string timeStr = getCurrentTime();

    // 1. Формуємо завдання
    PrintJob job(user, docName, priority, timeStr);

    // 2. Додаємо до черги принтера згідно з його пріоритетом (Завдання 1)
    printerQueue.enqueue(job);

    // 3. Зберігаємо у Черзі 1: Статистика запитів клієнтів (користувач, час)
    StatRecord reqRecord(user, timeStr, docName, priority);
    requestStats.enqueue(reqRecord);

    std::cout << "\n[Запит додано] Клієнт: " << user
              << " | Документ: '" << docName << "'"
              << " | Пріоритет: " << priority
              << " | Час: " << timeStr << "\n";
}

// Друк одного наступного завдання з черги
void Printer::printNextJob()
{
    if (printerQueue.isEmpty())
    {
        std::cout << "\n[Принтер] Черга друку порожня. Немає завдань для обробки.\n";
        return;
    }

    // Отримуємо завдання з найвищим пріоритетом
    PrintJob job = printerQueue.dequeue();
    std::string printTime = getCurrentTime();

    // Зберігаємо у Черзі 2: Статистика виведення на друк (користувач, час)
    StatRecord printRecord(job.user, printTime, job.docName, job.priority);
    printStats.enqueue(printRecord);

    std::cout << "\n[Принтер] НАДРУКОВАНО документ!\n"
              << "  - Клієнт:       " << job.user << "\n"
              << "  - Документ:     " << job.docName << "\n"
              << "  - Пріоритет:    " << job.priority << "\n"
              << "  - Час запиту:   " << job.time << "\n"
              << "  - Час друку:    " << printTime << "\n";
}

// Друк усіх завдань з черги
void Printer::printAllJobs()
{
    if (printerQueue.isEmpty())
    {
        std::cout << "\n[Принтер] Черга друку порожня.\n";
        return;
    }

    std::cout << "\n[Принтер] Починаємо друк усіх документів з черги...\n";
    while (!printerQueue.isEmpty())
    {
        printNextJob();
    }
    std::cout << "[Принтер] Усі документи з черги успішно надруковані!\n";
}

// Відображення поточної черги очікування
void Printer::showCurrentQueue() const
{
    printerQueue.printQueue();
}

// Відображення Черги 1: Статистика запитів клієнтів
void Printer::showRequestStats() const
{
    requestStats.print("Черга 1: Статистика запитів клієнтів (користувач, час)");
}

// Відображення Черги 2: Статистика виведення на друк
void Printer::showPrintStats() const
{
    printStats.print("Черга 2: Статистика виведення на друк (користувач, час)");
}

// Чи є ще документи в черзі
bool Printer::hasPendingJobs() const
{
    return !printerQueue.isEmpty();
}
