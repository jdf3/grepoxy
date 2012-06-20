#ifndef _G6_H
#define _G6_H

int v;
int **am;
int am_sz;

void g6_to_am(char *g6);
void print_g6();
void free_adj_mat(int**, int);

#endif
