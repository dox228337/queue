#ifndef PRINTJOB_H
#define PRINTJOB_H

#include <string>

// Структура для опису завдання на друк
struct PrintJob
{
    std::string user;       // Ім'я клієнта / користувача
    std::string docName;    // Назва документа
    int priority;           // Пріоритет (чим більше число, тим вищий пріоритет)
    std::string time;       // Час надходження запиту

    // Конструктор за замовчуванням
    PrintJob()
    {
        user = "";
        docName = "";
        priority = 0;
        time = "";
    }

    // Конструктор з параметрами
    PrintJob(const std::string& u, const std::string& doc, int p, const std::string& t)
    {
        user = u;
        docName = doc;
        priority = p;
        time = t;
    }
};

#endif // PRINTJOB_H
