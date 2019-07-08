#include <algorithm>
//#include <chrono>
#include <iostream>
#include "knn.h"
#include "pybind11/pybind11.h"
#include <set>

using namespace std;

namespace py = pybind11;


KNNClassifier::KNNClassifier(unsigned int n_neighbors)
{
    neighbors = n_neighbors;

}
void KNNClassifier::fit(Matrix X, Matrix y)

{
    vectores_palabras = X;
    pos_neg = y; 
}


Matrix KNNClassifier:: vectores(){
    return vectores_palabras;
}

Matrix KNNClassifier::labels(){
    return pos_neg;
}



void comparador_vectores(Vector& A, Matrix& vectores_palabras,Matrix r, int comparador ){
    // que a es mas parecido b que c si el comparador te da un numero mas chico(puede ser neg)
    switch(comparador){
        case 0:{
            //Hago ||v1-v2|| unas n veces
            for(unsigned k = 0; k < vectores_palabras.rows(); k++){                
                A[k] = (vectores_palabras.row(k) -r ).norm();       
            }
            break;
        }
        case 1:{
            //Hago MENOS(cantidad de veces que en ambos v[i] > 0)
            // lo dejo como negativo porque mientras mas negativo
            // mas se parecen en teoria
            int hits = 0;
            for (int i = 0, nRows = vectores_palabras.rows() , nCols = r.cols(); i < nRows; ++i){
                hits = 0;
                for (int j = 0; j < nCols; ++j){
                    if(r.coeffRef(0,j) > 0 and vectores_palabras.coeffRef(i,j) > 0){
                        hits -= 1;
                    }
                }
                A[i] = hits;
            }
            break;
        }
        case 2:{
            //Hago MENOS(cantidad de veces que en ambos v[i] > 0)
            // lo dejo como negativo porque mientras mas negativo
            // mas se parecen en teoria
            int hits = 0;
            for (int i = 0, nRows = vectores_palabras.rows() , nCols = r.cols(); i < nRows; ++i){
                hits = 0;
                for (int j = 0; j < nCols; ++j){
                    if(r.coeffRef(0,j) > 0 and vectores_palabras.coeffRef(i,j) > 0){
                        hits -= min(r.coeffRef(0,j),vectores_palabras.coeffRef(i,j));
                    }
                }
                A[i] = hits;
            }
            break;
        }
       
        
    }
    
}



double KNNClassifier::predict_row(const Matrix& r, int comparador){   
    Vector A(vectores_palabras.rows());   
    
    comparador_vectores(A,vectores_palabras,r,comparador);

    vector<int> y(vectores_palabras.rows(),0);
    for(unsigned int i = 0; i < y.size(); i++ ){
        y[i] = i;
    }    
    auto comparator = [&A](int a, int b){ return A(a) < A(b); };
    std::partial_sort(y.begin(), y.begin() + neighbors, y.end(), comparator);//se supone hace el sort en orden ascendente y me devuelve los indices.
    vector<double> k(neighbors, 0);
    for( unsigned int i =0; i < k.size(); i++){
        k[i] = pos_neg(y[i]); //es un double
    }//vector k tiene las  etiquetas de las k posiciones + cercanas.
    //Acá hacemos la contabilidad final
    int pos = 0;
    int neg = 0;
    for(unsigned int i = 0; i < k.size(); i++){
        if(k[i] == 1){
            pos++;
        }else{
            neg++;
        } 
    }    
    double res = 0;
    if(pos >= neg){
        res = 1;
    }
    return res;
}


 


Vector KNNClassifier::predict(const Matrix& X, int comparador)
{

    // Creamos vector columna a devolver
    auto ret = Vector(X.rows());     
    for (unsigned k = 0; k < X.rows(); k++)
    {
        ret(k) =  predict_row(X.row(k), comparador);
    }
    return ret;
}



