#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

#include "PriorityQueueArray.h"

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

    PriorityQueueArray queue;
    int choice = -1;

    std::cout << "=======================================================\n";
    std::cout << "  ЗАВДАННЯ 3: ЧЕРГА З ПРІОРИТЕТОМ НА БАЗІ МАСИВУ\n";
    std::cout << "=======================================================\n";

    while (choice != 0)
    {
        std::cout << "\n----------------------- МЕНЮ ---------------------------\n";
        std::cout << "1. Додати елемент у чергу (enqueue)\n";
        std::cout << "2. Вилучити елемент з найвищим пріоритетом (dequeue)\n";
        std::cout << "3. Переглянути елемент з найвищим пріоритетом (peek)\n";
        std::cout << "4. Вивести весь вміст черги\n";
        std::cout << "5. Очистити чергу (clear)\n";
        std::cout << "6. Завантажити демонстраційний набір даних\n";
        std::cout << "0. Завершити роботу програми\n";
        std::cout << "--------------------------------------------------------\n";

        choice = readInt("Ваш вибір: ");

        switch (choice)
        {
            case 1:
            {
                std::cout << "\n--- Додавання елемента ---\n";
                std::string data = readLine("Введіть значення (назву) елемента: ");
                int priority = readInt("Введіть пріоритет (число, більше = вищий пріоритет): ");

                queue.enqueue(data, priority);
                std::cout << "[Успішно] Елемент '" << data << "' з пріоритетом " << priority << " додано до черги.\n";
                break;
            }
            case 2:
            {
                if (queue.isEmpty())
                {
                    std::cout << "[Повідомлення] Черга порожня! Немає елементів для вилучення.\n";
                }
                else
                {
                    std::string item = queue.dequeue();
                    std::cout << "[Вилучено] Елемент: '" << item << "'\n";
                }
                break;
            }
            case 3:
            {
                if (queue.isEmpty())
                {
                    std::cout << "[Повідомлення] Черга порожня!\n";
                }
                else
                {
                    std::cout << "[Перший у черзі] Значення: '" << queue.peek()
                              << "', Пріоритет: " << queue.peekPriority() << "\n";
                }
                break;
            }
            case 4:
            {
                queue.printQueue();
                break;
            }
            case 5:
            {
                queue.clear();
                std::cout << "[Успішно] Чергу повністю очищено.\n";
                break;
            }
            case 6:
            {
                std::cout << "\n[Демо] Додаємо 5 елементів з різними пріоритетами...\n";
                queue.enqueue("Завдання_Фонове", 1);
                queue.enqueue("Завдання_Термінове", 10);
                queue.enqueue("Завдання_Середнє", 5);
                queue.enqueue("Завдання_Важливе", 8);
                queue.enqueue("Завдання_Низьке", 2);
                std::cout << "[Демо] Тестові дані успішно додано! Перегляньте чергу через пункт 4.\n";
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
