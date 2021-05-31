#include <iostream>
#include "ass3-refactor.cpp"

using namespace std;

int main(){
  Simulation sim;

  if(!sim.openFile("startgoal.txt")){
    sim.readFile();
    sim.run();
  } else {
    return 1;
  }

  
  return 0;
}
