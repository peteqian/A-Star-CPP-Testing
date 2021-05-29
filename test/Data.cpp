#include "../ass3-refactor.h"
#include "TestOracle.h"
#include <gtest/gtest.h>
#include <time.h>


class Data : public::testing::Test {

    private:
        int no_of_vertices = 0, no_of_edges = 0;
    protected:
        ofstream MyFile;
        Simulation* simulation;
        TestOracle* testOracle;

        Data(){ 
            simulation = new Simulation();
            testOracle = new TestOracle();
            std::cout << "Data Class is constructed" << std::endl; 
        }
        ~Data(){ 
            MyFile.close();
            delete testOracle;
            delete simulation;
            std::cout << "Destructing Data Class" << std::endl; 
        }
    public:
        void writeVertices(const char* fileName);
        void writeBadData();
        void writeCompletePath();
        void writeInCompletePath();
        void writeDuplicateEdge();
};

// Function writes the vertices into a data file only.
void Data::writeVertices(const char* fileName){

    MyFile.open(fileName);
    cout << "Opened File: " << fileName << endl;
    srand(time(NULL));

    // Generate a random number between 3 to 10 for vertices and generated number-1 for edges.
    no_of_vertices = rand() % 10 + 3;
    no_of_edges = no_of_vertices-1;
    
    // Writes: number_of_vertices \t
    MyFile << no_of_vertices << "\t" << no_of_edges << endl;

    // Write node, posX, posY
    for(int i = 1; i <= no_of_vertices; i++){
        // Generate random x and y coordinates for the vertex
        int posX = rand() % 5 + 1, posY = rand() % 5 + 1;
        MyFile << i << "\t" << posX << "\t" << posY << endl;
    }
}

// Function does write the correct amount of edges as specified on Line:1 in the file.
void Data::writeCompletePath(){
    for(int i = 1; i < no_of_edges; i++){
        MyFile << i << "\t" << i+1 << "\t" << 1 << endl; 
    }
    MyFile << no_of_edges << "\t" << no_of_edges << "\t" << 1 << endl; 
    MyFile << 1 << "\t" << no_of_edges << endl;
    MyFile.close();
}

// Function does not write the correct amount of edges as specified on Line:1 in the file.
void Data::writeInCompletePath(){
    
    for(int i = 1; i < no_of_edges; i++){
        MyFile << i << "\t" << i+1 << "\t" << 1 << endl; 
    }
    MyFile << " " << "\t" << " " << "\t" << " " << endl; 
    MyFile << 1 << "\t" << no_of_edges << endl;
    MyFile.close();
}


void Data::writeBadData(){
    char c;
    int r;
    srand (time(NULL));                                                 // initialize the random number generator
    for(int i = 1; i < no_of_edges; i++){
        r = rand()%26;                                                  // Function writes random letters from the alphabet
        c = 'a' + r;
        MyFile << i << "\t" << c << "\t" << 1 << endl; 
    }
    MyFile << 1 << "\t" << no_of_vertices << endl;
    MyFile.close();
}

/* Needs to be changed*/
void Data::writeDuplicateEdge(){

    for(int i = 1; i < no_of_edges/2; i++){
        MyFile << i << "\t" << i+1 << "\t" << 1 << endl; 
    }

    MyFile << no_of_edges << "\t" << no_of_edges-1 << "\t" << 100 << endl; 

    for(int i = no_of_edges/2; i < no_of_edges; i++){
        MyFile << i << "\t" << i+1 << "\t" << 1 << endl; 
    }

    MyFile << 1 << "\t" << no_of_edges << endl;
    MyFile.close();
}

TEST_F(Data, DuplicateEdge){
   const char* file = "DuplicateEdge.txt";
   writeVertices(file);
   writeDuplicateEdge();
   simulation->openFile(file);
   ASSERT_EQ(0, simulation->readFile());
}

TEST_F(Data, InCompletedPath){
    const char* file = "InCompletedPath.txt";
    writeVertices(file);
    writeInCompletePath();
    simulation->openFile(file);
    testOracle->openFile(file);
    ASSERT_EQ( testOracle->readFile(), simulation->readFile());
}

TEST_F(Data, CompletedPath){
    
    const char* file = "CompletedPath.txt";
    writeVertices(file);
    writeCompletePath();
    simulation->openFile(file);
    simulation->readFile();
    testOracle->openFile(file);
    testOracle->readFile();
    ASSERT_EQ(testOracle->run(),simulation->run());
}
