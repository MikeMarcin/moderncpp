#include <iostream>

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
	// Default functions
	//////////////////////////////////////////////////////////////////////////
	// prefer defaulted functions when possible
	RegularWidget(const RegularWidget&) = default;
	RegularWidget(RegularWidget&&) = default;
	RegularWidget& operator=(const RegularWidget &) = default;
	RegularWidget& operator=(RegularWidget &&) = default;

	//////////////////////////////////////////////////////////////////////////
	// Comparison operators
	//////////////////////////////////////////////////////////////////////////
	// base comparisons
	friend bool operator==(const RegularWidget& lhs, const RegularWidget& rhs)	{ return lhs.ordinal == rhs.ordinal;}
	friend bool operator<(const RegularWidget& lhs, const RegularWidget& rhs)	{ return lhs.ordinal < rhs.ordinal; }
	// derivative comparisons
	friend bool operator!=(const RegularWidget& lhs, const RegularWidget& rhs)	{ return !(lhs == rhs); }
	friend bool operator>(const RegularWidget& lhs, const RegularWidget& rhs)	{ return rhs < lhs; }
	friend bool operator<=(const RegularWidget& lhs, const RegularWidget& rhs)	{ return !(rhs < lhs); }
	friend bool operator>=(const RegularWidget& lhs, const RegularWidget& rhs)	{ return !(lhs < rhs); }

	//////////////////////////////////////////////////////////////////////////
	// Swap
	//////////////////////////////////////////////////////////////////////////
	// add swap if you can do better than the default std::swap
	// NOTE: this is not a case you would need to add a custom swap for
	// illustrate only
	void swap(RegularWidget& rhs)								{ std::swap(ordinal, rhs.ordinal); }
	friend void swap(RegularWidget& lhs, RegularWidget& rhs)	{ lhs.swap(rhs); }
private:
	// Use variable initialization
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
RegularWidget::RegularWidget(int ordinal_) : RegularWidget() {
	ordinal = ordinal_;
}

class NonCopyableType {
public:
	//////////////////////////////////////////////////////////////////////////
	// Deleted functions
	//////////////////////////////////////////////////////////////////////////
	NonCopyableType(const NonCopyableType&) = delete;
	NonCopyableType& operator=(const NonCopyableType &) = delete;
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