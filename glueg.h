#ifndef _GLUEG
#define _GLUEG

#define MV 32
#define MINCLIQUE 4
#define MAXCLIQUE 7
#define USAGE "glueg R(c4k(n-1)), forbiddenindsetsize"

#define DEBUG 0

typedef struct GraphStruct {
  int v;
  int** A;
} graph;
const size_t DEFAULT_SIZE = 0;
uint32_t *vcis;
#endif
