#include "../ass3-refactor.h"
#include "TestOracle.h"
#include <gtest/gtest.h>
#include <fstream> 

class SimulationFile : public::testing::Test {

    protected:
        ofstream MyFile;
        Simulation* simulation;
        TestOracle* testOracle;

        SimulationFile(){ 
            simulation = new Simulation();
            testOracle = new TestOracle();
            std::cout << "SimulationFile is constructed" << std::endl; 

            //MyFile.open(myFileName);
        }
        ~SimulationFile(){ 
            MyFile.close();
            delete testOracle;
            delete simulation;
            std::cout << "Destructing SimulationFile" << std::endl; 
            
        }

        void createFile(const char* myFileName){
            MyFile.open(myFileName);
        }

        void deleteFile(){
            MyFile.close();
        }

};

// Subtest of suite creates a file (not randomly) and tries to open it.
TEST_F(SimulationFile, openCreatedFile){
    const char* fileName = "CreatedFile.txt";
    createFile(fileName);
    ASSERT_EQ(testOracle->openFile(fileName),simulation->openFile(fileName));
}

// Subtest of suite tries to open a non-existing file
TEST_F(SimulationFile, openNonCreatedFile){
    const char* fileName = "NonCreatedFile.txt";
    ASSERT_EQ(testOracle->openFile(fileName),simulation->openFile(fileName));
}

// Subtest involves in running on a fixed test data 
// This is to provide a baseline for comparing test results 
// Will also be used for comparison when refactoring ass3-refactor
TEST_F(SimulationFile, workingRun){
    const char* fileName = "Ass3.txt";
    simulation->openFile(fileName);
    simulation->readFile();
    testOracle->openFile(fileName);
    testOracle->readFile();
    ASSERT_EQ(testOracle->run(),simulation->run());
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}