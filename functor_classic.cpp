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

// writing functors often involves a lot of uninteresting boilerplate
class IsShapeType {
public:
	IsShapeType(ShapeType type_) : type(type_) {}
	bool operator()( const Shape& shape ) const {
		return shape.type == type;
	}
private:
	ShapeType type;
};

int main() {
	std::vector<Shape> shapes{SHAPE_CIRCLE, SHAPE_SQUARE, SHAPE_CIRCLE, SHAPE_TRIANGLE, SHAPE_RHOMBUS};

	auto numCircles = std::count_if(begin(shapes), end(shapes), IsShapeType{SHAPE_CIRCLE});
	std::cout << "There are " << numCircles << " circles" << std::endl;
	return 0;
}
