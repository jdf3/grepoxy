#include <iostream>
#include <vector>

#include "g.h"
#include "set_operations.h"

#define MASK6 63

using namespace std;
//using namespace NTL;

char itosbbe(int n, int shift) {
  return (char) (((n >> shift) & MASK6) + 63);
}

int sbbetoi(string str) {
  int i = 0;
  int j = 0;
  while (str[i] != '\0') {
    j = j << 6;
    j += ((int) str[i]) - 63;
    i++;
  }
  return j;
}

g::g(string g6){
  string edgestr;
  unsigned short sixbit;
  int k, d;

  if (((int) g6[0]) == 126) {
    if (((int) g6[1]) == 126) {
      n = ::sbbetoi(g6.substr(2, 6));
      edgestr = g6.substr(8);
    } else {
      n = ::sbbetoi(g6.substr(1, 3));
      edgestr = g6.substr(4);
    }
  } else {
    n = ::sbbetoi(g6.substr(0, 1));
    edgestr = g6.substr(1);
  }

  arraySize = n / intSize;
  if ((n % intSize) != 0)
    arraySize++;
  gA.resize(n);

  edges = new int*[n];
  for (int i = 0; i < n; i++) {
    edges[i] = new int[n];
    gA[i].resize(arraySize, 0);
  }

  sixbit = ((int) edgestr.at(0)) - 63;
  d = 6;
  k = 1;
  edgestr = edgestr.substr(1);
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (d == 0) {
        sixbit = ((int) edgestr.at(0)) - 63;
        k++;
        d = 6;
        edgestr = edgestr.substr(1);
      }
      if (((sixbit >> (d - 1)) % 2) == 1) {
        add_edge(i, j);
      }
      d--;
    }
  }
}

void g::print_g6(ostream *o) {
  if (0 <= n && n <= 62)
    *o << ::itosbbe(n, 0);
  else if (63 <= n && n <= 258047)
    *o << (char) 126 << ::itosbbe(n, 12)
       << ::itosbbe(n, 6) << ::itosbbe(n, 0);
  else if (258048 <= n && n <= 68719476735)
    *o << (char) 126 << (char) 126 << ::itosbbe(n, 30)
       << ::itosbbe(n, 24) << ::itosbbe(n, 18) << ::itosbbe(n, 12)
       << ::itosbbe(n, 6) << ::itosbbe(n, 0);

  int i = 0;
  int sb = 0;
  for (int c = 1; c < n ; c++) {
    for (int r = 0; r < c; r++) {
      sb = (sb << 1) + is_edge(r, c);
      ++i;
      if (i == 6) {
        *o << ::itosbbe(sb, 0);
        i = 0;
        sb = 0;
      }
    }
  }
  if (i != 0) {
    sb = sb << (6 - i);
    *o << ::itosbbe(sb, 0);
  }
  *o << endl;
}

void g::add_edge(int u, int v){
  if (u < n && u >= 0 && v < n && v >= 0){
    numEdges++;
    set_insert(u, gA[v]);
    set_insert(v, gA[u]);
    edges[u][v] = numEdges;
    edges[v][u] = numEdges;
  }
  else{
    cerr << "Error: Invalid vertices " << u << " and " << v << endl;
    cerr << "Size of graph = " << n << endl;
  }
}

bool g::is_edge(int u, int v){
  return in_set(u, gA[v]);
}

int g::order() {
  return n;
}

int g::num_edges() {
  recalc_edges();
  return numEdges;
}

void g::recalc_edges() {
  numEdges = 0;
  for (int i = 0; i < n - 1; i++){
    for (int j = i; j < n; j++){
      if (is_edge(i, j)){
	      numEdges++;
	      edges[i][j] = numEdges;
	      edges[j][i] = numEdges;
      } else {
	      edges[i][j] = 0;
	      edges[j][i] = 0;
      }
    }
  }
}

bool g::has_cycle(int c) {
  bool found;
  switch (c) {
    case 4:
      for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
          found = false;
          for (int p = 0; p < n; p++) {
            if (is_edge(i, p) && is_edge(j, p)) {
              if (found == true) {
                return true;
              } else {
                found = true;
              }
            }
          }
        }
      }
    default:
      cerr << "has_cycle does not support n = " << n << endl;
  }
  return false;
}

bool g::has_ind_set(int k) {
  int i1, i2, i3, i4, i5, i6;
  switch (k) {
        /*case 4:
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
         return 0;*/

        case 6:
         for (i1 = 0; i1 < n; i1++) {
          for (i2 = i1+1; i2 < n; i2++) {
           if (!is_edge(i1, i2)) {
            for (i3 = i2+1; i3 < n; i3++) {
             if (!is_edge(i1, i3) && !is_edge(i2, i3)){
              for (i4 = i3+1; i4 < n; i4++) {
               if (!is_edge(i1, i4) && !is_edge(i2, i4)
                   && !is_edge(i3, i4)) {
                for (i5 = i4+1; i5 < n; i5++) {
                 if (!is_edge(i1, i5) && !is_edge(i2, i5) &&
                     !is_edge(i3, i5) && !is_edge(i4, i5)) {
                  for (i6 = i5+1; i6 < n; i6++) {
                   if (!is_edge(i1, i6) && !is_edge(i2, i6) &&
                       !is_edge(i3, i6) && !is_edge(i4, i6) &&
                       !is_edge(i5, i6))
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

        default:
            cerr << "has_ind_set does not support k = " << k << endl;
  }
  return 0;
}
