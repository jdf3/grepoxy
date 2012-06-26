#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "glueg.h"

size_t default_size = 0;

/* Should be public */
int hasindset(graph*, int, int*);
int hasp3(graph*);
int num_edges(graph*);
char* get_g6(graph*, char*);
void printg6(graph*);
graph* g6_to_gr(char*);

/* Should be private */
int _g6_order(int, int, char*);
void _free_neighborhoods(graph***, int);
graph*** _get_neighborhoods(int);
int _len_g6(int);
void _alloc_graph(graph*);
void _free_graph(graph*);


int main(int argc, char *argv[])
{
  char *g6 = NULL;
  graph*** neighborhoods; /* Allocated in get_neighborhoods */
  int max_min_deg = (int) NULL;
  int ind_set_size = (int) NULL;
  graph *g = (graph*) malloc(sizeof(graph));

  if (argc != 3) {
    fprintf(stderr, USAGE);
    return 1;
  }

  g->v = atoi(argv[1]);
  _alloc_graph(g);

  ind_set_size = atoi(argv[2]);

  max_min_deg = floor((1 + sqrt((4 * g->v) - 3)) / 2);

  neighborhoods = _get_neighborhoods(max_min_deg);

  /* The meat of the program
  while (getline(&g6, &default_size, fsm_comp) != -1) {
    comp1 = g6_to_gr(g6);
  } */

  _free_neighborhoods(neighborhoods, max_min_deg);
  _free_graph(g);
  return 0;
}

/* Triple pointers may look scary, but this is really just
 * a 2D-array of pointers to graphs. */
graph*** _get_neighborhoods(int max_min_deg) {
  graph*** neigh = (graph***) malloc((max_min_deg + 1) * sizeof(graph**));
  graph** p;
  int i;
  char *g6 = NULL;
  char filename[20];
  FILE *fp;

  for (i = 0; i <= max_min_deg; i++) {
    /* There are exactly floor(n/2) + 1 p3-free graphs on n vertices */
    neigh[i] = (graph**) malloc((i/2 + 1) * sizeof(graph*));
    sprintf(filename, "p3n%d.g6", i);
    fp = fopen(filename, "r");
    p = neigh[i];

    while (getline(&g6, &default_size, fp) != -1) {
      *p = g6_to_gr(g6);
      p += 1;
    }
  }
  return neigh;
}

void _free_neighborhoods(graph*** neighborhoods, int max_min_deg) {
  int i, j;
  for (i = 0; i <= max_min_deg; i++) {
    for (j = 0; j <= i/2; j++) {
      _free_graph(neighborhoods[i][j]);
    }
    free(neighborhoods[i]);
  }
  free(neighborhoods);
}

int hasp3(graph *g) {
  int i, j, ct;

  for (i = 2; i < g->v; i++) {
    ct = 0;
    for (j = 0; j < i; j++) {
      if (g->A[i][j] == 1) {
        if (ct == 1) {
          return 1;
        } else {
          ct++;
        }
      }
    }
  }
  return 0;
}

int num_edges(graph *g) {
  int i, j, ne;

  for (i = 1; i < g->v; i++) {
    for (j = 0; j < i; j++) {
      if (g->A[i][j] == 1) {
        ne++;
      }
    }
  }
  return ne;
}

/* Determine if the vertices given by startkk contain an independent
 * set of size sz in g. */
