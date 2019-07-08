#pragma once

#include "types.h"

using namespace std;

class KNNClassifier {
public:
    KNNClassifier(unsigned int n_neighbors);

  
    void fit(Matrix X, Matrix y);

    //Vector predict(const Matrix& X);
    Vector predict(const Matrix& X, int comparador);

    //double predict_row(const Matrix& X);
    double predict_row(const Matrix& r, int comparador);    
    Matrix vectores();
    Matrix labels();
    double norma(Vector trainRow, Vector testRow);
private:
	int neighbors;
    Matrix  vectores_palabras;
	Matrix pos_neg;
};


vector<pair< vector<int> , string>> entrenar_varios(const vector<pair<vector<string>,string>>& criticas,vector<string> positibidad,map<string, int>& vocabulary);
vector<int> entrenar(const pair<vector<string>, string>& critica, map<string, int>& vocabulary);
map<string, int>  generate_vocabulary(const vector<pair<vector<string>,string>>& criticas, double umbral_sup, double umbral_inf);
void comparador_vectores(Vector& A,Matrix& vectores_palabras,Matrix r, int comparador );