#include <utility>
#include "miniboost/noncopyable.hpp"

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
	// Copy/Assignment
	//////////////////////////////////////////////////////////////////////////
    // you get a default copy constructor if you don't have any
    // but you need to define an assignment operator yourself
    RegularWidget& operator=( const RegularWidget & rhs ) {
        ordinal = rhs.ordinal;
        return *this;
    }

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
    void initialize() { /*do stuff*/ }
	int ordinal;
};

//////////////////////////////////////////////////////////////////////////
// Default functions #2
//////////////////////////////////////////////////////////////////////////
RegularWidget::RegularWidget() : ordinal( 0 ) {
    initialize();
}

//////////////////////////////////////////////////////////////////////////
// Delegating constructors
//////////////////////////////////////////////////////////////////////////
RegularWidget::RegularWidget(int ordinal_) {
	ordinal = ordinal_;
    // without delegating constructors you have to either repeat yourself
    // or factor the work into something like an initialize method which you
    // have to call from all constructors
    initialize();
}

class NonCopyableWidget : boost::noncopyable {
private:
    // to prevent copy/assignment you would declare but not define
    // a private copy constructor and assignment operator
    //
    // this usually prevents compilation with a rather obscure message
    // about trying to access private methods
    //
    // sometimes this would even compile and not give you an error until link
    NonCopyableWidget( const NonCopyableWidget& );
    NonCopyableWidget& operator=( const NonCopyableWidget& );
};

// alternatively you could use an private base class to remove the boilerplate
// and sometimes give you better error messages
class NonCopyableWidget2 : boost::noncopyable {
public:
};


int main() {
}
