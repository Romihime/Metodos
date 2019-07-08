#include <iostream>
#include "pca.h"
#include "eigen.h"
#include "pybind11/pybind11.h"

using namespace std;

namespace py = pybind11;


PCA::PCA(unsigned int n_components)
{
    components = n_components;       
    
}


Matrix PCA::cov(){//es función para testing
	return covarianza;
}

Matrix PCA::cam_base(){
	return cambioDeBase;
};

Vector PCA::autoval(){
	return autovalores;
}


void PCA::fit(const Matrix& X, unsigned num_iter, int alpha)
{
	//Busco matriz de covarianza
	if(alpha < components){		
		cambioDeBase2 = cambioDeBase.block(0,0,cambioDeBase.rows(), alpha); 
	}else{
		components = alpha;		
		Vector u= X.colwise().mean(); //me devuelve un vector de nx1 
		Matrix M = X.rowwise() - u.transpose();
		double dim_menos_uno = M.rows() - 1;
		covarianza = ((M.transpose()*M)/ dim_menos_uno);//dimension de covarianza = mxm
		covarianza = covarianza/covarianza.norm();
		pair<Vector, Matrix> diagonalizacion = get_first_eigenvalues(covarianza, components,  num_iter, 1e-16);

		cambioDeBase = get<1>(diagonalizacion);
		cambioDeBase2 = get<1>(diagonalizacion);
		autovalores = get<0>(diagonalizacion);
		//en diagonalizacion.first tengo los alfa(components) autovalores + grandes(afectan + la varianza)
		//en diagonalizacion.second tengo los V (autovectores). Es una matriz de m x alfa
	}
}



MatrixXd PCA::transform(const Matrix& X)
{ 			
  return (X * cambioDeBase2);
}

