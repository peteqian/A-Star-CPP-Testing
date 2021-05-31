#include "../ass3-refactor.h"
#include <gtest/gtest.h>
#include "TestOracle.h"
#include <fstream> 

class SystemTest : public::testing::Test {

    protected:
        ifstream src;
        ofstream dest;
        ofstream MyFile;
        Simulation* simulation;
        TestOracle* testOracle;
        SystemTest(){ 
            simulation = new Simulation(); 
            testOracle = new TestOracle();
            std::cout << "SystemTest is constructed" << std::endl; 
        }
        ~SystemTest(){ 
            MyFile.close();
            delete testOracle;
            delete simulation;
            std::cout << "Destructing SystemTest" << std::endl; 
            
        }
};

// Subtest involves in running on a fixed test data 
TEST_F(SystemTest, workingRunOracle){
    const char* fileName = "Ass3.txt";
    simulation->openFile(fileName);
    simulation->readFile();
    testOracle->openFile(fileName);
    testOracle->readFile();
    ASSERT_EQ(testOracle->run(), simulation->run());
}