#include <iostream>
#include "Simplex.h"


SimplexTable::SimplexTable() {}

SimplexTable::SimplexTable(int NumberOfX) {

	std::cout << "put first characteristic equation  in form AX1 + BX2    to minimize" << std::endl;

	for (int i = 0; i < NumberOfX; i++) {
		std::cout << "put N for X" << i + 1 << std::endl;
		std::cin >> buff;
		_xVector.push_back(*new XVector);
		_xVector[i].X.push_back(buff);
	}

	Result.push_back(0);
	Z.push_back(1);

	Line = 1;

	while (1) {
		std::cout << "put equation in form AX1 +BX2 <= Result" << std::endl << std::endl;

		for (int i = 0; i < NumberOfX; i++) {
			std::cout << "put N for X" << i + 1 << std::endl;
			std::cin >> buff;
			_xVector[i].X.push_back(buff);
		}

		std::cout << "result=" << std::endl;
		std::cin >> buff;
		Result.push_back(buff);


		_simplexVector.push_back(*new SimplexVector);

		for (int i = 0; i < Line - 1; i++) {
			_simplexVector[i].S.push_back(0);
		}

		for (int i = 0; i < Line; i++) {
			_simplexVector[Line - 1].S.push_back(0);
		}

		_simplexVector[Line - 1].S.push_back(1);

		Z.push_back(0);

		std::cout << "Do you want to continue ??? if yes put 1" << std::endl;
		std::cin >> buff;
		if (buff != 1) {
			break;
		}
		Line++;
	}
}

SimplexTable::SimplexTable(int NumberOfX, SimplexTable _simplexTable, int Index) {
	Line = _simplexTable.Line;

	//space allocation	

	for (int i = 0; i < NumberOfX; i++) {
		_xVector.push_back(*new XVector);
		for (int j = 0; j <= Line; j++) {
			_xVector[i].X.push_back(0);
		}
	}


	for (int i = 0; i <= Line; i++) {
		Result.push_back(0);
		Z.push_back(0);
	}

	for (int i = 0; i < Line; i++) {
		_simplexVector.push_back(*new SimplexVector);

		for (int j = 0; j <= Line; j++) {
			_simplexVector[i].S.push_back(0);
		}
	}


	//default iteration

	int Counter;
	bool IsChosen = false;


	// choosing blank rows
	for (int j = 0; j <= Line; j++) {
		Counter = 0;
		for (int i = 0; i < NumberOfX; i++) {

			if (_simplexTable._xVector[i].X[j] == 1) {
				//check columne if there are zeros
				for (int k = 0; k <= Line; k++) {
					if (k != j && _simplexTable._xVector[i].X[k] == 0) {
						Counter = 1;
					}
					if (k != j && _simplexTable._xVector[i].X[k] != 0) {
						Counter = 0;
						break;
					}
				}
				if (Counter == 1) {
					BlankRow.push_back(0);
				}
				break;
			}
		}
		if (Counter == 0) {
			BlankRow.push_back(1);
		}
	}
	BlankRow[0] = 0;


	for (int i = 1; i <= Line; i++) {
		if (IsChosen == false && BlankRow[i] == 1 && _simplexTable._xVector[Index].X[i] != 0) {
			IsChosen = true;
			a = i;
			buff = _simplexTable._xVector[Index].X[i] / _simplexTable.Result[i];
		}
		else if (IsChosen == true && BlankRow[i] == 1 && buff > _simplexTable._xVector[Index].X[i] / _simplexTable.Result[i] && _simplexTable._xVector[Index].X[i] != 0) {
			buff = _simplexTable._xVector[Index].X[i] / _simplexTable.Result[i];
			a = i;
		}
	}

	// generating new rows except chosen one
	for (int i = 0; i <= Line; i++) {

		if (i != a) {
			_xVector[Index].X[i] = 0;
			for (int j = 0; j < NumberOfX; j++) {
				_xVector[j].X[i] = _simplexTable._xVector[j].X[i] - _simplexTable._xVector[j].X[a] * _simplexTable._xVector[Index].X[i] / _simplexTable._xVector[Index].X[a];
			}

			Result[i] = _simplexTable.Result[i] - _simplexTable.Result[a] * _simplexTable._xVector[Index].X[i] / _simplexTable._xVector[Index].X[a];
			Z[i] = _simplexTable.Z[i];

			for (int j = 0; j < Line; j++) {
				_simplexVector[j].S[i] = _simplexTable._simplexVector[j].S[i] - _simplexTable._simplexVector[j].S[a] * _simplexTable._xVector[Index].X[i] / _simplexTable._xVector[Index].X[a];
			}
		}
	}

	// generating numbers for chosen row
	for (int i = 0; i < NumberOfX; i++) {

		_xVector[i].X[a] = _simplexTable._xVector[i].X[a] / _simplexTable._xVector[Index].X[a];
	}

	Result[a] = _simplexTable.Result[a] / _simplexTable._xVector[Index].X[a];

	for (int j = 0; j < Line; j++) {
		_simplexVector[j].S[a] = _simplexTable._simplexVector[j].S[a] / _simplexTable._xVector[Index].X[a];
	}
}

void SimplexTable::PrintSimplexTable(int NumberOfX) {
	for (int i = 0; i < NumberOfX; i++) {
		std::cout << "X" << i + 1 << " ";
	}

	for (int i = 0; i < Line; i++) {
		std::cout << "S" << i + 1 << " ";
	}

	std::cout << "R  Z" << std::endl;

	for (int i = 0; i <= Line; i++) {

		for (int j = 0; j < NumberOfX; j++) {
			std::cout << _xVector[j].X[i] << " ";
		}

		for (int j = 0; j < Line; j++) {
			std::cout << _simplexVector[j].S[i] << "  ";
		}

		std::cout << Result[i] << "  " << Z[i] << std::endl;
	}
}

void SimplexTable::PrintResult(int NumberOfX) {
	for (int i = 0; i < NumberOfX; i++) {
		for (int j = 0; j <= Line; j++) {
			if (_xVector[i].X[j] == 1) {
				std::cout << "X" << i + 1 << " is equal to";
				std::cout << Result[j];
				std::cout << std::endl;
			}
		}
	}
}
