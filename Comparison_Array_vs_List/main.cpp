#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#endif

#include "PriorityQueueList.h"
#include "PriorityQueueArray.h"

// Допоміжна структура для попередньо згенерованих даних
struct TestItem
{
    std::string data;
    int priority;
};

// Допоміжна функція очищення буфера введення
void clearInput()
{
    int c;
    while ((c = std::cin.get()) != '\n' && c != EOF)
    {
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

// Функція запуску порівняльного тесту
void runBenchmark(int count)
{
    std::cout << "\n=========================================================================\n";
    std::cout << "  ТЕСТУВАННЯ ПРОДУКТИВНОСТІ НА КІЛЬКОСТІ ЕЛЕМЕНТІВ: " << count << "\n";
    std::cout << "=========================================================================\n";
    std::cout << "Генерація " << count << " тестових елементів з випадковими пріоритетами...\n";

    // Генеруємо один і той самий набір даних для обох черг
    std::vector<TestItem> testData;
    testData.reserve(count);
    for (int i = 0; i < count; i++)
    {
        TestItem item;
        item.data = "doc_" + std::to_string(i);
        item.priority = rand() % 1000 + 1; // випадковий пріоритет від 1 до 1000
        testData.push_back(item);
    }

    std::cout << "Тестові дані згенеровано. Починаємо вимірювання часу...\n\n";

    // -------------------------------------------------------------
    // 1. Тест для двозв'язного списку (PriorityQueueList)
    // -------------------------------------------------------------
    PriorityQueueList listQueue;

    // Вставка (Enqueue)
    auto listStartEnqueue = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++)
    {
        listQueue.enqueue(testData[i].data, testData[i].priority);
    }
    auto listEndEnqueue = std::chrono::high_resolution_clock::now();
    double listEnqueueMs = std::chrono::duration<double, std::milli>(listEndEnqueue - listStartEnqueue).count();

    // Вилучення (Dequeue)
    auto listStartDequeue = std::chrono::high_resolution_clock::now();
    while (!listQueue.isEmpty())
    {
        listQueue.dequeue();
    }
    auto listEndDequeue = std::chrono::high_resolution_clock::now();
    double listDequeueMs = std::chrono::duration<double, std::milli>(listEndDequeue - listStartDequeue).count();

    double listTotalMs = listEnqueueMs + listDequeueMs;

    // -------------------------------------------------------------
    // 2. Тест для динамічного масиву (PriorityQueueArray)
    // -------------------------------------------------------------
    PriorityQueueArray arrayQueue;

    // Вставка (Enqueue)
    auto arrayStartEnqueue = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++)
    {
        arrayQueue.enqueue(testData[i].data, testData[i].priority);
    }
    auto arrayEndEnqueue = std::chrono::high_resolution_clock::now();
    double arrayEnqueueMs = std::chrono::duration<double, std::milli>(arrayEndEnqueue - arrayStartEnqueue).count();

    // Вилучення (Dequeue)
    auto arrayStartDequeue = std::chrono::high_resolution_clock::now();
    while (!arrayQueue.isEmpty())
    {
        arrayQueue.dequeue();
    }
    auto arrayEndDequeue = std::chrono::high_resolution_clock::now();
    double arrayDequeueMs = std::chrono::duration<double, std::milli>(arrayEndDequeue - arrayStartDequeue).count();

    double arrayTotalMs = arrayEnqueueMs + arrayDequeueMs;

    // -------------------------------------------------------------
    // Виведення результатів у вигляді таблиці
    // -------------------------------------------------------------
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "-------------------------------------------------------------------------\n";
    std::cout << "Операція                 | Список (двозв'язний) | Масив (динамічний)  | Різниця / Переможець\n";
    std::cout << "-------------------------------------------------------------------------\n";

    // Enqueue
    std::cout << "Додавання (Enqueue)      | "
              << std::setw(17) << listEnqueueMs << " ms | "
              << std::setw(16) << arrayEnqueueMs << " ms | ";
    if (listEnqueueMs < arrayEnqueueMs)
    {
        std::cout << "Список швидший у " << (arrayEnqueueMs / listEnqueueMs) << "x разів\n";
    }
    else
    {
        std::cout << "Масив швидший у " << (listEnqueueMs / arrayEnqueueMs) << "x разів\n";
    }

    // Dequeue
    std::cout << "Вилучення (Dequeue)      | "
              << std::setw(17) << listDequeueMs << " ms | "
              << std::setw(16) << arrayDequeueMs << " ms | ";
    if (listDequeueMs < arrayDequeueMs)
    {
        std::cout << "Список швидший у " << (arrayDequeueMs / listDequeueMs) << "x разів\n";
    }
    else
    {
        std::cout << "Масив швидший у " << (listDequeueMs / arrayDequeueMs) << "x разів\n";
    }

    // Total
    std::cout << "-------------------------------------------------------------------------\n";
    std::cout << "ЗАГАЛЬНИЙ ЧАС (Total)    | "
              << std::setw(17) << listTotalMs << " ms | "
              << std::setw(16) << arrayTotalMs << " ms | ";
    if (listTotalMs < arrayTotalMs)
    {
        std::cout << "Список швидший у " << (arrayTotalMs / listTotalMs) << "x разів\n";
    }
    else
    {
        std::cout << "Масив швидший у " << (listTotalMs / arrayTotalMs) << "x разів\n";
    }
    std::cout << "-------------------------------------------------------------------------\n";

    // -------------------------------------------------------------
    // Аналітичні висновки для студента та викладача
    // -------------------------------------------------------------
    std::cout << "\n=========================== АНАЛІТИЧНИЙ ВИСНОВОК ===========================\n";
    std::cout << "1. ВИЛУЧЕННЯ (Dequeue):\n";
    std::cout << "   - У двозв'язному списку вилучення першого елемента виконується за O(1),\n";
    std::cout << "     оскільки ми лише переставляємо вказівник head = head->next.\n";
    std::cout << "   - У динамічному масиві вилучення займає O(N), тому що після вилучення\n";
    std::cout << "     arr[0] необхідно зсунути всі N-1 елементів ліворуч.\n";
    std::cout << "   -> Тому у операції Dequeue ДВОЗВ'ЯЗНИЙ СПИСОК колосально швидший за масив!\n\n";

    std::cout << "2. ДОДАВАННЯ (Enqueue):\n";
    std::cout << "   - Обидві структури мають складність O(N) для пошуку позиції вставки за пріоритетом.\n";
    std::cout << "   - Масив виграє за рахунок неперервного розташування в пам'яті (кеш-локальність CPU),\n";
    std::cout << "     але програє на зсуві елементів праворуч.\n";
    std::cout << "   - Список на кожен елемент робить окреме виділення пам'яті (new ListNode),\n";
    std::cout << "     проте сама вставка (перев'язка вказівників) не потребує копіювання даних.\n\n";

    std::cout << "3. ВИТРАТИ ПАМ'ЯТІ:\n";
    std::cout << "   - Двозв'язний список: має додатковий оверхед на 2 вказівники (prev і next),\n";
    std::cout << "     що займає додаткові 16 байт на кожен вузол у 64-бітній системі.\n";
    std::cout << "   - Динамічний масив: компактний у пам'яті, елементи лежать встик,\n";
    std::cout << "     проте може мати надлишково зарезервовану місткість (capacity > size).\n";
    std::cout << "============================================================================\n";
}

