#!/bin/bash

for i in 1 2 4 8
do
	for j in 10 100 500 1000 1500 2000 2500 3000
	do

		if [ $i == 1 ]
		then
		g++ OpenMPSecuencial.cpp
		./a.out $j 10
		else
		g++ OpenMPParalelizado.cpp -fopenmp
		./a.out $j $i 10
		fi
		
	done
done
