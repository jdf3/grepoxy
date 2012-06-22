#include <iostream>
#include <vector>

#include "lib/g.h"

using namespace std;

int main(int argc, char *argv[]) {
  vector<int> test;
  for (int i = 0 ; i < 5; i++) {
      test.push_back(i);
  }
  test.resize(10);
  for (int i = 0; i < 10; i++) {
      cout << test[i] << " ";
  }
  /*string str;
  while (getline(cin, str)) {
    cout << "IN: " << str << endl;
    g gr = g(str);
    gr.add_vertex();
    gr.print_g6();
    gr.print_am();
    //gr.addedges(4);*/
}

