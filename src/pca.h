#pragma once
#include "types.h"

class PCA {
public:
    PCA(unsigned int n_components);

    void fit(const Matrix& X, unsigned num_iter, int alpha);

    Matrix cov(); 
    Matrix cam_base();
    Vector autoval();


    Eigen::MatrixXd transform(const Matrix& X);
private:
	Matrix cambioDeBase;
    Matrix cambioDeBase2;
	Matrix  covarianza; 
	int components;   
	Vector autovalores;

    
};
