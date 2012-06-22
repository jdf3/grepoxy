#include <stdio.h>
#include <stdlib.h>

#define MV 32
#define MINCLIQUE 4
#define MAXCLIQUE 6
#define USAGE "addv forbiddencliquesize"

#define DEBUG 0

void printg6(int v, int am[][MV]);

/* input is a list of adjacency matrices generated by "showg -aq" */
int main(int argc, char *argv[])
{
    char *vstring;
    int i, j, max, b, sz, ct;
    char d;
    int v = 0;
    int am[MV][MV];
    int *startp3, *startkk, *p, *k;

    ct = 0;
    vstring = malloc(2*sizeof(char));
    startp3 = malloc(MV*sizeof(int));
    startkk = malloc(MV*sizeof(int));
    if (argc != 2) {
        fprintf(stderr, USAGE);
    }

    sz = atoi(argv[1]);

    while (fgets(vstring, 8, stdin) != 0) {
        v = atoi(vstring);
        i = 0;
        j = 0;
        while (i < v && (d = getchar()) != EOF) {
            if (d == '\n') {
                ++i;
                j = 0;
            } else {
                am[i][j] = atoi(&d);
                ++j;
            }
        }
        max = 2 << v;
        // Add a vertex and all possible edges and print the g6
        // representation if the graph is a (C4, Kk)-graph.
        for (i = 0; i < max; i++) {
            p = startp3;
            k = startkk;
            for (j = 0; j < v; j++) {
                b = (i >> j) & 1;
                am[v][j] = b;
                am[j][v] = b;

                if (b == 1) {
                    *(p++) = j;
                } else {
                    *(k++) = j;
                }
            }
            *p = v;
            *k = v;
            am[v][v] = 0;
            if (hasp3(v, am, startp3) == 0 &&
                         hasindset(sz-1, v, am, startkk) == 0) {
                printg6(v+1, am);
            }
        }
        if (++ct % 100 == 0) {
            fprintf(stderr, "addv: %d input graphs processed so far.\n", ct);
        }
    }
}

/* Print a g6 representation of the graph given by am. */
void printg6(int v, int am[][MV])
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
