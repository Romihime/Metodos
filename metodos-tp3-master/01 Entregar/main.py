import linearregression
import pandas as pd
from sklearn.metrics import accuracy_score
import numpy as np
from sklearn.feature_extraction.text import CountVectorizer
import time
import sys
import pickle




if __name__ == '__main__':
    if len(sys.argv) != 1:
        print("Uso: python metodo(0 o 1, en otro caso corre KNN+PCA) classify archivo_de_test archivo_salida")
        exit()
    #metodo = int(sys.argv[1])
    #test_path = sys.argv[2]
    #out_path = sys.argv[3]
    xs = np.array([5.2,2,3,4], dtype = float)
    ys = np.array([1,1,1,1], dtype = float)
    clf = linearregression.CuadradosMinimos('pol')
    clf.fit(2, xs, ys)
    res = clf.predict(xs);
    B = clf.armarMatrixA(2, xs)


    print(B)
    print(res)

    #df = pd.read_csv("data/imdb_small.csv")
    #df_test = pd.read_csv(test_path)

    print("Salida (vacía) guardada en {}".format('hola'))

