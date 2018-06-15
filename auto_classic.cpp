#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

struct thing_t {};

class widget;
widget* bar();
void foo(widget*);

bool is_even(int x) { return (x & 1) == 0; }
bool is_odd( int x ) { return !is_even(x); }

int main() {
    // look how many times we have to say the same thing
    std::unique_ptr<thing_t> x = std::unique_ptr<thing_t>( new thing_t );

    //////////////////////////////////////////////////////////////////////////
    // Function chaining
    //////////////////////////////////////////////////////////////////////////
    // here we use the return type of bar without an explict type name
    // seemingly no one has a problem with this
    foo( bar() );

    std::vector<int> values{ 0,1,2,3,4,5 };
    // sometimes chained function invocations get long and we want to break it up for readability,
    // but this often requires spelling out verbose types
    values.erase( std::remove_if( begin( values ), end( values ), is_even ), end( values ) );
    // notice how this intermediate line is even longer than the line that we thought was too long
    std::vector<int>::iterator new_last = std::remove_if( begin( values ), end( values ), is_odd );
    values.erase( new_last, end( values ) );

    

    return 0;
}

widget* bar() { return nullptr; }
void foo( widget* ) {}
