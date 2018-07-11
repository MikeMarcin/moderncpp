#include <iostream>
#include <array>
#include <vector>

#define HAS_CPP17 1

//////////////////////////////////////////////////////////////////////////
// Accumulate
//////////////////////////////////////////////////////////////////////////
#if HAS_CPP17
template<typename... Args>
constexpr inline int sum_all_the_ints( Args... args ) {
    // fold expression make working with variadic templates much easier
    return (args + ...);
}
#else
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


//////////////////////////////////////////////////////////////////////////
// Reuse
//////////////////////////////////////////////////////////////////////////

template<typename... Args>
inline int print_once( char* text, size_t length, const char* format, Args... args ) {
    int n = snprintf( text, length, format, args... );
    return n;
}


template<typename... Args>
inline int print_twice( char* text, size_t length, const char* format, Args... args ) {
    int n = print_once( text, length, format, args... );
    if ( n < length ) {
        n += print_once( text + n, length - n, format, args... );
    }
    return n;
}

//////////////////////////////////////////////////////////////////////////
// for_each_argument
//////////////////////////////////////////////////////////////////////////
#if HAS_CPP17
template<typename F, typename... Args>
void for_each_argument(F f, Args&&... args) {
   (f(std::forward<Args>(args)), ...);
}
#else
template<typename F, typename... Args>
void for_each_argument(F f, Args&&... args) {
    // there's an entire cppcon talk on how this lie of code works if you want to know
    // CppCon 2015: Vittorio Romeo "`for_each_argument` explained and expanded"
    // https://www.youtube.com/watch?v=2l83JlqkzBk

    using A = int[sizeof...(Args)];
    (void)A{(f(std::forward<Args>(args)), 0)...};
}
#endif

//////////////////////////////////////////////////////////////////////////
// Forwarding
//////////////////////////////////////////////////////////////////////////

// Sometimes you just want to pass a bunch of arguments along without knowing or caring what
// or even how many there are. Especially if you're writing generic library code that needs to
// handle all permutations of CV-qualified l/r-values variadic templates with std::forward can help.

// This example is a thin wrapper around placement new that demonstrates "perfect forwarding"
template< typename T, typename... Args >
void construct( T* p, Args&&... args ) {
    new (p) T( std::forward<Args>( args )... );
}


int main() {
    //////////////////////////////////////////////////////////////////////////
    // we no longer have to tell the function how many values to expect
    // also note this will inline easily
    constexpr int sum = sum_all_the_ints( 0, 1, 2, 3, 4, 5 );
    std::cout << sum << std::endl;

    // in fact not only can it be inlined it can be guaranteed to be evaluated
    // fully at compile time as long as all the parameters compile-time constant,
    // thus you can use the result of the algorithm as a compile-time constant, 
    // for instance the sum can be a size template parameter to a std::array
    std::array<int, sum> values = {};


    //////////////////////////////////////////////////////////////////////////
    char text[256];
    print_twice( text, std::size( text ), "%s %s \n", "hello", "world" );
    std::cout << text << std::endl;


    //////////////////////////////////////////////////////////////////////////
    auto print_thing = []( auto&& x ) { std::cout << x << std::endl; };
    for_each_argument( print_thing );
    for_each_argument( print_thing, "one", 2, 3, "four", '5', 6.7, "eight" );
    return 0;
}


//////////////////////////////////////////////////////////////////////////
// Summary
//////////////////////////////////////////////////////////////////////////
// the most common use cases for variable arguments are
//  - string formatting 
//  - template meta-programming
//  - forwarding arguments
//
// string formatting I recommend just grabbing an existing optimized library like fmt
// template meta-programming is a tool for experts and library writers, we don't do much of this
// forwarding arguments is still mostly the domain of library writers but may sometimes come up
// 
