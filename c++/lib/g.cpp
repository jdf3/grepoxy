#include <cstdlib>
#include <iostream>
#include <vector>
#include <list>

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

  gA.resize(n);

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
  else if (258048 <= n) /* && n <= 68719476735) */
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

void g::add_edge(int u, int v) {
  set_insert(u, gA[v]);
  set_insert(v, gA[u]);
}

void g::remove_edge(int u, int v) {
  set_delete(u, gA[v]);
  set_delete(v, gA[u]);
}

bool g::is_edge(int u, int v){
  return in_set(u, gA[v]);
}

int g::order() {
  return n;
}

int g::num_edges() {
  int numEdges = 0;
  for (int i = 0; i < n - 1; i++) {
    for (int j = i; j < n; j++) {
      if (is_edge(i, j)) {
	      numEdges++;
      }
    }
  }
  return numEdges;
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
                //cout << i << j << p << endl;
                //print_g6();
                return true;
              } else {
                //cout << i << j << p << endl;
                found = true;
              }
            }
          }
        }
      }
      return false;

    default:
      cerr << "has_cycle does not support c = " << c << endl;
  }
  return false;
}

bool g::set_has_ind_set(int size_left, list<int> vertices) {
  vector<int> indset;
  list<int> copy (vertices.begin(), vertices.end());
  return _set_has_ind_set_aux(size_left, indset, copy);
}

bool g::_set_has_ind_set_aux(int size_left, vector<int> indset, list<int> vertices) {
  int nv;

  if (size_left == 0) return true;
  if ((int) vertices.size() < size_left) return false;

  for (vector<int>::iterator it = indset.begin();
       it != indset.end(); it++) {
    if (is_edge(*it, vertices.front())) {
      vertices.pop_front();
      return _set_has_ind_set_aux(size_left, indset, vertices);
    }
  }

  nv = vertices.front();
  vertices.pop_front();
  if (_set_has_ind_set_aux(size_left, indset, vertices)) return true;

  indset.push_back(nv);
  return _set_has_ind_set_aux(size_left-1, indset, vertices);
}

bool g::has_ind_set(int size_left, vector<int> indset, int pos) {
  if (size_left == 0) return true;
  if ((n - 1) - pos > size_left) return false;

  for (vector<int>::iterator it = indset.begin();
       it != indset.end(); it++) {
    if (is_edge(*it, pos)) {
      return has_ind_set(size_left, indset, pos+1);
    }
  }

  if (has_ind_set(size_left, indset, pos+1)) return true;
  indset.push_back(pos);
  return (has_ind_set(size_left-1, indset, pos+1));
}

bool g::makes_p3(list<int> edges, int next) {
  for (list<int>::iterator it = edges.begin();
       it != edges.end(); it++) {
    for (int i = 0; i < n-1; i++) {
      if (is_edge(*it, i) && is_edge(next, i)) return true;
    }
  }
  return false;
}

/*bool g::has_ind_set(int k) {
  int i1, i2, i3, i4, i5, i6;
  switch (k) {
        case 4:
         cerr << "REALLY?\n";

        case 5:
         cerr << "REALLY?\n";

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
                    return true;
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
         return false;

        default:
            cerr << "has_ind_set does not support k = " << k << endl;
  }
  return false;
}*/

/* inefficient, but i can't do it another way... */
void g::add_vertex() {
  // There's a memory leak here, obviously, but I want to rewrite it anyways.
  n += 1;
  vector<vset> gAnew (n);
  for (int i = 0; i < n; i++) {
    gAnew[i].resize(n);
  }
  for (int i = 0; i < n-1; i++) {
    for (int j = 0; j < n-1; j++) {
      gAnew[i][j] = gA[i][j];
    }
  }
  gA = gAnew;
  // I'd like to be able to do this:
  /*gA.resize(n);
  for (int i = 0; i < n; i++) {
    gA[i].resize(n);
  }*/
  // ...but it doesn't work.
}

void g::addedges(int s) {
  size = s;
  list<int> no_edges;
  list<int> edges;

  _addedges(0, edges, no_edges);
}

void g::_addedges(int next, list<int> edges,
               list<int> no_edges) {
  if (next == n-1) {
    print_g6();
    // print_am();
    return;
  }

  remove_edge(next, n-1);
  no_edges.push_back(next);
  if (!(set_has_ind_set(size-1, no_edges))) {
    _addedges(next+1, edges, no_edges);
  }

  add_edge(next, n-1);

  if (!(makes_p3(edges, next))) {
    no_edges.pop_back();
    edges.push_back(next);
    _addedges(next+1, edges, no_edges);
  }
  return;
}

void g::print_am() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << is_edge(i, j) <<  " ";
    }
    cout << endl;
  }
}
