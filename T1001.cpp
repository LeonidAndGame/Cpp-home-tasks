#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

using charmatrix = std::vector<std::vector<char>>;

class Life {
 public:
  int n = 10;
  int m = 10;
  charmatrix field = charmatrix(n, std::vector<char>(m, '#'));

  void random_fill(double fill_percentage = 0.5) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (dis(gen) < fill_percentage) {
          field[i][j] = '#';
        } else {
          field[i][j] = ' ';
        }
      }
    }
  }

  void print_field() const {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        std::cout << field[i][j];
      }
      std::cout << "\n";
    }
    std::cout << "\n\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }

  void next_state() {
    charmatrix new_field = field;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        bool state;
        if (field[i][j] == '#') {
          state = true;
        } else {
          state = false;
        }
        if (next_state_of_cell(i, j, state)) {
          new_field[i][j] = '#';
        } else {
          new_field[i][j] = ' ';
        }
      }
    }
    field = new_field;
  }

 private:
  [[nodiscard]] bool next_state_of_cell(const int p, const int q,
                                        bool f) const {
    int counter = 0;
    for (int i = -1; i <= 1; ++i) {
      for (int j = -1; j <= 1; ++j) {
        if (i != 0 || j != 0) {
          if (p + i >= 0 && p + i < n && q + j >= 0 && q + j < m) {
            if (field[p + i][q + j] == '#') {
              ++counter;
            }
          }
        }
      }
    }
    if ((f && (counter == 2 || counter == 3)) || (not f && counter == 3)) {
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
    game.print_field();
    game.next_state();
  }
  return 0;
}
