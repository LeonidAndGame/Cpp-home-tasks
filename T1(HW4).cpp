#include <cmath>
#include <iostream>
#include <memory>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

struct Operation {
  virtual ~Operation() = default;
  [[nodiscard]] virtual int getArity() const = 0;
  [[nodiscard]] virtual double execute(
      const std::vector<double>& args) const = 0;
};

struct UnaryOperation : Operation {
  [[nodiscard]] int getArity() const override { return 1; }
};

struct BinaryOperation : Operation {
  [[nodiscard]] int getArity() const override { return 2; }
};

struct TernaryOperation : Operation {
  [[nodiscard]] int getArity() const override { return 3; }
};

struct SinOp : UnaryOperation {
  [[nodiscard]] double execute(const std::vector<double>& args) const override {
    return std::sin(args[0]);
  }
};

struct CosOp : UnaryOperation {
  [[nodiscard]] double execute(const std::vector<double>& args) const override {
    return std::cos(args[0]);
  }
};

struct TgOp : UnaryOperation {
  [[nodiscard]] double execute(const std::vector<double>& args) const override {
    return std::tan(args[0]);
  }
};

struct CtgOp : UnaryOperation {
  [[nodiscard]] double execute(const std::vector<double>& args) const override {
    return 1.0 / std::tan(args[0]);
  }
};

struct ExpOp : UnaryOperation {
  [[nodiscard]] double execute(const std::vector<double>& args) const override {
    return std::exp(args[0]);
  }
};

struct LogOp : UnaryOperation {
  [[nodiscard]] double execute(const std::vector<double>& args) const override {
    if (args[0] <= 0) throw std::runtime_error("log domain error");
    return std::log(args[0]);
  }
};

struct SqrtOp : UnaryOperation {
  [[nodiscard]] double execute(const std::vector<double>& args) const override {
    if (args[0] < 0) throw std::runtime_error("sqrt domain error");
    return std::sqrt(args[0]);
  }
};

struct AddOp : BinaryOperation {
  [[nodiscard]] double execute(const std::vector<double>& args) const override {
    return args[0] + args[1];
  }
};

struct SubOp : BinaryOperation {
  [[nodiscard]] double execute(const std::vector<double>& args) const override {
    return args[0] - args[1];
  }
};

struct MulOp : BinaryOperation {
  [[nodiscard]] double execute(const std::vector<double>& args) const override {
    return args[0] * args[1];
  }
};

struct DivOp : BinaryOperation {
  [[nodiscard]] double execute(const std::vector<double>& args) const override {
    if (args[1] == 0) throw std::runtime_error("division by zero");
    return args[0] / args[1];
  }
};

struct Atan2Op : BinaryOperation {
  [[nodiscard]] double execute(const std::vector<double>& args) const override {
    return std::atan2(args[0], args[1]);
  }
};

struct PowOp : BinaryOperation {
  [[nodiscard]] double execute(const std::vector<double>& args) const override {
    return std::pow(args[0], args[1]);
  }
};

struct MedianOp : TernaryOperation {
  [[nodiscard]] double execute(const std::vector<double>& args) const override {
    double a = args[0], b = args[1], c = args[2];
    if ((a <= b && b <= c) || (c <= b && b <= a)) return b;
    if ((b <= a && a <= c) || (c <= a && a <= b)) return a;
    return c;
  }
};

class RPNCalculator {
  std::unordered_map<std::string, std::unique_ptr<Operation>> operations_;
  std::stack<double> stack_;

  void initOperations() {
    operations_["+"] = std::make_unique<AddOp>();
    operations_["-"] = std::make_unique<SubOp>();
    operations_["*"] = std::make_unique<MulOp>();
    operations_["/"] = std::make_unique<DivOp>();
    operations_["sin"] = std::make_unique<SinOp>();
    operations_["cos"] = std::make_unique<CosOp>();
    operations_["tg"] = std::make_unique<TgOp>();
    operations_["ctg"] = std::make_unique<CtgOp>();
    operations_["exp"] = std::make_unique<ExpOp>();
    operations_["log"] = std::make_unique<LogOp>();
    operations_["sqrt"] = std::make_unique<SqrtOp>();
    operations_["atan2"] = std::make_unique<Atan2Op>();
    operations_["pow"] = std::make_unique<PowOp>();
    operations_["median"] = std::make_unique<MedianOp>();
  }

 public:
  RPNCalculator() { initOperations(); }

  double evaluate(const std::string& expression) {
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token) {
      auto it = operations_.find(token);
      if (it != operations_.end()) {
        const Operation* op = it->second.get();
        int arity = op->getArity();
        if (stack_.size() < static_cast<size_t>(arity)) {
          throw std::runtime_error("not enough operands");
        }
        std::vector<double> args(arity);
        for (int i = arity - 1; i >= 0; --i) {
          args[i] = stack_.top();
          stack_.pop();
        }
        try {
          double result = op->execute(args);
          stack_.push(result);
        } catch (const std::runtime_error& e) {
          throw std::runtime_error(std::string("operation error: ") + e.what());
        }
      } else {
        try {
          double value = std::stod(token);
          stack_.push(value);
        } catch (const std::invalid_argument&) {
          throw std::runtime_error("invalid token: " + token);
        } catch (const std::out_of_range&) {
          throw std::runtime_error("number out of range: " + token);
        }
      }
    }

    if (stack_.size() == 1) {
      double result = stack_.top();
      stack_.pop();
      return result;
    }
    if (stack_.size() > 1) {
      throw std::runtime_error("too many operands");
    }
    throw std::runtime_error("no result");
  }
};

void test() {
  RPNCalculator calc;
  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty()) continue;
    try {
      double result = calc.evaluate(line);
      std::cout << result << std::endl;
    } catch (const std::runtime_error& e) {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  }
}

int main() {
  test();
  return 0;
}
