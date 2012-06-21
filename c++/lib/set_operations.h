#ifndef _SET_OPERATIONS_H
#define _SET_OPERATIONS_H

#include <vector>
#include <stdint.h>

using namespace std;

const int intSize = sizeof(uint64_t) * 8;
const uint64_t shifter = 1;
const uint64_t empty = 0;

void set_insert(int u, uint64_t S);
void set_delete(int u, uint64_t S);
bool in_set(int u, uint64_t S);
void set_cut(int u, uint64_t S, int arraySize);
uint64_t set_union(uint64_t S, uint64_t R);
uint64_t set_intersection(uint64_t S, uint64_t R);
bool not_empty(uint64_t S);

#endif
