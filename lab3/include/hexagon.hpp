#pragma once

#include <iostream>
#include "Figure.hpp"
#include <array>

class Hexagon : public Figure 
{
    private:
        std::array<std::pair<double, double>, 6> apexes;
    public:
        // Конструкторы
        Hexagon();
        Hexagon(const std::array<std::pair<double, double>, 6>& apxs);
        Hexagon(const Hexagon& other);
        // Геттеры
        std::array<std::pair<double, double>, 6> get_apexes();
        void set_apexes(const std::array<std::pair<double, double>, 6>& apxs);
            // 1. Центр
        std::pair<double, double> getCenter() const override;

        // 2. Вывод
        void print(std::ostream& os) const override;

        // 3. Ввод
        void read(std::istream& is) override;

        // 4. Площадь
        double calculateArea() const override;
        operator double() const override;

        // Операторы
        Figure& operator=(const Figure& other) override;
        Figure& operator=(Figure&& other) noexcept override;
        bool operator==(const Figure& other) const override;

        // Клонирование
        std::unique_ptr<Figure> clone() const override;
};
