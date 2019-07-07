#include "matrix_cambiada.h"
#include <iomanip> 
#include <math.h>

using namespace std;

Matrix::Matrix()//devuelve Matriz vacia.
{
	matrixAdjacent= map<int, map<int, double> >();
	columns = 0;
	rows =0;
}

Matrix::Matrix(const Matrix& m) 
{
	columns= m.ColCount();
	rows = m.RowCount();
	map<int, map<int, double> > row;	
	for(uint i = 0; i < rows; i++){
		map<int, double> column;
		for(uint j = 0; j < columns; j++){
			if(m(i,j) > EPS){
				column[i] = m(i,j);
			}
		}
		row[i] = column;
	}
	matrixAdjacent = row;
}


Matrix::Matrix(int row_count, int col_count)
{
	columns = col_count;
	rows = row_count;
	matrixAdjacent = map<int, map<int, double> >();
}


Matrix::Matrix(const vector< vector<float> >& mat){

	for (uint i = 0; i < mat.size(); ++i){
		for (uint j = 0; j < mat[i].size(); ++j){				
			if(fabs(mat[i][j]) >= EPS){				
				SetValue(i, j, (double)mat[i][j]);
			}
		}
	}				
	
	rows = mat.size();
	if(mat.size() == 0){
		columns = 0;
	}else{
		columns = mat[0].size();
	}	
}

void Matrix::SetValue(uint row, uint col, double value)
{
	if(row < rows && col < columns){
		if(fabs(value) <= EPS){
			matrixAdjacent[row].erase(col);
		}else{
			matrixAdjacent[row][col] = value;
		}
	}
}

double Matrix::operator()(uint row, uint col) const
{
	double res = 0;
	map<int, map<int, double> >::const_iterator it= matrixAdjacent.find(row);
	if(it != matrixAdjacent.end()){
		map<int, double>::const_iterator it2= it->second.find(col);
		if(it2 != it->second.end()){
			res = it2->second;
		}
	}	
	return res;	
}
uint Matrix::RowCount() const
{
	return rows;
}

uint Matrix::ColCount() const
{
	return columns;
}


Matrix& Matrix::mult_scalar(double value)
{
	for(uint i=0; i< rows; i++){
		map<int,double>::iterator it=matrixAdjacent[i].begin();
		while(it!=matrixAdjacent[i].end()){
			SetValue(i, it->first, ((it->second) * value));
			++it;
		}
	}

	return *this;
}


Matrix& Matrix::mult_diag(const Matrix& m)
{
	for(uint i =0; i < rows; i++){//recorre las filas
		map<int,double>::iterator it=matrixAdjacent[i].begin();//recorre las columnas
		while(it!= matrixAdjacent[i].end()){
			SetValue(i, it->first, ((it -> second) * m(it->first,it->first)));
			++it;
		}			
	}

	return *this;
}


Matrix& Matrix::add(const Matrix& m)//son del mismo tamaño
{	
	map<int, map<int, double> >::const_iterator it= m.matrixAdjacent.begin();
	while(it!= m.matrixAdjacent.end()){
		map<int, double>::const_iterator it2= it->second.begin();
		while(it2!= it->second.end()){
			int i = it->first;//fila
			int j = it2->first;//columna
		    this->SetValue(i,j, (m(i,j)+(*this)(i,j)));		
			++it2;
		}
		++it;
	}	
	return *this;
}

bool Matrix::operator==(const Matrix& mat) const{
 
	bool equalRows = rows == mat.rows;
	bool equalCols = columns == mat.columns;
	
	bool equalMatrix = matrixAdjacent == mat.matrixAdjacent;
	return(equalMatrix and equalCols and equalRows);
}


Matrix& Matrix::operator=(const Matrix& other){
    matrixAdjacent =  other.matrixAdjacent;
	rows = other.rows;
	columns = other.columns;
	return *this;
}

Matrix& Matrix::gauss( vector<double>& v){	
    double coef;    
    double restador;
    double value;
    double restador_vec;
    double vectoraux;    
    for (uint k = 0; k < rows -1; k++){//ve las iteraciones de filas    	
        for (uint i = k+1; i < rows; i++){ 
        	map<int, double>::iterator it = matrixAdjacent[k].begin();//recorre columna k        	       	
            coef = (*this)(i,k)/it->second; //no va a ser cero           
            	while(it !=  matrixAdjacent[k].end()){                 	
             		restador = coef*it->second;
              		value = (*this)(i,it->first)-restador;
                	this->SetValue(i,it->first,value);            	
                	++it;                                 
            	}            
            	restador_vec = coef*v[k];
            	vectoraux = v[i] - restador_vec;
            	v[i] = vectoraux;        	
    	}    
	}
	return *this;
}



ostream& operator<<(ostream& os, const Matrix& A) {
  for(uint i=0; i< A.RowCount(); i++) {
    for(uint j=0; j< A.ColCount(); j++) {
      os << setprecision(15) << A(i, j) << "\t";
    }
    os << "\n";
  }
  return os;
}

