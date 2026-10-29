#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

#include "Printer.h"

// Допоміжна функція очищення буфера введення
void clearInput()
{
    int c;
    while ((c = std::cin.get()) != '\n' && c != EOF)
    {
        // пропускаємо залишок рядка
    }
}

// Допоміжна функція для читання цілого числа
int readInt(const std::string& prompt)
{
    int value;
    while (true)
    {
        std::cout << prompt;
        if (std::cin >> value)
        {
            clearInput();
            return value;
        }
        else
        {
            if (std::cin.eof())
            {
                return 0;
            }
            std::cout << "[Помилка] Введіть коректне ціле число!\n";
            std::cin.clear();
            clearInput();
        }
    }
}

// Допоміжна функція для читання рядка
std::string readLine(const std::string& prompt)
{
    std::cout << prompt;
    std::string text = "";
    while (std::getline(std::cin, text))
    {
        if (!text.empty() && text.back() == '\r')
        {
            text.pop_back();
        }
        if (!text.empty())
        {
            return text;
        }
    }
    return text;
}

int main()
{
#ifdef _WIN32
    // Налаштування UTF-8 для коректного виведення кирилиці в консолі Windows
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif

    Printer printer;
    int choice = -1;

    std::cout << "=======================================================\n";
    std::cout << "  ЗАВДАННЯ 1 І 2: СИМУЛЯЦІЯ ЧЕРГИ ДРУКУ ПРИНТЕРА\n";
    std::cout << "  (Черга з пріоритетом на базі двозв'язного списку)\n";
    std::cout << "=======================================================\n";

    while (choice != 0)
    {
        std::cout << "\n----------------------- МЕНЮ ---------------------------\n";
        std::cout << "1. Додати новий запит на друк від клієнта\n";
        std::cout << "2. Надрукувати одне завдання (з найвищим пріоритетом)\n";
        std::cout << "3. Надрукувати всі поточні завдання з черги\n";
        std::cout << "4. Переглянути поточну чергу принтера\n";
        std::cout << "5. Переглянути Чергу 1: Статистика запитів (користувач, час)\n";
        std::cout << "6. Переглянути Чергу 2: Статистика друку (користувач, час)\n";
        std::cout << "7. Додати демонстраційний набір клієнтів (автоматично)\n";
        std::cout << "0. Завершити роботу програми\n";
        std::cout << "--------------------------------------------------------\n";

        choice = readInt("Ваш вибір: ");

        switch (choice)
        {
            case 1:
            {
                std::cout << "\n--- Додавання нового запиту на друк ---\n";
                std::string user = readLine("Введіть ім'я клієнта: ");
                std::string doc = readLine("Введіть назву документа: ");
                int priority = readInt("Введіть пріоритет (наприклад, 1-10, де більше = вищий пріоритет): ");

                printer.addRequest(user, doc, priority);
                break;
            }
            case 2:
            {
                printer.printNextJob();
                break;
            }
            case 3:
            {
                printer.printAllJobs();
                break;
            }
            case 4:
            {
                printer.showCurrentQueue();
                break;
            }
            case 5:
            {
                printer.showRequestStats();
                break;
            }
            case 6:
            {
                printer.showPrintStats();
                break;
            }
            case 7:
            {
                std::cout << "\n[Демо] Додаємо попередньо визначених клієнтів з різними пріоритетами...\n";
                printer.addRequest("Олена (Секретар)", "Наказ_№104.pdf", 4);
                printer.addRequest("Іван (Студент)", "Курсова_робота.docx", 1);
                printer.addRequest("Петро (Директор)", "Звіт_річний_терміново.pdf", 10);
                printer.addRequest("Марія (Бухгалтер)", "Зарплатна_відомість.xlsx", 8);
                printer.addRequest("Олексій (Менеджер)", "Презентація.pptx", 5);
                std::cout << "[Демо] Клієнти успішно додані до черги принтера!\n";
                break;
            }
            case 0:
            {
                std::cout << "\nРоботу програми завершено. До побачення!\n";
                break;
            }
            default:
            {
                std::cout << "Невірний вибір! Спробуйте ще раз.\n";
                break;
            }
        }
    }

    return 0;
}
