#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

class Life {
 public:
  void random_fill(double fill_percentage = 0.5) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    for (int width_iter = 0; width_iter < width; ++width_iter) {
      for (int length_iter = 0; length_iter < length; ++length_iter) {
        if (dis(gen) < fill_percentage) {
          field[width_iter][length_iter] = '#';
        } else {
          field[width_iter][length_iter] = ' ';
        }
      }
    }
    print_field();
  }

  void update() {
    next_state();
    print_field();
  }

 private:
  using charmatrix = std::vector<std::vector<char>>;

  int width = 10;
  int length = 10;
  charmatrix field = charmatrix(width, std::vector<char>(length, '#'));

  void print_field() const {
    for (int width_iter = 0; width_iter < width; ++width_iter) {
      for (int length_iter = 0; length_iter < length; ++length_iter) {
        std::cout << field[width_iter][length_iter];
      }
      std::cout << "\n";
    }
    std::cout << "\n\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }

  void next_state() {
    charmatrix new_field = field;
    for (int width_iter = 0; width_iter < width; ++width_iter) {
      for (int length_iter = 0; length_iter < length; ++length_iter) {
        bool state;
        if (field[width_iter][length_iter] == '#') {
          state = true;
        } else {
          state = false;
        }
        if (next_state_of_cell(width_iter, length_iter, state)) {
          new_field[width_iter][length_iter] = '#';
        } else {
          new_field[width_iter][length_iter] = ' ';
        }
      }
    }
    field = new_field;
  }

  [[nodiscard]] bool next_state_of_cell(const int width_pos,
                                        const int length_pos,
                                        bool flag_of_living) const {
    int counter_live_neighbors = 0;
    // Search through all the neighbors
    for (int width_iter = -1; width_iter <= 1; ++width_iter) {
      for (int length_iter = -1; length_iter <= 1; ++length_iter) {
        if (width_iter == 0 && length_iter == 0) {
          continue;
        }
        if (width_pos + width_iter >= 0 && width_pos + width_iter < width &&
            length_pos + length_iter >= 0 &&
            length_pos + length_iter < length) {
          if (field[width_pos + width_iter][length_pos + length_iter] == '#') {
            ++counter_live_neighbors;
          }
        }
      }
    }
    if ((flag_of_living &&
         (counter_live_neighbors == 2 || counter_live_neighbors == 3)) ||
        (not flag_of_living && counter_live_neighbors == 3)) {
      return true;
    }
    return false;
  }
};

int main() {
  int moves = 100;
  Life game;
  game.random_fill();
  while (--moves) {
    game.update();
  }
  return 0;
}
