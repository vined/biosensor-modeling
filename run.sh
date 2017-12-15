#!/bin/sh
#SBATCH -p short
#SBATCH -n1
echo ------------------ Building -------------------
cd src
make clean
make
mv biosensor-modeling ../
cd ../

echo ------------------ Running -------------------
mpirun biosensor-modeling

