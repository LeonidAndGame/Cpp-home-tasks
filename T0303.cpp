#include <iostream>

class List {
 public:
  List() = default;

  ~List() {
    while (!empty()) {
      pop_front();
    }
  }

  [[nodiscard]] bool empty() const { return first == nullptr; }

  void show() const {
    Node* cur = first;
    while (cur != nullptr) {
      std::cout << (cur->value) << " ";
      cur = cur->next;
    }
    std::cout << "\n";
  }

  void push_back(int new_value) {
    Node* new_last = new Node{new_value, nullptr};
    if (empty()) {
      first = new_last;
    } else {
      last->next = new_last;
    }
    last = new_last;
  }

  void push_front(int new_value) {
    Node* new_first = new Node{new_value, first};
    if (first == nullptr) {
      last = new_first;
    }
    first = new_first;
  }

  void pop_back() {
    if (empty()) {
      return;
    }
    if (first == last) {
      delete first;
      first = nullptr;
      last = nullptr;
      return;
    }
    Node* cur = first;
    while (cur->next != last) {
      cur = cur->next;
    }
    delete last;
    last = cur;
    last->next = nullptr;
  }

  void pop_front() {
    if (empty()) {
      return;
    }
    Node* old_first = first;
    first = first->next;
    delete old_first;
    if (first == nullptr) {
      last = nullptr;
    }
  }

  int get() const {
    if (empty()) {
      std::cout << "List is empty\n";
      return -1;
    }
    Node* slow = first;
    Node* fast = first;

    while (fast != nullptr && fast->next != nullptr) {
      slow = slow->next;
      fast = fast->next->next;
    }

    return slow->value;
  }

 private:
  struct Node {
    int value = 0;
    Node* next = nullptr;
  };

  Node* first = nullptr;
  Node* last = nullptr;
};

int main() {
  List list;
  std::cout << list.empty() << "\n";
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.show();
  std::cout << list.empty() << "\n";
  list.push_front(10);
  list.show();
  std::cout << list.get() << "\n";
  list.pop_front();
  list.show();
  list.pop_back();
  list.show();
  return 0;
}
