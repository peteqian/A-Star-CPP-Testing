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
            delete simulation;
            delete testOracle;
            MyFile.close();
            std::cout << "Destructing MissingData Class" << std::endl; 
           
            
        }
    public:
        void writeVertices(const char* fileName);
        void writeOneNode(const char* fileName);
        void writeOneEdge();
        void writeMissingVerticeEdges(const char* fileName);
        void writeMissingVertices(const char* fileName);
        void writeMissingEdges();
        void writeMissingGoalVertex();
        void writeCompletePath();
        
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

// Function writes only one vertex.
void MissingData::writeOneNode(const char* fileName){

    MyFile.open(fileName);
    cout << "Opened File: " << fileName << endl;
    srand(time(NULL));

    no_of_vertices = rand() % 10 + 3;
    no_of_edges = no_of_vertices-1;
    
    // Writes: number_of_vertices \t
    MyFile << no_of_vertices << "\t" << no_of_edges << endl;

    int posX = rand() % 5 + 1, posY = rand() % 5 + 1;
    MyFile << 1 << "\t" << posX << "\t" << posY << endl;
    
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

// Function writes only one edge.
void MissingData::writeOneEdge(){

    MyFile << 1 << "\t" << 2 << "\t" << 1 << endl; 
    MyFile << 1 << "\t" << no_of_edges << endl;
    
}

TEST_F(MissingData, Missing_No_Vertices_Edges){
    const char* fileName = "Missing_No_Vertices_Edges.txt";
    writeMissingVerticeEdges(fileName);
    writeCompletePath();
    simulation->openFile(fileName);               
    ASSERT_EQ(1,simulation->readFile());
}

TEST_F(MissingData, OneNode){
    const char* fileName = "OneNode.txt";
    writeOneNode(fileName);
    writeCompletePath();
    simulation->openFile(fileName);           
    ASSERT_EQ(1,simulation->readFile());
}

// Write in functionality for this one.
TEST_F(MissingData, OneEdge){
    const char* fileName = "OneEdge.txt";
    writeOneNode(fileName);
    writeCompletePath();
    simulation->openFile(fileName);           
    ASSERT_EQ(1,simulation->readFile());
}

TEST_F(MissingData, missingVerticesFromInputData){
    const char* fileName = "Missing_Vertices.txt";
    writeMissingVertices(fileName);
    writeCompletePath();
    simulation->openFile(fileName);            
    ASSERT_EQ(1,simulation->readFile());
}


TEST_F(MissingData, missingEdgesFromInputData){
    const char* fileName = "Missing_Edges.txt";
    writeVertices(fileName);
    writeMissingEdges();
    simulation->openFile(fileName);             
    ASSERT_EQ(1,simulation->readFile());
}

TEST_F(MissingData, writeMissingStartGoalPosition){
    const char* fileName = "Missing_StartGoalPosition.txt";
    writeVertices(fileName);
    writeMissingGoalVertex();
    simulation->openFile(fileName);       
    ASSERT_EQ(1,simulation->readFile());
}

TEST_F(MissingData, writeOneNode){
    const char* fileName = "OneNode.txt";
    writeOneNode(fileName);
    writeCompletePath();
    simulation->openFile(fileName);       
    ASSERT_EQ(1,simulation->readFile());
}

TEST_F(MissingData, writeOneEdge){
    const char* fileName = "OneEdge.txt";
    writeVertices(fileName);
    writeOneEdge();
    simulation->openFile(fileName);       
    ASSERT_EQ(1,simulation->readFile());
}

TEST_F(MissingData, completedPath){
    const char* fileName = "CompletedPath.txt";
    writeVertices(fileName);
    writeCompletePath();
    simulation->openFile(fileName);    
    simulation->readFile();   
    ASSERT_EQ(0,simulation->run());
}


TEST_F(MissingData, completedPathWithOracle){
    const char* fileName = "CompletedPath.txt";
    writeVertices(fileName);
    writeCompletePath();
    simulation->openFile(fileName);    
    simulation->readFile();   
    testOracle->openFile(fileName);    
    testOracle->readFile();   
    ASSERT_EQ(testOracle->run(),simulation->run());
}