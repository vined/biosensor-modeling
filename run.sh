#!/usr/bin/env bash
echo ------------------ Cleaning up -------------------
rm out/*
rm biosensor-modeling

echo ------------------ Building ------------------
cd src
make clean
make
mv biosensor-modeling ../
cd ../

echo ------------------ Running -------------------
./biosensor-modeling params.txt
