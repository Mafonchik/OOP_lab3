#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "include/diamond.hpp"
#include "include/pentagon.hpp"
#include "include/hexagon.hpp"

// Вспомогательная функция: вывод информации о фигуре
void printFigureInfo(const Figure& fig) {
    auto center = fig.getCenter();
    double area = static_cast<double>(fig);
    std::cout << "Центр: (" << center.first << ", " << center.second << "), "
              << "Площадь: " << area << "\n";
}

// Вспомогательная функция: подсчёт общей площади
double totalArea(const std::vector<std::unique_ptr<Figure>>& figures) {
    double total = 0.0;
    for (const auto& fig : figures) {
        total += static_cast<double>(*fig);
    }
    return total;
}

// Вспомогательная функция: удаление по индексу
bool removeFigure(std::vector<std::unique_ptr<Figure>>& figures, size_t index) {
    if (index >= figures.size()) {
        return false;
    }
    figures.erase(figures.begin() + index);
    return true;
}

int main() {
    std::vector<std::unique_ptr<Figure>> figures;
    std::string command;

    std::cout << "Доступные команды:\n"
              << "  add diamond    — добавить ромб\n"
              << "  add pentagon   — добавить пятиугольник\n"
              << "  add hexagon    — добавить шестиугольник\n"
              << "  list           — вывести все фигуры\n"
              << "  total          — общая площадь\n"
              << "  remove <индекс> — удалить фигуру по индексу (начиная с 0)\n"
              << "  quit           — завершить программу\n\n";

    while (true) {
        std::cout << "> ";
        std::cin >> command;

        if (command == "quit") {
            break;
        }
        else if (command == "add") {
            std::string type;
            std::cin >> type;

            if (type == "diamond") {
                auto d = std::make_unique<Diamond>();
                std::cout << "Введите 4 вершины ромба (x1 y1 x2 y2 ... x4 y4):\n";
                std::cin >> *d;
                figures.push_back(std::move(d));
            }
            else if (type == "pentagon") {
                auto p = std::make_unique<Pentagon>();
                std::cout << "Введите 5 вершин пятиугольника (x1 y1 ... x5 y5):\n";
                std::cin >> *p;
                figures.push_back(std::move(p));
            }
            else if (type == "hexagon") {
                auto h = std::make_unique<Hexagon>();
                std::cout << "Введите 6 вершин шестиугольника (x1 y1 ... x6 y6):\n";
                std::cin >> *h;
                figures.push_back(std::move(h));
            }
            else {
                std::cout << "Неизвестный тип фигуры: " << type << "\n";
            }
        }
        else if (command == "list") {
            if (figures.empty()) {
                std::cout << "Нет фигур.\n";
            } else {
                for (size_t i = 0; i < figures.size(); ++i) {
                    std::cout << "[" << i << "] ";
                    printFigureInfo(*figures[i]);
                }
            }
        }
        else if (command == "total") {
            std::cout << "Общая площадь: " << totalArea(figures) << "\n";
        }
        else if (command == "remove") {
            size_t index;
            std::cin >> index;
            if (removeFigure(figures, index)) {
                std::cout << "Фигура удалена.\n";
            } else {
                std::cout << "Ошибка: индекс вне диапазона [0, " << figures.size() - 1 << "]\n";
            }
        }
        else {
            std::cout << "Неизвестная команда. Доступные: add, list, total, remove, quit\n";
        }
    }

    std::cout << "Выход.\n";
    return 0;
}