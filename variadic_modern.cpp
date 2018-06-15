#include <iostream>
#include <array>

template<typename... Args>
constexpr inline int sum_all_the_ints( Args... args ) {
    // fold expression make working with variadic templates much easier
    return (args + ...);
}

#ifdef NO_CPP17
// The base case: we just have a single number.
inline int sum_all_the_ints( int x ) {
    return x;
}

// The recursive case: we take a number, alongside
// some other numbers, and produce their sum.
template <typename... Rest>
inline int sum_all_the_ints( int x, Rest... rest ) {
    return x + sum_all_the_ints( rest... );
}
#endif


int main() {
    // we no longer have to tell the function how many values to expect
    // also note this will inline easily
    constexpr int sum = sum_all_the_ints( 0, 1, 2, 3, 4, 5 );
    std::cout << sum << std::endl;

    // in fact not only can it be inlined it can be guaranteed to be evaluated
    // fully at compile time as long as all the parameters compile-time constant,
    // thus you can use the result of the algorithm as a compile-time constant, 
    // for instance the sum can be a size template parameter to a std::array
    std::array<int, sum> values = {};
    return 0;
}



//////////////////////////////////////////////////////////////////////////
// Bonus
//////////////////////////////////////////////////////////////////////////
// the most common use cases for variable arguments are
//  - string formatting 
//  - template meta-programming
//  - forwarding arguments
// string formatting I recommend just grabbing an existing optimized library like fmt
// template meta-programming is a tool for experts and library writers, we don't do much of this
// forwarding arguments is still mostly the domain of library writers but may sometimes come up
// 
// here's an function example from some real code that takes an uninitialized array of Ts
// and calls placement new forwarding all args to each constructor
template< typename T, typename... Args >
void construct_n( T* p, std::size_t n, Args&&... args ) {
    for ( ; n > 0; ++p, (void)--n ) {
        // WARNING!
        // looking at this again this is in fact likely wrong, an rvalue will be passed
        // multiple times and if the T constructor moves from it, bad things will happen
        new (p) T( std::forward<Args>( args )... );
    }
}
