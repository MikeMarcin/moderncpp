#include <utility>

class RegularWidget {
public:
	//////////////////////////////////////////////////////////////////////////
	// Constructors
	//////////////////////////////////////////////////////////////////////////
	// provide default constructors if possible
	RegularWidget();
	// mark explicit single argument constructors
	// or constructors with default parameters 
	// unless they are the copy/move constructor
	explicit RegularWidget(int ordinal);

	//////////////////////////////////////////////////////////////////////////
	// Copy/Assignment & Default functions
	//////////////////////////////////////////////////////////////////////////
	// prefer defaulted functions when possible
	RegularWidget(const RegularWidget&) = default;
	RegularWidget(RegularWidget&&) = default;
	RegularWidget& operator=(const RegularWidget &) = default;
	RegularWidget& operator=(RegularWidget &&) = default;

	//////////////////////////////////////////////////////////////////////////
	// Comparison operators
	//////////////////////////////////////////////////////////////////////////
#if HAS_CPP20
    // C++20 adds the spaceship operator! Also known as the three-way comparison operator
    // if you define operator<=> the compiler automatically generates operators
    // == , != , <, <= , >, and >= which are implemented in terms of <=>.
    //
    // If you define operator<=> as defaulted the compiler will generate a member-wise
    // comparison implementation for the three-way comparison operator.
    auto operator<=>(const Point&) const = default;
#else
    // until then, nothing has changed since c++98
	// base comparisons
	friend bool operator==(const RegularWidget& lhs, const RegularWidget& rhs)	{ return lhs.ordinal == rhs.ordinal;}
	friend bool operator<(const RegularWidget& lhs, const RegularWidget& rhs)	{ return lhs.ordinal < rhs.ordinal; }
	// derivative comparisons
	friend bool operator!=(const RegularWidget& lhs, const RegularWidget& rhs)	{ return !(lhs == rhs); }
	friend bool operator>(const RegularWidget& lhs, const RegularWidget& rhs)	{ return rhs < lhs; }
	friend bool operator<=(const RegularWidget& lhs, const RegularWidget& rhs)	{ return !(rhs < lhs); }
	friend bool operator>=(const RegularWidget& lhs, const RegularWidget& rhs)	{ return !(lhs < rhs); }
#endif

	//////////////////////////////////////////////////////////////////////////
	// Swap
	//////////////////////////////////////////////////////////////////////////
	// add swap if you can do better than the default std::swap
    // FOR ILLUSTRATION ONLY: this is not a case you would need to add a custom swap 
	void swap(RegularWidget& rhs)								{ std::swap(ordinal, rhs.ordinal); }
	friend void swap(RegularWidget& lhs, RegularWidget& rhs)	{ lhs.swap(rhs); }
private:
	// Use variable initialization as a shorthand to initialize your variables across all constructors
    // and often prevent needing to have explict constructor definitions at all
	int ordinal = 0;
};

//////////////////////////////////////////////////////////////////////////
// Default functions #2
//////////////////////////////////////////////////////////////////////////
// you can use =default in the source file, it doesn't have to be in the header
RegularWidget::RegularWidget() = default;

//////////////////////////////////////////////////////////////////////////
// Delegating constructors
//////////////////////////////////////////////////////////////////////////
// you can use delegating constructors to not repeat yourself
// just put all your common logic in one constructor, like the default constructor,
// and forward to it.
RegularWidget::RegularWidget(int ordinal_) : RegularWidget() {
    // if you use a delegating constructor it must be the only member initializer
    // GUIDELINE: 
    // provide full implementation for your highest arity constructor
    // and have the lower arity constructors forward to it (not shown here)
    ordinal = ordinal_;
}

//////////////////////////////////////////////////////////////////////////
// Deleted functions
//////////////////////////////////////////////////////////////////////////
class NonCopyableWidget {
public:
    NonCopyableWidget(const NonCopyableWidget&) = delete;
    NonCopyableWidget& operator=(const NonCopyableWidget &) = delete;
};


int main() {
}

//////////////////////////////////////////////////////////////////////////
// Summary
//////////////////////////////////////////////////////////////////////////
/*
Try to create complete and regular types.
Prefer to use deleted and defaulted functions
Use delegating constructors to avoid code duplication.
Implement all comparison operators variations in terms of < and ==.
*/