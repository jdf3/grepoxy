#include <stdio.h>
#include <stdlib.h>

#define MINCLIQUE 4
#define MAXCLIQUE 6
#define USAGE "usage: addv (forbiddencliquesize)\n"

#define DEBUG 0

unsigned int num_bytes = 128;
unsigned int sz;

int hasp3(int v, int *startp3);
int hasindset(int sz, int *startkk);
int hasc4();
int hasindsetnoptr(int sz);
void add_vertex();
int makesp3(unsigned int *e, unsigned int s);
int makes_ind_set(unsigned int *ne, unsigned int s);
