#!/bin/bash
# Basic while loop

make solucionFC

for i in {1..50}
do
   ./solucionFC test_15_segundos.txt 0.9 >> resultados_tiempos15seg
done

python promedio_tiempos.py >> promedio_tiempos15seg

rm -rf resultados_tiempos15seg
make clean
