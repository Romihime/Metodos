
def archivo_a_lista(nombre):
    archivo = open (nombre,'r')
    lista = archivo.read().split()
    return [float(elem) for elem in lista]

def comparador(mi_res,catedra_res):
    i = 0
    while i < len(mi_res):
        if abs(mi_res[i] - catedra_res[i]) >= 10e-4:
            print("error de " + str(abs(mi_res[i] - catedra_res[i])) )
            return
        i += 1
    print("Pasa los tests!")

if __name__ == "__main__":
    mi_res = archivo_a_lista("archivo.out")
    catedra_res = archivo_a_lista("test_30_segundos.txt.out")
    comparador(mi_res,catedra_res)
   