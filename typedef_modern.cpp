#include <iostream>
#include <vector>

// pretend this is cooler, maybe an arena allocator
template< typename T >
struct CoolAllocator : std::allocator<T> {};

template<typename T>
using CoolVector = std::vector<T, CoolAllocator<T>>;

int main() {
    //////////////////////////////////////////////////////////////////////////
    // Simple typedefs
    //////////////////////////////////////////////////////////////////////////
    // using syntax restores order to the universe
    // the new type name is on the left (where it should be)
    using PlayerId = int;
    using PlayerIdContainer = std::vector<PlayerId>;
    PlayerId pid = 76;
    PlayerIdContainer players{ pid };

    //////////////////////////////////////////////////////////////////////////
    // Function pointer typedefs
    //////////////////////////////////////////////////////////////////////////
    using Callback = void( *)(PlayerId);
    Callback callback = []( PlayerId pid ) {
        std::cout << pid << std::endl;
    };
    callback( pid );

    //////////////////////////////////////////////////////////////////////////
    // Template typedefs
    //////////////////////////////////////////////////////////////////////////
    // Using gives natural template typedef syntax
    CoolVector<PlayerId> coolPlayers{ pid };
    return 0;
}

//////////////////////////////////////////////////////////////////////////
// Summary
//////////////////////////////////////////////////////////////////////////
/*
Using is more powerful and has a more natural syntax.
I know of no reason to use typedef anymore.
*/