#include "../ass3-refactor.h"
#include <gtest/gtest.h>
#include <fstream> 

using namespace std;

class InappropriateDataTypes : public::testing::Test {

    private:
        int no_of_vertices = 0, no_of_edges = 0;

    protected:
        ofstream outData;
        Simulation* simulation;

        virtual void SetUp() override {
            simulation = new Simulation();
        }

        virtual void TearDown() override {
            delete simulation;
        }

        InappropriateDataTypes(){ 
            std::cout << "VerifyData Class is constructed" << std::endl; 
        }
        ~InappropriateDataTypes(){ 
            std::cout << "Destructing VerifyData Class" << std::endl; 
            outData.close();
        }

    public:
        void writeCorrectNumberOf(const char* fileName);
        void writeCorrectVertices();
        void writeCorrectEdges();
        void writeCorrectStartGoal();
        void writeCharNumberOf(const char* fileName);
        void writeCharVertices();
        void writeCharEdges();
        void writeCharStartGoal();
        void writeFloatVertices();
        void writeFloatEdges();
        void writeNegativeNumberOf(const char* fileName);
        void writeNegativeVertices();
        void writeNegativeEdges();
        void writeNegativeStartGoal();
};

void InappropriateDataTypes::writeCorrectNumberOf(const char* fileName){
    outData.open(fileName);
    cout << "Opened File: " << fileName << endl;

    // Set nVertices and nEdges
    srand(time(NULL));
    no_of_vertices = rand() % 5 + 1;
    no_of_edges = no_of_vertices-1;

    // Writes: number_of_vertices \t
    outData << no_of_vertices << "\t" << no_of_edges << endl;
}

void InappropriateDataTypes::writeCorrectVertices(){
    srand(time(NULL));
    // Write node, posX, posY
    for(int i = 1; i <= no_of_vertices; i++){
        // Node \t posX \t posY
        int posX = rand() % 5 + 1, posY = rand() % 5 + 1;
        outData << i << "\t" << posX << "\t" << posY << endl;
    }
}

void InappropriateDataTypes::writeCorrectEdges(){
    for(int i = 1; i < no_of_edges; i++){
        outData << i << "\t" << i+1 << "\t" << 1 << endl; 
    }
    outData << no_of_edges << "\t" << no_of_edges << "\t" << 1 << endl; 
}

void InappropriateDataTypes::writeCorrectStartGoal(){
    outData << 1 << "\t" << no_of_edges << endl;
    outData.close();
}

void InappropriateDataTypes::writeCharNumberOf(const char* fileName){
    outData.open(fileName);
    cout << "Opened File: " << fileName << endl;

    // Set nVertices and nEdges
    char c, a;
    int r;
    srand(time(NULL));
    r = rand()%26; 

    c = 'a' + r;
    a = 'b' + r;

    outData << c << "\t" << a << endl; 
}

void InappropriateDataTypes::writeCharVertices(){
    srand(time(NULL));

    // Write node, posX, posY
    for(int i = 1; i <= no_of_vertices; i++){
        // Node \t posX \t posY
        int r = rand()%26; 

        char a = 'a' + r;
        char b = 'b' + r;
        char c = 'c' + r;
        outData << a << "\t" << b << "\t" << c << endl;
    }
}

void InappropriateDataTypes::writeCharEdges(){
    srand(time(NULL));

    for(int i = 1; i < no_of_edges; i++){
        int r = rand()%26; 

        char a = 'a' + r;
        char b = 'b' + r;
        char c = 'c' + r;
        outData << a << "\t" << b << "\t" << c << endl; 
    }
    outData << 'a' << "\t" << 'b' << "\t" << 'c' << endl; 
}

void InappropriateDataTypes::writeCharStartGoal(){
    char m, n;
    int r;
    srand(time(NULL));
    r = rand()%26; 

    m = 'a' + r;
    n = 'b' + r;

    outData << m << "\t" << n << endl;
    outData.close();
}

void InappropriateDataTypes::writeFloatVertices(){
    srand(time(NULL));
    // Write node, posX, posY
    for(int i = 1; i <= no_of_vertices; i++){
        // Node \t posX \t posY
        float x = ((float)rand()/5), y = rand() % 5 + x;
        outData << i << "\t" << x << "\t" << y << endl;
    }
}

void InappropriateDataTypes::writeFloatEdges(){
    srand(time(NULL));

    for(int i = 1; i < no_of_edges; i++){
        float a = (float(rand()) / float(5) + 1);
        outData << i << "\t" << a << "\t" << i+a << endl; 
    }
    outData << no_of_edges << "\t" << no_of_edges << "\t" << 1 << endl; 
}

void InappropriateDataTypes::writeNegativeNumberOf(const char* fileName){
    outData.open(fileName);
    cout << "Opened File: " << fileName << endl;

    // Set nVertices and nEdges
    srand(time(NULL));
    no_of_vertices = rand() % 5 + 1;
    no_of_edges = no_of_vertices-1;

    // Writes: number_of_vertices \t
    outData << -no_of_vertices << "\t" << -no_of_edges << endl;
}

