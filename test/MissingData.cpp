#include "../ass3-refactor.h"
#include "TestOracle.h"
#include <gtest/gtest.h>

class MissingData : public::testing::Test {
    private:
        int no_of_vertices = 0, no_of_edges = 0;
    protected:
        ofstream MyFile;
        Simulation* simulation;
        TestOracle* testOracle;

        MissingData(){ 
            simulation = new Simulation();
            testOracle = new TestOracle();
            std::cout << "MissingData Class is constructed" << std::endl; 
            
        }
        ~MissingData(){ 
            delete testOracle;
            delete simulation;
            MyFile.close();
            std::cout << "Destructing MissingData Class" << std::endl; 
           
            
        }
    public:
        void writeVertices(const char* fileName);
        void writeMissingVerticeEdges(const char* fileName);
        void writeMissingVertices(const char* fileName);
        void writeMissingEdges();
        void writeMissingGoalVertex();
        void writeCompletePath();
        void oneNode();
};

// Function writes the vertices into a data file only.
void MissingData::writeVertices(const char* fileName){

    MyFile.open(fileName);
    cout << "Opened File: " << fileName << endl;
    srand(time(NULL));

    no_of_vertices = rand() % 10 + 3;
    no_of_edges = no_of_vertices-1;
    
    // Writes: number_of_vertices \t
    MyFile << no_of_vertices << "\t" << no_of_edges << endl;

    // Write node, posX, posY
    for(int i = 1; i <= no_of_vertices; i++){
        // Node \t posX \t posY
        int posX = rand() % 5 + 1, posY = rand() % 5 + 1;
        MyFile << i << "\t" << posX << "\t" << posY << endl;
    }
}

// Function does writes blank for the number of vertices and edges needed for the program.
void MissingData::writeMissingVerticeEdges(const char* fileName){
    MyFile.open(fileName);
    cout << "Opened File: " << fileName << endl;
    srand(time(NULL));

    no_of_vertices = rand() % 10 + 3;
    no_of_edges = no_of_vertices-1;
    
    // Write node, posX, posY
    for(int i = 1; i <= no_of_vertices; i++){
        // Node \t posX \t posY
        int posX = rand() % 5 + 1, posY = rand() % 5 + 1;
        MyFile << i << "\t" << posX << "\t" << posY << endl;
    }
}

// Function does writes blank for vertices needed.
void MissingData::writeMissingVertices(const char* fileName){
    MyFile.open(fileName);
    cout << "Opened File: " << fileName << endl;
    srand(time(NULL));

    no_of_vertices = rand() % 10 + 3;
    no_of_edges = no_of_vertices-1;
    
    // Writes: number_of_vertices \t
    MyFile << no_of_vertices << "\t" << no_of_edges << endl;

    for(int i = 1; i <= no_of_vertices; i++){
        MyFile << " " << "\t" << " " << "\t" << " " << endl;
    }
}

// Function does writes blank for the edges.
void MissingData::writeMissingEdges(){
    for(int i = 1; i <= no_of_edges; i++){
        MyFile << " " << "\t" << " " << "\t" << " " << endl; 
    }
    MyFile << 1 << "\t" << no_of_edges << endl;
}

// Function does writes blank for the start and goal vertex needed.
void MissingData::writeMissingGoalVertex(){

    for(int i = 1; i < no_of_edges; i++){
        MyFile << i << "\t" << i+1 << "\t" << 1 << endl; 
    }
    MyFile << no_of_edges << "\t" << no_of_edges << "\t" << 1 << endl; 

}

// Function does writes complete edges
void MissingData::writeCompletePath(){
    for(int i = 1; i < no_of_edges; i++){
        MyFile << i << "\t" << i+1 << "\t" << 1 << endl; 
    }
    MyFile << no_of_edges << "\t" << no_of_edges << "\t" << 1 << endl; 
    MyFile << 1 << "\t" << no_of_edges << endl;
}

TEST_F(MissingData, Missing_No_Vertices_Edges){
    const char* fileName = "Missing_No_Vertices_Edges.txt";
    writeMissingVerticeEdges(fileName);
    writeCompletePath();
    simulation->openFile(fileName);                // Using simulation booject to open the file
    //ASSERT_EQ(1,simulation->readFile());

    // Compare with Test Oracle
    testOracle->openFile(fileName);
    ASSERT_EQ( testOracle->readFile(), simulation->readFile());
}

TEST_F(MissingData, missingVerticesFromInputData){
    const char* fileName = "Missing_Vertices.txt";
    writeMissingVertices(fileName);
    writeCompletePath();
    simulation->openFile(fileName);                // Using simulation booject to open the file
    //ASSERT_EQ(1,simulation->readFile());

    // Compare with Test Oracle
    testOracle->openFile(fileName);
    ASSERT_EQ( testOracle->readFile(), simulation->readFile());
}


TEST_F(MissingData, missingEdgesFromInputData){
    const char* fileName = "Missing_Edges.txt";
    writeVertices(fileName);
    writeMissingEdges();
    simulation->openFile(fileName);                // Using simulation booject to open the file
    //ASSERT_EQ(1,simulation->readFile());

    // Compare with Test Oracle
    testOracle->openFile(fileName);
    ASSERT_EQ( testOracle->readFile(), simulation->readFile());
}

TEST_F(MissingData, writeMissingStartGoalPosition){
    const char* fileName = "Missing_StartGoalPosition.txt";
    writeVertices(fileName);
    writeMissingGoalVertex();
    simulation->openFile(fileName);                // Using simulation booject to open the file
    //ASSERT_EQ(1,simulation->readFile());

    // Compare with Test Oracle
    testOracle->openFile(fileName);
    ASSERT_EQ( testOracle->readFile(), simulation->readFile());
}