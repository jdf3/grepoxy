#include <vector>
#include <iostream>
#include "set_operations.h"

/* A set of functions for set operations when a set is a 64 bit unsigned
   integer.

   All algorithms based off those described in Chapter 1 of the textbook
   "Combinatorial Algorithms" by Donald Kreher and Douglas Stinson
*/

// insert bit into set
// algorithm 1.3
void set_insert(int u, vector<bool> V){
  int j = intSize - 1 - (u % intSize);
  V = V | (shifter << j);
}

// delete bit from set
// Algorithm 1.4
void set_delete(int u, uint64_t V) {
  int j = intSize - 1 - (u % intSize);
  V = V & ~(shifter << j);
}

// determine if a bit is in S
// Algorithm 1.5
bool in_set(int u, uint64_t V) {
  int j = intSize - 1 - (u % intSize);
  if (V & (shifter << j)) {
    return true;
  } else {
    return false;
  }
}

// I WAS RIGHT HERE

// removes bit from set
/*
void set_cut(int u, uint64_t V, int arraySize) {
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
}*/

// determine union of two sets
// Algorithm 1.6
uint64_t set_union(uint64_t S, uint64_t R) {
  return S | R;
}

// determine intersection of two sets
// Algorithm 1.7
uint64_t set_intersection(uint64_t S, uint64_t R, int arraySize) {
  return S & R;
}

// determine if a set is empty
bool not_empty(uint64_t S) {
  return ((S > 0) ? true : false);
}
