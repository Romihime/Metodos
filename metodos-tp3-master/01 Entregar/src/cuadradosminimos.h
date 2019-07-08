#pragma once
#include "types.h"
#include <string>


class CuadradosMinimos {
public:
    CuadradosMinimos(std::string func);

    Matrix armarMatrixA(unsigned int grado, Vector xs);
    Matrix armarMatrixA_fusion(unsigned int grado_pol, float pi, Vector xs);
    Matrix armarMatrixA_trigo(float grado,  Vector xs);
    void fit(float grado, Vector xi, Vector yi);
    void fit_fusion(unsigned int grado_pol, float grado_trigo, Vector xi, Vector yi);
    Vector predict(Vector xs);
private:
    
	std::string Family;
	Vector coef;
	Matrix A;
    unsigned int gradopol;
    float gradotrigo;
};

