#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>
struct thing_t {};

class widget;
widget* bar();
void foo( widget* );

bool is_even( int x ) { return (x & 1) == 0; }
bool is_odd( int x ) { return !is_even( x ); }

//////////////////////////////////////////////////////////////////////////
// Return type deduction
//////////////////////////////////////////////////////////////////////////
// the return type can be deduced by the compiler from the return statement
// a great help for complicated return types
// elegant if the return type is obvious or doesn't matter
// many widely-used languages never specify return types
auto add_five( int x ) {
    return x + 5;
}

int main() {
    // you're not allowed to know the name of a lambda, you can only store one with auto
    auto print_int = []( int x ) { std::cout << x << std::endl; };
    print_int( add_five( 1 ) );

    // auto follows the don't repeat yourself principle
    auto x = std::make_unique<thing_t>();


    //////////////////////////////////////////////////////////////////////////
    // Function chaining
    //////////////////////////////////////////////////////////////////////////
    // This is almost identical different
    auto w = bar();
    foo( w );


    std::vector<int> values{ 0,1,2,3,4,5 };
    values.erase( std::remove_if( begin( values ), end( values ), is_even ), end( values ) );
    // now it's a bit shorter, and will do the right thing if the type of values changes
    auto new_last = std::remove_if( begin( values ), end( values ), is_odd );
    values.erase( new_last, end( values ) );

    //////////////////////////////////////////////////////////////////////////
    // Variable definitions and literals
    //////////////////////////////////////////////////////////////////////////
    using namespace std::chrono_literals;
    using namespace std::string_literals;
    auto i = 0; // int (int32_t)
    auto u = 0u; // unsigned (uint32_t)
    auto u32 = uint32_t{ 0 }; // also acceptable
    auto ull = 0ull; // unsigned long long (uint64_t)
    auto f = 0.f; // float
    auto d = 0.; // double
    auto time = 33ms; // chrono::milliseconds{33}
    auto s = "hello world"s; // std::string
    auto c = 299'792'458; // int (speed of light in m/s2)
#ifdef BAD
    // avoid long types, on platform we care about they have different bit lengths
    // 32 bits on MSVC, 64 bits on clang/gcc
    auto l = 1l; // long should
    auto ul = 1ul; // unsigned long
#endif
    return 0;
}

widget* bar() { return nullptr; }
void foo( widget* ) {}

//////////////////////////////////////////////////////////////////////////
// Summary
//////////////////////////////////////////////////////////////////////////
/*
Almost Always Auto is the rule of thumb.

If the type is already said on the right hand side, use auto on the left. Don't repeat yourself.
If you don't care about the type, if it's just a token to pass from Foo to Bar, use auto.
If you're confused about the type, go ahead and spell it out.

Keep in mind auto prefers values to references. Watch out for unintended copies!
Refer back to the earlier talk "Abit About Auto" for more in depth.
*/