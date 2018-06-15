#include <vector>

struct thing_t {};

int main() {
    //////////////////////////////////////////////////////////////////////////
    // Allocation
    //////////////////////////////////////////////////////////////////////////
    // old style allocates with raw new
    thing_t* thing = new thing_t{};

#ifdef BAD
    // auto_ptr tried to solve the same problem as unique_ptr but wasn't able to
    // it's a misfeature; deprecated in C++11, removed in C++17
    std::auto_ptr<thing_t*> thing2( new thing_t{} );
#endif

    // thing_array and thing look identical
    // easy to mistake a single thing for an array of things
    thing_t* thing_array = new thing_t[6];
    // access the first element of the thing array
    thing_array[0];

    // ownership is *not* clear from declaration, must carefully study usage
    std::vector<thing_t*> many_things;
    
    for ( int i = 0; i < 100; ++i ) {
        many_things.push_back( new thing_t{} );
    }

    //////////////////////////////////////////////////////////////////////////
    // Array Access
    //////////////////////////////////////////////////////////////////////////
    thing_array[0];

    //////////////////////////////////////////////////////////////////////////
    // Exception Safety
    //////////////////////////////////////////////////////////////////////////
    // very difficult to achieve basic exception safety without RAII
    void function_that_may_throw();
    try {
        
        function_that_may_throw();
    } catch ( ... ) {
        // good luck not leaking memory on a thrown exception
        // in fact all of this code is riddled with exception unsafety
        throw;
    }

    //////////////////////////////////////////////////////////////////////////
    // Passing Pointers
    //////////////////////////////////////////////////////////////////////////
    // cannot distinguish transfer of ownership from simple usage at declaration
    // or at call site without thorough study of implementation
    void use_but_dont_store( thing_t* );
    use_but_dont_store( thing );

    void take_ownership( thing_t* );
    take_ownership( thing );

    //////////////////////////////////////////////////////////////////////////
    // Shared Ownership
    //////////////////////////////////////////////////////////////////////////
    // difficult to express and implement these concepts without modern tools
    void share_ownership( thing_t* );
    void store_without_ownership( thing_t* );

    //////////////////////////////////////////////////////////////////////////
    // Cleanup
    //////////////////////////////////////////////////////////////////////////
    // remember to clean everything up!

    // generally clean-up should happen in the reverse creation order
    // a thing constructed second could have a reference to a thing constructed first
    // keep track of this order manually
    for ( thing_t* x : many_things ) {
        delete x;
    }
    many_things.clear();

    // remember to call the array version of delete
    delete[] thing_array;

    // remember to delete your thing when you're done with it
    delete thing;
    // OOOPS! thing was passed to take_ownership above
    // we've now either double deleted thing or deleted it out from under someone
}

void function_that_may_throw() {}
void use_but_dont_store( thing_t* x ) {}
void take_ownership( thing_t* x ) {}

