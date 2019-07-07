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
	
	Matrix(const vector< vector<float>>& );

	void SetValue(uint i, uint j, double value);

	double operator()(uint row, uint col) const;

	uint RowCount() const;

	uint ColCount() const;
	
	Matrix& mult_diag(const Matrix& D);
	
	Matrix& mult_matrix(const Matrix& m);

	Matrix& mult_scalar(double value);

	Matrix& add(const Matrix& m);
	
	Matrix&	less(const Matrix& m);

	Matrix& gauss();

	bool operator==(const Matrix&) const;

	Matrix& operator=(const Matrix& other);

private:

	map<int,map<int, double> > matrixAdjacent;
	uint columns;
	uint rows;
	double multiplicacion_vectorial(vector<double> fila, vector<double> columna) const;
	vector<double> dameFila(int i) const;
	vector<double> dameColumna(int i) const;
	vector<double> restarVector(vector<double> v1,vector<double> v2) const;//gauss
	vector<double> multiplicarVector(double ,vector<double>) const;//gauss

};


ostream& operator<<(ostream& os, const Matrix& A);




#endif // MATRIX_H
