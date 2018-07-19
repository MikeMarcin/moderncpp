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


int main() {
	std::vector<Shape> shapes{SHAPE_CIRCLE, SHAPE_SQUARE, SHAPE_CIRCLE, SHAPE_TRIANGLE, SHAPE_RHOMBUS};

	//////////////////////////////////////////////////////////////////////////
	// Lambda
	//////////////////////////////////////////////////////////////////////////
	// notice how concise the lambda form is relative to the explicit functor class
	auto isCircle = [](const Shape& shape) { return shape.type == SHAPE_CIRCLE; };
	auto numCircles = std::count_if(begin(shapes), end(shapes), isCircle);
	std::cout << "There are " << numCircles << " circles" << std::endl;

	//////////////////////////////////////////////////////////////////////////
	// Lambda Captures
	//////////////////////////////////////////////////////////////////////////
	auto isShapeOfTheDay = [shapeOfTheDay = ShapeOfTheDay()](const Shape& shape) { return shape.type == shapeOfTheDay; };
	auto numShapeOfTheDay = std::count_if(begin(shapes), end(shapes), isShapeOfTheDay);
	std::cout << "There are " << numShapeOfTheDay << " shapes of the day" << std::endl;

	//////////////////////////////////////////////////////////////////////////
	// Generic Lambda
	//////////////////////////////////////////////////////////////////////////
	auto isGood = [](const auto& x){  return x.good; };
	Dog dog;
	Cat cat;
	std::cout << "Dog is good? " << isGood(dog) << std::endl;
	std::cout << "Cat is good? " << isGood(cat) << std::endl;
}


//////////////////////////////////////////////////////////////////////////
// Summary
//////////////////////////////////////////////////////////////////////////
/*
Lambdas provide a terse syntax for code you could already accomplish
*/