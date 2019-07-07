#include <iostream>
#include <fstream>
#include <algorithm>
#include "matrixFC.h"
#include <math.h>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;


 vector<int> linksQuantity(MatrixFC& matrixOfLinks){
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


void llenarDiagonal(MatrixFC& d, vector<int> quantityOfLinks){
   	for(uint j=0; j< quantityOfLinks.size(); j++ ){ 
    	if(abs(quantityOfLinks[j]) >= EPS){     		
    		double value = 1.0/quantityOfLinks[j];    		 	
    		d.SetValue(j,j, value);
    	}    	   	
    }       
}


vector<double> resolucion(MatrixFC& d, vector<double>& v){
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

void constructorMatrizA(MatrixFC& M, double p){
    M.mult_scalar(-1);   

    vector<double> z;

    for(int j = 0; j < M.ColCount(); j++){
        int i =0;
        for(i = 0; i < M.RowCount(); i++){
            if(M(i,j) > EPS){
                z.push_back(((1.0-p)/M.RowCount()));
                break;
            }
        }
        if(i >= M.RowCount()){
            z.push_back(1.0/M.RowCount());
        }
    }

    for(int i = 0; i < M.RowCount(); i++){
        for(int j = 0; j < M.ColCount(); j++){
            if(M(i,j) < EPS){
                M.SetValue(i,j, z[j]);    
            }else{
                M.SetValue(i,j,M(i,j) + z[j]);
            }
        }
    }

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

vector<double> multiplicacionMatrizVector(MatrixFC& M, vector<double>& v){
    vector<double> res;

    for(int i = 0; i < M.RowCount(); i++){
        double aux = 0;
        for(int j = 0; j < M.ColCount();j++){
            aux += M(i,j) * v[j];
        }
        res.push_back(aux);
    }
    return res;
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
    fs.open(argv[1], fstream::in);
    salida.open("archivo.out", fstream::out); 
    p = atof(argv[2]);    
    if(fs.is_open()){
        while(!fs.eof()){
           // int k = 1;
            //fs >> k;

            //for(int i = 0; i < k; i++){ //para levantar varias entradas
                int paginas = 0;
                fs >> paginas;
                // cout << "paginas" << paginas<< endl;
                MatrixFC m(paginas, paginas);

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
    
                MatrixFC d(paginas, paginas);
                llenarDiagonal(d, quantityOfLinks);

                m.mult_diag(d);
                
                m.mult_scalar(-p);//(-1*p)
                
                MatrixFC id(paginas, paginas);
                for(uint i= 0; i < id.RowCount(); i++){
                  id.SetValue(i, i, 1);
                }

                id.add(m);
                
                //cout << aux << endl;
                vector<double> unos(paginas, 1.0);
                // cout << "entre a gaus" << endl;

                id.gauss(unos);

                // cout << "gaussie re piola" << endl;

                vector<double> incognitas =resolucion(id, unos);

                // cout << "averigue las incognitas" << endl;

                normalizar(incognitas);

                // cout << "vector normalizado" << endl;
                             
                
                high_resolution_clock::time_point t4 = high_resolution_clock::now();

                duration<double> time_span1 = duration_cast<duration<double>>(t4 - t1);
                //cout << time_span1.count() << endl; 
                salida << p << endl;
                for(int i = 0; i < paginas; i++){
                
                salida << incognitas[i]<<endl;                                               
                //cout << incognitas[i];
                } 

                MatrixFC M(m);
                constructorMatrizA(M, p);
                vector<double> res = multiplicacionMatrizVector(M, incognitas);
                for(int i = 0; i < paginas; i++){
                    res[i] -= incognitas[i];
                }

                cout << norma(res) << endl;
           // }
            
        }
    
    }

    fs.close();
    salida.close();
    return 0;
}
