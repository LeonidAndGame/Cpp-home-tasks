#include <cassert>
#include <string>

std::string decimal_to_roman(unsigned int number) {
    static constexpr std::pair<unsigned int, const char*> roman[13] = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},
        {90, "XC"},  {50, "L"},   {40, "XL"}, {10, "X"},   {9, "IX"},
        {5, "V"},    {4, "IV"},   {1, "I"}};
    if (number > 3999) {
        return "Very Big Number";
    }
    std::string result;
    result.reserve(15);
    for (const auto& [value, letters] : roman) {
        while (number >= value) {
            result += letters;
            number -= value;
        }
    }
    return result;
}

int main() {
    assert(decimal_to_roman(42) == "XLII");
    assert(decimal_to_roman(228) == "CCXXVIII");
    assert(decimal_to_roman(1984) == "MCMLXXXIV");
    assert(decimal_to_roman(3999) == "MMMCMXCIX");
    assert(decimal_to_roman(1) == "I");
    assert(decimal_to_roman(0).empty());
    assert(decimal_to_roman(4000) == "Very Big Number");
    return 0;
}
