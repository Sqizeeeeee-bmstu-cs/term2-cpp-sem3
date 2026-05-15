# Анализ метрик ООП для системы "Цех/Фабрика" (Workshop/Factory System)

## Часть 1. Описание иерархии классов

Система состоит из двух основных иерархий наследования и вспомогательных классов:

### Иерархия 1: Люди (Human Hierarchy)
```
Human (абстрактный)
├── Worker (рабочий)
├── Master (мастер)
└── Accountant (бухгалтер)
```

### Иерархия 2: Машины (Machine Hierarchy)
```
Machine (абстрактный)
├── Lathe (токарный станок)
├── Milling (фрезерный станок)
└── Grinding (шлифовальный станок)
```

### Вспомогательные классы:
- **Factory** — фабрика, управляет цехами и работниками
- **Workshop** — цех, управляет машинами
- **MyContainer<T>** — шаблонный контейнер
- **MyHeapContainer<T>** — специализированный контейнер с буфером и кучей
- **PendingQueue** — очередь отложенных операций
- **IPending** (абстрактный) — интерфейс отложенной операции
- **Pending<Callable, Args...>** — конкретная реализация отложенной операции

---

## Часть 2. Расчёт метрик для каждого класса

### 2.1. Класс Human (Абстрактный базовый класс)

#### Структура:
```cpp
class Human {
private:
    std::string name;      // 1 атрибут
    int age;               // 2 атрибут
    int id;                // 3 атрибут
    
public:
    Human(...)             // конструктор
    virtual ~Human()       // деструктор
    std::string getName()  // 1 метод
    int getAge()          // 2 метод
    int getId()           // 3 метод
    virtual void work()   // 4 метод (чистая виртуальная функция)
};
```

| Метрика | Значение | Пояснение |
|---------|----------|-----------|
| WMC | 5 | 4 метода + конструктор (деструктор не считается, так как он не имеет логики) |
| DIT | 0 | Корневой класс иерархии, без родителей |
| NOC | 3 | Три непосредственных наследника: Worker, Master, Accountant |
| CBO | 1 | Forward declaration Machine (не влияет на связность) |
| RFC | 5 | 5 методов могут быть вызваны на объекте Human |
| LCOM | 0.67 | Методы используют разные поля: getName(name), getAge(age), getId(id) — низкая связность методов |
| Атрибуты (private) | 3 | name, age, id |

---

### 2.2. Класс Worker

#### Структура:
```cpp
class Worker : public Human {
private:
    Machine* currentMachine;  // 1 атрибут
    int experience;           // 2 атрибут
    
public:
    Worker(...)                       // конструктор
    void work() override;             // 1 переопределённый метод
    void assignMachine(Machine*)      // 2 метод
    Machine* getCurrentMachine()      // 3 метод
    int getExperience()              // 4 метод
};
```

| Метрика | Значение | Пояснение |
|---------|----------|-----------|
| WMC | 5 | 4 метода (includeOverride) + конструктор |
| DIT | 1 | Наследуется от Human (Human → Worker) |
| NOC | 0 | Нет наследников |
| CBO | 2 | Machine (использует), Human (базовый класс) |
| RFC | 9 | 4 своих метода + 5 унаследованных от Human |
| LCOM | 0.5 | assignMachine(currentMachine), getCurrentMachine(currentMachine), getExperience(experience) — методы используют разные поля |
| Атрибуты (private) | 2 | currentMachine, experience |

---

### 2.3. Класс Master

#### Структура:
```cpp
class Master : public Human {
private:
    std::vector<Worker*> team;  // 1 атрибут
    
public:
    Master(...)              // конструктор
    void work() override;    // 1 переопределённый метод
    void addWorker(Worker*)  // 2 метод
    void removeWorker(int)   // 3 метод
    const std::vector<Worker*>& getTeam()  // 4 метод
};
```

