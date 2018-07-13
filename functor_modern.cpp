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

int main() {
	std::vector<Shape> shapes{SHAPE_CIRCLE, SHAPE_SQUARE, SHAPE_CIRCLE, SHAPE_TRIANGLE, SHAPE_RHOMBUS};

	// notice how concise the lambda form is relative to the explicit functor class
	auto isCircle = [](auto& shape){ return shape.type == SHAPE_CIRCLE; };

	auto numCircles = std::count_if(begin(shapes), end(shapes), isCircle);
	std::cout << "There are " << numCircles << " circles" << std::endl;
	return 0;
}


//////////////////////////////////////////////////////////////////////////
// Summary
//////////////////////////////////////////////////////////////////////////
/*
Lambdas provide a terse syntax for code you could already accomplish
*/