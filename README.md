# Лабораторна робота: Черги з пріоритетом

Проєкт розбитий на три окремі папки відповідно до завдань:

---

### 1. `Task1_2_PrinterQueue/` (Завдання 1 та 2)
**Тема:** Черга з пріоритетом на базі двозв'язного списку та симуляція черги друку принтера.

Файли:
* `PrintJob.h` — структура завдання друку (користувач, документ, пріоритет, час).
* `PriorityQueueList.h` / `PriorityQueueList.cpp` — клас черги з пріоритетом на базі двозв'язного списку (Завдання 1).
* `StatQueue.h` / `StatQueue.cpp` — черга для збереження хронологічної статистики (FIFO).
* `Printer.h` / `Printer.cpp` — симуляція принтера з двома чергами статистики: запити клієнтів і фактичний друк (Завдання 2).
* `main.cpp` — меню та введення даних для симуляції принтера.

**Компіляція та запуск:**
```bash
cd Task1_2_PrinterQueue
g++ -std=c++11 PriorityQueueList.cpp StatQueue.cpp Printer.cpp main.cpp -o printer_simulation.exe
./printer_simulation.exe
```

---

### 2. `Task3_PriorityQueueArray/` (Завдання 3)
**Тема:** Черга з пріоритетом на базі динамічного масиву.

Файли:
* `PriorityQueueArray.h` / `PriorityQueueArray.cpp` — клас черги з пріоритетом на базі динамічного масиву з авторозширенням місткості (Завдання 3).
* `main.cpp` — меню та введення даних для тестування методів черги на масиві.

**Компіляція та запуск:**
```bash
cd Task3_PriorityQueueArray
g++ -std=c++11 PriorityQueueArray.cpp main.cpp -o array_queue_demo.exe
./array_queue_demo.exe
```

---

### 3. `Comparison_Array_vs_List/` (Порівняння швидкості: Список vs Масив)
**Тема:** Бенчмарк та експериментальне порівняння часу виконання операцій `enqueue` та `dequeue`.

Файли:
* `PriorityQueueList.h` / `PriorityQueueList.cpp` — черга на базі списку.
* `PriorityQueueArray.h` / `PriorityQueueArray.cpp` — черга на базі динамічного масиву.
* `main.cpp` — програма для вимірювання часу (через `std::chrono`), побудови порівняльної таблиці та виведення теоретичних висновків.

**Компіляція та запуск:**
```bash
cd Comparison_Array_vs_List
g++ -std=c++11 PriorityQueueList.cpp PriorityQueueArray.cpp main.cpp -o compare_queues.exe
./compare_queues.exe
```
