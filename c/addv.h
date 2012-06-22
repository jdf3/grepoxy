#include <stdio.h>
#include <stdlib.h>

#define MINCLIQUE 4
#define MAXCLIQUE 6
#define USAGE "usage: addv (forbiddencliquesize)\n"

#define DEBUG 0

int num_bytes = 128;
int sz;

int hasp3(int v, int *startp3);
int has_ind_set(int sz, int *startkk);
int hasc4();
int hasindsetnoptr(int sz);
void add_vertex();
int makesp3(int *e, int s);
int makes_ind_set(int *ne, int s);
