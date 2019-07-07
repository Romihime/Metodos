#include "matrix.h"
#include <iomanip> 
#include <math.h>

using namespace std;

// Matrix
Matrix::Matrix()//devuelve Matriz vacia.
{
	matrixAdjacent= map<int, map<int, double> >();
	columns = 0;
	rows =0;
}

Matrix::Matrix(const Matrix& m) //no estoy para nada segura de que esto ande
{
	columns= m.ColCount();
	rows = m.RowCount();
	map<int, map<int, double> > column;	
	for(uint j = 0; j < columns; j++){
		map<int, double> row;
		for(uint i = 0; i < rows; i++){
			if(m(i,j) > EPS){
				row[i] = m(j,i);
			}
		}
		column[j] = row;
	}
	matrixAdjacent = column;

	// HACER
}


Matrix::Matrix(int row_count, int col_count)
{
	columns = col_count;
	rows = row_count;
	//No es necesario esto, se esta definiendo columnas y filas que capaz no se usan

	//map<int, map<int, double> > columns;
	//for(int i = 0; i< col_count; i++){
	//	columns[i] = map<int, double>();//filas
	//}
	matrixAdjacent = map<int, map<int, double> >();
}

/*Matrix::Matrix(const vector< vector<float>>& mat){

	if (mat.size() > 0){
		
		for (int i = 0; i < mat.size(); ++i)
			for (int j = 0; j < mat[i].size(); ++j){
				//cout << mat[i][j] << endl;
				SetValue(i, j, mat[i][j]);
		}
			
	}
}VERSION ORIGINAL DADA POR LA CATEDRA
*/   
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
	//if(row < rows && col < columns){
		if(fabs(value) <= EPS){
			matrixAdjacent[col].erase(row);
		}else{
			matrixAdjacent[col][row] = value;
		}
	//}

	// HACER
	// ATENCION: no hacer if value == 0 usar EPS
}

double Matrix::operator()(uint row, uint col) const
{
	double res = 0;
	map<int, map<int, double> >::const_iterator it= matrixAdjacent.find(col);
	if(it != matrixAdjacent.end()){
		map<int, double>::const_iterator it2= it->second.find(row);
		if(it2 != it->second.end()){
			res = it2->second;
		}
	}		
	// HACER
	return res;	
}
uint Matrix::RowCount() const
{
		
	return rows;
	// HACER
}

uint Matrix::ColCount() const
{
	
	return columns;
	// HACER
}


Matrix& Matrix::mult_scalar(double value)
{
	for(uint j=0; j< columns; j++){
		map<int,double>::iterator it=matrixAdjacent[j].begin();
		while(it!=matrixAdjacent[j].end()){
			SetValue(it->first, j, ((it->second) * value));
			++it;
		}
	}

	return *this;
}


Matrix& Matrix::mult_diag(const Matrix& m)
{
	for(uint j =0; j < columns; j++){
		map<int,double>::iterator it=matrixAdjacent[j].begin();
		while(it!= matrixAdjacent[j].end()){
			SetValue(it->first, j, ((it -> second) * m(j,j)));
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
			int j = it->first;//columna
			int i = it2->first;//fila
		    this->SetValue(i,j, (m(i,j)+(*this)(i,j)));		
			++it2;
		}
		++it;
	}	
	return *this;
}

bool Matrix::operator==(const Matrix& mat) const{//como estamos tratando con maps esto puede estar mallll
 
	bool equalRows = rows == mat.rows;
	bool equalCols = columns == mat.columns;
	
	bool equalMatrix = matrixAdjacent == mat.matrixAdjacent;
	/*bool equalMatrix = true;
	map<int, map<int, double> >::const_iterator it= matrixAdjacent.begin();
	while(it != matrixAdjacent.end()){
		map<int, double>::const_iterator it2= it->second.begin();
		while(it2 != it->second.end()){
			map<int, map<int, double> >::const_iterator it_mat = mat.matrixAdjacent.find(it->first); 
			if(it_mat != mat.matrixAdjacent.end()){
				map<int, double>::const_iterator it_mat2 = it_mat->second.find(it2->second);
				if(it_mat2 == it_mat->second.end()){
					equalMatrix = false;
				}
			}else{
				equalMatrix = false;
			}
			++it2;
		}

		++it;
	}*/

	return(equalMatrix and equalCols and equalRows);
}