int main()
{
#ifdef _WIN32
    // Налаштування UTF-8 для коректного виведення кирилиці в консолі Windows
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif

    srand(12345); // фіксований seed для повторюваності результатів

    int choice = -1;

    std::cout << "=========================================================================\n";
    std::cout << "   ПОРІВНЯННЯ ПРОДУКТИВНОСТІ: ЧЕРГА-СПИСОК VS ЧЕРГА-МАСИВ\n";
    std::cout << "=========================================================================\n";

    while (choice != 0)
    {
        std::cout << "\nОберіть розмір вибірки для тестування:\n";
        std::cout << "1. Швидкий тест       (3 000 елементів)\n";
        std::cout << "2. Стандартний тест   (10 000 елементів)\n";
        std::cout << "3. Великий тест       (20 000 елементів)\n";
        std::cout << "4. Ввести власну кількість елементів\n";
        std::cout << "0. Завершити роботу\n";
        std::cout << "-------------------------------------------------------------------------\n";

        choice = readInt("Ваш вибір: ");

        switch (choice)
        {
            case 1:
            {
                runBenchmark(3000);
                break;
            }
            case 2:
            {
                runBenchmark(10000);
                break;
            }
            case 3:
            {
                runBenchmark(20000);
                break;
            }
            case 4:
            {
                int customN = readInt("Введіть кількість елементів (рекомендовано від 1000 до 30000): ");
                if (customN <= 0)
                {
                    std::cout << "Кількість має бути додатною!\n";
                }
                else
                {
                    runBenchmark(customN);
                }
                break;
            }
            case 0:
            {
                std::cout << "\nРоботу завершено. До побачення!\n";
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
