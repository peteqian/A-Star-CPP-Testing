#include <iostream>
#include "ass3-refactor.cpp"

using namespace std;

int main(){
  Simulation sim;
  sim.openFile("InCompletedPath.txt");
  sim.readFile();
  sim.run();
  return 0;
}