int hasindset(graph *g, int sz, int *startkk)
{
  int i1, i2, i3, i4, i5, i6, i7;
  int *p1, *p2, *p3, *p4, *p5, *p6, *p7;

  p1 = startkk;
  switch (sz) {
    case 4:
     for (i1 = *p1; i1 < g->v; i1 = *(++p1)) {
      p2 = p1 + 1;
      for (i2 = ((*p2 > 0) ? *p2 : g->v); i2 < g->v; i2 = *(++p2)) {
       p3 = p2 + 1;
       if (g->A[i1][i2] == 0) {
        for (i3 = ((*p3 > 0) ? *p3 : g->v); i3 < g->v; i3 = *(++p3)) {
         p4 = p3 + 1;
         if (g->A[i1][i3] == 0 && g->A[i2][i3] == 0){
          for (i4 = ((*p4 > 0) ? *p4 : g->v); i4 < g->v; i4 = *(++p4)) {
           if (g->A[i1][i4] == 0 && g->A[i2][i4] == 0 &&
                g->A[i3][i4] == 0) {
            if (DEBUG) fprintf(stderr, "(%d, %d, %d, %d)", i1, i2, i3, i4);
            return 1;
           }
          }
         }
        }
       }
      }
     }
     return 0;

    case 5:
     for (i1 = *p1; i1 < g->v; i1 = *(++p1)) {
      p2 = p1 + 1;
      for (i2 = ((*p2 > 0) ? *p2 : g->v); i2 < g->v; i2 = *(++p2)) {
       p3 = p2 + 1;
       if (g->A[i1][i2] == 0) {
        for (i3 = ((*p3 > 0) ? *p3 : g->v); i3 < g->v; i3 = *(++p3)) {
         p4 = p3 + 1;
         if (g->A[i1][i3] == 0 && g->A[i2][i3] == 0){
          for (i4 = ((*p4 > 0) ? *p4 : g->v); i4 < g->v; i4 = *(++p4)) {
           p5 = p4 + 1;
           if (g->A[i1][i4] == 0 && g->A[i2][i4] == 0 &&
               g->A[i3][i4] == 0) {
            for (i5 = ((*p5 > 0) ? *p5 : g->v); i5 < g->v; i5 = *(++p5)) {
             if (g->A[i1][i5] == 0 && g->A[i2][i5] == 0 &&
                 g->A[i3][i5] == 0 && g->A[i4][i5] == 0) {
              if (DEBUG) fprintf(stderr, "(%d, %d, %d, %d, %d)", i1, i2, i3, i4, i5);
              return 1;
             }
            }
           }
          }
         }
        }
       }
      }
     }
     return 0;

    case 6:
     for (i1 = *p1; i1 < g->v; i1 = *(++p1)) {
      p2 = p1 + 1;
      for (i2 = ((*p2 > 0) ? *p2 : g->v); i2 < g->v; i2 = *(++p2)) {
       p3 = p2 + 1;
       if (g->A[i1][i2] == 0) {
        for (i3 = ((*p3 > 0) ? *p3 : g->v); i3 < g->v; i3 = *(++p3)) {
         p4 = p3 + 1;
         if (g->A[i1][i3] == 0 && g->A[i2][i3] == 0){
          for (i4 = ((*p4 > 0) ? *p4 : g->v); i4 < g->v; i4 = *(++p4)) {
           p5 = p4 + 1;
           if (g->A[i1][i4] == 0 && g->A[i2][i4] == 0 &&
               g->A[i3][i4] == 0) {
            for (i5 = ((*p5 > 0) ? *p5 : g->v); i5 < g->v; i5 = *(++p5)) {
             p6 = p5 + 1;
             if (g->A[i1][i5] == 0 && g->A[i2][i5] == 0 &&
                 g->A[i3][i5] == 0 && g->A[i4][i5] == 0) {
              for (i6 = ((*p6 > 0) ? *p6 : g->v); i6 < g->v; i6 = *(++p6)) {
               if (g->A[i1][i6] == 0 && g->A[i2][i6] == 0 &&
                   g->A[i3][i6] == 0 && g->A[i4][i6] == 0 &&
                   g->A[i5][i6] == 0) {
                if (DEBUG) fprintf(stderr, "(%d, %d, %d, %d, %d, %d)", i1, i2, i3, i4, i5, i6);
                return 1;
               }
              }
             }
            }
           }
          }
         }
        }
       }
      }
     }
     return 0;

    case 7:
     for (i1 = *p1; i1 < g->v; i1 = *(++p1)) {
      p2 = p1 + 1;
      for (i2 = ((*p2 > 0) ? *p2 : g->v); i2 < g->v; i2 = *(++p2)) {
       if (g->A[i1][i2] == 0) {
        p3 = p2 + 1;
        for (i3 = ((*p3 > 0) ? *p3 : g->v); i3 < g->v; i3 = *(++p3)) {
         if (g->A[i1][i3] == 0 && g->A[i2][i3] == 0){
          p4 = p3 + 1;
          for (i4 = ((*p4 > 0) ? *p4 : g->v); i4 < g->v; i4 = *(++p4)) {
           if (g->A[i1][i4] == 0 && g->A[i2][i4] == 0 &&
               g->A[i3][i4] == 0) {
            p5 = p4 + 1;
            for (i5 = ((*p5 > 0) ? *p5 : g->v); i5 < g->v; i5 = *(++p5)) {
             if (g->A[i1][i5] == 0 && g->A[i2][i5] == 0 &&
                 g->A[i3][i5] == 0 && g->A[i4][i5] == 0) {
              p6 = p5 + 1;
              for (i6 = ((*p6 > 0) ? *p6 : g->v); i6 < g->v; i6 = *(++p6)) {
               if (g->A[i1][i6] == 0 && g->A[i2][i6] == 0 &&
                   g->A[i3][i6] == 0 && g->A[i4][i6] == 0 &&
                   g->A[i5][i6] == 0) {
                p7 = p6 + 1;
                for (i7 = ((*p7 > 0) ? *p7 : g->v); i7 < g->v; i7 = *(++p7)) {
                 if (g->A[i1][i7] == 0 && g->A[i2][i7] == 0 &&
                    g->A[i3][i7] == 0 && g->A[i4][i7] == 0 &&
                    g->A[i5][i7] == 0 && g->A[i6][i7] == 0) {
                  if (DEBUG) fprintf(stderr, "(%d, %d, %d, %d, %d, %d, %d)", i1, i2, i3, i4, i5, i6, i7);
                 return 1;
                 }
                }
               }
              }
             }
            }
           }
          }
         }
        }
       }
      }
     }
     return 0;
  }
  return 0;
}

