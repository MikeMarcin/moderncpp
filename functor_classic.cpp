#include <iostream>
#include <vector>
#include <algorithm>

enum ShapeType {
	SHAPE_CIRCLE,
	SHAPE_SQUARE,
	SHAPE_TRIANGLE,
	SHAPE_RHOMBUS
};

struct Shape {
	// Not explicit for illustrative purposes only, not a good pattern
	Shape(ShapeType type_) : type(type_) {}
	ShapeType type;
};

ShapeType ShapeOfTheDay() { return  SHAPE_RHOMBUS; }

struct Dog {
	bool good = true;
};

struct Cat {
	bool good = false;
};

//////////////////////////////////////////////////////////////////////////
// Functor 1/2
//////////////////////////////////////////////////////////////////////////
// writing functors involves a lot of uninteresting boilerplate
class IsCircle {
public:
	bool operator()(const Shape& shape) const {
		return shape.type == SHAPE_CIRCLE;
	}
};

class IsShapeType {
public:
	IsShapeType(ShapeType type_) : type(type_) {}
	bool operator()( const Shape& shape ) const {
		return shape.type == type;
	}
private:
	ShapeType type;
};

//////////////////////////////////////////////////////////////////////////
// Generic Functor 1/2
//////////////////////////////////////////////////////////////////////////
class IsGood {
public:
	template< typename T >
	bool operator()( const T& x ) const {
		return x.good;
	}
};


int main() {
	std::vector<Shape> shapes{SHAPE_CIRCLE, SHAPE_SQUARE, SHAPE_CIRCLE, SHAPE_TRIANGLE, SHAPE_RHOMBUS};

	//////////////////////////////////////////////////////////////////////////
	// Functor 2/2
	//////////////////////////////////////////////////////////////////////////
	auto numCircles = std::count_if(begin(shapes), end(shapes), IsCircle{});
	std::cout << "There are " << numCircles << " circles" << std::endl;

	// functors with variables
	auto numShapeOfTheDay = std::count_if(begin(shapes), end(shapes), IsShapeType{ShapeOfTheDay()});
	std::cout << "There are " << numShapeOfTheDay << " shapes of the day" << std::endl;

	//////////////////////////////////////////////////////////////////////////
	// Generic Functor 2/2
	//////////////////////////////////////////////////////////////////////////
	auto isGood = IsGood{};
	Dog dog;
	Cat cat;
	std::cout << "Dog is good? " << isGood(dog) << std::endl;
	std::cout << "Cat is good? " << isGood(cat) << std::endl;
}
