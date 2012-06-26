#ifndef _GLUEG
#define _GLUEG

#define MV 32
#define MINCLIQUE 4
#define MAXCLIQUE 7
#define USAGE "glueg vertices forbiddenindsetsize"

#define DEBUG 0

typedef struct GraphStruct {
  int v;
  int** A;
} graph;

#endif
