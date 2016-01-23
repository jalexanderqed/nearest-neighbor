#!/bin/bash

clear

echo
echo Optimal
time ./randData $1 | ./closestPair optimal

echo
echo Basic
time ./randData $1 | ./closestPair basic

echo
echo Brute
time ./randData $1 | ./closestPair brute
