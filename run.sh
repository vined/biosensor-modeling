#!/usr/bin/env bash
echo ------------------ Building ------------------
cd src
make clean
make
mv biosensor-modeling ../
cd ../

echo ------------------ Cleaning up -------------------
rm out/*

echo ------------------ Running -------------------
./biosensor-modeling params.txt