void InappropriateDataTypes::writeNegativeVertices(){
    srand(time(NULL));
    // Write node, posX, posY
    for(int i = 1; i <= no_of_vertices; i++){
        // Node \t posX \t posY
        int posX = rand() % 5 + 1, posY = rand() % 5 + 1;
        outData << i << "\t" << -posX << "\t" << -posY << endl;
    }
}

void InappropriateDataTypes::writeNegativeEdges(){
    for(int i = 1; i < no_of_edges; i++){
        outData << -i << "\t" << -i+1 << "\t" << -1 << endl;
    }
    outData << -no_of_edges << "\t" << -no_of_edges << "\t" << -1 << endl; 
}

void InappropriateDataTypes::writeNegativeStartGoal(){
    outData << -1 << "\t" << -no_of_edges << endl;
    outData.close();
}



TEST_F(InappropriateDataTypes, InputCorrectValues){
    const char* file = "VerifyData_CorrectValues.txt";
    writeCorrectNumberOf(file);
    writeCorrectVertices();
    writeCorrectEdges();
    writeCorrectStartGoal();
    simulation->openFile(file);
    ASSERT_EQ(0, simulation->readFile());
}

TEST_F(InappropriateDataTypes, InputCharValues_NumberOf){
    const char* file = "VerifyData_CharValues_NumberOf.txt";
    writeCharNumberOf(file);
    writeCorrectVertices();
    writeCorrectEdges();
    writeCorrectStartGoal();
    simulation->openFile(file);
    ASSERT_EQ(1, simulation->readFile());
}

TEST_F(InappropriateDataTypes, InputCharValues_Edges){
    const char* file = "VerifyData_CharValues_Edges.txt";
    writeCorrectNumberOf(file);
    writeCorrectVertices();
    writeCharEdges();
    writeCorrectStartGoal();
    simulation->openFile(file);
    ASSERT_EQ(1, simulation->readFile());
}

TEST_F(InappropriateDataTypes, InputCharValues_Vertices){
    const char* file = "VerifyData_CharValues_Vertices.txt";
    writeCorrectNumberOf(file);
    writeCharVertices();
    writeCorrectEdges();
    writeCorrectStartGoal();
    simulation->openFile(file);
    ASSERT_EQ(1, simulation->readFile());
}

TEST_F(InappropriateDataTypes, InputCharValues_StartGoal){
    const char* file = "VerifyData_CharValues_StartGoal.txt";
    writeCorrectNumberOf(file);
    writeCorrectVertices();
    writeCorrectEdges();
    writeCharStartGoal();
    simulation->openFile(file);
    ASSERT_EQ(1, simulation->readFile());
}

// TEST_F(VerifyData, InputFloatValues_Edges){
//     const char* file = "VerifyData_FloatValues_Edges.txt";
//     writeCorrectNumberOf(file);
//     writeCorrectVertices();
//     writeFloatEdges();
//     writeCorrectStartGoal();
//     simulation->openFile(file);
//     ASSERT_EQ(1, simulation->readFile());
// }

// TEST_F(VerifyData, InputFloatValues_Vertices){
//     const char* file = "VerifyData_FloatValues_Vertices.txt";
//     writeCorrectNumberOf(file);
//     writeFloatVertices();
//     writeCorrectEdges();
//     writeCorrectStartGoal();
//     simulation->openFile(file);
//     ASSERT_EQ(1, simulation->readFile());
// }

TEST_F(InappropriateDataTypes, InputNegativeIntValues_NumberOf){
    const char* file = "VerifyData_NegativeIntValues_NumberOf.txt";
    writeNegativeNumberOf(file);
    writeCorrectVertices();
    writeCorrectEdges();
    writeCorrectStartGoal();
    simulation->openFile(file);
    ASSERT_EQ(1, simulation->readFile());
}

TEST_F(InappropriateDataTypes, InputNegativeIntValues_Edges){
    const char* file = "VerifyData_NegativeIntValues_Edges.txt";
    writeCorrectNumberOf(file);
    writeCorrectVertices();
    writeNegativeEdges();
    writeCorrectStartGoal();
    simulation->openFile(file);
    ASSERT_EQ(1, simulation->readFile());
}

TEST_F(InappropriateDataTypes, InputNegativeIntValues_Vertices){
    const char* file = "VerifyData_NegativeIntValues_Vertices.txt";
    writeCorrectNumberOf(file);
    writeNegativeVertices();
    writeCorrectEdges();
    writeCorrectStartGoal();
    simulation->openFile(file);
    ASSERT_EQ(1, simulation->readFile());
}

TEST_F(InappropriateDataTypes, InputNegativeIntValues_StartGoal){
    const char* file = "VerifyData_NegativeIntValues_StartGoal.txt";
    writeCorrectNumberOf(file);
    writeCorrectVertices();
    writeCorrectEdges();
    writeNegativeStartGoal();
    simulation->openFile(file);
    ASSERT_EQ(1, simulation->readFile());
}