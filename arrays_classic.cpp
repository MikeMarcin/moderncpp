#include <iostream>

// this syntax is pretty bizarre
// you can put any number you want in the brackets or none at all
// it's meaningless, it's just an odd syntax for a raw pointer
void pass_by_value_is_pass_by_pointer( int values[9999] ) {
    values[0] = 1;
}

auto dangling_return_value() {
    // note here we use the one very nice feature std::array lacks
    // the ability to not have to specify the number of elements explicitly 
    int local_values[] = {0,1,2,3,4,5};
    return local_values;
}

int main() {
    //////////////////////////////////////////////////////////////////////////
    // Initialization
    //////////////////////////////////////////////////////////////////////////
    int values[6] = {};
    // values == {0, 0, 0, 0, 0, 0}

    //////////////////////////////////////////////////////////////////////////
    // Size
    //////////////////////////////////////////////////////////////////////////
    // use subtle tricks to get the size of the array, brittle
    auto count = sizeof(values)/sizeof(values[0]);
    // count == 6
    // note: in C++17 std::size(values) will also return the count
    
    //////////////////////////////////////////////////////////////////////////
    // Passing Arrays
    //////////////////////////////////////////////////////////////////////////
    // you can't pass a raw array by value
    // this looks like a pass by value but it's actually a pass by pointer
    pass_by_value_is_pass_by_pointer(values);
    // values == {1, 0, 0, 0, 0, 0}

    //////////////////////////////////////////////////////////////////////////
    // Assignment
    //////////////////////////////////////////////////////////////////////////
    // raw arrays are not assignable either
    int values2[6] = {};
#ifdef COMPILER_ERROR
    values2 = values;
#endif

    //////////////////////////////////////////////////////////////////////////
    // Array Return Values
    //////////////////////////////////////////////////////////////////////////
    // can't return an array from a function, just returns a dangling pointer to the local array
    auto values3 = dangling_return_value();

    //////////////////////////////////////////////////////////////////////////
    // Array Comparison
    //////////////////////////////////////////////////////////////////////////
    // comparison compares the pointer
    bool equal = values == values2; // false pointers don't match
    bool less = values < values2;   // technically undefined behavior I believe, but anyone's guess

    //////////////////////////////////////////////////////////////////////////
    // Debug Bounds Checking
    //////////////////////////////////////////////////////////////////////////
    // out of bounds access, no diagnostic in most cases
    // note: msvc does issue a warning here at compile time
    // however as isn't known at compile time all bets are off
    values[7] = 0xdeadbeef;
}
