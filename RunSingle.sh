#!/bin/bash

#./randData 100000 > test_data.txt
echo Optimal
./closestPair optimal < test_data.txt
echo Basic
./closestPair basic < test_data.txt
echo Brute
./closestPair brute < test_data.txt
