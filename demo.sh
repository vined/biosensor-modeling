#!/usr/bin/env bash
echo ------------------ Building ------------------
cd src
make clean
make
mv biosensor-modeling ../
cd ../

echo ------------------ Running -------------------
./biosensor-modeling