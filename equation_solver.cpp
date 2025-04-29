#include <iostream>
#include <cmath>
#include <utility>
#include <vector>

// Цвета ANSI
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"

inline double f(double x, double a) {
    return std::pow(x, 5) + x + a;
}

inline double df(double x) {
    return 5 * std::pow(x, 4) + 1;
}

inline std::pair<double, double> find_interval(double a) {
    if (a >= 0) {
        double left = -2;
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

inline double bisection(double a, double left, double right, double epsilon) {
    int iter = 0;
    while (right - left > epsilon && iter < 1000) {
        double mid = (left + right) / 2;
        double f_mid = f(mid, a);
        std::cout << "Бисекция, итерация " << iter << ": mid = " << mid << ", f(mid) = " << f_mid << std::endl;
        if (f_mid == 0.0) {
            return mid;
        }
        if (f_mid * f(left, a) < 0) {
            right = mid;
        } else {
            left = mid;
        }
        iter++;
    }
    double root = (left + right) / 2;
    std::cout << GREEN << "Метод бисекции: корень = " << root << ", f(root) = " << f(root, a) << RESET << std::endl;
    return root;
}

inline double newton(double a, double x0, double epsilon) {
    double x = x0;
    double delta = 1.0;
    int iter = 0;
    while (std::abs(delta) > epsilon && iter < 1000) {
        double fx = f(x, a);
        double dfx = df(x);
        if (std::abs(dfx) < 1e-12) {
            std::cerr << RED << "Производная близка к нулю!" << RESET << std::endl;
            break;
        }
        delta = fx / dfx;
        x -= delta;
        std::cout << "Ньютон, итерация " << iter << ": x = " << x << ", f(x) = " << f(x, a) << std::endl;
        iter++;
    }
    std::cout << GREEN << "Метод Ньютона: корень = " << x << ", f(root) = " << f(x, a) << RESET << std::endl;
    return x;
}

void run_tests() {
    std::cout << BLUE << "=== Запуск тестов ===" << RESET << std::endl;
    const double eps = 1e-10;
    struct Test { double a; };
    std::vector<Test> tests = {
        {2.0}, {-2.0}, {1e-6}, {-1e-6}, {8e-11}, {-8e-11}, {10.0}, {-10.0}, {1000.0}, {-1000.0}
    };
    for (auto t : tests) {
        auto [left, right] = find_interval(t.a);
        double x0 = (std::abs(t.a) < 1e-5) ? -t.a : (left + right) / 2;
        std::cout << BLUE << "a = " << t.a << RESET << std::endl;
        std::cout << BLUE << "---Бисекция---" << RESET << std::endl;
        double root_b = bisection(t.a, left, right, eps);
        std::cout << BLUE << "---Ньютон---" << RESET << std::endl;
        double root_n = newton(t.a, x0, eps);
        std::cout << GREEN << "Результаты для сравнения: Ньютон: " << root_n << " Бисекции: " << root_b << RESET << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }
    std::cout << BLUE << "=== Тестирование завершено ===" << RESET << std::endl;
}

int main() {
    run_tests();
    return 0;
}
