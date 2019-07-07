#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>

using namespace std;

#ifndef MATRIX_H
#define MATRIX_H

#define EPS 10e-4

class MatrixFC
{
public:
	MatrixFC();
	
	MatrixFC(const MatrixFC& m);

	MatrixFC(int row_count, int col_count);
	
	MatrixFC(const vector< vector<float>>& );

	void SetValue(uint i, uint j, double value);

	double operator()(uint row, uint col) const;

	uint RowCount() const;

	uint ColCount() const;
	
	MatrixFC& mult_diag(const MatrixFC& D);
	
	MatrixFC& mult_matrix(const MatrixFC& m);

	MatrixFC& mult_scalar(double value);

	MatrixFC& add(const MatrixFC& m);
	
	MatrixFC& less(const MatrixFC& m);

	MatrixFC& gauss(vector<double>& v);

	bool operator==(const MatrixFC&) const;

	MatrixFC& operator=(const MatrixFC& other);

private:

	vector< map<int, double> > matrixAdjacent; //vector fila devuelve un avl con las colm def con su valor
	uint columns;
	uint rows;
};

ostream& operator<<(ostream& os, const MatrixFC& A);

#endif // MATRIX_H
