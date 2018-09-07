#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <array>

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

	bool IsType(ShapeType type_) const { return type == type_; }
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

struct Node {
	std::array<Node*, 2> children;
	int id = -1;
};

Node* BuildTree_r( Node* node, int id, int size) {
	node->id = id;
	if (size == 0) {
		node->children.fill(nullptr);
	} else if (size == 1) {
		node->children[0] = BuildTree_r(node + 1, id + 1, 0);
		node->children[1] = nullptr;
	} else {
		auto rhalf = (size / 2);
		auto lhalf = size - rhalf;
		node->children[0] = BuildTree_r(node + 1, id + 1, lhalf - 1);
		node->children[1] = BuildTree_r(node + 1 + lhalf, id + 1 + lhalf, rhalf - 1);
	}
	return node;
}

Node* BuildTree() {
	static std::vector<Node> nodes;
	nodes.resize(14);
	
	return BuildTree_r(nodes.data(), 0, static_cast<int>(nodes.size()) - 1);
}
Node* root = BuildTree();

class NodeCallback {
public:
	virtual void operator()(Node& n) = 0;
};

void visit_r(Node* node, NodeCallback& callback) {
	if (node == nullptr) {
		return;
	}
	callback(*node);
	for (Node* child : node->children) {
		visit_r(child, callback);
	}
}

//////////////////////////////////////////////////////////////////////////
// Recursive Call 1/2
//////////////////////////////////////////////////////////////////////////
void PrintId_r(Node& n) {
	std::cout << n.id << ' ';
	for (Node* child : n.children) {
		if (child != nullptr) {
			PrintId_r(*child);
		}
	}
}

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

	//////////////////////////////////////////////////////////////////////////
	// Data Captures
	//////////////////////////////////////////////////////////////////////////
	// curry data with your functor by creating a function object that stores the data
	auto numShapeOfTheDay = std::count_if(begin(shapes), end(shapes), IsShapeType{ShapeOfTheDay()});
	std::cout << "There are " << numShapeOfTheDay << " shapes of the day" << std::endl;

	// or using bind to build a function object
	using namespace std::placeholders;
	auto numShapesOfTheDay2 = std::count_if(begin(shapes), end(shapes), std::bind(&Shape::IsType, _1, ShapeOfTheDay()));

	//////////////////////////////////////////////////////////////////////////
	// Generic Functor 2/2
	//////////////////////////////////////////////////////////////////////////
	auto isGood = IsGood{};
	Dog dog;
	Cat cat;
	std::cout << "Dog is good? " << isGood(dog) << std::endl;
	std::cout << "Cat is good? " << isGood(cat) << std::endl;

	//////////////////////////////////////////////////////////////////////////
	// Type Erased Functor
	//////////////////////////////////////////////////////////////////////////
	class PrintId : public NodeCallback {
	public:
		void operator()(Node& n) override {
			std::cout << n.id << ' ';
		}
	};
	PrintId printId;
	visit_r(root, printId);
	std::cout << std::endl;

	class CountNodes : public NodeCallback {
	public:
		void operator()(Node& n) override {
			++count;
		}
		int count = 0;
	};
	CountNodes countNodes;
	visit_r(root, countNodes);
	std::cout << "node count: " << countNodes.count << std::endl;

	//////////////////////////////////////////////////////////////////////////
	// Recursive Call 2/2
	//////////////////////////////////////////////////////////////////////////
	PrintId_r(*root);
	std::cout << std::endl;
}
