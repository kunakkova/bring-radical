#include <iostream>
#include <cmath>
#include <utility>
#include <vector>

// Определение ANSI цветов для вывода в консоль
#define RESET   "\033[0m"
#define RED     "\033[31m" 
#define YELLOW   "\033[93m"
#define PINK    "\033[95m"

// Функция f(x) = x^5 + x + a
inline double f(double x, double a) {
    return std::pow(x, 5) + x + a;
}

// Производная функции f(x): f'(x) = 5x^4 + 1
inline double df(double x) {
    return 5 * std::pow(x, 4) + 1;
}

// Функция для нахождения интервала, содержащего корень
inline std::pair<double, double> find_interval(double a) {
    if (a >= 0) {
        // Для положительных a ищем отрицательную границу
        double left = -2;
        // Удваиваем left пока f(left) не станет отрицательным
        while (f(left, a) >= 0) {
            left *= 2;
        }
        return {left, 0};  // Возвращаем интервал (left, 0)
    } else {
        // Для отрицательных a ищем положительную границу
        double right = 1;
        // Удваиваем right пока f(right) не станет положительным
        while (f(right, a) <= 0) {
            right *= 2;
        }
        return {0, right};  // Возвращаем интервал (0, right)
    }
}

// Метод бисекции для нахождения корня
inline double bisection(double a, double left, double right, double epsilon) {
    int iter = 0;  // Счетчик итераций
    // Продолжаем, пока интервал больше epsilon и не превышено максимальное число итераций
    while (right - left > epsilon && iter < 1000) {
        double mid = (left + right) / 2;  // Середина интервала
        double f_mid = f(mid, a);        // Значение функции в середине
        std::cout << "Бисекция, итерация " << iter << ": mid = " << mid << ", f(mid) = " << f_mid << std::endl;
        
        if (f_mid == 0.0) {
            return mid;  // Нашли точный корень
        }
        // Выбираем левую или правую половину интервала
        if (f_mid * f(left, a) < 0) {
            right = mid;  // Корень в левой половине
        } else {
            left = mid;   // Корень в правой половине
        }
        iter++;
    }
    // Возвращаем середину конечного интервала
    double root = (left + right) / 2;
    std::cout << "Метод бисекции: корень = " << root << ", f(root) = " << f(root, a) << std::endl;
    return root;
}

// Метод Ньютона для нахождения корня
inline double newton(double a, double x0, double epsilon) {
    double x = x0;       // Начальное приближение
    double delta = 1.0;  // Разница между итерациями
    int iter = 0;        // Счетчик итераций
    
    // Продолжаем, пока разница больше epsilon и не превышено максимальное число итераций
    while (std::abs(delta) > epsilon && iter < 1000) {
        double fx = f(x, a);   // Значение функции
        double dfx = df(x);     // Значение производной
        
        // Проверка на слишком малую производную
        if (std::abs(dfx) < 1e-12) {
            std::cerr << RED << "Производная близка к нулю!" << RESET << std::endl;
            break;
        }
        
        delta = fx / dfx;  // Вычисляем поправку
        x -= delta;        // Обновляем приближение
        std::cout << "Ньютон, итерация " << iter << ": x = " << x << ", f(x) = " << f(x, a) << std::endl;
        iter++;
    }
    std::cout << "Метод Ньютона: корень = " << x << ", f(root) = " << f(x, a) << std::endl;
    return x;
}

// Функция для запуска тестов
void run_tests() {
    std::cout << PINK << "=== Запуск тестов ===" << RESET << std::endl;
    const double eps = 1e-10;  // Точность вычислений
    
    // Структура для тестовых случаев
    struct Test { double a; };
    
    // Вектор тестовых значений параметра a
    std::vector<Test> tests = {
        {2.0}, {-2.0}, {1e-6}, {-1e-6}, {8e-11}, {-8e-11}, {10.0}, {-10.0}, {1000.0}, {-1000.0}
    };
    
    // Проход по всем тестовым случаям
    for (auto t : tests) {
        // Находим интервал, содержащий корень
        auto [left, right] = find_interval(t.a);
        // Выбираем начальное приближение для метода Ньютона
        double x0 = (std::abs(t.a) < 1e-5) ? -t.a : (left + right) / 2;
        
        std::cout << PINK << "a = " << t.a << RESET << std::endl;
        std::cout << PINK << "---Бисекция---" << RESET << std::endl;
        double root_b = bisection(t.a, left, right, eps);  // Метод бисекции
        
        std::cout << PINK << "---Ньютон---" << RESET << std::endl;
        double root_n = newton(t.a, x0, eps);  // Метод Ньютона
        
        // Вывод результатов для сравнения
        std::cout << YELLOW << "Результаты для сравнения: Ньютон: " << root_n << " Бисекции: " << root_b << RESET << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }
    std::cout << PINK << "=== Тестирование завершено ===" << RESET << std::endl;
}

int main() {
    run_tests();  // Запуск тестов
    return 0;
}
