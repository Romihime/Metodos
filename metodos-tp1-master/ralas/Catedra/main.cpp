#include <iostream>

// #include "matrix.h"
#include "matrixFC.h"
using namespace std;


int main(int argc, char* argv[])
{
    
    MatrixFC m = MatrixFC(3, 3);

	m.SetValue(0, 0, 1);
	m.SetValue(1, 1, 1);
	m.SetValue(2, 2, 1);
	
	cout << m.RowCount() << endl;
	
	cout << m.ColCount() << endl;
	
	cout << m << endl;	

	
	////////////////////
	
	MatrixFC m2({
				{1.4, 2.0, 3.0},
				{4.0, 5.0, 6.7},
				{7.5, 8.0, 9.0},
				{10.0, 11.9, 12.0}
			  });


	cout << m2.RowCount() << endl;
	
	cout << m2.ColCount() << endl;
	
	cout << m2 << endl;	
	
	/////////////////////

	
	MatrixFC m3({
			{0.0, 2.0, 3.0},
			{4.0, 0.0, 6.0},
			{7.0, 8.0, 0.0}			
		  });

	
	cout << m3.RowCount() << endl;
	
	cout << m3.ColCount() << endl;
	
	cout << m3 << endl;	

	m3.mult_scalar(2);

	cout << m3 << endl;	
	
	
	MatrixFC d1({
			{2.0, 0.0, 0.0},
			{0.0, 1.0, 0.0},
			{0.0, 0.0, 2.0}			
		  });

	cout << d1 << endl;

	m3.mult_diag(d1);

	cout << m3 << endl;
	m3.add(d1);
	
	cout << m3 << endl;
	

	cout << (m3 == m3) << (m2 == m3) << endl;
	///////////////////////
	MatrixFC m4({
				{1.0, 2.0},
				{3.0, 1.0},
				{4.0, 2.0},
			    });
	MatrixFC m5({
				{2.0, 1.0},
				{1.0, 5.0},				
			  });


	cout << m4 << endl;


	
	return 0;
}