char* get_g6(graph *g, char *g6) {
  int c, r, i, sixbit;
  int vert = _len_g6(g->v);
  g6 = (char*) malloc(vert*sizeof(char));

  if (0 <= g->v && g->v <= 62)
    sprintf(g6, "%c", g->v + 63);
  else if (63 <= g->v && g->v <= 258047)
    sprintf(g6, "%c%c%c%c", 126, g->v >> 12, g->v >> 6, g->v);
  else if (258048 <= g->v) /* && g->v <= 68719476735) */
    sprintf(g6, "%c%c%c%c%c%c%c%c", 126, 126, g->v >> 30, g->v >> 24,
           g->v >> 18, g->v >> 12, g->v >> 6, g->v);
  else {
    fprintf(stderr, "I can't deal with that many vertices...\n");
    exit(EXIT_FAILURE);
  }

  i = 0;
  sixbit = 0;
  for (c = 1; c < g->v; c++) {
    for (r = 0; r < c; r++) {
      sixbit = (sixbit << 1) + g->A[r][c];
      ++i;
      if (i == 6) {
        sprintf(g6, "%s%c", g6, 63 + sixbit);
        i = 0;
        sixbit = 0;
      }
    }
  }
  if (i != 0) {
    sixbit = sixbit << (6 - i);
    sprintf(g6, "%s%c", g6, 63 + sixbit);
  }
  return g6;
}

int _g6_order(int s, int e, char *g6) {
  int vert = 0;
  while (s < e) {
    vert += (((g6[s]) - 63) << (6 * (e - 1 - s)));
    s++;
    }
  return vert;
}

graph* g6_to_gr(char *g6) {
  int i, j;
  int sb, d;
  graph *g = (graph*) malloc(sizeof(graph));

  if ((g6[0]) != 126) {
    g->v = _g6_order(0, 1, g6);
    g6++;
  } else if (g6[1] != 126) {
    g->v = _g6_order(1, 4, g6);
    g6 += 4;
  } else {
    g->v = _g6_order(2, 8, g6);
    g6 += 8;
  }

  _alloc_graph(g);

  sb = (g6[0]) - 63;
  g6++;
  d = 6;
  for (i = 1; i < g->v; i++) {
    for (j = 0; j < i; j++) {
      if (d == 0) {
        sb = (g6[0]) - 63;
        g6++;
        d = 6;
      }
      if (((sb >> (d - 1)) % 2) == 1) {
        g->A[i][j] = 1;
        g->A[j][i] = 1;
      } else {
        g->A[i][j] = 0;
        g->A[j][i] = 0;
      }
      d--;
    }
  }
  return g;
}

void _alloc_graph(graph *g) {
  int i;
  g->A = (int **) malloc(g->v*sizeof(int*));
  for (i = 0; i < g->v; i++) {
    g->A[i] = (int *) malloc(g->v*sizeof(int));
  }
}

void _free_graph(graph *g) {
  int i;

  for (i = 0; i < g->v; i++) {
    free(g->A[i]);
  }
  free(g->A);
  free(g);
}

int _len_g6(int vertices) {
  int ord;
  if (vertices < 63) {
    ord = 1;
  } else if (vertices < 258048) {
    ord = 4;
  } else {
    ord = 8;
  }
  return (ord + vertices*(vertices-1)/12 + 1);
}
