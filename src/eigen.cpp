#include <algorithm>
#include <chrono>
#include <iostream>
#include "eigen.h"

using namespace std;


pair<double, Vector> power_iteration(const Matrix& X, unsigned num_iter, double eps)
{

    
    double eigenvalue;
    Vector b;        
    b = Vector::Random(X.cols());
    b = b/b.norm();        
        
    for( unsigned i = 0; i < num_iter ; i++){                        
        b = (X * b)/(X * b).norm();
    }

    double aux1 = (b.transpose())*X*b;
    double aux2 = (b.transpose())*b;
    eigenvalue = aux1 / aux2;

    return make_pair(eigenvalue, b);
}

pair<Vector, Matrix> get_first_eigenvalues(const Matrix& X, unsigned num, unsigned num_iter, double epsilon)
{
    Matrix A(X);
    Vector eigvalues(num);
    Matrix eigvectors(A.rows(), num);

    for(unsigned i = 0; i < num ; i++){
        pair<double, Vector> buscador = power_iteration(A, num_iter, epsilon);
        A = A - buscador.first * buscador.second * buscador.second.transpose();
        eigvalues[i] = buscador.first;
        eigvectors.col(i)= buscador.second;
    }

    return make_pair(eigvalues, eigvectors);
}

