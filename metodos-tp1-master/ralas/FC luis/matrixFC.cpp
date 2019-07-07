#include "matrixFC.h"
#include <iomanip> 
#include <math.h>

using namespace std;

MatrixFC::MatrixFC()//devuelve Matriz vacia.
{
	matrixAdjacent= vector< map<int, double> >();
	columns = 0;
	rows = 0;
}

MatrixFC::MatrixFC(const MatrixFC& m)
{
	columns= m.ColCount();
	rows = m.RowCount();
	matrixAdjacent = vector< map<int, double> > (rows, map<int, double>());
	for (uint i = 0; i < m.RowCount(); i++){
		map<int,double>::const_iterator it= m.matrixAdjacent[i].begin();
		while(it != m.matrixAdjacent[i].end()){								
			SetValue(i, it->first, it->second);
			++it;
		}
	}					
}

MatrixFC::MatrixFC(int row_count, int col_count)
{
	columns = col_count;
	rows = row_count;
	matrixAdjacent = vector<map<int, double> >(rows,map<int,double>() );
}
  
MatrixFC::MatrixFC(const vector< vector<float> >& mat){
    matrixAdjacent = vector<map<int, double> >(mat.size(),map<int,double>() );
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

void MatrixFC::SetValue(uint row, uint col, double value)
{
	if(row < rows && col < columns){
		if(fabs(value) <= EPS){
			matrixAdjacent[row].erase(col);
		}else{
			matrixAdjacent[row][col] = value;
		}
	}
}

double MatrixFC::operator()(uint row, uint col) const
{
    map<int, double>::const_iterator it= matrixAdjacent[row].find(col);
    if (it != matrixAdjacent[row].end()){
        return it->second;
    }
	return 0;	
}
uint MatrixFC::RowCount() const
{	
	return rows;
}

uint MatrixFC::ColCount() const
{
	return columns;
}


MatrixFC& MatrixFC::mult_scalar(double value)
{
	for(uint j=0; j< rows; j++){
		map<int,double>::iterator it=matrixAdjacent[j].begin();
		while(it!=matrixAdjacent[j].end()){
			SetValue(j,it->first, ((it->second) * value));
			++it;
		}
	}

	return *this;
}


MatrixFC& MatrixFC::mult_diag(const MatrixFC& m)
{
	for(uint j =0; j < rows; j++){
		map<int,double>::iterator it=matrixAdjacent[j].begin();
		while(it!= matrixAdjacent[j].end()){
			SetValue(j, it->first, ((it -> second) * m(it->first,it->first)));
			++it;
		}			
	}

	return *this;
}


MatrixFC& MatrixFC::add(const MatrixFC& m)
{	
	for(uint i = 0; i < rows; i++){
        map<int, double>::const_iterator it= m.matrixAdjacent[i].begin();
        while(it!= m.matrixAdjacent[i].end()){
            double valor = it->second+(*this)(i,it->first);
            SetValue(i,it->first,valor);
            ++it;
	    }
    }
	return *this;
}

bool MatrixFC::operator==(const MatrixFC& mat) const{
 
	bool equalRows = rows == mat.rows;
	bool equalCols = columns == mat.columns;
	
	bool equalMatrix = matrixAdjacent == mat.matrixAdjacent;
	
	return(equalMatrix and equalCols and equalRows);
}

MatrixFC& MatrixFC::less(const MatrixFC& m)
{
    for(uint i = 0; i < rows; i++){
        map<int, double>::const_iterator it= m.matrixAdjacent[i].begin();
        while(it!= m.matrixAdjacent[i].end()){
            SetValue(i,it->first,(*this)(i,it->first) - it->second);
            ++it;
	    }
    }
	return *this;
	

}

MatrixFC& MatrixFC::operator=(const MatrixFC& other){
    matrixAdjacent =  other.matrixAdjacent;
	rows = other.rows;
	columns = other.columns;
	return *this;
}

MatrixFC& MatrixFC::gauss(vector<double>& v){
    double coef;    
    double restador;
    double value;
    double restador_vec;
    double vectoraux;
	for(uint i = 0; i < rows - 1; i++){
        for(uint k = i+1; k < rows; k++){
            coef = (*this)(k,i)/(*this)(i,i);
			
			if (fabs(coef) >= EPS){
				map<int,double>::iterator it=matrixAdjacent[i].begin();
				while(it != matrixAdjacent[i].end()){
					restador = coef*it->second;
					value = (*this)(k,it->first) - restador;
					SetValue(k,it->first,value);
					it++;
				}
				
				restador_vec = coef*v[i];
				vectoraux = v[k] - restador_vec;
				v[k] = vectoraux;
			}
            
        }
    }
    return *this;
}


ostream& operator<<(ostream& os, const MatrixFC& A) {
  for(uint i=0; i< A.RowCount(); i++) {
    for(uint j=0; j< A.ColCount(); j++) {
    	if(i != j){
      os << setprecision(15) << A(i, j) << "\t";
    	}
    }
    os << "\n";
  }
  return os;
}

