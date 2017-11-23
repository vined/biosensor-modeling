#!/usr/bin/env bash
echo ------------------ Building ------------------
cd src
make clean
make
echo ------------------ Running -------------------
./biosensor-modeling
