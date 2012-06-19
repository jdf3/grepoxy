#include <iostream>
#include <vector>

#include "g.h"

using namespace std;

int main(int argc, char *argv[]) {
  string str;
  while (getline(cin, str)) {
    g gr = g(str);
    gr.add_edge(0, 1);
    cout << gr.order() << endl;
  }
}
