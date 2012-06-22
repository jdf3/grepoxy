#ifndef _SET_OPERATIONS_H
#define _SET_OPERATIONS_H

#include <vector>
#include <stdint.h>

using namespace std;

typedef vector<bool> vset;
/*const int intSize = sizeof(vset) * 8;
const vset shifter = 1;
const vset empty = 0;*/

void set_insert(int u, vset &S);
void set_delete(int u, vset &S);
bool in_set(int u, vset &S);
/*void set_cut(int u, vset S, int arraySize);
vset set_union(vset S, vset R);
vset set_intersection(vset S, vset R);*/
bool not_empty(vset &S);

#endif
