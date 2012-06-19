#include <stdio.h>
#include <stdlib.h>

#define MV 32
#define MINCLIQUE 4
#define MAXCLIQUE 6
#define USAGE "addv: usage: addv (forbiddencliquesize)\n"

#define DEBUG 0

int hasp3(int v, int am[][MV], int *startp3);
int hasindset(int sz, int v, int am[][MV], int *startkk);
void printg6(int v, int am[][MV]);
int hasc4(int v, int am[][MV]);
int hasindsetnoptr(int sz, int v, int am[][MV]);

