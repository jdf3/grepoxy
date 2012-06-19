//
// File: g.h
//

#ifndef _G_H
#define _G_H

#include <vector>
#include "set_operations.h"

using namespace std;

class g {

  public:
    g(string g6);

  public:
    int order();
    void add_edge(int u, int v);
    bool is_edge(int u, int v);
    int num_edges();
    bool has_ind_set(int k);
    bool has_cycle(int c = 4);
    void print_g6(ostream *o = &cout);

  private:
    int n, arraySize, numEdges, oldN;
    vector<vset> gA;
    int **edges;

  private:
    int sbbetoi(string str);
    void recalc_edges();

};

#endif
