#include <iostream>
#include <cmath>
#include "../include/pentagon.hpp"

Pentagon::Pentagon() {
    // Правильный пятиугольник с центром в (0,0), радиусом 1
    const double angle = 2.0 * M_PI / 5.0;
    for (int i = 0; i < 5; ++i) {
        double phi = i * angle;
        apexes[i] = {std::cos(phi), std::sin(phi)};
    }
}

Pentagon::Pentagon(const std::array<std::pair<double, double>, 5>& apxs) 
    : apexes(apxs) {}

std::array<std::pair<double, double>, 5> Pentagon::get_apexes() {
    return apexes;
}

void Pentagon::print(std::ostream& os) const {
    os << "Вершины: ";
    for (int i = 0; i < 5; i++) {
        os << apexes[i].first << "," << apexes[i].second;
        if (i < 4) {
            os << ";";
        }
    }
}

void Pentagon::read(std::istream& is) {
    for (auto &a : apexes) {
        is >> a.first >> a.second;
    }
}

// Формула Гаусса
double Pentagon::calculateArea() const {
    double area = 0.0;
for (size_t i = 0; i < 5; ++i) {
    size_t j = (i + 1) % 5; // следующая вершина (после последней — первая)
    area += apexes[i].first * apexes[j].second; // x_i * y_{i+1}
    area -= apexes[j].first * apexes[i].second; // x_{i+1} * y_i
}
    return std::abs(area) / 2.0;
}

Pentagon::operator double() const {
    return calculateArea();
}

std::pair<double, double> Pentagon::getCenter() const {
    double cx = 0.0, cy = 0.0;
    for (const auto& a : apexes) {
        cx += a.first;
        cy += a.second;
    }
    return {cx / 5.0, cy / 5.0};
}

void Pentagon::set_apexes(const std::array<std::pair<double, double>, 5>& apxs) {
    apexes = apxs;
}

Figure& Pentagon::operator=(const Figure& other) {
    if (this != &other) {
        const Pentagon* pent = dynamic_cast<const Pentagon*>(&other);
        if (!pent) {
            throw std::invalid_argument("Cannot assign non-Pentagon to Pentagon");
        }
        this->apexes = pent->apexes;
    }
    return *this;
}

Figure& Pentagon::operator=(Figure&& other) noexcept {
    if (this != &other) {
        Pentagon* pent = dynamic_cast<Pentagon*>(&other);
        if (pent) {
            this->apexes = std::move(pent->apexes);
        }
    }
    return *this;
}

bool Pentagon::operator==(const Figure& other) const {
    const Pentagon* pent = dynamic_cast<const Pentagon*>(&other);
    if (!pent) return false;
    for (size_t i = 0; i < 5; ++i) {
        if (apexes[i] != pent->apexes[i]) return false;
    }
    return true;
}

Pentagon::Pentagon(const Pentagon& other) 
    : apexes(other.apexes) {}

std::unique_ptr<Figure> Pentagon::clone() const {
    return std::make_unique<Pentagon>(*this);
}