#include <iostream>
#include"Simplex.h"

int main() {
	int NumberOfX;
	std::vector<SimplexTable> _simplexTable;

	std::cout << "define number of variables" << std::endl;
	std::cin >> NumberOfX;


	if (NumberOfX < 1) {
		std::cout << "wrong number" << std::endl;
		return -1;
	}
	_simplexTable.push_back(*new SimplexTable(NumberOfX));
	_simplexTable[0].PrintSimplexTable(NumberOfX);


	for (int i = 0; i < NumberOfX; i++) {
		_simplexTable.push_back(*new SimplexTable(NumberOfX, _simplexTable[i], i));
		_simplexTable[i + 1].PrintSimplexTable(NumberOfX);
	}

	_simplexTable.back().PrintResult(NumberOfX);

	return 0;
}