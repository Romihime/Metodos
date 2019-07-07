def archivo_a_lista(nombre):
    archivo = open (nombre,'r')
    lista = archivo.read().split()
    return [float(elem) for elem in lista]

def promedio(lista):
    acum = 0
    for elem in lista:
        acum += elem
    return acum/len(lista)

if __name__ == "__main__":
    tiempos = archivo_a_lista("resultados_tiempos15seg")
    print(promedio(tiempos))