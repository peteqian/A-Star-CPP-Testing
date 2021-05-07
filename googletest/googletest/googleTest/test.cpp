#include <gtest/gtest.h>
#include "pch.h"
#include "ass3-refactor.h"

using namespace std;

struct SimulationTest :testing::Test {
	Simulation* sim;
	SimulationTest() {
		sim = new Simulation;
	}

	~SimulationTest() {
		delete sim;
	}

};

TEST(SimulationTest, openfile) {
	Simulation sim = new Simulation();

}


int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}