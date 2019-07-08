
def levantar_archivo(nombre):
    f = open(nombre, "r")
    return (f.readline()).split()

def separar_resultados(resultados,cant_criticas):
    res = []
    solucion_i = []
    contador_resultados = 0
    for elem in resultados:
        if contador_resultados > 0 and contador_resultados % cant_criticas == 0: 
            res.append(solucion_i)
            solucion_i = []
        solucion_i.append(int(elem))
        contador_resultados += 1
    res.append(solucion_i)
    return res

def metricas(nuestros_res, resultados_reales):
    tp = 0
    tn = 0
    fp = 0
    fn = 0
    for i in range(len(nuestros_res)):
        if nuestros_res[i] == 1 and resultados_reales[i] == 1:
            tp += 1
        if nuestros_res[i] == 0 and resultados_reales[i] == 0:
            tn += 1
        if nuestros_res[i] == 1 and resultados_reales[i] == 0:
            fp += 1
        if nuestros_res[i] == 0 and resultados_reales[i] == 1:
            fn += 1
    return tp,tn,fp,fn

def todas_las_metricas(todos_los_res, resultados_reales):
    res = []
    for res_i in todos_los_res:
        tp,tn,fp,fn = metricas(res_i,resultados_reales)
        res.append((tp,tn,fp,fn))
    return res

def accuracy(valores):
    #toma una tupla(tp,tn,fp,fn)
    #tp/(tp+tn+fp+fn)
    return (valores[0]+valores[1])/sum(valores)

def todos_los_accuracy(nuestros_res, resultados_reales):
    precisiones = todas_las_metricas(nuestros_res,resultados_reales)
    res = []
    for i in precisiones:
        res.append(accuracy(i))
    return res

def recall(valores):
    #toma una tupla(tp,tn,fp,fn)
    #tp/(tp+fn)
    return (valores[0])/(valores[0]+valores[3])

def precision(valores):
    #toma una tupla(tp,tn,fp,fn)
    #tp/(tp+fp)
    return (valores[0])/(valores[0]+valores[2])



def todos_los_precision(nuestros_res, resultados_reales):
    precisiones = todas_las_metricas(nuestros_res,resultados_reales)
    res = []
    for i in precisiones:
        res.append(precision(i))
    return res

def todos_los_recall(nuestros_res, resultados_reales):
    precisiones = todas_las_metricas(nuestros_res,resultados_reales)
    res = []
    for i in precisiones:
        res.append(recall(i))
    return res


if __name__ == '__main__':
    aux = levantar_archivo('positividad_01.txt')
    aux2 = levantar_archivo('positividad_real_no_fake.txt')
    cantidad_criticas = 6275
    nuestros_res = separar_resultados(aux,cantidad_criticas)
    resultados_reales = separar_resultados(aux2,cantidad_criticas)[0]
    accuracys = (todos_los_accuracy(nuestros_res,resultados_reales))
    recalls = (todos_los_recall(nuestros_res,resultados_reales))
    precisions = (todos_los_precision(nuestros_res,resultados_reales))
    maxima_sum = 0
    pos_max = 0
    for i in range(len(accuracys)):
        if maxima_sum < accuracys[i] + recalls[i] + precisions[i]:
            maxima_sum = accuracys[i] + recalls[i] + precisions[i]
            pos_max = i
    i = pos_max
    if pos_max == 0:
        pos_max = 1
    else:
        pos_max*= 15
    print("K que maxifica las metricas: {}".format(pos_max ))
    print("Accuracy: {} ".format(accuracys[i]))
    print("Recall : {} ".format(recalls[i]))
    print("Precision: {} ".format(precisions[i]))
    print(max(accuracys))
    print("NO NECESARIAMENTE DE LA MISMA MUESTRA!")
