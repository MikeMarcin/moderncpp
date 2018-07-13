#include <iostream>
#include <vector>
#include <algorithm>

//////////////////////////////////////////////////////////////////////////
// Many types that are expensive to copy are cheap to move.
// Return these types directly from the function.
// Note: this is an implicit move, not a copy.
std::vector<int> heavy_result_type() {
	std::vector<int> results;
	results.resize(100'000);
	return results;
}

//////////////////////////////////////////////////////////////////////////
// Minor variations
//////////////////////////////////////////////////////////////////////////
// Make lots of little variation on your functions and give them good names
// When it makes the calling code more readable.
template< class InputIt, class Value >
bool any_equal(InputIt f, InputIt l, const Value& v) {
	return std::find(f, l, v) != l;
}

template< class InputIt, class Value >
bool none_equal(InputIt f, InputIt l, const Value& v) {
	return std::find(f, l, v) == l;
}

template< class InputIt, class Value >
bool all_equal(InputIt f, InputIt l, const Value& v) {
	return std::all_of(f, l, [&v](auto&& x){ return x == v; });
}

//////////////////////////////////////////////////////////////////////////
// Overload sets
//////////////////////////////////////////////////////////////////////////
// Create overloads for simple things where the reader should not need to care which version is being called
// Overload sets should be able to be documented with one comment for the entire set of functions
template< class Range, class Value > 
bool any_equal(Range&& r, const Value& v) {
	// illustrative purposes only, Range template parameter should be appropriately constrained
	return any_equal(begin(r), end(r), v);
}

template< class Range, class Value >
bool none_equal(Range&& r, const Value& v) {
	return none_equal(begin(r), end(r), v);
}

template< class Range, class Value >
bool all_equal(Range&& r, const Value& v) {
	return all_equal(begin(r), end(r), v);
}


int main() {
	auto results = heavy_result_type();

	bool allZero = all_equal(results, 0);
	return 0;
}


//////////////////////////////////////////////////////////////////////////
// Summary
//////////////////////////////////////////////////////////////////////////
/*
Prefer pass-by-value and return value.
Pass-by-reference for in-out parameters.
Pass-by-reference for expensive to move out parameters. (e.g. array<BigFoo>)
Pass-by-value for cheap to copy or impossible to copy.
Pass-by-const ref for don't know
When optimization matters consider adding pass-by-rvalue ref overloads or perfect forwarding


Make lots of little variations on your functions and give them good names.

Use overloaded functions (including constructors) only if a reader looking at a call site can get a
good idea of what is happening without having to first figure out exactly which overload is being called.
-- Google C++ Style Guide



Explain lifetime requirements in comments if they extend beyond the function call.
Example 1: storing a non-owning reference to an object
Example 2: asynchronous calls
*/
