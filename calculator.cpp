#include <iostream>
#include <limits>
#include <cmath>
#include <iomanip>
#include <string>


// 1. ИНТЕРФЕЙС ICalculator
// Определяет базовые функции калькулятора, которые должны быть реализованы.

class ICalculator {
public:
    // Виртуальный деструктор нужен для корректного удаления объектов-наследников
    virtual ~ICalculator() = default;
    
    // Метод выполнения математической операции (чисто виртуальный)
    virtual double PerformCalculation(double firstNumber, double secondNumber, char operation) = 0;
    
    // Метод запуска основного цикла приложения (чисто виртуальный)
    virtual void RunApplication() = 0;
};


// 2. АБСТРАКТНЫЙ КЛАСС AbstractCalculatorApp
// Содержит общую логику приложения, наследуется от ICalculator

class AbstractCalculatorApp : public ICalculator {
protected:
    // Поля для хранения операндов и символа операции
    double _firstNumber = 0.0;
    double _secondNumber = 0.0;
    char _operation = ' ';

    // Метод очистки буфера ввода после ошибки
    void ClearInputBuffer() {
        std::cin.clear(); // Сбрасываем флаги ошибки потока
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Удаляем все символы до конца строки
    }

    // Метод вывода результата с фиксированной точностью (2 знака после запятой)
    void PrintResult(double result) {
        int outputPrecision = 2; // Точность вывода чисел

        std::cout << std::fixed << std::setprecision(outputPrecision); // Настройка форматирования
        std::cout << "\n=> РЕЗУЛЬТАТ: " 
                  << _firstNumber << " " << _operation << " " << _secondNumber << " = " 
                  << result << std::endl;
    }

    // Метод отображения главного меню и обработки выбора пользователя
    int DisplayMenu() {
        int menuChoice;
        
        std::cout << "\n=======================================" << std::endl;
        std::cout << "          МЕНЮ КАЛЬКУЛЯТОРА" << std::endl;
        std::cout << "=======================================" << std::endl;
        std::cout << "1. Выполнить новую операцию" << std::endl;
        std::cout << "0. Выйти из программы" << std::endl;
        std::cout << "---------------------------------------" << std::endl;
        std::cout << "Ваш выбор: ";

        // Проверка ввода
        if (!(std::cin >> menuChoice)) {
            std::cout << "Неверный ввод. Пожалуйста, введите число." << std::endl;
            ClearInputBuffer(); // Очистка буфера после ошибки
            return -1; // Возврат к повторному вводу
        }
        
        // Проверка корректности выбора
        if (menuChoice < 0 || menuChoice > 1) {
            std::cout << "Неверный выбор. Пожалуйста, выберите 1 или 0." << std::endl;
            return -1;
        }
        return menuChoice;
    }

public:
    // Реализация основного цикла приложения
    void RunApplication() override {
        std::cout << "Добро пожаловать в ООП-Калькулятор!" << std::endl;
        int currentChoice; 

        do {
            currentChoice = DisplayMenu(); // Показ меню
            
            if (currentChoice == 0) break; // Выход из цикла
            
            // Вызов метода выполнения одной операции (полиморфизм)
            if (currentChoice == 1) RunSingleOperation();

        } while (currentChoice != 0);

        std::cout << "\nПрограмма завершена. Спасибо за использование!" << std::endl;
    }

    // Чисто виртуальный метод: реализация выполнения одной операции
    virtual void RunSingleOperation() = 0; //выполнение одной операции калькулятора (ввод чисел, операция, вычисление и вывод результата)
};


// 3. КОНКРЕТНАЯ РЕАЛИЗАЦИЯ ConsoleCalculator
// Содержит конкретную логику ввода/вывода и вычислений

class ConsoleCalculator : public AbstractCalculatorApp {
public:
    // Реализация метода выполнения математической операции
    double PerformCalculation(double firstNumber, double secondNumber, char operation) override {
        switch (operation) {
            case '+': return firstNumber + secondNumber; // Сложение
            case '-': return firstNumber - secondNumber; // Вычитание
            case '*': return firstNumber * secondNumber; // Умножение
            case '/': // Деление с проверкой на 0
                if (secondNumber != 0) {
                    return firstNumber / secondNumber;
                } else {
                    std::cerr << "!!! Ошибка: Деление на ноль! !!!" << std::endl;
                    return std::numeric_limits<double>::quiet_NaN(); // Возврат NaN
                }
            default: // Ошибка, неподдерживаемая операция
                std::cerr << "!!! Ошибка: Неподдерживаемая операция (" << operation << ") !!!" << std::endl;
                return std::numeric_limits<double>::quiet_NaN();
        }
    }

    // Реализация выполнения одной операции
    void RunSingleOperation() override {
        std::cout << "\n--- Новая операция ---" << std::endl;
        
        // Ввод первого числа
        std::cout << "Введите первое число (A): ";
        if (!(std::cin >> _firstNumber)) { 
            std::cout << "Ошибка ввода числа." << std::endl;
            ClearInputBuffer();
            return;
        }

        // Ввод операции
        std::cout << "Введите операцию (+, -, *, /): ";
        if (!(std::cin >> _operation)) {
            std::cout << "Ошибка ввода операции." << std::endl;
            ClearInputBuffer();
            return;
        }

        // Ввод второго числа
        std::cout << "Введите второе число (B): ";
        if (!(std::cin >> _secondNumber)) {
            std::cout << "Ошибка ввода числа." << std::endl;
            ClearInputBuffer();
            return;
        }

        // Выполнение расчета
        double result = PerformCalculation(_firstNumber, _secondNumber, _operation);

        // Вывод результата, если нет ошибки
        if (!std::isnan(result)) {
            PrintResult(result);
        }
    }
};

// ============================================================
// 4. Основная функция main()
// ============================================================
int main() {
    // Создание объекта конкретного калькулятора
    ConsoleCalculator calculatorApp;

    // Запуск приложения
    calculatorApp.RunApplication();

    return 0;
}
    