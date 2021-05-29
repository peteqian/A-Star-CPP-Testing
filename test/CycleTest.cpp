#include "../ass3-refactor.h"
#include "TestOracle.h"
#include <gtest/gtest.h>

class CycleTest : public::testing::Test{
    protected:
        int noVertices = 0, noEdges = 0;
        ofstream myFile;
        Simulation* simulation;
        TestOracle* testOracle;
        CycleTest(){ 
            simulation = new Simulation();
            testOracle = new TestOracle();
            std::cout << "CycleTest Class is constructed." << std::endl; 
        }
        ~CycleTest(){ 
            delete testOracle;
            delete simulation;
            std::cout << "Destructing CycleTest Class." << std::endl; 
        }
        
    public:
       void writeVertices(const char* fileName);
       void writeEdgesInCycle();
       void writeStartAndGoalVertices();

};

void CycleTest::writeVertices(const char* fileName){
    myFile.open(fileName);
    cout << "Opened File: " << fileName << endl;
    srand(time(NULL));

    noVertices = rand() % 10 + 3;
    noEdges = noVertices;
    
    // Writes: number_of_vertices \t
    myFile << noVertices << "\t" << noEdges << endl;

    // Write node, posX, posY
    for(int i = 1; i <= noVertices; i++){
        // Node \t posX \t posY
        int posX = rand() % 5 + 1, posY = rand() % 5 + 1;
        myFile << i << "\t" << posX << "\t" << posY << endl;
    }
}

void CycleTest::writeEdgesInCycle(){
   for(int i = 1; i < noEdges-1; i++){
      myFile << i << "\t" << i+1 << "\t" << 1 << endl; 
   }
   myFile << noEdges-1 << "\t" << noEdges << "\t" << 1000 << endl;
   myFile << noEdges-1 << "\t" << noEdges-(rand() % (noVertices-3) +1) << "\t" << 1 << endl; 
}

void CycleTest::writeStartAndGoalVertices(){
   myFile << "1" << "\t" << noVertices << endl;
}

TEST_F(CycleTest, TestCycle){
   const char* file = "cycle.txt";
   writeVertices(file);
   writeEdgesInCycle();
   writeStartAndGoalVertices();
   simulation->openFile(file);
   simulation->readFile();
   ASSERT_EQ(0, simulation->run());
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
