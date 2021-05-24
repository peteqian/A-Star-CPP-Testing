#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// Prototype functions
int astar();
void makeheap(int *heap, int heapSize);
void siftUp(int *heap, int i);
void siftDown (int *heap, int heapSize, int i);


struct vertex {
    double xCoordinate, yCoordinate;
    double length;
    int previous;
    double heuristic;
};

vertex *vertices;

double **edgeWeight;

int *candidate;

int nVertices;

int startVertex, goalVertex;

int main(){

    //char fileName[20];
    string fileName;
    ifstream fin;

    cerr << "Please enter the name of the input file: ";
    //cin >> fileName;
    fileName = "Ass3.txt";

    fin.open(fileName);

    if(!fin){
        cerr << "Error opening file " << fileName << ". Program will exit" << endl;
        return 0;
    }

    int id, nEdges;

    // Read into number of vertices and edges from top line of sample data
    fin >> nVertices >> nEdges;

    // Initialize the data
    vertices = new vertex[nVertices];
    for(int i = 0; i < nVertices; i++){
        fin >> id >> vertices[i].xCoordinate >> vertices[i].yCoordinate;
    }

    edgeWeight = new double*[nVertices];

    for (int i = 0; i < nVertices; i++){
        edgeWeight[i] = new double[nVertices];
    }

    for (int row = 0; row < nVertices; row++){
        for (int col = 0; col < nVertices; col++){

            edgeWeight[row][col] = HUGE_VAL;
        }
    }
    cout << "Finished " << endl;
    int row, col;

    // Account for duplicate paths. Since graph is non-directed, store both [i][j] and [j][i] weights.
    for (int i = 0; i < nEdges;i++){
        fin >> row >> col >> edgeWeight[row-1][col-1];
        row--;
        col--;
        if (edgeWeight[row][col] < edgeWeight[col][row]){
            edgeWeight[col][row] = edgeWeight[row][col];
        } else {
            edgeWeight[row][col] = edgeWeight[row][col];
        }
    }


    // Read start and goal vertex and calculate heuristics for each vertex.
    fin >> startVertex >> goalVertex;
    startVertex--;
    goalVertex--;

    // Find shortest path
    int status = 0;
    status = astar();

    // Report shortest Path information
    int *path;
    int nPathVertices;

    if (status == 0){
        cout << "The shortest path has a length of " << vertices[goalVertex].length << endl;
        path = new int[nVertices];
        nPathVertices = 0;

        for (int i = goalVertex; i != startVertex; i = vertices[i].previous){
            path[nPathVertices++] = i;
        }

        path[nPathVertices++] = startVertex;

        cout << "The vertices on this path are: ";
        for (int i = nPathVertices; i > 0; i--){
            cout << path[i-1]+1 << " ";
        }
        cout << endl;

    } else {
        cout << "*** No path found between vertices " << startVertex << " and " << goalVertex << endl;
        return 1;
    }

    // For second shortest path
    int nPathEdges;
    double bestLength;
    double savedWeight;
    int from, to;
    int nPath2Vertices;
    int *path2;

    path2 = new int[nVertices];
    nPathEdges = nPathVertices - 1;
    bestLength = HUGE_VAL;

    for(int i = 0; i < nPathEdges; i++){

        // Remove this edge
        from = path[i];
        to = path[i+1];
        savedWeight = edgeWeight[from][to];
        edgeWeight[from][to] =  edgeWeight[to][from] = HUGE_VAL;

        status = astar();

        // Restore the removed edge
        edgeWeight[from][to] =  edgeWeight[to][from] = savedWeight;


        if(status == 0 && vertices[goalVertex].length < bestLength){
            bestLength = vertices[goalVertex].length;
            nPath2Vertices = 0;
            for(int i = goalVertex; i != startVertex; i = vertices[i].previous){
                path2[nPath2Vertices++] = i;
            }
            path2[nPath2Vertices++] = startVertex;
        }
    }

    if(nPath2Vertices > 0){
        cout << "The 2nd shortest path has a length of " << vertices[goalVertex].length << endl;
        cout << " The vertices on this path are: ";
        for(int i = nPath2Vertices; i > 0; i--){
            cout << path2[i-1]+1 << " ";
        }
        cout << endl;
    }


    fin.close();
    delete[] vertices;
    for(int i = 0; i < nVertices; i ++){
        delete[] edgeWeight[i];
    }
    delete[] edgeWeight;
    delete[] path;
    delete[] path2;

    return 0;
}

int astar(){
    double current, update;

    // Candidate Variables
    int *candidate;
    int nCandidates;

    // Prepare to run the A* Algorithm
    candidate = new int[nVertices];
    for (int i = 0; i < nVertices; i++){
        candidate[i] = i;
    }
    
    nCandidates = nVertices - 1;
    candidate[startVertex] = nCandidates;

    for (int i = 0; i < nVertices; i++){
        vertices[i].length = edgeWeight[startVertex][i];
        vertices[i].previous = startVertex;
    }

    makeheap(candidate, nCandidates);

    while(candidate[0] != goalVertex && vertices[candidate[0]].length != HUGE_VAL){
        // Remove the best candidate
        int selected = candidate[0];

        nCandidates--;
        candidate[0] = candidate[nCandidates];
        siftDown(candidate, nCandidates,0);

        for(int i = 0; i < nCandidates; i++){
            current = vertices[candidate[i]].length;
            update = vertices[selected].length + edgeWeight[selected][candidate[i]];

            if(update < current){
                // Update candidates values and restore the heap
                vertices [candidate [i]].length = update;
                vertices [candidate [i]].previous = selected;
                siftUp (candidate, i);
            }
        }
    }
    //Return the appropriate completion status
    delete[] candidate;
    if(vertices[goalVertex].length != HUGE_VAL){
        return 0;
    }

    return 1;
}

void makeheap(int *heap, int heapSize){
    for (int i = heapSize/2; i >= 0; i--){
        siftDown(heap, heapSize, i);
    }
}

void siftUp(int *heap, int i){

    int temp;

    if(i == 0){
        return;
    }

    int p = (i-1)/2;
    double iVal = vertices[heap[i]].length + vertices[heap[i]].heuristic;
    double pVal = vertices[heap[p]].length + vertices[heap[p]].heuristic;

    if(pVal < iVal) {
        return;
    }

    temp = heap[p];
    heap[p] = heap[i];
    heap[i] = temp;
    siftUp (heap, p);
    return ;
}

void siftDown (int *heap, int heapSize, int i){
    int temp, c;
    double iVal, cVal, c1Val ;
    c = 2 * i + 1;
    if (c >= heapSize ) {
        return;
    }

    iVal = vertices [heap[i]].length + vertices [heap[i]].heuristic ;
    cVal = vertices [heap[c]].length + vertices [heap[c]].heuristic ;

    if (c + 1 < heapSize ) {
        c1Val = vertices [heap[c + 1]].length + vertices [heap[c + 1]].heuristic;
        if (c1Val < cVal ){
            c++;
            cVal = c1Val;
        }
    }
    
    if (cVal > iVal ) {
        return;
    }

    temp = heap[c];
    heap[c] = heap[i];
    heap[i] = temp;
    siftDown (heap, heapSize, c);
    return;
}
