#include <cstdlib>
#include <iostream>
#include <list>

#include "lib/g.h"
#include "vextend.h"

#define USAGE "vextend (forbiddensizeofindset)"

using namespace std;

int main(int argc, char *argv[]) {
  string g6;
  int size;

  if (argc != 2) {
    cout << USAGE << endl;
  }

  size = atoi(argv[1]);

  while (getline(cin, g6)) {
    g gr = g(g6);
    gr.add_vertex();
    gr.addedges(size);
  }
}
