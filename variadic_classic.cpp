#include <iostream>
#include <stdarg.h> 

// no matter how hard you try a varargs function won't be inlined
__forceinline int sum_all_the_ints( int n, ... ) {
    va_list args;                     
    int sum = 0;

    // initialize args to store all input values after n
    va_start( args, n );
    // sum all the inputs; we still rely on the caller to tell us how many there are
    for ( int i = 0; i < n; ++i ) {
        sum += va_arg( args, int ); 
    }
    // cleanup args
    va_end ( args );

    return sum;;
}

int main() {
    // note: the first parameter has to tell us how many args to expect
    int sum = sum_all_the_ints( 6, 0, 1, 2, 3, 4, 5 );
    std::cout << sum << std::endl;
    return 0;
}
