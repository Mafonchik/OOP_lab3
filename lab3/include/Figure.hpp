#pragma once

#include <iostream>
#include <memory>

class Figure {
public:
    // Виртуальный деструктор
    virtual ~Figure() = default;

    // 1. Вычисление геометрического центра
    virtual std::pair<double, double> getCenter() const = 0;

    // 2. Перегрузка оператора вывода
    virtual void print(std::ostream& os) const = 0;
    friend std::ostream& operator<<(std::ostream& os, const Figure& fig);

    // 3. Перегрузка оператора ввода
    virtual void read(std::istream& is) = 0;
    friend std::istream& operator>>(std::istream& is, Figure& fig);

    // 4. Перегрузка оператора приведения к double (площадь)
    virtual operator double() const = 0;
    virtual double calculateArea() const = 0;

    // Операции копирования, перемещения, сравнения
    virtual Figure& operator=(const Figure& other) = 0;
    virtual Figure& operator=(Figure&& other) noexcept = 0;
    virtual bool operator==(const Figure& other) const = 0;

    // Виртуальная функция клонирования для полиморфного копирования
    virtual std::unique_ptr<Figure> clone() const = 0;
};
