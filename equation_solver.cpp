#include <iostream>
#include <cmath>
#include <utility>

// Функция f(x) = x^5 + x + a
double f(double x, double a) {
    return std::pow(x, 5) + x + a;
}

// Производная f'(x) = 5x^4 + 1
double df(double x) {
    return 5 * std::pow(x, 4) + 1;
}

// Нахождение интервала [left, right], где f(left) * f(right) < 0
std::pair<double, double> find_interval(double a) {
    if (a >= 0) {
        double left = -2; // Начинаем с -2, чтобы избежать проблем при больших a
        while (f(left, a) >= 0) {
            left *= 2;
        }
        return {left, 0};
    } else {
        double right = 1;
        while (f(right, a) <= 0) {
            right *= 2;
        }
        return {0, right};
    }
}

// Метод бисекции
void bisection(double a, double left, double right, double epsilon) {
    int iter = 0;
    while (right - left > epsilon) {
        double mid = (left + right) / 2;
        double f_mid = f(mid, a);
        std::cout << "Бисекция, итерация " << iter << ": mid = " << mid << ", f(mid) = " << f_mid << std::endl;
        
        if (f_mid == 0) {
            std::cout << "Точный корень найден: " << mid << std::endl;
            return;
        }
        
        if (f_mid * f(left, a) < 0) {
            right = mid;
        } else {
            left = mid;
        }
        iter++;
        
        if (iter > 1000) {
            std::cerr << "Бисекция: превышено максимальное число итераций!" << std::endl;
            break;
        }
    }
    double root = (left + right) / 2;
    std::cout << "Метод бисекции: корень = " << root << ", f(root) = " << f(root, a) << std::endl;
}

// Метод Ньютона
void newton(double a, double x0, double epsilon) {
    double x = x0;
    double delta = 1;
    int iter = 0;
    while (std::abs(delta) > epsilon) {
        double fx = f(x, a);
        double dfx = df(x);
        
        if (std::abs(dfx) < 1e-10) {
            std::cerr << "Производная близка к нулю! Метод Ньютона не может продолжаться." << std::endl;
            break;
        }
        
        delta = fx / dfx;
        x -= delta;
        std::cout << "Ньютон, итерация " << iter << ": x = " << x << ", f(x) = " << f(x, a) << std::endl;
        iter++;
        
        if (iter > 1000) {
            std::cerr << "Метод Ньютона: превышено максимальное число итераций!" << std::endl;
            break;
        }
    }
    std::cout << "Метод Ньютона: корень = " << x << ", f(root) = " << f(x, a) << std::endl;
}

int main() {
    double a;
    std::cout << "Введите a: ";
    std::cin >> a;

    // Находим интервал
    auto [left, right] = find_interval(a);
    double epsilon = 1e-10; // Уменьшили точность для избежания бесконечных циклов

    std::cout << "Интервал: [" << left << ", " << right << "]" << std::endl;

    // Начальное приближение для метода Ньютона
    double x0 = (left + right) / 2;
    std::cout << "Начальное приближение для Ньютона: " << x0 << std::endl;

    // Выполняем оба метода
    bisection(a, left, right, epsilon);
    newton(a, x0, epsilon);

    return 0;
}