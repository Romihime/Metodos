#include <iostream>
#include <fstream>
#include <algorithm>
#include "matrixFC.h"
#include <math.h>
#include <ctime>
#include <chrono>


//Voy a hacer la norma matricial inducida infinita, porque sino tengo que encontrarla entre todos los vectores de la imagen de  Ax con vectores x de norma 1, y esos son muchos vectores.
double norma_matricial_inducida_infinita(MatrixFC& m){
    //maximo entre las sumatorias de las filas
    vector<double> sumatoriasDeModulos;
    for(uint i =0; i< m.RowCount(); i++){
        double acum = 0.00;
        for(uint j= 0; j < m.ColCount(); j++){
            acum = acum + fabs(m(i, j));    
        }
        sumatoriasDeModulos.push_back(acum);
    }
    double max = *max_element(sumatoriasDeModulos.begin(), sumatoriasDeModulos.end());
    return max;
}


double norma_matricial_inducida_uno(MatrixFC& m){
    //maximo entre las sumatorias de las filas
    vector<double> sumatoriasDeModulos;
    for(uint j =0; j< m.ColCount(); j++){
        double acum = 0.00;
        for(uint i= 0; i < m.RowCount(); i++){
            acum = acum + fabs(m(i, j));    
        }
        sumatoriasDeModulos.push_back(acum);
    }
    double max = *max_element(sumatoriasDeModulos.begin(), sumatoriasDeModulos.end());
    return max;
}



int main(){

	MatrixFC m2({
				{0.0, 2.0, 3.0},
				{4.0, 0.0, 6.7},
				{7.5, 2.0, 0.0},				
			  });

	cout << m2 << endl;
	cout << "norma matricial "<<norma_matricial_inducida_infinita(m2) << endl;
	cout << "norma matricial "<<norma_matricial_inducida_uno(m2) << endl;


return 0;
}