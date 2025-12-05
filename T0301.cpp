#include <algorithm>
#include <cassert>
#include <vector>

struct Rectangle {
  int x_left = 0;
  int y_left = 0;
  int x_right = 0;
  int y_right = 0;

  [[nodiscard]] bool is_valid() const {
    return ((x_left <= x_right) && (y_left <= y_right));
  }

  [[nodiscard]] int area() const {
    if (is_valid()) {
      return (y_right - y_left) * (x_right - x_left);
    }
    return 0;
  }
};

int rectangle_intersection_area(const std::vector<Rectangle>& rectangles) {
  int count = static_cast<int>(rectangles.size());
  if (count == 0) {
    return 0;
  }
  Rectangle Answer = rectangles[0];
  for (int i = 1; i < count; ++i) {
    Answer.x_left = std::max(rectangles[i].x_left, Answer.x_left);
    Answer.x_right = std::min(rectangles[i].x_right, Answer.x_right);
    Answer.y_left = std::max(rectangles[i].y_left, Answer.y_left);
    Answer.y_right = std::min(rectangles[i].y_right, Answer.y_right);
  }
  return Answer.area();
}

Rectangle rectangle_union(const std::vector<Rectangle>& rectangles) {
  int count = static_cast<int>(rectangles.size());
  if (count == 0) {
    return {};
  }
  Rectangle Answer = rectangles[0];
  for (int i = 1; i < count; ++i) {
    Answer.x_left = std::min(rectangles[i].x_left, Answer.x_left);
    Answer.x_right = std::max(rectangles[i].x_right, Answer.x_right);
    Answer.y_left = std::min(rectangles[i].y_left, Answer.y_left);
    Answer.y_right = std::max(rectangles[i].y_right, Answer.y_right);
  }
  return Answer;
}

int main() {
  assert(rectangle_intersection_area({}) == 0);
  assert(rectangle_intersection_area({{0, 0, 5, 5}}) == 25);
  assert(rectangle_intersection_area({{0, 0, 4, 4}, {2, 2, 6, 6}}) == 4);
  assert(rectangle_intersection_area({{0, 0, 2, 2}, {3, 3, 5, 5}}) == 0);
  assert(rectangle_intersection_area(
             {{0, 0, 10, 10}, {4, 4, 12, 12}, {6, 6, 8, 8}}) == 4);
  Rectangle empty_union = rectangle_union({});
  assert(empty_union.x_left == 0 && empty_union.y_left == 0 &&
         empty_union.x_right == 0 && empty_union.y_right == 0);
  Rectangle single_union = rectangle_union({{2, 3, 8, 9}});
  assert(single_union.x_left == 2 && single_union.y_left == 3 &&
         single_union.x_right == 8 && single_union.y_right == 9);
  Rectangle disjoint_union = rectangle_union({{0, 0, 2, 2}, {5, 5, 7, 7}});
  assert(disjoint_union.x_left == 0 && disjoint_union.y_left == 0 &&
         disjoint_union.x_right == 7 && disjoint_union.y_right == 7);
  Rectangle overlap_union = rectangle_union({{0, 0, 4, 4}, {2, 2, 6, 6}});
  assert(overlap_union.x_left == 0 && overlap_union.y_left == 0 &&
         overlap_union.x_right == 6 && overlap_union.y_right == 6);
  Rectangle triple_union =
      rectangle_union({{1, 1, 3, 4}, {2, 0, 5, 3}, {0, 2, 4, 5}});
  assert(triple_union.x_left == 0 && triple_union.y_left == 0 &&
         triple_union.x_right == 5 && triple_union.y_right == 5);
  return 0;
}
