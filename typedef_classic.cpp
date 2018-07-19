#include <iostream>
#include <vector>

// pretend this is cooler, maybe an arena allocator
template< typename T >
struct CoolAllocator : std::allocator<T> {};

//////////////////////////////////////////////////////////////////////////
// Template typedefs 1/2
//////////////////////////////////////////////////////////////////////////
template< typename T >
struct CoolVector {
    typedef std::vector<T,CoolAllocator<T> > type;
};

//////////////////////////////////////////////////////////////////////////
// C-style struct definition
//////////////////////////////////////////////////////////////////////////
typedef struct {
	int value;
} Foo;

// shhh, this should be PlayerId but we're
// cheating here to keep the typedef near the usage
void print_id( int pid ) {
    std::cout << pid << std::endl;
}

int main() {
    //////////////////////////////////////////////////////////////////////////
    // Simple typedefs
    //////////////////////////////////////////////////////////////////////////
    // typedef syntax is reverse of pretty much everything else in the language
    // the new type name is on the right
    typedef int PlayerId;
    typedef std::vector<PlayerId> PlayerIdContainer;
    PlayerId pid = 76;
    PlayerIdContainer players{ pid };

    //////////////////////////////////////////////////////////////////////////
    // Function pointer typedefs
    //////////////////////////////////////////////////////////////////////////
    // very unnatural syntax
    typedef void( *Callback )(PlayerId);
    Callback callback = &print_id;
    callback( pid );

    //////////////////////////////////////////////////////////////////////////
    // Template typedefs 2/2
    //////////////////////////////////////////////////////////////////////////
    // Emulated template typedefs are fugly
    CoolVector<PlayerId>::type coolPlayers{ pid };
    return 0;
}
