#!/usr/bin/env bash
echo ------------------ Building tests ------------------
cd tests
make clean
make
echo ------------------ Running tests -------------------
./biosensor-modeling-unittests