| Метрика | Значение | Пояснение |
|---------|----------|-----------|
| WMC | 5 | 4 методa (include Override) + конструктор |
| DIT | 1 | Наследуется от Human |
| NOC | 0 | Нет наследников |
| CBO | 2 | Worker (использует), Human (базовый класс) |
| RFC | 9 | 4 своих метода + 5 унаследованных от Human |
| LCOM | 1.0 | Все методы работают с одним полем (team) — идеальная связность |
| Атрибуты (private) | 1 | team (vector<Worker*>) |

---

### 2.4. Класс Accountant

#### Структура:
```cpp
class Accountant : public Human {
private:
    std::string department;  // 1 атрибут
    
public:
    Accountant(...)          // конструктор
    void work() override;    // 1 переопределённый метод
    std::string getDepartment()  // 2 метод
};
```

| Метрика | Значение | Пояснение |
|---------|----------|-----------|
| WMC | 3 | 2 метода (include Override) + конструктор |
| DIT | 1 | Наследуется от Human |
| NOC | 0 | Нет наследников |
| CBO | 1 | Human (базовый класс) |
| RFC | 7 | 2 своих метода + 5 унаследованных от Human |
| LCOM | 1.0 | Один метод работает с одним полем — идеальная связность |
| Атрибуты (private) | 1 | department |

---

### 2.5. Класс Machine (Абстрактный базовый класс)

#### Структура:
```cpp
class Machine {
private:
    std::string model;       // 1 атрибут
    int power;               // 2 атрибут
    bool isWorking;          // 3 атрибут
    
public:
    Machine(...)             // конструктор
    virtual ~Machine()       // деструктор
    std::string getModel()   // 1 метод
    int getPower()          // 2 метод
    bool getIsWorking()     // 3 метод
    void start()            // 4 метод
    void stop()             // 5 метод
    virtual void process() = 0;           // 6 чистая виртуальная функция
    virtual std::string getType() = 0;    // 7 чистая виртуальная функция
};
```

| Метрика | Значение | Пояснение |
|---------|----------|-----------|
| WMC | 7 | 6 методов + конструктор |
| DIT | 0 | Корневой класс иерархии |
| NOC | 3 | Три наследника: Lathe, Milling, Grinding |
| CBO | 1 | Workshop (использует через указатель) |
| RFC | 7 | 7 методов |
| LCOM | 0.5 | getModel, getPower, getIsWorking используют разные поля; start() и stop() используют isWorking |
| Атрибуты (private) | 3 | model, power, isWorking |

---

### 2.6. Класс Lathe

#### Структура:
```cpp
class Lathe : public Machine {
private:
    double maxDiameter;  // 1 атрибут
    
public:
    Lathe(...)                        // конструктор
    void process() override;          // 1 переопределённый метод
    std::string getType() override;   // 2 переопределённый метод
    double getMaxDiameter()          // 3 метод
};
```

| Метрика | Значение | Пояснение |
|---------|----------|-----------|
| WMC | 4 | 3 метода (2 переопределения + 1 свой) + конструктор |
| DIT | 1 | Наследуется от Machine |
| NOC | 0 | Нет наследников |
| CBO | 1 | Machine (базовый класс) |
| RFC | 10 | 3 своих метода + 7 унаследованных от Machine |
| LCOM | 1.0 | getMaxDiameter() работает с maxDiameter — идеальная связность |
| Атрибуты (private) | 1 | maxDiameter |

---

### 2.7. Класс Milling

#### Структура:
```cpp
class Milling : public Machine {
private:
    int spindleSpeed;  // 1 атрибут
    
public:
    Milling(...)                      // конструктор
    void process() override;          // 1 переопределённый метод
    std::string getType() override;   // 2 переопределённый метод
    int getSpindleSpeed()            // 3 метод
};
```

