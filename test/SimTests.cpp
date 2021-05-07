#include "../ass2-refactor.h"
#include <gtest/gtest.h>
<<<<<<< Updated upstream

TEST(TestCase1, subTest1){
    Sim sim;
    sim.run();
=======

class SimulationTest : public::testing::Test{
    protected:
        SimulationTest() = default;
        Simulation simulation;
};

TEST_F(SimulationTest, OpenExistingFile){
    ASSERT_EQ(1,simulation.openFile("Ass3.txt"));
}

TEST_F(SimulationTest, OpenNonExistingFile){
    ASSERT_EQ(1,simulation.openFile("Ass2.txt"));
}

TEST_F(SimulationTest, correctRun){
    simulation.openFile("Ass3.txt");
    simulation.run();
    ASSERT_TRUE(true);
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
>>>>>>> Stashed changes
}