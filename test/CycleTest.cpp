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

    noVertices = 2*(rand() % 10 + 3);
    noEdges = noVertices+2;
    
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


    for(int i = 1; i <= noVertices/2-1; i++){
        myFile << i << "\t" << i+1 << "\t" << 1 << endl; 
    }

    // Create a cycle in the middle of the path.
    myFile << noVertices/2-1 << "\t" << noVertices/2+1 << "\t" << rand()%1000+10 << endl;
    myFile << noVertices/2 << "\t" << noVertices/2+2 << "\t" << 1 << endl;
    myFile << noVertices/2+1 << "\t" << noVertices/2+2 << "\t" << 1 << endl;
    myFile << noVertices/2+1 << "\t" << noVertices/2-1 << "\t" << 53 << endl;
    myFile << noVertices/2+2 << "\t" << noVertices/2+3 << "\t" << rand()%1000+10 << endl;
    myFile << noVertices/2+2 << "\t" << noVertices/2+1 << "\t" << 1 << endl;

    for(int i = noVertices/2+3; i < noVertices; i++){
        myFile << i << "\t" << i+1 << "\t" << 1 << endl; 
    }
    myFile << 1 << "\t" << noVertices << endl;
}

TEST_F(CycleTest, TestCycle){
    const char* file = "cycleMiddle.txt";
    writeVertices(file);
    writeEdgesInCycle();
    simulation->openFile(file);
    simulation->readFile();
    ASSERT_EQ(0, simulation->run());
}

TEST_F(CycleTest, TestCycleWithOracle){
    const char* file = "cycleMiddle.txt";
    writeVertices(file);
    writeEdgesInCycle();
    simulation->openFile(file);
    simulation->readFile();
    testOracle->openFile(file);
    testOracle->readFile();
    ASSERT_EQ(testOracle->run(), simulation->run());
}