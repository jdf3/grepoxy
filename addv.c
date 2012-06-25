#include <stdio.h>
#include <stdlib.h>

#include "addv.h"
int v = 0;
int am[][MV];
int num_bytes = (MV-1)*MV/12 + 1;
int oldv;

void print_g6();
void g6_to_am(char*);
void print_am();

int main(int argc, char *argv[])
{
    char *g6 = (char *) malloc(num_bytes + 1);
    int i, j, max, b, sz, ct, oldv;
    char d;
    int *startp3, *startkk, *p, *k;

    ct = 0;
    startp3 = malloc(MV*sizeof(int));
    startkk = malloc(MV*sizeof(int));
    if (argc != 2) {
        fprintf(stderr, USAGE);
    }

    sz = atoi(argv[1]);

    while (getline(&g6, &num_bytes, stdin) != EOF) {
        g6_to_am(g6);
        oldv = v;
        ++v;
        max = 2 << v;
        // Add a vertex and all possible edges and print the g6
        // representation if the graph is a (C4, Kk)-graph.
        for (i = 0; i < max; i++) {
            p = startp3;
            k = startkk;
            for (j = 0; j < v; j++) {
                b = (i >> j) & 1;
                if (DEBUG) printf("v = %d, i = %d, j = %d, b = %d\n", v, i, j, b);
                am[oldv][j] = b;
                am[j][oldv] = b;
                if (DEBUG) printf("am[v][j] = %d, am[j][v] = %d\n", am[v][j], am[j][v]);
                if (DEBUG) {
                  printf("\n");
                  print_am(am);
                  printf("\n");
                }

                if (b == 1) {
                    *(p++) = j;
                } else {
                    *(k++) = j;
                }
            }
            *p = v;
            *k = v;
            am[oldv][oldv] = 0;
            if (hasp3(startp3) == 0 &&
                         hasindset(sz-1, startkk) == 0) {
                print_g6();
                if (DEBUG) print_am();
            }
        }
        if (++ct % 100 == 0) {
            fprintf(stderr, "addv: %d input graphs processed so far.\n", ct);
        }
    }
    free(startp3);
    free(startkk);
    free(g6);
}

/* Determine if the vertices given by startp3 make a P3 in am. */
int hasp3(int *startp3)
{
    int i, j, k, ct;
    int *p, *r;

    p = startp3;
    if (DEBUG) fprintf(stderr, "\n");

    for (i = *p; i < v; i = *(++p)) {
        ct = 0;
        r = p+1;
        for (j = *r; j < v; j = *(++r)) {
            for (k = 0; k < v-1; k++) {

                if (am[i][k] == 1 && am[j][k] == 1) {
                    if (DEBUG) fprintf(stderr, "(%d, %d, %d) is a P3\n", i, j, k);
                    return 1;
                }
            }
            if (DEBUG) fprintf(stderr, "(%d, %d) do not form a P3\n", i, j);
        }
        //free(r);
    }
    //free(p);
    return 0;
}

/* Determine if the vertices given by startkk contain an independent
 * set of size sz in am. */
