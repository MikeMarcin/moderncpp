#include <iostream>
#include <stdarg.h> 


//////////////////////////////////////////////////////////////////////////
// Accumulate
//////////////////////////////////////////////////////////////////////////

// note: no matter how hard you try a varargs function won't be inlined
__forceinline int sum_all_the_ints( int n, ... ) {
    
    va_list args;                     
    int sum = 0;

    // initialize args to store all input values after n (the last fixed argument)
    // on all implementations we care about this essentially gets the pointer to n on the stack
    // and moves the pointer by sizeof(n)
    va_start( args, n );
    // sum all the inputs; we still rely on the caller to tell us how many there are
    for ( int i = 0; i < n; ++i ) {
        // no type safety, the user better have passed us an int
        // this very strange function-like macro takes a type name as the second parameter
        // and its 'return value' is of the same type as the second argument
        // it also advanced the args list pointer by the size of the second argument
        sum += va_arg( args, int ); 

        //////////////////////////////////////////////////////////////////////////
        // !!! BEWARE !!!
        //////////////////////////////////////////////////////////////////////////
        // When a function with a variable-length argument list is called, the variable arguments
        // are passed using C's old 'default argument promotions.'
        // These say that types  char and short int are automatically promoted to int,
        // and type float is automatically promoted to double.
        // Therefore, varargs functions will never receive arguments of type char, short int, or float.
        // Furthermore, it's an error to 'pass' the type names char, short int, or float
        // as the second argument to the va_arg() macro.
        // Finally, for vaguely related reasons, the last fixed argumen
        // (the one whose name is passed as the second argument to the va_start() macro) 
        // should not be of type char, short int, or float, either.
        // see: https://www.eskimo.com/~scs/cclass/int/sx11c.html

    }
    // cleanup args
    va_end( args );

    return sum;
}

//////////////////////////////////////////////////////////////////////////
// Reuse
//////////////////////////////////////////////////////////////////////////

__forceinline int print_once( char* text, size_t length, const char* format, ... ) {
    va_list args;
    va_start( args, format );
    int n = vsnprintf( text, length, format, args );
    va_end( args );
    return n;
}

// you usually must create versions of your functions which take a va_list instead of a ... as well
// this allows you to compose vararg functions as we shall see in shortly
__forceinline int vprint_once( char* text, size_t length, const char* format, va_list va ) {
    va_list args;
    // note: instead of va_start here or just using the passed in va_list directly we must
    // va_copy it into a local va_list, on most platforms using the argument 'va' directly here
    // will appear to work correctly because the implementation stores pointers to the stack
    // but this isn't necessary and some implementations store offsets to the stack instead
    // va_copy is simple direct pointer assignment on the former platform and a fix-up on the latter.
    // there could be other implementations because none of the details are specified by the standard
    va_copy( args, va );
    int n = vsnprintf( text, length, format, args );
    va_end( args );
    return n;
}

__forceinline int print_twice( char* text, size_t length, const char* format, ... ) {
    va_list args;
    va_start( args, format );
    // here finally we get to reuse our var args to format the same string twice
    int n = vprint_once( text, length, format, args );
    if ( n < length ) {
        n += vprint_once( text + n, length - n, format, args );
    }
    va_end( args );
    return n;
}

int main() {
    //////////////////////////////////////////////////////////////////////////
    // note: the first parameter has to tell us how many args to expect
    // no diagnostic if you get it wrong, just likely undefined behavior
    int sum = sum_all_the_ints( 6, 0, 1, 2, 3, 4, 5 );
    std::cout << sum << std::endl;

    
    //////////////////////////////////////////////////////////////////////////
    char text[256];
    print_twice( text, std::size(text), "%s %s \n", "hello", "world" );
    std::cout << text << std::endl;


    //////////////////////////////////////////////////////////////////////////
    return 0;
}
