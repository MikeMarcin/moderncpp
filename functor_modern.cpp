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
};

ShapeType ShapeOfTheDay() { return  SHAPE_RHOMBUS; }

struct Dog {
	bool good = true;
};

struct Cat {
	bool good = false;
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

using NodeCallback = std::function<void(Node&)>;
void visit_r(Node* node, const std::function<void(Node&)>& callback) {
	if (node == nullptr) {
		return;
	}
	callback(*node);
	for (Node* child : node->children) {
		visit_r(child, callback);
	}
}

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
	// Data Captures
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

	//////////////////////////////////////////////////////////////////////////
	// Type Erased Functor
	//////////////////////////////////////////////////////////////////////////
	using NodeCallback = std::function<void(Node&)>;
	NodeCallback printId = [](Node& n) { std::cout <<  n.id << ' '; };
	visit_r(root, printId);
	std::cout << std::endl;
	int nodeCount = 0;
	NodeCallback countNodes = [&nodeCount](Node& ) { ++nodeCount; };
	visit_r(root, countNodes);
	std::cout << "node count: " << nodeCount << std::endl;

	//////////////////////////////////////////////////////////////////////////
	// Recursive Call
	//////////////////////////////////////////////////////////////////////////
	auto printId_r = [](Node& n)
    {
    	auto lambda = [](Node& n, const auto& lambda_r) -> void
    	{  
			std::cout << n.id << ' ';
			for (Node* child : n.children) {
				if (child != nullptr) {
					lambda_r(*child, lambda_r);
				}
			}
        };
        lambda(n, lambda);
    };
	printId_r(*root);
	std::cout << std::endl;

#if HAS_P0839
	// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/p0839r0.html
	auto printId_r = [&]visit(Node& n) -> void {
		std::cout << n.id << ' ';
		for (Node* child : n.children) {
			if (child != nullptr) {
				visit(*child);
			}
		}
	};
#endif
}


//////////////////////////////////////////////////////////////////////////
// Summary
//////////////////////////////////////////////////////////////////////////
/*
Lambdas provide a terse syntax for code you could already accomplish
*/