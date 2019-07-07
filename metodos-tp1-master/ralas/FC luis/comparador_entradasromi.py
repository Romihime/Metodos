
def archivo_a_lista(nombre):
    archivo = open (nombre,'r')
    lista = archivo.read().split()
    return [float(elem) for elem in lista]

if __name__ == "__main__":
    mi_res = archivo_a_lista("archivo.out")
    catedra_res = archivo_a_lista("test_30_segundos.txt.out")
    i = 0
    acum = 0
    while i < len(mi_res):
        acum = acum + abs(mi_res[i] - catedra_res[i])
        i += 1
print( acum )