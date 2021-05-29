#ifndef TESTORACLE_H
#define TESTORACLE_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <signal.h>
#include <iomanip>

using namespace std;

struct vertexStruct {
    double xCoordinate, yCoordinate;
    double length;
    int previous;
    double heuristic;
};

class TestOracle{

    private:
        ifstream fileIn;
        vertexStruct *vertices;
        double **edgeWeight;
        int *candidate;
        int nVertices;
        int startVertex = -1, goalVertex = -1;
        string fileName = "";
        int id, nEdges;
        int id_tracker = 0;

        // Report shortest Path information
        int *path;
        int nPathVertices;
        
        // For second shortest path
        int nPathEdges;
        double bestLength;
        double savedWeight;
        int from, to;
        int nPath2Vertices;
        int *path2;


    public:
        TestOracle() {cout << "Default TestOracle Constructed" << endl; }
        ~TestOracle() {cout << "TestOracle Destroyed" << endl;}
        int openFile(const char* fileName);
        int readFile();
        int run();
        int astar();
        void makeheap(int *heap, int heapSize);
        void siftUp(int *heap, int i);
        void siftDown (int *heap, int heapSize, int i);
};

#endif