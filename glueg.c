#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "glueg.h"

/* Globals from glueg.h */
uint32_t *
const size_t DEFAULT_SIZE;

/* Should be public */
int hasindset(graph*, int, int*);
int hasp3(graph*);
int num_edges(graph*);
void get_g6(graph*, char*);
void printg6(graph*);
void g6_to_gr(graph*, char*, int);
int det_max_vert(int);
int det_max_min_deg(int);

/* Should be private */
int _g6_order(int, int, char*);
void _free_neighborhoods(graph***, int);
void _get_neighborhoods(graph***, int);
int _len_g6(int);
void _realloc_graph(graph*, int);
void _free_graph(graph*);


int main(int argc, char *argv[])
{
  char *g6 = NULL;
  char *filename;
  FILE *fcomp;
  graph*** neighborhoods;
  graph** curr_neighs;
  int max_min_deg, old_ramsey_num, min_vert, max_vert, largest_crit;
  int avoid_iset, old_iset;
  int i, j, k, l, m, max;
  int *mmds;
  uint32_t *hp3ep, *vcis, *clos, *bsep, *helper, *clos_help;
  uint32_t set_end, bs_helper, intset;
  int **endpts;
  int *covered;
  graph *g;

  if (argc != 3) {
    fprintf(stderr, USAGE);
    return 1;
  }

  _populate_mmds(mmds);
  old_ramsey_num = atoi(argv[1]);
  max_vert = det_max_vert(old_ramsey_num - 1);

  neighborhoods = (graph***) malloc((mmds[max_vert] + 1) * sizeof(graph**));
  _get_neighborhoods(neighborhoods, mmds[max_vert]);

  mmds = (int*) malloc((max_vert + 2)*sizeof(int));
  for (i = 0; i <= (max_vert + 2); i++) {
    mmds[i] = det_max_min_deg(i);
  }

  /* We can always add a triangle, so the new number must be at least
   * three larger than the number of vertices in the largest
   * critical graph before. */
  min_vert = old_ramsey_num + 2;

  /* Rather than play around with memory allocation/reallocation,
   * we have a graph of each possible size. */
  **gs = (graph**) malloc((max_vert - min_vert + 1) * sizeof(graph*));
  for (i = 0; i < (max_vert - min_vert + 1); i++) {
    _realloc_graph(gs[i], (i + min_vert));
    gs[i]->v = (i + min_vert);
  }

  avoid_iset = atoi(argv[2]);
  old_iset = avoid_iset - 1;
  largest_crit = old_ramsey_num - 1;

  /* These are arrays to help with doing things */
  hp3ep = (uint32_t*) malloc((1 << largest_crit) * sizeof(uint32_t));
  vcis = (uint32_t*) malloc((1 << largest_crit) * sizeof(uint32_t));
  clos = (uint32_t*) malloc((1 << largest_crit) * sizeof(uint32_t));

  clos_help = (uint32_t*) malloc(largest_crit * sizeof(uint32_t));

  endpts = (int**) malloc(largest_crit * sizeof(int*));
  for (i = 0; i < largest_crit; i++) {
    endpts[i] = (int*) malloc(largest_crit * sizeof(int));
  }
  bsep = (uint32_t*) malloc(largest_crit * largest_crit * sizeof(uint32_t));
  for (i = min_vert - mmds[min_vert]; i <= largest_crit; i++) {
    sprintf(filename, "c4k%dn%d.g6", old_iset, i);
    fcomp = fopen(filename, "r");

    for (max = 0; ((min_vert + max) - mmds[min_vert + max] - 1) <= i; max++);

    while (getline(&g6, &DEFAULT_SIZE, fcomp) != -1) {
      /* fill the graph */
      g6_to_gr(g, g6, 0);

      /* endpts[j][k] is 1 iff j and k are the end points of some P3 in
       * the graph */
      for (j = 0; j < i; j++) {
        for (k = 0; k < i; k++) {
          endpts[j][k] = 0;
          endpts[k][j] = 0;
        }
      }
      for (j = 0; j < i; j++) {
        for (k = 1; k < j; k++) {
          for (l = 0; l < k; l++) {
            if (g6[0]->A[j][k] && g6[0]->A[j][l]) {
              endpts[k][l] = 1;
            }
          }
        }
      }
      helper = bsep;
      for (j = 1; j < i; j++) {
        for (k = 0; k < j; k++) {
          if (endpts[j][k]) {
            *(helper++) = (1 << j) + (1 << k);
            /* helper++; */
          }
        }
      }
      *helper = 0;

      set_end = (1 << i);
      for (bs_helper = 0; bs_helper < set_end; bs_helper++) {
        hp3ep[bs_helper] = 0;
        for (helper = bsep; *helper > 0; helper++) {
          if (*helper & bs_helper == *helper) {
            hp3ep[bs_helper] = 1;
          }
        }
      }
      /* hp3ep is now properly filled. */

      /* fill clos */
      for (j = 0; j < i; j++) {
        clos_help[j] = (1 << j);
        for (k = 0; k < i; k++) {
          if (g6[0]->A[j][k]) {
            clos_help[j] |= (1 << k);
          }
        }
      }

      for (bs_helper = 0; bs_helper < set_end; bs_helper++) {
        clos[bs_helper] = bs_helper;
        for (j = 0; j < i; j++) {
          if ((bs_helper >> (i - 1 - j)) % 1) {
            clos[bs_helper] |= clos_help[j];
          }
        }
      }
      /* clos is now properly filled.
       * now compute all independence numbers of V \ S for every subset S
       * of V */
      _fill_vcis((uint32_t) ((1 < i) - 1), (uint32_t) 0, 0, 0, i);
      /* vcis is now properly filled. */

      for (j = 2; j <= mmds[j+i]; j++) {
        /* There are exactly floor(n/2) + 1 p3-free graphs on n vertices */
        curr_neighs = neighborhoods[j];
        for (k = 0; k < floor(n/2) + 1; k++) {




      /* Here is where I would iterate through the possible neighborhoods */
    }
  _free_neighborhoods(neighborhoods, max_min_deg);
  _free_graph(g);
  return 0;
}

void _populate_mmds(int *mmds) {
  int i;
  for (i = 0; i < MV; i++) {
    mmds[i] = det_max_min_deg(i);
  }
}

/* Three choices: either we use the vertex, saying we saw it, don't use
 * the vertex, saying we saw it, or don't use the vertex and don't say
 * that we saw it. */
/* v should probably be global here */
void _fill_vcis(uint32_t VminusS, uint32_t IS, int iset_size, int next, int v) {
  if (next > v) {
    if (iset_size > vcis[VminusS]) {
      vcis[VminusS] = iset_size;
    }
    exit(0);
  }
  if is_ind(IS, next) {
    fill_vcis(VminusS & ~(1 << next), IS | (1 << next), iset_size + 1, next + 1, v);
  }
  fill_vcis(VminusS, IS, iset_size, next + 1, v);
  fill_vcis(VminusS & ~(1 << next), IS, iset_size, next + 1, v);
}

/* The expression is derived by solving for n in the equation
 * m + (1/2)(1 + sqrt(4n - 3)) + 1 >= n, where m := orm. */
int det_max_vert(int orm) {
  return ((orm + 2) + floor(sqrt(orm + 1)));
}

/* This expression follows from the minimum degree being bounded above
 * by 0.5*(1 + sqrt(4n-3)), where n is the number of vertices, for any
 * C4-free graph */
int det_max_min_deg(int vertices) {
  return floor(0.5 * (1 + sqrt((4 * vertices) - 3)));
}

/* Triple pointers may look scary, but this is really just
 * a 2D-array of pointers to graphs. */
void _get_neighborhoods(graph ***neigh, int max_min_deg) {
  graph** p;
  int i;
  char *g6 = NULL;
  char filename[20];
  FILE *fp;

  for (i = 1; i <= max_min_deg; i++) {
    /* There are exactly floor(n/2) + 1 p3-free graphs on n vertices */
    neigh[i] = (graph**) malloc((i/2 + 1) * sizeof(graph*));
    sprintf(filename, "p3n%d.g6", i);
    fp = fopen(filename, "r");
    p = neigh[i];

    while (getline(&g6, &DEFAULT_SIZE, fp) != -1) {
      *p = g6_to_gr(g6);
      p += 1;
    }
  }
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
      if (g->A[i][j]) {
        if (ct) {
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
      if (g->A[i][j]) {
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
              if (DEBUG) fprintf(stderr, "(%d, %d, %d, %d, %d)",
                                           i1, i2, i3, i4, i5);
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
                if (DEBUG) fprintf(stderr, "(%d, %d, %d, %d, %d, %d)",
                                             i1, i2, i3, i4, i5, i6);
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
                  if (DEBUG) fprintf(stderr, "(%d, %d, %d, %d, %d, %d, %d)",
                                               i1, i2, i3, i4, i5, i6, i7);
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

void get_g6(char *g6, graph *g) {
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


void g6_to_gr(graph *g, char *g6, int pos = 0) {
  int i, j;
  int sb, d;
  int vert, max;
  char *g6cpy = g6;

  if ((g6cpy[0]) != 126) {
    vert = _g6_order(0, 1, g6cpy);
    g6cpy++;
  } else if (g6cpy[1] != 126) {
    vert = _g6_order(1, 4, g6cpy);
    g6cpy += 4;
  } else {
    vert = _g6_order(2, 8, g6cpy);
    g6cpy += 8;
  }

  sb = (g6cpy[0]) - 63;
  g6cpy++;
  max = vert + pos;
  d = 6;
  for (i = (1 + pos); i < max; i++) {
    for (j = (1 + pos); j < i; j++) {
      if (d == 0) {
        sb = (g6cpy[0]) - 63;
        g6cpy++;
        d = 6;
      }
      if (((sb >> (d - 1)) % 2)) {
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

void _realloc_graph(graph *g, int size) {
  int i;
  g->A = (int **) realloc(g->A, size*sizeof(int*));
  for (i = 0; i < size; i++) {
    g->A[i] = (int *) realloc(g->A[i], size*sizeof(int));
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

void print_gr(graph *g) {
  int i, j;

  printf("Order: %d", g->v);

  for (i = 0; i < g->v; i++) {
    for (j = 0; j < g->v; j++) {
      printf("%d ", g->A[i][j]);
    }
    printf("\n");
  }
}