Matrix& Matrix::less(const Matrix& m)//son del mismo tamaño
{
	map<int, map<int, double> >::const_iterator it= m.matrixAdjacent.begin();
	while(it!= m.matrixAdjacent.end()){
		map<int, double>::const_iterator it2= it->second.begin();
		while(it2!= it->second.end()){
			int j = it->first;//columna
			int i = it2->first;//fila
			this->SetValue(i,j, ((*this)(i,j) - m(i,j)));		
			++it2;
		}
		++it;
	}	
	return *this;
}

Matrix& Matrix::operator=(const Matrix& other){
    matrixAdjacent =  other.matrixAdjacent;
	rows = other.rows;
	columns = other.columns;
	return *this;
}

double Matrix::multiplicacion_vectorial(vector<double> fila, vector<double> columna) const{
    double res = 0;
    for (uint k = 0; k < fila.size(); k++){
        res +=  fila[k]*columna[k];
    }
    return res;
}

vector<double> Matrix::dameColumna(int k) const{
	vector<double> res;
	for(uint i = 0; i < rows; i++){
		res.push_back((*this)(i,k));
	}
	return res;
}

vector<double> Matrix::dameFila(int k) const{
	vector<double> res;
	for(uint i = 0; i < columns; i++){
		res.push_back((*this)(k,i));
	}
	return res;
}

vector<double> Matrix::multiplicarVector(double f,vector<double> v) const{
    for (uint i = 0; i < v.size(); i++){
           v[i] *= f;
    }
    return v;
}

vector<double> Matrix::restarVector(vector<double> v1,vector<double> v2) const{
    //asumo mismas dimensiones
    for (uint i = 0; i < v1.size(); i++){
           v1[i] -= v2[i];
    }
    return v1;
}

/*Matrix& Matrix::mult_matrix(const Matrix& m){
	Matrix res = Matrix(rows,m.columns);
	if(columns == m.rows){
		int fila = 0;
		vector<double> vector_fila;
		vector<double> vector_columna;
		for (int i = 0; i < rows ;i++ ){
			vector_fila	=	(*this).dameFila(i);
			for(int j = 0; j < m.columns; j++){
				vector_columna	= m.dameColumna(j);
				double producto_vectorial = multiplicacion_vectorial(vector_columna,vector_fila);
				res.SetValue(j,i,producto_vectorial);
			}
		}
	}
	*this = res;
	return *this;
}*/

Matrix& Matrix::mult_matrix(const Matrix& m){
	Matrix res = Matrix(rows,m.columns);
	if(columns == m.rows){		
		vector<double> vector_fila;
		vector<double> vector_columna;
		for (uint j = 0; j < columns ;j++ ){
			for(uint i = 0; i < rows; i++ ){
				for(uint c=0; c< m.columns; c++){
					double val = (*this)(i,j)*m(j,c);
					if(fabs(val) >= EPS){			
						res.SetValue(i, c, res(i,c) + val);
					}
				}	
			}
		}
	}	
	*this = res;
	return *this;
}

Matrix& Matrix::gauss(){
	double coef;
	vector<double> fila;
    for (uint i = 1; i < rows; i++){
            coef = (*this)(i,0)/(*this)(0,0);
            fila = restarVector(dameFila(i),multiplicarVector(coef,dameFila(0)));
			for(uint j = 0; j < fila.size();j++){
				SetValue(i,j,fila[j]);
			}
			fila.clear();
    }
    for (uint k = 1; k < rows -1; k++){
        for (uint i = k+1; i < rows; i++){
            coef = (*this)(i,k)/(*this)(k,k);
			fila = restarVector(dameFila(i),multiplicarVector(coef,dameFila(k)));
			for(uint j = 0; j < fila.size();j++){
				SetValue(i,j,fila[j]);
			}
			fila.clear();
        }
    }
    return *this;
}


ostream& operator<<(ostream& os, const Matrix& A) {
  for(uint i=0; i< A.RowCount(); i++) {
    for(uint j=0; j< A.ColCount(); j++) {
	  // setprecision(4) define la cantidad de decimales a mostrar
      os << setprecision(15) << A(i, j) << "\t";
    }
    os << "\n";
  }
  return os;
}

