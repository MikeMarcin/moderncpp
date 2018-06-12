#include <iostream>
#include <iterator>
#include <algorithm>

// this syntax is pretty bizarre
// you can put any number you want in the brackets or none at all
// it's meaningless, it's just an odd syntax for a raw pointer
void pass_by_pointer_only( int values[12] ) {
    values[0] = 1;
}

int main() {
    int values[6] = {};

    // use subtle tricks to get the size of the array, brittle
    auto count = sizeof(values)/sizeof(values[0]);
    std::cout << count << std::endl;

    for ( int x : values ) { std::cout << x << ' '; }
    std::cout << std::endl;

    // you can't pass a raw array by value
    // this looks like a pass by value but it's actually a pass by pointer
    pass_by_pointer_only(values);

    for ( int x : values ) { std::cout << x << ' '; }
    std::cout << std::endl;

    // raw arrays are not assignable either
    int values2[6] = {};
    // values2 = values;

    // out of bounds access, no diagnostic in most cases
    // note: msvc does issue a warning here at compile time
    // however as isn't known at compile time all bets are off
    values[7] = 0xdeadbeef;
}
