#pragma once
#include<iostream>
#include<vector>

// class defined to obtain 2d vector of added variables
class SimplexVector {
	public:
	std::vector<double> S;
	SimplexVector() {}
};

// class defined  to obtain 2d vecto of X variables
class XVector {
public:
	std::vector<double> X;
	XVector() {}
};


// main class of simplex table
class SimplexTable {
	double buff;
public:
	//columns of results and Z's
	std::vector <double> Result;
	std::vector <double> Z;
	
	// vector defined to avoid overreading rows with variables
	std::vector<double> BlankRow;

	// declaration of 2d vectors for X's and S values
	std::vector<SimplexVector> _simplexVector;
	std::vector <XVector> _xVector;

	// variables used as counters
	// Line - number of Rows
	// a - chosen row to obtain X
	int Line;
	int a;

	// default constructor put to avoid compile errors
	SimplexTable();

	// create first table constructor
	SimplexTable(int NumberOfX);

	// copy constructor, that allocates memory and does iterations
	SimplexTable(int NumberOfX, SimplexTable _simplexTable, int Index);
	
	// prints obtained simplex table to the console
	void PrintSimplexTable(int NumberOfX);

	// prints obtained results 
	void PrintResult(int NumberOfX);
};