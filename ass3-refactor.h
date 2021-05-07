#ifndef ASS3REFACTOR_H
#define ASS3REFACTOR_H

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

/*
// Prototype functions
int astar();
void makeheap(int *heap, int heapSize);
void siftUp(int *heap, int i);
void siftDown (int *heap, int heapSize, int i);
*/
struct vertex {
    double xCoordinate, yCoordinate;
    double length;
    int previous;
    double heuristic;
};

/*
vertex *vertices;

double **edgeWeight;

int *candidate;

int nVertices;

int startVertex, goalVertex;
*/

class Simulation{
    private:
        ifstream fin;
        vertex *vertices;
        double **edgeWeight;
        int *candidate;
        int nVertices;
        int startVertex, goalVertex;
        string fileName = "";
    public:
        int openFile(const char* fileName);
        int run();
        int astar();
        void makeheap(int *heap, int heapSize);
        void siftUp(int *heap, int i);
        void siftDown (int *heap, int heapSize, int i);
        
};

#endif