| Метрика | Значение | Пояснение |
|---------|----------|-----------|
| WMC | 4 | 3 метода (2 переопределения + 1 свой) + конструктор |
| DIT | 1 | Наследуется от Machine |
| NOC | 0 | Нет наследников |
| CBO | 1 | Machine (базовый класс) |
| RFC | 10 | 3 своих метода + 7 унаследованных от Machine |
| LCOM | 1.0 | getSpindleSpeed() работает с spindleSpeed — идеальная связность |
| Атрибуты (private) | 1 | spindleSpeed |

---

### 2.8. Класс Grinding

#### Структура:
```cpp
class Grinding : public Machine {
private:
    double precision;  // 1 атрибут
    
public:
    Grinding(...)                     // конструктор
    void process() override;          // 1 переопределённый метод
    std::string getType() override;   // 2 переопределённый метод
    double getPrecision()            // 3 метод
};
```

| Метрика | Значение | Пояснение |
|---------|----------|-----------|
| WMC | 4 | 3 метода (2 переопределения + 1 свой) + конструктор |
| DIT | 1 | Наследуется от Machine |
| NOC | 0 | Нет наследников |
| CBO | 1 | Machine (базовый класс) |
| RFC | 10 | 3 своих метода + 7 унаследованных от Machine |
| LCOM | 1.0 | getPrecision() работает с precision — идеальная связность |
| Атрибуты (private) | 1 | precision |

---

### 2.9. Класс Factory

#### Структура:
```cpp
class Factory {
private:
    std::string name;                           // 1 атрибут
    std::vector<std::unique_ptr<Workshop>> workshops;  // 2 атрибут
    std::vector<Human*> workers;                // 3 атрибут
    
public:
    Factory(...)                                    // конструктор
    std::string getName()                          // 1 метод
    void addWorkshop(const std::string&)           // 2 метод
    Workshop* getWorkshop(const std::string&)      // 3 метод
    const std::vector<...>& getWorkshops()        // 4 метод
    void hireWorker(Human*)                        // 5 метод
    void fireWorker(int)                           // 6 метод
    const std::vector<Human*>& getWorkers()        // 7 метод
    void showInfo()                                // 8 метод
};
```

| Метрика | Значение | Пояснение |
|---------|----------|-----------|
| WMC | 9 | 8 методов + конструктор |
| DIT | 0 | Нет наследования |
| NOC | 0 | Нет наследников |
| CBO | 3 | Workshop, Human, std::vector (используются) |
| RFC | 9 | 9 методов |
| LCOM | 0.33 | getName/showInfo → name; addWorkshop/getWorkshop/getWorkshops → workshops; hireWorker/fireWorker/getWorkers → workers; каждая группа использует свои поля |
| Атрибуты (private) | 3 | name, workshops, workers |

---

### 2.10. Класс Workshop

#### Структура:
```cpp
class Workshop {
private:
    std::string name;                    // 1 атрибут
    std::vector<std::unique_ptr<Machine>> machines;  // 2 атрибут
    
public:
    Workshop(...)                        // конструктор
    ~Workshop()                          // деструктор
    std::string getName()                // 1 метод
    void addMachine(Machine*)            // 2 метод
    const std::vector<...>& getMachines()  // 3 метод
    void showMachines()                  // 4 метод
};
```

| Метрика | Значение | Пояснение |
|---------|----------|-----------|
| WMC | 5 | 4 метода + конструктор |
| DIT | 0 | Нет наследования |
| NOC | 0 | Нет наследников |
| CBO | 2 | Machine, std::vector (используются) |
| RFC | 5 | 5 методов |
| LCOM | 0.5 | getName → name; addMachine/getMachines/showMachines → machines; методы используют разные поля |
| Атрибуты (private) | 2 | name, machines |

---

### 2.11. Класс IPending (Абстрактный интерфейс)

#### Структура:
```cpp
class IPending {
public:
    virtual void run() = 0;           // 1 чистая виртуальная функция
    virtual ~IPending() = default;    // виртуальный деструктор
};
```

