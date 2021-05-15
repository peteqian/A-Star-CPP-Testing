#include "../ass3-refactor.h"
#include <gtest/gtest.h>
#include <fstream> 

using namespace std;

class SimulationTest : public::testing::Test{
    protected:
        SimulationTest() = default;
        Simulation simulation;
};

class SimulationFile : public::testing::Test {

    protected:
        ofstream MyFile;

        void createFile(const char* myFileName){
            MyFile.open(myFileName);
        }

        void deleteFile(){
            MyFile.close();
        }

        virtual void SetUp() override {
            //std::cout << "Starting up!" << std::endl;
            simulation = new Simulation();
        }

        virtual void TearDown() override {
            //std::cout << "Tearing Down!" << std::endl;
            delete simulation;
        }

        SimulationFile(){ 
            std::cout << "SimulationFile is constructed" << std::endl; 
            //MyFile.open(myFileName);
        }
        ~SimulationFile(){ 
            std::cout << "Destructing SimulationFile" << std::endl; 
            //MyFile.close();
        }
        Simulation* simulation;
};

TEST_F(SimulationFile, openExistingFile){
    ASSERT_EQ(1,simulation->openFile("Ass3.txt"));
}

TEST_F(SimulationFile, openCreatedFile){
    const char* fileName = "CreatedFile.txt";
    createFile(fileName);
    ASSERT_EQ(1,simulation->openFile(fileName));
}

TEST_F(SimulationFile, openNonCreatedFile){
    const char* fileName = "NonCreatedFile.txt";
    ASSERT_EQ(0,simulation->openFile(fileName));
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}