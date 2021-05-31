#include "../ass3-refactor.h"
#include "TestOracle.h"
#include <gtest/gtest.h>

class HeapTest : public::testing::Test {

    protected:
        int *heap;
        int size = 0;
        vertex *verticesTest;
        Simulation* simulation;
        TestOracle* testOracle;
        HeapTest(){ 
            simulation = new Simulation();
            testOracle = new TestOracle();
            std::cout << "HeapTest Class is constructed." << std::endl; 
        }
        ~HeapTest(){ 
            delete testOracle;
            delete simulation;
            delete verticesTest;
            delete heap;
            std::cout << "Destructing HeapTest Class." << std::endl; 
        }
        
    public:
        int check(int[]);
        void createRandomVertices();
        void printHeap(int size);
};



int HeapTest::check(int heap[]){
    int parentWeight, child1Weight, child2Weight;

    for(int i = 0; i <= (size-2)/2; i++){
        parentWeight = verticesTest[heap[i]].length + verticesTest[heap[i]].heuristic;
        child1Weight = verticesTest[heap[2*i+1]].length + verticesTest[heap[2*i+1]].heuristic;
        
        //make sure the second child is not out of range to avoid segmentation fault
        if(2*i + 2 != size){
            child2Weight = verticesTest[heap[2*i+2]].length + verticesTest[heap[2*i+2]].heuristic;
        } else {child2Weight = 0;}

        // If either child is larger than parent, heap has an error so return false 
        if(parentWeight  > child1Weight || (2*i + 2 != size && parentWeight > child2Weight)){
            return -1;
        }
    }
   return 1; // all checks succeeded, return true
}


//Creates random sized vertices array populated with vertices with random heuristics
void HeapTest::createRandomVertices(){
    srand(time(NULL));

    size = rand()%100+5;
    
    verticesTest = new vertex[size];
    heap = new int[size];

    //creates random values for heuristics and maps index to heap array to be sorted
    for(int i = 0 ; i < size; i++){
        verticesTest[i].length = 0; 
        verticesTest[i].heuristic = rand()%20+1;
        heap[i] = i;
    }
}

void HeapTest::printHeap(int size){

    cout << "Printing the Heap index. " << endl;
    for (int i = 0; i < size; i++) {
        cout << heap[i] << "\t";
    }
    cout << endl;
    cout << "Printing the verticesTest array. " << endl;
    for (int i = 0; i < size; i++) {
        cout << verticesTest[heap[i]].heuristic << "\t";
    }
 
}

TEST_F(HeapTest, subtestOne){
    createRandomVertices();
    simulation->makeheap(heap, size, verticesTest);
    ASSERT_EQ(check(heap), 1);
}
