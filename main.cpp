#include <iomanip>

#include "include/array.h"
#include "include/figure.h"
#include "include/point.h"
#include "include/rectangle.h"
#include "include/square.h"
#include "include/triangle.h"

template <Scalar T>
using FigureArray = Array<std::shared_ptr<Figure<T>>>;

void printMenu() {
    std::cout << "\n=== Меню работы с фигурами ===" << std::endl;
    std::cout << "1. Добавить фигуру" << std::endl;
    std::cout << "2. Вывести все фигуры" << std::endl;
    std::cout << "3. Показать центры и площади всех фигур" << std::endl;
    std::cout << "4. Вычислить общую площадь всех фигур" << std::endl;
    std::cout << "5. Сравнить две фигуры" << std::endl;
    std::cout << "6. Удалить фигуру по индексу" << std::endl;
    std::cout << "7. Очистить все фигуры" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "Выберите действие: ";
}

template <Scalar T>
void addFigure(FigureArray<T>& array) {
    std::cout << "\nВыберите тип фигуры:" << std::endl;
    std::cout << "1. Квадрат" << std::endl;
    std::cout << "2. Прямоугольник" << std::endl;
    std::cout << "3. Треугольник" << std::endl;
    std::cout << "Ваш выбор: ";

    int choice;
    std::cin >> choice;


    try {
        switch (choice) {
            case 1: {
                auto sq = std::make_shared<Square<T>>();
                std::cin >> *sq;
                array.add(sq);
                break;
            }
            case 2: {
                auto rec = std::make_shared<Rectangle<T>>();
                std::cin >> *rec;
                array.add(rec);
                break;
            }
            case 3: {
                auto tri = std::make_shared<Triangle<T>>();
                std::cin >> *tri;
                array.add(tri);
                break;
            }
            default:
                std::cout << "Неверный выбор!" << std::endl;
                return;
        }

        std::cout << "Фигура успешно добавлена! Всего фигур: " << array.size() << std::endl;

    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

template <Scalar T>
void compareFigures(const FigureArray<T>& array) {
    if (array.size() < 2) {
        std::cout << "\nНедостаточно фигур для сравнения! Требуется минимум 2." << std::endl;
        return;
    }

    std::cout << "\nВведите индексы двух фигур для сравнения (0-" << (array.size() - 1) << "): ";
    size_t idx1, idx2;
    std::cin >> idx1 >> idx2;

    try {
        if (*array[idx1] == *array[idx2]) {
            std::cout << "Фигуры #" << idx1 << " и #" << idx2 << " равны" << std::endl;
        } else {
            std::cout << "Фигуры #" << idx1 << " и #" << idx2 << " не равны" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

template <Scalar T>
void deleteFigure(FigureArray<T>& array) {
    if (array.empty()) {
        std::cout << "\nМассив фигур пуст!" << std::endl;
        return;
    }

    std::cout << "\nВведите индекс фигуры для удаления (0-" << (array.size() - 1) << "): ";
    size_t idx;
    std::cin >> idx;

    try {
        array.remove(idx);
        std::cout << "Фигура #" << idx << " успешно удалена! Осталось фигур: " << array.size() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

template <Scalar T>
void print_all(const FigureArray<T>& array) {
    if (array.empty()) {
        std::cout << "Массив фигур пуст!" << std::endl;
        return;
    }

    std::cout << "=== Все фигуры ===" << std::endl;
    for (size_t i = 0; i < array.size(); i++) {
        std::cout << "Фигура #" << i << ":" << std::endl;
        std::cout << *array[i] << std::endl;
    }
}

template <Scalar T>
void print_centers_and_areas(const FigureArray<T>& array) {
    if (array.empty()) {
        std::cout << "Массив фигур пуст!" << std::endl;
        return;
    }

    std::cout << "=== Центры и площади фигур ===" << std::endl;

    for (size_t i = 0; i < array.size(); ++i) {
        Point center = array[i]->center();
        double area = static_cast<double>(*array[i]);

        std::cout << "Фигура #" << i << ":" << std::endl;
        std::cout << "Центр:" << center << std::endl;
        std::cout << "Площадь: " << area << std::endl;
        std::cout << *array[i] << std::endl;
    }
}

template <Scalar T>
double total_area(const FigureArray<T>& array) {
    double total = 0.0;
    for (size_t i = 0; i < array.size(); ++i) {
        total += static_cast<double>(*array[i]);
    }
    return total;
}


int main() {
    FigureArray<double> array;
    int choice;

    while (true) {
        printMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                addFigure(array);
                break;
            case 2:
                print_all(array);
                break;
            case 3:
                print_centers_and_areas(array);
                break;
            case 4: {
                if (array.empty()) {
                    std::cout << "\nМассив фигур пуст!" << std::endl;
                } else {
                    std::cout << std::fixed << std::setprecision(2);
                    std::cout << "\nОбщая площадь всех фигур: " << total_area(array) << std::endl;
                }
                break;
            }
            case 5:
                compareFigures(array);
                break;
            case 6:
                deleteFigure(array);
                break;
            case 7:
                array.clear();
                std::cout << "\nВсе фигуры удалены!" << std::endl;
                break;
            case 0:
                std::cout << "\nВыход из программы..." << std::endl;
                return 0;
            default:
                std::cout << "Неверный выбор! Попробуйте снова." << std::endl;
        }
    }

    return 0;
}