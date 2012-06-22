#include <stdio.h>
#include <stdlib.h>

#include "g6.h"

void _alloc_am();
void _realloc_am();

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

  if (am_sz == 0) _alloc_am();
  else if (v > am_sz) _realloc_am();

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

void _alloc_am() {
  int i;

  am_sz = 2*v;
  am = (int**) malloc(am_sz*sizeof(int**));
  for (i = 0; i < am_sz; i++) {
    am[i] = (int*) malloc(am_sz*sizeof(int*));
  }
}

void _realloc_am() {
  int i, j;
  int nam_sz;
  int **nam;

  nam_sz = 2*v;
  nam = (int**) malloc(nam_sz*sizeof(int*));
  for (i = 0; i < nam_sz; i++) {
    nam[i] = (int*) malloc(nam_sz*sizeof(int));
  }
  for (i = 0; i < am_sz; i++) {
    for (j = 0; j < am_sz; j++) {
      nam[i][j] = am[i][j];
    }
    free(am[i]);
  }
  free(am);
  am = nam;
  for (i = 0; i < nam_sz; i++) {
    free(nam[i]);
  }
  free(nam);
  //am_sz = 2*v;
}

void free_adj_mat(int **A, int size) {
  int i;

  for (i = 0; i < size; i++) {
    free(A[i]);
  }
  free(A);
}

/* print adjacency matrix in g6 format */
void print_g6()
{
  int c, r;
  int i, sixbit;

  if (0 <= v && v <= 62)
    printf("%c", v + 63);
  else if (63 <= v && v <= 258047)
    printf("%c%c%c%c", 126, v >> 12, v >> 6, v);
  else if (258048 <= v) /* (&& v <= 68719476735) */
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
        printf("%c", (63 + sixbit));
        i = 0;
        sixbit = 0;
      }
    }
  }
  if (i != 0) {
    sixbit = sixbit << (6 - i);
    printf("%c", (63 + sixbit));
  }
  printf("\n");
}
