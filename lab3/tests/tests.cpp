#include <gtest/gtest.h>
#include <memory>
#include <array>
#include <sstream>
#include <cmath>
#include "../include/diamond.hpp"
#include "../include/pentagon.hpp"
#include "../include/hexagon.hpp"

// Вспомогательная функция для сравнения вершин с точностью
template<typename T>
bool apexes_equal(const T& a1, const T& a2, double eps = 1e-9) {
    if (a1.size() != a2.size()) return false;
    for (size_t i = 0; i < a1.size(); ++i) {
        if (std::abs(a1[i].first - a2[i].first) > eps ||
            std::abs(a1[i].second - a2[i].second) > eps) {
            return false;
        }
    }
    return true;
}

// =============== DIAMOND TESTS ===============

TEST(DiamondTest, DefaultConstructor) {
    Diamond d;
    auto center = d.getCenter();
    EXPECT_NEAR(center.first, 0.0, 1e-9);
    EXPECT_NEAR(center.second, 0.0, 1e-9);
}

TEST(DiamondTest, ParameterizedConstructor) {
    std::array<std::pair<double, double>, 4> verts = {{{1,0}, {0,1}, {-1,0}, {0,-1}}};
    Diamond d(verts);
    EXPECT_TRUE(apexes_equal(d.get_apexes(), verts));
}

TEST(DiamondTest, Center) {
    std::array<std::pair<double, double>, 4> verts = {{{2,0}, {0,2}, {-2,0}, {0,-2}}};
    Diamond d(verts);
    auto c = d.getCenter();
    EXPECT_NEAR(c.first, 0.0, 1e-9);
    EXPECT_NEAR(c.second, 0.0, 1e-9);
}

TEST(DiamondTest, Area) {
    std::array<std::pair<double, double>, 4> verts = {{{2,0}, {0,3}, {-2,0}, {0,-3}}};
    Diamond d(verts);
    double area = static_cast<double>(d);
    EXPECT_NEAR(area, (4.0 * 6.0) / 2.0, 1e-9); // d1=4, d2=6 → S=12
}

TEST(DiamondTest, Clone) {
    Diamond orig;
    auto cloned = orig.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_TRUE(dynamic_cast<Diamond*>(cloned.get()) != nullptr);
    EXPECT_NEAR(static_cast<double>(*cloned), static_cast<double>(orig), 1e-9);
}

TEST(DiamondTest, Equality) {
    std::array<std::pair<double, double>, 4> v1 = {{{1,0}, {0,1}, {-1,0}, {0,-1}}};
    std::array<std::pair<double, double>, 4> v2 = {{{1,0}, {0,1}, {-1,0}, {0,-1}}};
    std::array<std::pair<double, double>, 4> v3 = {{{2,0}, {0,2}, {-2,0}, {0,-2}}};

    Diamond d1(v1), d2(v2), d3(v3);
    EXPECT_TRUE(d1 == d2);
    EXPECT_FALSE(d1 == d3);
}

TEST(DiamondTest, Print) {
    std::array<std::pair<double, double>, 4> verts = {{{1,0}, {0,1}, {-1,0}, {0,-1}}};
    Diamond d(verts);
    std::stringstream ss;
    ss << d;
    EXPECT_EQ(ss.str(), "Ромб:(1, 0); (0, 1); (-1, 0); (0, -1)");
}

TEST(DiamondTest, Read) {
    std::stringstream ss;
    ss << "1 0 0 1 -1 0 0 -1";
    Diamond d;
    ss >> d;
    std::array<std::pair<double, double>, 4> expected = {{{1,0}, {0,1}, {-1,0}, {0,-1}}};
    EXPECT_TRUE(apexes_equal(d.get_apexes(), expected));
}

// =============== PENTAGON TESTS ===============

TEST(PentagonTest, DefaultConstructor) {
    Pentagon p;
    auto center = p.getCenter();
    EXPECT_NEAR(center.first, 0.0, 1e-6);
    EXPECT_NEAR(center.second, 0.0, 1e-6);
}

TEST(PentagonTest, AreaRegular) {
    Pentagon p;
    double area = static_cast<double>(p);
    double expected = (5.0 / 2.0) * std::sin(2 * M_PI / 5.0);
    EXPECT_NEAR(area, expected, 1e-6);
}

TEST(PentagonTest, Clone) {
    Pentagon orig;
    auto cloned = orig.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_TRUE(dynamic_cast<Pentagon*>(cloned.get()) != nullptr);
    EXPECT_NEAR(static_cast<double>(*cloned), static_cast<double>(orig), 1e-6);
}