| Метрика | Значение | Пояснение |
|---------|----------|-----------|
| WMC | 1 | 1 чистая виртуальная функция |
| DIT | 0 | Корневой класс |
| NOC | 1 | Pending<Callable, Args...> |
| CBO | 0 | Нет зависимостей |
| RFC | 1 | 1 метод |
| LCOM | 0 | Нет атрибутов |
| Атрибуты (private) | 0 | Нет |

---

### 2.12. Класс Pending<Callable, Args...> (Шаблонный класс)

#### Структура:
```cpp
template<typename Callable, typename... Args>
class Pending : public IPending {
private:
    Callable _callable;           // 1 атрибут
    std::tuple<Args...> _args;    // 2 атрибут
    
public:
    Pending(Callable, Args...)    // конструктор
    void run() override;          // 1 переопределённый метод
};
```

| Метрика | Значение | Пояснение |
|---------|----------|-----------|
| WMC | 2 | 1 переопределённый метод + конструктор |
| DIT | 1 | Наследуется от IPending |
| NOC | 0 | Нет наследников (это шаблонный класс) |
| CBO | 1 | IPending (базовый класс) |
| RFC | 2 | 1 свой метод + 1 унаследованный от IPending |
| LCOM | 0 | Оба атрибута используются в методе run() через std::apply |
| Атрибуты (private) | 2 | _callable, _args |

---

### 2.13. Класс PendingQueue

#### Структура:
```cpp
class PendingQueue : public std::queue<std::unique_ptr<IPending>> {
public:
    ~PendingQueue()                               // деструктор
    template<typename Callable, typename... ArgTypes>
    void enqueue(Callable, ArgTypes...)          // 1 шаблонный метод
    void run_one()                               // 2 метод
    void run_all()                               // 3 метод
};
```

| Метрика | Значение | Пояснение |
|---------|----------|-----------|
| WMC | 3 | 2 неTemplateметода + 1 шаблонный + деструктор |
| DIT | 1 | Наследуется от std::queue |
| NOC | 0 | Нет наследников |
| CBO | 2 | IPending, std::queue (используются) |
| RFC | 3 | 3 методa |
| LCOM | 0 | Все методы работают с очередью |
| Атрибуты (private) | 0 | Наследуются из std::queue |

---

### 2.14. Класс MyContainer<T> (Шаблонный контейнер)

#### Структура:
```cpp
template <typename T>
class MyContainer {
private:
    T* data;              // 1 атрибут
    size_t size;          // 2 атрибут
    size_t capacity;      // 3 атрибут
    void resize(...)      // приватный метод
    
public:
    MyContainer()                     // конструктор
    ~MyContainer()                    // деструктор
    size_t getSize()                  // 1 метод
    size_t getCapacity()              // 2 метод
    void push_back(const T&)          // 3 метод
    void pop_back()                   // 4 метод
    T& operator[](size_t)             // 5 метод
    const T& operator[](size_t)       // 6 метод
    // Iterator class...
    Iterator begin()                  // 7 метод
    Iterator end()                    // 8 метод
};
```

| Метрика | Значение | Пояснение |
|---------|----------|-----------|
| WMC | 10 | 9 публичных методов (include операторы) + конструктор + приватный resize |
| DIT | 0 | Нет наследования |
| NOC | 0 | Нет наследников |
| CBO | 1 | Iterator (встроенный класс) |
| RFC | 10 | 10 методов |
| LCOM | 0.33 | getSize/getCapacity используют size/capacity; push_back/pop_back/operator[] используют все три поля |
| Атрибуты (private) | 3 | data, size, capacity |

---

### 2.15. Класс MyHeapContainer<T> (Специализированный контейнер)

