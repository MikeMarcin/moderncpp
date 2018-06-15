// show some unique_ptrs
// pass some unique_ptrs around by raw ptr
// show some shared_ptr
// show some weak_ptr

#include <vector>
#include <memory>


struct thing_t {};
std::shared_ptr<thing_t> g_thing;


void use_but_dont_store( thing_t* );
void use_but_dont_store( thing_t& x );
void take_ownership( std::unique_ptr<thing_t> store_this );

int main() {
    //////////////////////////////////////////////////////////////////////////
    // Allocation
    //////////////////////////////////////////////////////////////////////////
    // new style: avoid raw new, wrap pointer ownership in smart pointers
    auto thing = std::make_unique<thing_t>(); // unique_ptr since C++11, make_unique since C++14
#ifdef NO_CPP14
    // if you don't have make_unique you can use this instead
    std::unique_ptr<thing_t> thing2( new thing_t{} );
#endif

    auto thing_array = std::make_unique<thing_t[]>(6);
    // note: this is not bounds checked
    // it does *not* store how many elements are in this array

    // ownership is clear from the type
    std::vector<std::unique_ptr<thing_t>> many_things;
    for ( int i = 0; i < 100; ++i ) {
        many_things.push_back( std::make_unique<thing_t>() );
    }

#ifdef BAD
    // note: do *not* do this
    // it will leak if vector fails to realloc
    many_things.emplace_back( new thing_t{} );
#endif

    //////////////////////////////////////////////////////////////////////////
    // Array Access
    //////////////////////////////////////////////////////////////////////////
    // unique_ptr to an array has an operator[]
    thing_array[0];

    //////////////////////////////////////////////////////////////////////////
    // Exception Safety
    //////////////////////////////////////////////////////////////////////////
    // don't need to write try-catch,
    // smart pointers give basic exception safety automatically
    void function_that_may_throw();
    function_that_may_throw();


    //////////////////////////////////////////////////////////////////////////
    // Passing Pointers
    //////////////////////////////////////////////////////////////////////////
    // prefer passing by raw reference or raw pointer to functions that need to use the object
    // but don't need ownership and won't store a reference beyond the scope of the function
    void use_but_dont_store( thing_t* );
    void use_but_dont_store( thing_t& );
    use_but_dont_store(*thing);

#ifdef BAD
    // const unique_ptr& is an oxymoron
    void use_but_dont_store( const std::unique_ptr<thing_t>& x );
#endif

    //////////////////////////////////////////////////////////////////////////
    // easy to see we're transferring ownership here
    // consistent usage of raw pointer/reference for non-ownership makes code easy to understand
    void take_ownership( std::unique_ptr<thing_t> store_this );
    // pass by value with std::move to transfer ownership
    take_ownership(std::move(thing));

    //////////////////////////////////////////////////////////////////////////
    // Shared Ownership
    //////////////////////////////////////////////////////////////////////////
    // if you're going to share ownership use a shared_ptr (probably)
    // good designs involving shared ownership are rare, look for alternatives

    // prefer make_shared to separate new and shared_ptr construction in most cases
    // make_shared does one allocation containing the object and the reference count
    // new + shared_ptr construction requires 2 allocations (new the object and allocate the ref count)
    auto shared_thing = std::make_shared<thing_t>();

#ifdef EXCEPTION_TO_RULE
    // if your object is big and you expect weak_ptrs to greatly outlive the shared_ptr
    // you might want to separate the allocations
    auto shared_thing2 = std::shared_ptr<thing_t>( new thing_t{} );
#endif

    // one las thing, if you're going to use a shared_ptr that might get released
    std::shared_ptr<thing_t> pinned_thing = g_thing;
    use_but_dont_store( pinned_thing.get() );

    // if you're going to share ownership use a shared_ptr (probably)
    // good designs involving shared ownership are rare, look for alternatives
    void share_ownership( std::shared_ptr<thing_t> );
    share_ownership( pinned_thing );

    //////////////////////////////////////////////////////////////////////////
    // Cleanup
    //////////////////////////////////////////////////////////////////////////
    // all cleanup happens automatically in proper reverse order of creation
    // because destructors are invoked when the smart pointers go out of scope 


    //////////////////////////////////////////////////////////////////////////
    // Bonus
    //////////////////////////////////////////////////////////////////////////
    // Use unique_ptr with custom deleter for other pointer-like resource types too
    struct file_deleter {
        void operator()( FILE* f ) { fclose(f); }
    };
    std::unique_ptr<FILE, file_deleter> file( fopen( "temp.txt", "a" ) );

#ifdef AVOID
    // avoid this form, while it will function correctly it will not be zero-overhead
    // this deleter is a function pointer that will be stored in the unique_ptr
    // the prior version will use empty base optimization (EBO) achieve zero overhead
    std::unique_ptr<FILE, int( *)(FILE*)> file2( fopen( "temp2.txt", "a" ), &fclose );
#endif

}

void function_that_may_throw() {}
void use_but_dont_store( thing_t* ) {}
void use_but_dont_store( thing_t& ) {}
void take_ownership( std::unique_ptr<thing_t> store_this ) {}

void share_ownership( std::shared_ptr<thing_t> store_this ) {}

// if you're storing a reference without wanting ownership, store a weak_ptr
// if you're just storing and not using, pass a weak_ptr directly
// if you're going to use 
void store_without_ownership( std::shared_ptr<thing_t> x ) {
    std::weak_ptr<thing_t> store_this{ x };
}


//////////////////////////////////////////////////////////////////////////
// SUMMARY
//////////////////////////////////////////////////////////////////////////
/*
As we will see, an essential best practice for any reference-counted smart pointer type
is to avoid copying it unless you really mean to add a new reference. This cannot be stressed enough.
This directly addresses both of these costs and pushes their performance impact down into the noise 
for most applications, and especially eliminates the second cost because 
it is an antipattern to add and remove references in tight loops.
-- Herb Sutter GOTW 91


In late 2013 Facebook RocksDB changed from pass-by-value shared_ptr to pass-by-pointer/ref
Queries per second improved 4x( 100k -> 400k ) in one benchmark
https://github.com/facebook/rocksdb/commit/5b825d6964e26ec3b4bb6faa708ebb1787f1d7bd

Write make_unique by default (or make_shared if you need ref count) instead of new / malloc delete / free.
- Don't use owning raw *, new, or delete any more, except rarely inside the implementation details of low-level data structures.
- Do use non - owning raw * and &, especially for parameters.
- Don't copy/assign refcounted smart pointers, including pass-by-value or in loops, unless you really want the semantics they express: altering object lifetime.
- Pin a non - local shared_ptr by making one copy at the top of the tree( pay for addref once ), then pass by raw pointer / reference
*/