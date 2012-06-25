#!/bin/bash

cd c
gcc -Wall -pedantic -o addv addv.c
gcc -Wall -pedantic -o glueg glueg.c
cd old
gcc -Wall -pedantic -o addv addv.c
