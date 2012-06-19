#include <iostream>

#include "lib/g.h"

#define USAGE "vextend"

using namespace std;

void addedges(int i, int max, g gr);

int main(int argc, char *argv[]) {
  string g6;
  while (getline(cin, g6)) {
    g gr = g(g6);
    //if (gr.has_cycle(4)) gr.print_g6();
    gr.add_vertex();
    int max = gr.order() - 1;
    addedges(0, max, gr);
  }
}

void addedges(int i, int max, g gr) {
  if (i == max) {
    if (!(gr).has_cycle(4) && !(gr).has_ind_set(6)) {
      (gr).print_g6();
    }
    return;
  }
  addedges(i+1, max, gr);
  (gr).add_edge(i, max);
  addedges(i+1, max, gr);
  (gr).remove_edge(i, max);
  return;
}
