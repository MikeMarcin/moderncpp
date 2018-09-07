#include <iostream>
#include <vector>
#include <numeric>
#include <mutex>

class Widget {
public:
	//////////////////////////////////////////////////////////////////////////
	// Const qualifier
	//////////////////////////////////////////////////////////////////////////
	// overloading on const is typical
	// const is basically a promise to the reset of your program
	// this promise is important for reasoning about multi-threaded applications
	int value() const { return m_value; }
	int& value() { return m_value; }

	//////////////////////////////////////////////////////////////////////////
	// Ref qualifier
	//////////////////////////////////////////////////////////////////////////
	// ref qualifiers can present optimization opportunities
	// use sparingly, makes code more complicated
	const std::vector<int>& data() const & { return m_data;  }
	std::vector<int>& data() & { return m_data; }
	std::vector<int>&& data() && { return std::move(m_data); }

	//////////////////////////////////////////////////////////////////////////
	// Mutable
	//////////////////////////////////////////////////////////////////////////
	// if a cached value updated by const function make it mutable
	// is it ever possible for an instance of the type to be accessed from multiple threads concurrently?
	// then you must create an internal mutable mutex to guard access to cached value
	int sum() const { 
		std::lock_guard<std::mutex> _{m_cached_mutex};
		if (m_cached == -1) {
			m_cached = std::accumulate(begin(m_data), end(m_data), 0);
		}
		return m_cached;
	}

	//////////////////////////////////////////////////////////////////////////
	// Noexcept
	//////////////////////////////////////////////////////////////////////////
	// mark functions that cannot throw noexcept
	// this one is debatable, the upside is minor optimization
	// the downside for getting it wrong is immediate program termination
	int set_value(int v) noexcept { m_value = v; }
private:
	int m_value;
	std::vector<int> m_data;

	mutable std::mutex m_cached_mutex;
	mutable int m_cached = -1;

#ifdef BAD
	// volatile does not mean thread-safe!
	// this keyword is meant for things like reading hardware data ports that are memory mapped
	volatile int m_shared_int;
#endif
};

int main() {

}

//////////////////////////////////////////////////////////////////////////
// Summary
//////////////////////////////////////////////////////////////////////////
/*
thread-compatible (good/default): concurrent const ops safe, const + non-const op needs external synchronization (like int)
thread-safe (good/overhead): concurrent const and mutable operations safe (like atomic<int>)
thread-unsafe (mostly bad):

Changes to mutable data members from const functions should synchronized unless you can prove you don't need it.

consider noexcept for things that will never throw

Don't use volatile. It does not mean thread-safe.
*/
