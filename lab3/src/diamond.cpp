#include "../include/diamond.hpp"
#include <ostream>
#include <cmath>
// Конструкторы
Diamond::Diamond() {
    // По умолчанию — ромб со стороной 1, центром в (0,0), оси параллельны осям
    apexes = {{
        {0.5, 0.0},   // правая
        {0.0, 0.5},   // верхняя
        {-0.5, 0.0},  // левая
        {0.0, -0.5}   // нижняя
    }};
}


Diamond::Diamond(const std::array<std::pair<double, double>, 4>& apxs) {
    apexes = apxs;
}
// Геттеры/Сеттеры
std::array<std::pair<double, double>, 4> &Diamond::get_apexes() {
    return apexes;
}

void Diamond::set_apexes(const std::array<std::pair<double, double>, 4>& apxs) {
    apexes = apxs;
}

std::pair<double, double> Diamond::getCenter() const {
    double sum_x = 0;
    double sum_y = 0;
    for (const std::pair<double, double>& a : apexes) {
        sum_x += a.first;
        sum_y += a.second;
    }
    return {sum_x / 4.0, sum_y / 4.0};
}

void Diamond::print(std::ostream& os) const {
    os << "Ромб:";
    for (size_t i = 0; i < 4; i++) {
        os << "(" << apexes[i].first << ", " << apexes[i].second << ")";
        if (i < 3) {
            os << "; ";
        }
    }
}

void Diamond::read(std::istream& is) {
    for (std::pair<double, double>& a : apexes) {
        is >> a.first >> a.second;
    }
}

double Diamond::calculateArea() const {
    // Площадь ромба через диагонали: S = (d1 * d2) / 2
    double d1 = std::sqrt(std::pow(apexes[0].first - apexes[2].first, 2) +
                          std::pow(apexes[0].second - apexes[2].second, 2));
    double d2 = std::sqrt(std::pow(apexes[1].first - apexes[3].first, 2) +
                          std::pow(apexes[1].second - apexes[3].second, 2));
    return (d1 * d2) / 2.0;
}

Diamond::operator double() const {
    return calculateArea();
}

Figure& Diamond::operator=(const Figure& other) {
    if (this != &other) {
        const Diamond* diam = dynamic_cast<const Diamond*>(&other);
        if (!diam) {
            throw std::invalid_argument("Cannot assign non-Rhombus to Rhombus");
        }
        this->apexes = diam->apexes;
    }
    return *this;
}

Figure& Diamond::operator=(Figure&& other) noexcept {
    if (this != &other) {
        Diamond* diam = dynamic_cast<Diamond*>(&other);
        if (diam) {
            this->apexes = std::move(diam->apexes);
        }
    }
    return *this;
}

bool Diamond::operator==(const Figure& other) const {
    const Diamond* diam = dynamic_cast<const Diamond*>(&other);
    if (!diam) return false;
    for (size_t i = 0; i < 4; ++i) {
        if (apexes[i] != diam->apexes[i]) return false;
    }
    return true;
}

Diamond::Diamond(const Diamond& other)
    : apexes(other.apexes) {}

std::unique_ptr<Figure> Diamond::clone() const {
    return std::make_unique<Diamond>(*this);
}

