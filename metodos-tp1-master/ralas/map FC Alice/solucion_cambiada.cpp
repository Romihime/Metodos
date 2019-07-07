#include <iostream>
#include <fstream>
#include <algorithm>
#include "matrix_cambiada.h"
#include <math.h>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;


 vector<int> linksQuantity(Matrix& matrixOfLinks){
 	vector<int> res; 	

 	for (uint j=0; j < matrixOfLinks.ColCount(); j++){
 		int externalLinks = 0;
 		for(uint i =0; i< matrixOfLinks.RowCount(); i++){
 			externalLinks = externalLinks + matrixOfLinks(i, j);
 		}
 		res.push_back(externalLinks);
 	}
 	return res;
 	
 }


void llenarDiagonal(Matrix& d, vector<int> quantityOfLinks){
   	for(uint j=0; j< quantityOfLinks.size(); j++ ){ 
    	if(abs(quantityOfLinks[j]) >= EPS){     		
    		double value = 1.0/quantityOfLinks[j];    		 	
    		d.SetValue(j,j, value);
    	}    	   	
    }       
}



void gaussianna(Matrix& d, vector<double>& v){//falta vector de la extendida
    double coef;    
    double restador;
    double value;
    double restador_vec;
    double vectoraux;
    for (uint k = 0; k < d.RowCount() -1; k++){
        for (uint i = k+1; i < d.RowCount(); i++){
            coef = d(i,k)/d(k,k);            
            for(uint j = k; j < d.ColCount();j++){//puse j=k en vez de j = 0
                restador = coef*d(k,j);
                value = d(i,j)- restador;
                d.SetValue(i,j,value);                 
            }
            restador_vec = coef*v[k];
            vectoraux = v[i] - restador_vec;
            v[i] = vectoraux;           
        }
    }    
}

vector<double> resolucion(Matrix& d, vector<double>& v){
    int n = d.RowCount();
    vector<double> res(n,0);    
    double aux;
    for(int i= n-1; i >=0; i--){        
        double incog_vector = v[i];
        for(uint j = i+1; j < d.ColCount(); j++){// ColCount = n;
            incog_vector = incog_vector - (res[j]*d(i,j));
        }
        aux = incog_vector/d(i,i);
        res[i] = aux;

    }
    return res;
}


double norma(vector<double>& v){
    sort(v.begin(), v.end());
    double acum = 0.00;
    for(uint i=0; i < v.size(); i++){        
        acum = acum + (v[i] * v[i]);
    }    
    return sqrt(acum);
}




double sumatoria(vector<double>& v){
    double acum = 0.00;
    for(uint i=0; i < v.size(); i++){        
        acum = acum + v[i];
    }    
    return acum;
}


void normalizar(vector<double>& v){
    double nor = sumatoria(v);
    double valor_normalizado;
    for(uint i=0; i < v.size(); i++){
        valor_normalizado = v[i]/nor;
        v[i] = valor_normalizado;
    }
}



int main(int argc, char**argv)
{

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    if(argc < 3){
        cout << "Faltan parametros" << endl;
        return 0;
    }
    fstream fs;
    fstream salida;
    double p;
    //Abre el archivo pasado por parametro en modo solo lectura
    fs.open(argv[1], fstream::in);
    salida.open("archivo.out", fstream::out); 
    p = atof(argv[2]);    
    if(fs.is_open()){
        while(!fs.eof()){
            //int k = 0;
            //fs >> k;

            //for(int i = 0; i < k; i++){
                int paginas = 0;
                fs >> paginas;
                Matrix m(paginas, paginas);

                int cantLinks = 0;
                fs >> cantLinks;
                int receptor = 0;
                int emisor = 0;
                for(int i = 0; i < cantLinks; i++){
                    fs >> emisor;
                    fs >> receptor;
                    m.SetValue(receptor-1, emisor-1, 1);
                }
     
                vector<int> quantityOfLinks = linksQuantity(m); 
    
                Matrix d(paginas, paginas);
                llenarDiagonal(d, quantityOfLinks);

                m.mult_diag(d);

                m.mult_scalar(-p);//(-1*p)

                Matrix id(paginas, paginas);
                for(uint i= 0; i < id.RowCount(); i++){
                  id.SetValue(i, i, 1);
                }

                id.add(m);

                vector<double> unos(paginas, 1.0);
                cout << "entre a gaussianna" << endl;
                id.gauss(unos);//gaussianna(id, unos);
                cout << "gaussie re piola" << endl;

                vector<double> incognitas =resolucion(id, unos);

                normalizar(incognitas);
                
                high_resolution_clock::time_point t4 = high_resolution_clock::now();

                duration<double> time_span1 = duration_cast<duration<double>>(t4 - t1);
                //cout << "tardó " << time_span1.count() << endl; 
                salida << p << endl;
                for(int i = 0; i < paginas; i++){
                salida << incognitas[i]<<endl;                                 
                } 
            //}
        }
    }

    fs.close();
    salida.close();
    return 0;
}
