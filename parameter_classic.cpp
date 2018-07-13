#include <iostream>
#include <vector>

//////////////////////////////////////////////////////////////////////////
// Heavy out types were passed by reference to out parameters
// returning a copy was too expensive
void heavy_result_type(std::vector<int>& out) {
	out.resize(100'000);
}

int main() {
	std::vector<int> results;
	heavy_result_type(results);
}
