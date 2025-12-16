#include <array>
#include <cassert>
#include <cstdint>
#include <sstream>
#include <string>

class IPv4 {
  std::array<std::uint8_t, 4> data;

 public:
  IPv4() : data{0, 0, 0, 0} {}

  IPv4(std::uint8_t a, std::uint8_t b, std::uint8_t c, std::uint8_t d)
      : data{a, b, c, d} {}

  IPv4& operator++() {
    for (int i = 3; i >= 0; --i) {
      if (data[i] < 255) {
        ++data[i];
        return *this;
      }
      data[i] = 0;
    }
    return *this;
  }

  IPv4 operator++(int) {
    IPv4 temp = *this;
    ++(*this);
    return temp;
  }

  IPv4& operator--() {
    for (int i = 3; i >= 0; --i) {
      if (data[i] > 0) {
        --data[i];
        return *this;
      }
      data[i] = 255;
    }
    return *this;
  }

  IPv4 operator--(int) {
    IPv4 temp = *this;
    --(*this);
    return temp;
  }

  friend bool operator==(const IPv4& left_ip, const IPv4& right_ip) {
    return left_ip.data == right_ip.data;
  }

  friend bool operator!=(const IPv4& left_ip, const IPv4& right_ip) {
    return !(left_ip == right_ip);
  }

  friend bool operator<(const IPv4& left_ip, const IPv4& right_ip) {
    return left_ip.data < right_ip.data;
  }

  friend bool operator>(const IPv4& left_ip, const IPv4& right_ip) {
    return right_ip < left_ip;
  }

  friend bool operator<=(const IPv4& left_ip, const IPv4& right_ip) {
    return !(left_ip > right_ip);
  }

  friend bool operator>=(const IPv4& left_ip, const IPv4& right_ip) {
    return !(left_ip < right_ip);
  }

  friend std::istream& operator>>(std::istream& is, IPv4& ip) {
    int a, b, c, d;
    char dot1, dot2, dot3;
    if (is >> a >> dot1 >> b >> dot2 >> c >> dot3 >> d) {
      if (dot1 == '.' && dot2 == '.' && dot3 == '.' && a >= 0 && a <= 255 &&
          b >= 0 && b <= 255 && c >= 0 && c <= 255 && d >= 0 && d <= 255) {
        ip.data = {static_cast<uint8_t>(a), static_cast<uint8_t>(b),
                   static_cast<uint8_t>(c), static_cast<uint8_t>(d)};
      } else {
        is.setstate(std::ios::failbit);
      }
    }
    return is;
  }

  friend std::ostream& operator<<(std::ostream& os, const IPv4& ip) {
    os << static_cast<int>(ip.data[0]) << '.' << static_cast<int>(ip.data[1])
       << '.' << static_cast<int>(ip.data[2]) << '.'
       << static_cast<int>(ip.data[3]);
    return os;
  }
};

void test() {
  IPv4 ip1(192, 168, 1, 1);
  std::stringstream ss1;
  ss1 << ip1;
  assert(ss1.str() == "192.168.1.1");
  IPv4 ip2;
  std::stringstream ss2("10.0.0.1");
  ss2 >> ip2;
  assert(ip2 == IPv4(10, 0, 0, 1));
  IPv4 ip3(192, 168, 1, 255);
  ++ip3;
  assert(ip3 == IPv4(192, 168, 2, 0));
  IPv4 ip4(10, 0, 0, 254);
  IPv4 ip4_old = ip4++;
  assert(ip4_old == IPv4(10, 0, 0, 254));
  assert(ip4 == IPv4(10, 0, 0, 255));
  IPv4 ip5(192, 168, 2, 0);
  --ip5;
  assert(ip5 == IPv4(192, 168, 1, 255));
  IPv4 ip6(10, 0, 0, 1);
  IPv4 ip6_old = ip6--;
  assert(ip6_old == IPv4(10, 0, 0, 1));
  assert(ip6 == IPv4(10, 0, 0, 0));
  assert(IPv4(192, 168, 1, 1) < IPv4(192, 168, 1, 2));
  assert(IPv4(10, 0, 0, 1) > IPv4(10, 0, 0, 0));
  assert(IPv4(192, 168, 1, 1) != IPv4(192, 168, 1, 2));
  assert(IPv4(192, 168, 1, 1) == IPv4(192, 168, 1, 1));
}

int main() {
  test();
  return 0;
}
