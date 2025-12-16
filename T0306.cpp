#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

class Shape {
 public:
  virtual ~Shape() = default;
  [[nodiscard]] virtual double perimeter() const = 0;
  [[nodiscard]] virtual double area() const = 0;
};

class Circle final : Shape {
  double radius;

 public:
  explicit Circle(double r) : radius(r) {}

  [[nodiscard]] double perimeter() const override { return 2 * M_PI * radius; }

  [[nodiscard]] double area() const override { return M_PI * radius * radius; }
};

class Polygon : public Shape {};

class Rectangle : public Polygon {
  double width;
  double height;

 public:
  Rectangle(double w, double h) : width(w), height(h) {}

  [[nodiscard]] double perimeter() const final { return 2 * (width + height); }

  [[nodiscard]] double area() const final { return width * height; }
};

class Square final : public Rectangle {
 public:
  explicit Square(double side) : Rectangle(side, side) {}
};

class Triangle : public Polygon {
  double a, b, c;

 public:
  Triangle(double side1, double side2, double side3)
      : a(side1), b(side2), c(side3) {}

  [[nodiscard]] double perimeter() const override { return a + b + c; }

  [[nodiscard]] double area() const override {
    double s = perimeter() / 2;
    return std::sqrt(s * (s - a) * (s - b) * (s - c));
  }
};

void demonstrate_polymorphism() {
  std::vector<std::unique_ptr<Shape>> shapes;
  shapes.push_back(std::make_unique<Circle>(5.0));
  shapes.push_back(std::make_unique<Triangle>(3.0, 4.0, 5.0));
  shapes.push_back(std::make_unique<Rectangle>(4.0, 6.0));
  shapes.push_back(std::make_unique<Square>(5.0));
  shapes.push_back(std::make_unique<Circle>(2.5));
  shapes.push_back(std::make_unique<Triangle>(5.0, 5.0, 5.0));
  for (const auto& shape : shapes) {
    double p = shape->perimeter();
    double a = shape->area();
    std::cout << p << " " << a << "\n";
  }
}

void test_shapes() {
  Circle circle(10.0);
  assert(std::abs(circle.perimeter() - 2 * M_PI * 10.0) < 0.0001);
  assert(std::abs(circle.area() - M_PI * 100.0) < 0.0001);
  Triangle triangle(3.0, 4.0, 5.0);
  assert(std::abs(triangle.perimeter() - 12.0) < 0.0001);
  assert(std::abs(triangle.area() - 6.0) < 0.0001);
  Rectangle rectangle(4.0, 5.0);
  assert(std::abs(rectangle.perimeter() - 18.0) < 0.0001);
  assert(std::abs(rectangle.area() - 20.0) < 0.0001);
  Square square(4.0);
  assert(std::abs(square.perimeter() - 16.0) < 0.0001);
  assert(std::abs(square.area() - 16.0) < 0.0001);
  Rectangle* rectPtr = &square;
  assert(std::abs(rectPtr->perimeter() - 16.0) < 0.0001);
  assert(std::abs(rectPtr->area() - 16.0) < 0.0001);
}

int main() {
  demonstrate_polymorphism();
  test_shapes();
  return 0;
}
