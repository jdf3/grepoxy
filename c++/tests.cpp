#include <iostream>
#include <vector>

#include "lib/g.h"

using namespace std;

int main(int argc, char *argv[]) {
  string str;
  while (getline(cin, str)) {
    cout << "IN: " << str << endl;
    g gr = g(str);
    cout << "EDGES: " << gr.num_edges() << endl << "VERTICES: " << gr.order() << endl << "GRAPH: ";
    gr.print_g6();
    gr.add_vertex();
    gr.addedges(6);
    cout << endl;
  }
}
