#include <iostream>
#include <cmath>
#include "../include/hexagon.hpp"

Hexagon::Hexagon() {
    // Правильный шестиугольник с центром в (0,0), радиусом 1
    const double angle = 2.0 * M_PI / 6.0;
    for (int i = 0; i < 6; ++i) {
        double phi = i * angle;
        apexes[i] = {std::cos(phi), std::sin(phi)};
    }
}

Hexagon::Hexagon(const std::array<std::pair<double, double>, 6>& apxs) 
    : apexes(apxs) {}

std::array<std::pair<double, double>, 6> Hexagon::get_apexes() {
    return apexes;
}

void Hexagon::print(std::ostream& os) const {
    os << "Вершины: ";
    for (int i = 0; i < 6; i++) {
        os << apexes[i].first << "," << apexes[i].second;
        if (i < 5) {
            os << ";";
        }
    }
}

void Hexagon::read(std::istream& is) {
    for (auto &a : apexes) {
        is >> a.first >> a.second;
    }
}

// Формула Гаусса
double Hexagon::calculateArea() const {
    double area = 0.0;
for (size_t i = 0; i < 6; ++i) {
    size_t j = (i + 1) % 6; // следующая вершина (после последней — первая)
    area += apexes[i].first * apexes[j].second; // x_i * y_{i+1}
    area -= apexes[j].first * apexes[i].second; // x_{i+1} * y_i
}
    return std::abs(area) / 2.0;
}

std::pair<double, double> Hexagon::getCenter() const {
    double sum_x = 0.0;
    double sum_y = 0.0;
    for (const auto& a : apexes) {
        sum_x += a.first;
        sum_y += a.second;
    }
    return {sum_x / 6.0, sum_y / 6.0};
}

Hexagon::operator double() const {
    return calculateArea();
}

void Hexagon::set_apexes(const std::array<std::pair<double, double>, 6>& apxs) {
    apexes = apxs;
}

Figure& Hexagon::operator=(const Figure& other) {
    if (this != &other) {
        const Hexagon* hex = dynamic_cast<const Hexagon*>(&other);
        if (!hex) {
            throw std::invalid_argument("Cannot assign non-Hexagon to Hexagon");
        }
        this->apexes = hex->apexes;
    }
    return *this;
}

Figure& Hexagon::operator=(Figure&& other) noexcept {
    if (this != &other) {
        Hexagon* hex = dynamic_cast<Hexagon*>(&other);
        if (hex) {
            this->apexes = std::move(hex->apexes);
        }
    }
    return *this;
}

bool Hexagon::operator==(const Figure& other) const {
    const Hexagon* hex = dynamic_cast<const Hexagon*>(&other);
    if (!hex) return false;
    for (size_t i = 0; i < 6; ++i) {
        if (apexes[i] != hex->apexes[i]) return false;
    }
    return true;
}

Hexagon::Hexagon(const Hexagon& other) 
    : apexes(other.apexes) {}

std::unique_ptr<Figure> Hexagon::clone() const {
    return std::make_unique<Hexagon>(*this);
}