TEST(PentagonTest, Equality) {
    Pentagon p1, p2;
    EXPECT_TRUE(p1 == p2);

    std::array<std::pair<double, double>, 5> other = {{
        {1,0}, {0,1}, {-1,0}, {0,-1}, {0.5, 0.5}
    }};
    Pentagon p3(other);
    EXPECT_FALSE(p1 == p3);
}

TEST(PentagonTest, Print) {
    std::array<std::pair<double, double>, 5> verts = {{
        {1,0}, {0,1}, {-1,0}, {0,-1}, {0.5,0.5}
    }};
    Pentagon p(verts);
    std::stringstream ss;
    ss << p;
    std::string expected = "Вершины: 1,0;0,1;-1,0;0,-1;0.5,0.5";
    EXPECT_EQ(ss.str(), expected);
}

TEST(PentagonTest, Read) {
    std::stringstream ss;
    ss << "1 0 0 1 -1 0 0 -1 0.5 0.5";
    Pentagon p;
    ss >> p;
    std::array<std::pair<double, double>, 5> expected = {{
        {1,0}, {0,1}, {-1,0}, {0,-1}, {0.5,0.5}
    }};
    EXPECT_TRUE(apexes_equal(p.get_apexes(), expected));
}

// =============== HEXAGON TESTS ===============

TEST(HexagonTest, DefaultConstructor) {
    Hexagon h;
    auto center = h.getCenter();
    EXPECT_NEAR(center.first, 0.0, 1e-6);
    EXPECT_NEAR(center.second, 0.0, 1e-6);
}

TEST(HexagonTest, AreaRegular) {
    Hexagon h;
    double area = static_cast<double>(h);
    double expected = (3.0 * std::sqrt(3.0)) / 2.0; // ≈ 2.598
    EXPECT_NEAR(area, expected, 1e-6);
}

TEST(HexagonTest, Clone) {
    Hexagon orig;
    auto cloned = orig.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_TRUE(dynamic_cast<Hexagon*>(cloned.get()) != nullptr);
    EXPECT_NEAR(static_cast<double>(*cloned), static_cast<double>(orig), 1e-6);
}

TEST(HexagonTest, Equality) {
    Hexagon h1, h2;
    EXPECT_TRUE(h1 == h2);

    std::array<std::pair<double, double>, 6> other = {{
        {1,0}, {0,1}, {-1,0}, {0,-1}, {0.5,0.5}, {-0.5,-0.5}
    }};
    Hexagon h3(other);
    EXPECT_FALSE(h1 == h3);
}

TEST(HexagonTest, Print) {
    std::array<std::pair<double, double>, 6> verts = {{
        {1,0}, {0,1}, {-1,0}, {0,-1}, {0.5,0.5}, {-0.5,-0.5}
    }};
    Hexagon h(verts);
    std::stringstream ss;
    ss << h;
    std::string expected = "Вершины: 1,0;0,1;-1,0;0,-1;0.5,0.5;-0.5,-0.5";
    EXPECT_EQ(ss.str(), expected);
}

TEST(HexagonTest, Read) {
    std::stringstream ss;
    ss << "1 0 0 1 -1 0 0 -1 0.5 0.5 -0.5 -0.5";
    Hexagon h;
    ss >> h;
    std::array<std::pair<double, double>, 6> expected = {{
        {1,0}, {0,1}, {-1,0}, {0,-1}, {0.5,0.5}, {-0.5,-0.5}
    }};
    EXPECT_TRUE(apexes_equal(h.get_apexes(), expected));
}

// =============== POLYMORPHISM TEST ===============

TEST(FigureTest, PolymorphismVector) {
    std::vector<std::unique_ptr<Figure>> figures;
    figures.push_back(std::make_unique<Diamond>());
    figures.push_back(std::make_unique<Pentagon>());
    figures.push_back(std::make_unique<Hexagon>());

    double total_area = 0.0;
    for (const auto& fig : figures) {
        total_area += static_cast<double>(*fig);
    }
    EXPECT_GT(total_area, 0.0);
}

TEST(FigureTest, ClonePolymorphic) {
    std::unique_ptr<Figure> d1 = std::make_unique<Diamond>();
    auto d2 = d1->clone();
    EXPECT_TRUE(dynamic_cast<Diamond*>(d2.get()) != nullptr);
    EXPECT_NEAR(static_cast<double>(*d1), static_cast<double>(*d2), 1e-9);
}