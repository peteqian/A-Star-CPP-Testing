#include "../ass3-refactor.h"
#include "TestOracle.h"
#include <gtest/gtest.h>

class Heuristic : public::testing::Test{
    protected:
        Simulation* simulation;
        vertex *vertices;
        double *xCoordinate;
        double *yCoordinate;
        int size;
        Heuristic(){ 
            simulation = new Simulation();
            std::cout << "CycleTest Class is constructed." << std::endl; 
        }
        ~Heuristic(){ 
            delete simulation;
            std::cout << "Destructing CycleTest Class." << std::endl; 
        }
        
    public:
       void createTestData();
       double distanceFormula(int vertexOne, int vertexTwo);
};

// Distance formula
double Heuristic::distanceFormula(int vertexOne, int vertexTwo){
    double distance = 0.0;
    distance =  sqrt( pow(xCoordinate[vertexTwo]-xCoordinate[vertexOne],2)+ pow(yCoordinate[vertexTwo]-yCoordinate[vertexOne],2));
    return distance;
}

void Heuristic::createTestData(){
    srand(time(NULL));
    size = rand()%20+10;

    vertices = new vertex[size];
    xCoordinate = new double[size];
    yCoordinate = new double[size];

    // Create x-coordinates
    for(int i = 0; i < size; i++){
        vertices[i].xCoordinate = rand()%20+10;
        xCoordinate[i] = vertices[i].xCoordinate;
    }

    // Create y-coordinates
    for(int i = 0; i < size; i++){
        vertices[i].yCoordinate = rand()%20+10;
        yCoordinate[i] = vertices[i].yCoordinate;
    }
}

TEST_F(Heuristic, testDistanceCalculation){
    cout << "Testing Distance calculation" << endl;
    createTestData();

    for(int i = 0; i < size-1; i++){
        EXPECT_EQ(distanceFormula(i,size-1), simulation->calculateHeuristic(i, size-1, vertices));
    }
}