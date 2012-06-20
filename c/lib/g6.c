#include <stdio.h>
#include <stdlib.h>

#include "g6.h"

void _alloc_am();
void _realloc_am();

unsigned int _g6_order(int s, int len, char *g6) {
  unsigned int vert = 0;
  unsigned short i = 0;
  while (i < len) {
    vert += ((((int) g6[s]) - 63) << (6 * (len - 1 - i)));
    i++;
  }
  return vert;
}

void g6_to_am(char *g6) {
  unsigned int i, j;
  unsigned short sb, d;

  if (((int) g6[0]) != 126) {
    v = _g6_order(0, 1, g6);
    g6++;
  } else if ((int) g6[1] != 126) {
    v = _g6_order(1, 3, g6);
    g6 += 4;
  } else {
    v = _g6_order(2, 6, g6);
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
        am[i][j] = (unsigned short) 1;
        am[j][i] = (unsigned short) 1;
      } else {
        am[i][j] = (unsigned short) 0;
        am[j][i] = (unsigned short) 0;
      }
      d--;
    }
  }
}

void _alloc_am() {
  int i;

  am_sz = 2*v;
  am = (unsigned short**) malloc(am_sz*sizeof(unsigned short**));
  for (i = 0; i < am_sz; i++) {
    am[i] = (unsigned short*) malloc(am_sz*sizeof(unsigned short*));
  }
}

void _realloc_am() {
  int i, j;
  unsigned int nam_sz;
  unsigned short **nam;

  nam_sz = 2*v;
  nam = (unsigned short**) malloc(nam_sz*sizeof(unsigned short*));
  for (i = 0; i < nam_sz; i++) {
    nam[i] = (unsigned short*) malloc(nam_sz*sizeof(unsigned short));
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

void free_adj_mat(unsigned short **A, unsigned int size) {
  unsigned int i;

  for (i = 0; i < size; i++) {
    free(A[i]);
  }
  free(A);
}

/* print adjacency matrix in g6 format */
void print_g6()
{
  unsigned int c, r;
  int i, sixbit;

        printf("\n1\n");
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
              printf("\n2\n");

        if ((63 + sixbit) > 126) printf("\n\nv = %d\n\n", v);
        printf("%c", 63 + sixbit);
        i = 0;
        sixbit = 0;
      }
    }
  }
  if (i != 0) {
    sixbit = sixbit << (6 - i);
          printf("\n3\n");
    printf("%c", 63 + sixbit);
    printf("\n4\n");
  }
  printf("\n");
}
