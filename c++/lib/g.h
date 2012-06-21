//
// File: g.h
//

#ifndef _G_H
#define _G_H

#include <vector>
#include <list>
#include "set_operations.h"

using namespace std;

class g {

  public:
    g(string g6);

  public:
    int order();
    void add_vertex();
    void add_edge(int u, int v);
    void remove_edge(int u, int v);
    bool is_edge(int u, int v);
    int num_edges();
    bool has_cycle(int c = 4);
    void print_g6(ostream *o = &cout);
    void addv();
    bool set_has_ind_set(int s, list<int> v);
    bool has_ind_set(int s, vector<int> l, int p);
    bool makes_p3(list<int> edges, int next);
    void addedges(int size);
    void print_am();

  private:
    int n;
    vector<uint64_t> gA;
    int size;

  private:
    int sbbetoi(string str);
    bool _set_has_ind_set_aux(int s, vector<int> l, list<int> v);
    void _addedges(int next, list<int> edges,
               list<int> no_edges);

};

#endif
