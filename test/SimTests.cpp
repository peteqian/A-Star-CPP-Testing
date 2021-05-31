#include "../ass3-refactor.h"
#include <gtest/gtest.h>
#include <fstream> 

class SimulationFile : public::testing::Test {

    protected:
        ifstream src;
        ofstream dest;
        ofstream MyFile;
        Simulation* simulation;

        SimulationFile(){ 
            simulation = new Simulation();

            // Copy the static Input Test Data into location of the test folder
            std::ifstream src("../../Ass3.txt", std::ios::binary);
            std::ofstream dest("Ass3.txt", std::ios::binary);
            dest << src.rdbuf();
            
            std::cout << "SimulationFile is constructed" << std::endl; 
        }
        ~SimulationFile(){ 
            MyFile.close();
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
    ASSERT_EQ(0,simulation->openFile(fileName));
}

// Subtest of suite tries to open a non-existing file
TEST_F(SimulationFile, openNonCreatedFile){
    const char* fileName = "NonCreatedFile.txt";
    ASSERT_EQ(1,simulation->openFile(fileName));
}

TEST_F(SimulationFile, workingRun){
    const char* fileName = "Ass3.txt";
    simulation->openFile(fileName);
    simulation->readFile();
    ASSERT_EQ(0,simulation->run());
}


int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}