#### Структура:
```cpp
template <typename T>
class MyHeapContainer {
private:
    T buffer[BUFFER_SIZE];      // 1 атрибут
    size_t buffer_count;        // 2 атрибут
    std::vector<T> heap;        // 3 атрибут
    size_t total_size;          // 4 атрибут
    void flushBufferToHeap()    // приватный метод
    T& getElementAt(...)        // приватный метод
    const T& getElementAt(...) // приватный метод
    
public:
    MyHeapContainer()                 // конструктор
    ~MyHeapContainer()                // деструктор
    size_t getSize()                  // 1 метод
    size_t getCapacity()              // 2 метод
    void push_back(const T&)          // 3 метод
    void pop_back()                   // 4 метод
    T& operator[](size_t)             // 5 метод
    const T& operator[](size_t)       // 6 метод
    // Iterator class...
    Iterator begin()                  // 7 метод
    Iterator end()                    // 8 метод
};
```

| Метрика | Значение | Пояснение |
|---------|----------|-----------|
| WMC | 12 | 8 публичных методов + 3 приватных + конструктор |
| DIT | 0 | Нет наследования |
| NOC | 0 | Нет наследников |
| CBO | 2 | Iterator, std::vector (используются) |
| RFC | 8 | 8 публичных методов |
| LCOM | 0.2 | Все методы работают с разными наборами полей; высокая сложность |
| Атрибуты (private) | 4 | buffer, buffer_count, heap, total_size |

---

## Часть 3. Расчёт системных метрик MOOD (Абреу)

Общие данные по системе (исключая шаблонные специализации):
- Общее количество классов (TC) = 13
  - Иерархия Human: Human, Worker, Master, Accountant (4)
  - Иерархия Machine: Machine, Lathe, Milling, Grinding (4)
  - Остальные: Factory, Workshop, IPending, Pending, PendingQueue (5)
  - Исключены контейнеры и утилиты: MyContainer, MyHeapContainer

Актуальное количество классов для анализа:
- **Бизнес-логика**: Human, Worker, Master, Accountant, Machine, Lathe, Milling, Grinding, Factory, Workshop = 10 классов

### 3.1. MIF (Method Inheritance Factor) — Фактор наследования методов

Рассчитаем для каждого класса отношение числа унаследованных методов к общему числу методов:

| Класс | Унаследованные методы | Всего методов | Отношение |
|-------|----------------------|---------------|-----------|
| Human | 0 | 5 | 0.00 |
| Worker | 5 | 9 | 0.56 |
| Master | 5 | 9 | 0.56 |
| Accountant | 5 | 7 | 0.71 |
| Machine | 0 | 7 | 0.00 |
| Lathe | 7 | 10 | 0.70 |
| Milling | 7 | 10 | 0.70 |
| Grinding | 7 | 10 | 0.70 |
| Factory | 0 | 9 | 0.00 |
| Workshop | 0 | 5 | 0.00 |

**Сумма отношений** = 0.00 + 0.56 + 0.56 + 0.71 + 0.00 + 0.70 + 0.70 + 0.70 + 0.00 + 0.00 = 4.23

**MIF = 4.23 / 10 = 0.423**

