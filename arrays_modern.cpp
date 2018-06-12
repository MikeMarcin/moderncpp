#include <iostream>
#include <array>
#include <iterator>
#include <algorithm>

// std::array initially joined the C++ standard in TR1 back in 2006
// it moved out into the main standard in C++11 (2011)
// like many standard library features it started life in boost
// first released in boost version 1.17.0 (2000)

void pass_by_value( std::array<int, 6> values ) {
    values[0] = 1;
}

int main() {
    std::array<int, 6> values = {};

    // straight forward to get the size of the array
    auto count = values.size();
    std::cout << count << std::endl;

    for ( int x : values ) { std::cout << x << ' '; }
    std::cout << std::endl;

    // you can pass by value to functions in the normal way
    pass_by_value(values);

    for ( int x : values ) { std::cout << x << ' '; }
    std::cout << std::endl;

    // assignment works fine!
    std::array<int, 6> values2 = {};
    values2 = values;

    // out of bounds access detected in debug mode
    // note: msvc doesn't issue a warning here at compile time
    // seems a deficiency they should be able to
    values[7] = 0xdeadbeef;
}
