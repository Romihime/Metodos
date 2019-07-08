#include <iostream>
#include "cuadradosminimos.h"
#include <string>
#include "eigen.h"
#include "pybind11/pybind11.h"
#include <cmath>
using namespace std;

namespace py = pybind11;

CuadradosMinimos::CuadradosMinimos(string func)
{
    Family = func;    

}

//    def armar_matriz_A(self, grado ,xs):
//        res = []
//        for i in range(grado + 1):
//            columna_i = xs**i
//            res.append(columna_i)
//        self.matrix = np.asmatrix(res).T
//        return self.matrix


Matrix  CuadradosMinimos::armarMatrixA(unsigned int grado, Vector xs)
{
	Matrix res(xs.size(), grado+1);	
	for(unsigned int i= 0; i < grado+1; i++){
		res.col(i) = (xs.array().pow(i)).matrix();//potencia(xs, i);		
	}
	A = res;
	return res;
}

Matrix  CuadradosMinimos::armarMatrixA_trigo(float pi, Vector xs)
{
	Matrix res(xs.size(), 3);
	
	for(unsigned int i= 0; i < xs.size(); i++){
		res(i,0) = (float)1;
		res(i,1) = (cos(xs[i]*pi));
		res(i,2) = (sin(xs[i]*pi));
	}
	A = res;
	return res;
}

Matrix  CuadradosMinimos::armarMatrixA_fusion(unsigned int grado_pol, float pi, Vector xs)
{
	Matrix res(xs.size(), 3 + grado_pol);
	
	for(unsigned int i= 0; i < xs.size(); i++){
		res(i,0) = (float)1;
		res(i,1) = (cos(xs[i]*pi));
		res(i,2) = (sin(xs[i]*pi));
		for(unsigned int j= 0; j < grado_pol; j++){
			res(i,j+3) = pow((xs(i)),j+1); //el termino indep ya esta agregado		
		}
	}
	A = res;
	return res;
}


//    def fit(self,grado,xi,yi):
//        A = self.armar_matriz_A(grado,xi)
//        self.coef, _, _, _ = np.linalg.lstsq(A,yi)
//        #AtA  = A.T @ A 
//        #Atb  = A.T @ yi.reshape(-1,1)
//        #self.coef = np.linalg.solve(AtA, Atb)

void CuadradosMinimos::fit_fusion(unsigned int grado_pol, float grado_trigo, Vector xi, Vector yi){
	A = armarMatrixA_fusion(grado_pol,grado_trigo ,xi);
	gradotrigo = grado_trigo;
	gradopol =	grado_pol;
	Matrix AtA = A.transpose() * A;	
	Matrix Atb = A.transpose() * yi;
	//usando ecuaciones normales
	coef = (AtA).ldlt().solve(Atb);	//Vector con grado filas
	//coef = (AtA).fullPivLu().solve(Atb);
	//usando QR
	//coef =A.colPivHouseholderQr().solve(yi);
	//usando SVD NO FUNCA
	
	//coef =A.bdcSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(yi);
	//estoy haciendo trampa.XD
}

void CuadradosMinimos::fit(float grado, Vector xi, Vector yi){
	if (Family == "pol"){
		A = armarMatrixA((unsigned int)grado, xi);
		gradopol = (unsigned int)grado;
	}else{		
		A = armarMatrixA_trigo(grado ,xi);
		gradotrigo = grado;
	}
	

	Matrix AtA = A.transpose() * A;	
	Matrix Atb = A.transpose() * yi;
	//usando ecuaciones normales
	coef = (AtA).ldlt().solve(Atb);	//Vector con grado filas
	//coef = (AtA).fullPivLu().solve(Atb);
	//usando QR
	//coef =A.colPivHouseholderQr().solve(yi);
	//usando SVD NO FUNCA
	
	//coef =A.bdcSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(yi);
	//estoy haciendo trampa.XD
}

 //   def predict(self, xs):
 //       pol = self.coef
 //       ys = np.zeros(xs.size)
 //       for j in range(len(xs)):
 //           res = 0
 //           for i in range(len(pol)):
 //               res += pol[i]*(xs[j]**i)
 //           ys[j] = res
 //       return np.array(ys)

Vector CuadradosMinimos::predict(Vector xs)
{
	Matrix funcion;
	if (Family == "pol"){
		funcion = armarMatrixA(gradopol, xs);
	}
	if (Family == "trigo"){		
		funcion = armarMatrixA_trigo(gradotrigo, xs);
	}
	if (Family == "fusion"){
		funcion = armarMatrixA_fusion(gradopol, gradotrigo, xs);
	}

	

	Vector ys = funcion * coef; 
	return ys;
}
