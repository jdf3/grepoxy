#!/bin/bash

cd c++/
g++ -Wall -pedantic -g -o tests tests.cpp lib/g.cpp lib/set_operations.cpp
g++ -Wall -pedantic -g -o vextend vextend.cpp lib/g.cpp lib/set_operations.cpp
cd .. && cd c/
gcc -Wall -pedantic -o addv addv.c lib/g6.c
