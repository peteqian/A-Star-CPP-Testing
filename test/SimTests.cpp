#include "../ass3-refactor.h"
#include <gtest/gtest.h>

class SimulationTest : public::testing::Test{
    protected:
        SimulationTest() = default;
        Simulation simulation;
};

class SimulationTestTwo : public::testing::Test {

    protected:
        virtual void SetUp() override {
            std::cout << "Starting up!" << std::endl;
            simulation = new Simulation();
        }

        virtual void TearDown() override {
            std::cout << "Tearing Down!" << std::endl;
            delete simulation;
        }

        SimulationTestTwo(){ std::cout << "SimulatTestTwo is constructed" << std::endl; }
        ~SimulationTestTwo(){ std::cout << "Destructing SimulationTestTwo" << std::endl; }
        Simulation* simulation;
};

/*
TEST_F(SimulationTest, OpenExistingFile){
    ASSERT_EQ(1,simulation.openFile("Ass3.txt"));
}

TEST_F(SimulationTest, OpenNonExistingFile){
    ASSERT_EQ(0,simulation.openFile("Ass2.txt"));
}

TEST_F(SimulationTest, correctRun){
    simulation.openFile("Ass3.txt");
    ASSERT_EQ(1,simulation.run() );
}

TEST_F(SimulationTest, noPath){
    simulation.openFile("NoPath.txt");
    ASSERT_EQ(1,simulation.run());
}
*/

TEST_F(SimulationTestTwo, testOpenFile){
    simulation->openFile("Ass3.txt");
}

TEST_F(SimulationTestTwo, testOpenFileTwo){
    simulation->openFile("NoPath.txt");
}

TEST_F(SimulationTestTwo, testOpenFileThree){
    simulation->openFile("Ass2.txt");
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}