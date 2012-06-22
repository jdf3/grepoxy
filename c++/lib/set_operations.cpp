#include <vector>
#include <iostream>
#include "set_operations.h"

/* A set of functions for set operations when a set is a 64 bit unsigned
   integer.

   All algorithms based off those described in Chapter 1 of the textbook
   "Combinatorial Algorithms" by Donald Kreher and Douglas Stinson
*/

// insert bit into set
void set_insert(int u, vset &V){
  V[u] = 1;
}

// delete bit from set
void set_delete(int u, vset &V) {
  V[u] = 0;
}

// determine if a bit is in V
bool in_set(int u, vset &V) {
  return (V[u] == 0) ? false : true;
}

// I WAS RIGHT HERE

// removes bit from set
/*
void set_cut(int u, vset V, int arraySize) {
  int j = u % intSize;
  uint64_t x = (V & ((~empty) >> (j+1))) << 1;
  if (j == 0) {
    V = x;
  }
  else if (j != (intSize - 1)) {
    uint64_t y = (V & ((~empty) << (intSize-j)));
    V = x | y;
  }
  //cout << "j " << j << endl;
  // cout << "i " << i << endl;
  for (; i < arraySize - 1; i++) {
    if (in_set((i+1)*intSize, S)) {
      V = V | shifter;
    } else {
      V = (V & ((~empty)<<1));
    }
    S[i+1] = S[i+1] << 1;
  }
}

// determine union of two sets
vset set_union(vset S, vset R) {
  return S | R;
}

// determine intersection of two sets
// Algorithm 1.7
uint64_t set_intersection(uint64_t S, uint64_t R, int arraySize) {
  return S & R;
}
*/

// determine if a set is empty
bool not_empty(vset &V) {
  for (vset::iterator it = V.begin(); it != V.end(); it++) {
    if (*it != 0) return true;
  }
  return false;
}
