#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>

using namespace std;

#ifndef MATRIX_H
#define MATRIX_H

#define EPS 10e-4

class Matrix
{
public:
	Matrix();
	
	Matrix(const Matrix& m);

	Matrix(int row_count, int col_count);
	
	Matrix(const vector< vector<float> >& );

	void SetValue(uint i, uint j, double value);

	double operator()(uint row, uint col) const;

	uint RowCount() const;

	uint ColCount() const;
	
	Matrix& mult_diag(const Matrix& D);
	
	Matrix& mult_matrix(const Matrix& m);

	Matrix& mult_scalar(double value);

	Matrix& add(const Matrix& m);	
	
	Matrix& gauss( vector<double>& v);

	bool operator==(const Matrix&) const;

	Matrix& operator=(const Matrix& other);

private:

	map<int,map<int, double> > matrixAdjacent;
	uint columns;
	uint rows;//map<int row, map<int column, double value> > matrixAdyacent;
};


ostream& operator<<(ostream& os, const Matrix& A);


#endif // MATRIX_H
