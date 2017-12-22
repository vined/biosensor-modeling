#!/bin/sh
#SBATCH -p short
#SBATCH -n3
rm biosensor-modeling
echo ------------------ Building -------------------
cd src
make clean
make
mv biosensor-modeling ../
cd ../

echo ------------------ Running -------------------
mpirun biosensor-modeling C1.data C2.data