**Интерпретация**: 42.3% методов системы являются унаследованными — хорошее использование наследования, что соответствует принципу DRY (Don't Repeat Yourself). Система хорошо использует переиспользование кода через наследование.

---

### 3.2. AHF (Attribute Inheritance Factor) — Фактор наследования атрибутов

В этой системе классы наследуют методы, но не атрибуты (как и в примере Библиотеки), так как все атрибуты определены в конкретных классах.

| Класс | Унаследованные атрибуты | Всего атрибутов | Отношение |
|-------|-------------------------|-----------------|-----------|
| Human | 0 | 3 | 0.00 |
| Worker | 0 | 5 | 0.00 |
| Master | 0 | 4 | 0.00 |
| Accountant | 0 | 4 | 0.00 |
| Machine | 0 | 3 | 0.00 |
| Lathe | 0 | 4 | 0.00 |
| Milling | 0 | 4 | 0.00 |
| Grinding | 0 | 4 | 0.00 |
| Factory | 0 | 3 | 0.00 |
| Workshop | 0 | 2 | 0.00 |

**Сумма отношений** = 0.00

**AHF = 0.00**

**Интерпретация**: Атрибуты не наследуются. Каждый класс определяет свои атрибуты. Это соответствует хорошей практике: базовые классы определяют интерфейс, а конкретные классы определяют свою реализацию.

---

### 3.3. POF (Polymorphism Factor) — Фактор полиморфизма

Рассчитаем для каждого класса число переопределённых методов:

| Класс | Переопределённые методы | Всего методов | Отношение |
|-------|------------------------|---------------|-----------|
| Human | 0 (базовый) | 5 | 0.00 |
| Worker | 1 (work) | 9 | 0.11 |
| Master | 1 (work) | 9 | 0.11 |
| Accountant | 1 (work) | 7 | 0.14 |
| Machine | 0 (базовый) | 7 | 0.00 |
| Lathe | 2 (process, getType) | 10 | 0.20 |
| Milling | 2 (process, getType) | 10 | 0.20 |
| Grinding | 2 (process, getType) | 10 | 0.20 |
| Factory | 0 | 9 | 0.00 |
| Workshop | 0 | 5 | 0.00 |

**Сумма отношений** = 0.00 + 0.11 + 0.11 + 0.14 + 0.00 + 0.20 + 0.20 + 0.20 + 0.00 + 0.00 = 0.96

**POF = 0.96 / 10 = 0.096**

**Интерпретация**: 9.6% методов переопределены. Это низкий показатель полиморфизма. Система использует полиморфизм исключительно для переопределения методов работы (work для Human, process/getType для Machine), что соответствует минималистичному подходу. Это может указывать на хорошее понимание того, где нужен полиморфизм.

---

### 3.4. COF (Coupling Factor) — Фактор сцепления

Определим связи между классами (направление не важно, учитываем уникальные пары):

**Связи:**

1. Human ↔ Worker (наследование)
2. Human ↔ Master (наследование)
3. Human ↔ Accountant (наследование)
4. Machine ↔ Lathe (наследование)
5. Machine ↔ Milling (наследование)
6. Machine ↔ Grinding (наследование)
7. Worker ↔ Machine (Worker использует Machine через указатель)
8. Master ↔ Worker (Master использует Worker)
9. Factory ↔ Workshop (Factory использует Workshop)
10. Factory ↔ Human (Factory использует Human)
11. Workshop ↔ Machine (Workshop использует Machine)

**Количество реальных связей** = 11

**Количество возможных связей** = (10 × 9) / 2 = 45 (число пар)

**COF = 11 / 45 = 0.244**

**Интерпретация**: 24.4% возможных связей реализованы. Это достаточно низкое сцепление, что является хорошим показателем. Классы слабо связаны между собой, что означает хорошую модульность и независимость компонентов. Классы Factory, Workshop и машины образуют общую архитектуру, но слабо связаны с иерархией Human.

---

### 3.5. MHF (Method Hiding Factor) — Фактор сокрытия методов

Рассчитаем для каждого класса число закрытых (private/protected) методов:

| Класс | Закрытые методы | Всего методов | Отношение |
|-------|-----------------|---------------|-----------|
| Human | 0 | 5 | 0.00 |
| Worker | 0 | 9 | 0.00 |
| Master | 0 | 9 | 0.00 |
| Accountant | 0 | 7 | 0.00 |
| Machine | 0 | 7 | 0.00 |
| Lathe | 0 | 10 | 0.00 |
| Milling | 0 | 10 | 0.00 |
| Grinding | 0 | 10 | 0.00 |
| Factory | 0 | 9 | 0.00 |
| Workshop | 0 | 5 | 0.00 |

**Сумма отношений** = 0.00

**MHF = 0.00 / 10 = 0.00**

**Интерпретация**: Все методы публичные. Нет скрытых (private/protected) методов. Это может быть недостатком: классы не скрывают внутреннюю реализацию. Рекомендуется добавить private/protected методы для инкапсуляции.

---

### 3.6. CHF (Attribute Hiding Factor) — Фактор сокрытия атрибутов

Рассчитаем для каждого класса число закрытых (private/protected) атрибутов:

| Класс | Закрытые атрибуты | Всего атрибутов | Отношение |
|-------|-------------------|-----------------|-----------|
| Human | 3 | 3 | 1.00 |
| Worker | 2 | 2 | 1.00 |
| Master | 1 | 1 | 1.00 |
| Accountant | 1 | 1 | 1.00 |
| Machine | 3 | 3 | 1.00 |
| Lathe | 1 | 1 | 1.00 |
| Milling | 1 | 1 | 1.00 |
| Grinding | 1 | 1 | 1.00 |
| Factory | 3 | 3 | 1.00 |
| Workshop | 2 | 2 | 1.00 |

**Сумма отношений** = 10.00

**CHF = 10.00 / 10 = 1.00**

**Интерпретация**: 100% атрибутов закрыты (private). Это отличный показатель инкапсуляции! Все данные защищены, доступ осуществляется только через getter/setter методы. Это соответствует принципу инкапсуляции ООП.

---

## Часть 4. Сводная таблица метрик ООП

### 4.1. Метрики по классам

| Класс | WMC | DIT | NOC | CBO | RFC | LCOM | CHF |
|-------|-----|-----|-----|-----|-----|------|-----|
| Human | 5 | 0 | 3 | 1 | 5 | 0.67 | 1.00 |
| Worker | 5 | 1 | 0 | 2 | 9 | 0.50 | 1.00 |
| Master | 5 | 1 | 0 | 2 | 9 | 1.00 | 1.00 |
| Accountant | 3 | 1 | 0 | 1 | 7 | 1.00 | 1.00 |
| Machine | 7 | 0 | 3 | 1 | 7 | 0.50 | 1.00 |
| Lathe | 4 | 1 | 0 | 1 | 10 | 1.00 | 1.00 |
| Milling | 4 | 1 | 0 | 1 | 10 | 1.00 | 1.00 |
| Grinding | 4 | 1 | 0 | 1 | 10 | 1.00 | 1.00 |
| Factory | 9 | 0 | 0 | 3 | 9 | 0.33 | 1.00 |
| Workshop | 5 | 0 | 0 | 2 | 5 | 0.50 | 1.00 |

### 4.2. Системные метрики MOOD

| Метрика | Значение | Статус | Оценка |
|---------|----------|--------|---------|
| MIF | 0.423 | Хорошо | Наследование используется умеренно, нет дублирования |
| AHF | 0.000 | Хорошо | Интерфейсы и реализация разделены |
| POF | 0.096 | Слабо | Минималистичный полиморфизм, используется только где нужен |
| COF | 0.244 | Отлично | Низкое сцепление, хорошая модульность |
| MHF | 0.000 | Плохо | Все методы публичные, нет инкапсуляции методов |
| CHF | 1.000 | Отлично | Все атрибуты защищены, идеальная инкапсуляция |

---

## Часть 5. Анализ результатов

### 5.1. Сильные стороны

1. **Идеальная инкапсуляция (CHF = 1.00)** — все атрибуты защищены
2. **Низкое сцепление (COF = 0.244)** — классы слабо связаны, хорошая модульность
3. **Хорошее наследование (MIF = 0.423)** — переиспользование кода без дублирования
4. **Правильная иерархия** — две четкие иерархии: Human и Machine
5. **Подходящие размеры методов** — WMC в диапазоне 3-9 (оптимально)

### 5.2. Слабые стороны и потенциальные улучшения

| Метрика | Значение | Проблема | Рекомендация |
|---------|----------|----------|---------------|
| POF | 0.096 | Минимальный полиморфизм | Рассмотреть более активное использование полиморфизма (паттерны Strategy, Visitor) |
| MHF | 0.000 | Все методы публичные | Скрыть вспомогательные методы (например, resize в MyContainer) |
| LCOM | 0.33-0.67 | Низкая связность в некоторых классах | Factory и Human могут быть переработаны |
| Factory WMC | 9 | Относительно сложный | Может быть разбит на несколько классов с четко определенной ответственностью |

### 5.3. Рекомендации по рефакторингу

#### Приоритет 1: Скрытие методов (MHF)

```cpp
// Добавить приватные методы в Machine
class Machine {
private:
    void validateModel(const std::string& model);
    void validatePower(int power);
    // ...
};

// Добавить приватные методы в Factory
class Factory {
private:
    Workshop* findWorkshop(const std::string& name);
    void notifyWorkshopAdded(Workshop* workshop);
    // ...
};
```

#### Приоритет 2: Разделение ответственности (Factory WMC = 9)

```cpp
// Создать отдельный класс для управления работниками
class HumanResources {
private:
    std::vector<Human*> workers;
public:
    void hireWorker(Human* worker);
    void fireWorker(int id);
    const std::vector<Human*>& getWorkers() const;
};

// Переработанный Factory
class Factory {
private:
    std::string name;
    std::vector<std::unique_ptr<Workshop>> workshops;
    HumanResources hr;  // delegation
public:
    // методы делегируют HumanResources
};
```

#### Приоритет 3: Расширение полиморфизма

```cpp
// Добавить интерфейс для различных типов работников
class IWorker : public Human {
public:
    virtual double calculateSalary() const = 0;
    virtual int getProductivityIndex() const = 0;
};

// Реализовать для Worker и Master
class Worker : public IWorker { /* ... */ };
class Master : public IWorker { /* ... */ };
```

---

## Часть 6. Выводы и оценка качества архитектуры

### Общая оценка: **ХОРОШО** (с потенциалом для улучшения)

**Архитектура системы Workshop/Factory характеризуется:**

1. **Четкая структура** — две отдельные иерархии (Human и Machine) с четкой ответственностью
2. **Хорошая инкапсуляция** — все атрибуты защищены
3. **Низкое сцепление** — классы слабо зависят друг от друга
4. **Умеренное использование наследования** — нет излишнего дублирования
5. **Простые классы** — WMC находится в приемлемом диапазоне

### Итоговые рекомендации:

✅ **Оставить как есть:**
- Иерархии классов
- Инкапсуляцию атрибутов
- Связь между компонентами

⚠️ **Улучшить в следующих итерациях:**
- Добавить private/protected методы для лучшей инкапсуляции
- Рассмотреть разделение Factory на несколько классов
- Расширить использование полиморфизма для большей гибкости

🎯 **Система готова для:**
- Дальнейшей разработки
- Расширения новыми машинами и типами работников
- Добавления новых функций

---

## Метрики сложности для основных компонентов

### WMC по группам:
- **Иерархия Human**: 5 (Human) + 5 (Worker) + 5 (Master) + 3 (Accountant) = 18
- **Иерархия Machine**: 7 (Machine) + 4 (Lathe) + 4 (Milling) + 4 (Grinding) = 19
- **Управление**: 9 (Factory) + 5 (Workshop) = 14
- **ИТОГО**: 51 (средний WMC на класс: 5.1)

### DIT статистика:
- DIT = 0: 4 класса (корневые)
- DIT = 1: 6 классов (листья иерархии)
- Максимум DIT: 1 (отличный результат, < 5)

### COF анализ:
- Связи через наследование: 6
- Связи через использование: 5
- Слабо связанная система - хорошо для масштабируемости