int hasindset(int sz, int *startkk)
{
    int i1, i2, i3, i4, i5, i6, k;
    int *p1, *p2, *p3, *p4, *p5, *p6, *d;

    /*p1 = malloc(sizeof(startkk));
    p2 = malloc(sizeof(startkk));
    p3 = malloc(sizeof(startkk));
    p4 = malloc(sizeof(startkk));
    p5 = malloc(sizeof(startkk));
    p6 = malloc(sizeof(startkk));*/
    if (DEBUG) {
        d = startkk;
        k = *d;
        while (k < v) {
            fprintf(stderr, "%d ", k = *(d++));
        }
        fprintf(stderr, "\n");
    }
    p1 = startkk;
    switch (sz) {
        case 4:
         for (i1 = *p1; i1 < v; i1 = *(++p1)) {
          p2 = p1 + 1;
          if (DEBUG) fprintf(stderr, "l1: (%d, %d, %d, %d)", i1, *p2, *(p2+1), *(p2+2));
          for (i2 = ((*p2 > 0) ? *p2 : v); i2 < v; i2 = *(++p2)) {
           p3 = p2 + 1;
           if (am[i1][i2] == 0) {
            for (i3 = ((*p3 > 0) ? *p3 : v); i3 < v; i3 = *(++p3)) {
             p4 = p3 + 1;
             if (am[i1][i3] == 0 && am[i2][i3] == 0){
              for (i4 = ((*p4 > 0) ? *p4 : v); i4 < v; i4 = *(++p4)) {
               if (am[i1][i4] == 0 && am[i2][i4] == 0 &&
                   am[i3][i4] == 0) {
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
         for (i1 = *p1; i1 < v; i1 = *(++p1)) {
          p2 = p1 + 1;
          if (DEBUG) fprintf(stderr, "l1: (%d, %d, %d, %d, %d)", i1, *p2, *(p2+1), *(p2+2), *(p2+3));
          for (i2 = ((*p2 > 0) ? *p2 : v); i2 < v; i2 = *(++p2)) {
           p3 = p2 + 1;
           if (am[i1][i2] == 0) {
            for (i3 = ((*p3 > 0) ? *p3 : v); i3 < v; i3 = *(++p3)) {
             p4 = p3 + 1;
             if (am[i1][i3] == 0 && am[i2][i3] == 0){
              for (i4 = ((*p4 > 0) ? *p4 : v); i4 < v; i4 = *(++p4)) {
               p5 = p4 + 1;
               if (am[i1][i4] == 0 && am[i2][i4] == 0 &&
                   am[i3][i4] == 0) {
                for (i5 = ((*p5 > 0) ? *p5 : v); i5 < v; i5 = *(++p5)) {
                 if (am[i1][i5] == 0 && am[i2][i5] == 0 &&
                     am[i3][i5] == 0 && am[i4][i5] == 0) {
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
         if (DEBUG) fprintf(stderr, "Graph has no ind set of size %d", sz);
         return 0;

        case 6:
         for (i1 = *p1; i1 < v; i1 = *(++p1)) {
          p2 = p1 + 1;
          if (DEBUG) fprintf(stderr, "l1: (%d, %d, %d, %d, %d, %d)", i1, *p2, *(p2+1), *(p2+2), *(p2+3), *(p2+4));
          for (i2 = ((*p2 > 0) ? *p2 : v); i2 < v; i2 = *(++p2)) {
           p3 = p2 + 1;
           if (am[i1][i2] == 0) {
            for (i3 = ((*p3 > 0) ? *p3 : v); i3 < v; i3 = *(++p3)) {
             p4 = p3 + 1;
             if (am[i1][i3] == 0 && am[i2][i3] == 0){
              for (i4 = ((*p4 > 0) ? *p4 : v); i4 < v; i4 = *(++p4)) {
               p5 = p4 + 1;
               if (am[i1][i4] == 0 && am[i2][i4] == 0 &&
                   am[i3][i4] == 0) {
                for (i5 = ((*p5 > 0) ? *p5 : v); i5 < v; i5 = *(++p5)) {
                 p6 = p5 + 1;
                 if (am[i1][i5] == 0 && am[i2][i5] == 0 &&
                     am[i3][i5] == 0 && am[i4][i5] == 0) {
                  for (i6 = ((*p6 > 0) ? *p6 : v); i6 < v; i6 = *(++p6)) {
                   if (am[i1][i6] == 0 && am[i2][i6] == 0 &&
                       am[i3][i6] == 0 && am[i4][i6] == 0 &&
                       am[i5][i6] == 0) {
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
    }
}
/* Print a g6 representation of the graph given by am. */
void print_g6()
{
    int c, r, i, sixbit;

    if (0 <= v && v <= 62)
        printf("%c", v + 63);
    else if (63 <= v && v <= 258047)
        printf("%c%c%c%c", 126, v >> 12, v >> 6, v);
    else if (258048 <= v && v <= 68719476735)
        printf("%c%c%c%c%c%c%c%c", 126, 126, v >> 30, v >> 24,
               v >> 18, v >> 12, v >> 6, v);
    else {
        fprintf(stderr, "I can't deal with that many vertices...\n");
        exit(EXIT_FAILURE);
    }

    i = 0;
    sixbit = 0;
    for (c = 1; c < v; c++) {
        for (r = 0; r < c; r++) {
            sixbit = (sixbit << 1) + am[r][c];
            ++i;
            if (i == 6) {
                printf("%c", 63 + sixbit);
                i = 0;
                sixbit = 0;
            }
        }
    }
    if (i != 0) {
        sixbit = sixbit << (6 - i);
        printf("%c", 63 + sixbit);
    }
    printf("\n");
}

/* Determine if am has a C4. */
int hasc4()
{
    int i, ct;
    int p = 0;

    for (i = 0; i < v; i++) {
        ct = 0;
        for (p = i + 1; p < v; p++) {
            if (am[i][p] == 1 && am[v-1][p] == 1) {
                ct++;
                if (ct == 2) return 1;
            }
        }
    }
    return 0;
}

/* Determine if the graph given by am has an independent set of size sz. */
int hasindsetnoptr(int sz)
{
    int i1, i2, i3, i4, i5, i6;

    //printf("%d", sz);
    switch (sz) {
        case 4:
         for (i1 = 0; i1 < v; i1++) {
          for (i2 = i1+1; i2 < v; i2++) {
           if (am[i1][i2] == 0) {
            for (i3 = i2+1; i3 < v; i3++) {
             if (am[i1][i3] == 0 && am[i2][i3] == 0){
              for (i4 = i3+1; i4 < v; i4++) {
               if (am[i1][i4] == 0 && am[i2][i4] == 0 && am[i3][i4] == 0)
                return 1;
               }
              }
             }
            }
           }
          }
         return 0;

        case 5:
         for (i1 = 0; i1 < v; i1++) {
          for (i2 = i1+1; i2 < v; i2++) {
           if (am[i1][i2] == 0) {
            for (i3 = i2+1; i3 < v; i3++) {
             if (am[i1][i3] == 0 && am[i2][i3] == 0){
              for (i4 = i3+1; i4 < v; i4++) {
               if (am[i1][i4] == 0 && am[i2][i4] == 0 && am[i3][i4] == 0) {
                for (i5 = i4+1; i5 < v; i5++) {
                 if (am[i1][i5] == 0 && am[i2][i5] == 0 && am[i3][i5] == 0 &&
                     am[i4][i5] == 0)
                  return 1;
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
         for (i1 = 0; i1 < v; i1++) {
          for (i2 = i1+1; i2 < v; i2++) {
           if (am[i1][i2] == 0) {
            for (i3 = i2+1; i3 < v; i3++) {
             if (am[i1][i3] == 0 && am[i2][i3] == 0){
              for (i4 = i3+1; i4 < v; i4++) {
               if (am[i1][i4] == 0 && am[i2][i4] == 0 &&
                   am[i3][i4] == 0) {
                for (i5 = i4+1; i5 < v; i5++) {
                 if (am[i1][i5] == 0 && am[i2][i5] == 0 &&
                     am[i3][i5] == 0 && am[i4][i5] == 0) {
                  for (i6 = i5+1; i6 < v; i6++) {
                   if (am[i1][i6] == 0 && am[i2][i6] == 0 &&
                       am[i3][i6] == 0 && am[i4][i6] == 0 &&
                       am[i5][i6] == 0)
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
         return 0;

        default:
            fprintf(stderr, "Currently, this program only detects cliques of size between %d and %d, inclusive.\n", \
                    MINCLIQUE, MAXCLIQUE);
    }
}

int _g6_order(int s, int e, char *g6) {
  int vert = 0;
  while (s < e) {
    vert += ((((int) g6[s]) - 63) << (6 * (e - 1 - s)));
    s++;
  }
  return vert;
}

void g6_to_am(char *g6) {
  int i, j;
  int sb, d;

  if (((int) g6[0]) != 126) {
    v = _g6_order(0, 1, g6);
    g6++;
  } else if ((int) g6[1] != 126) {
    v = _g6_order(1, 4, g6);
    g6 += 4;
  } else {
    v = _g6_order(2, 8, g6);
    g6 += 8;
  }

  sb = ((int) g6[0]) - 63;
  g6++;
  d = 6;
  for (i = 1; i < v; i++) {
    for (j = 0; j < i; j++) {
      if (d == 0) {
        sb = ((int) g6[0]) - 63;
        g6++;
        d = 6;
      }
      if (((sb >> (d - 1)) % 2) == 1) {
        am[i][j] = (int) 1;
        am[j][i] = (int) 1;
      } else {
        am[i][j] = (int) 0;
        am[j][i] = (int) 0;
      }
      d--;
    }
  }
}

void print_am() {
  int i, j;
  for (i = 0; i < v; i++) {
    for (j = 0; j < v; j++) {
      printf("%d ", am[i][j]);
    }
    printf("\n");
  }
}
