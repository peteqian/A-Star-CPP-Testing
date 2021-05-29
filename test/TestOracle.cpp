#include "TestOracle.h"

int TestOracle::openFile(const char* fileName){
    fileIn.open(fileName);
    if(!fileIn){
        cerr << "TestOracle - Error opening file " << fileName << "." << endl;
        return 1;
    }
    cout << "TestOracle - Successfully opened: " << fileName << endl;
    return 0;
}

int TestOracle::readFile(){
    // Read into number of vertices and edges from top line of sample data
    fileIn >> nVertices >> nEdges;
    
    // Output an error if the symbol cannot be read into an int variable
    if(!fileIn.good()){
        cerr << "You must enter an int value for the number of vertices and/or number of edges." << endl;
        return 1;
    }

    // With this condition, the program cannot accept negative number of vertices and number of edges
    if(nVertices < 0 || nEdges < 0){
        cerr << "Cannot input negative number of vertices and/or number of edges." << endl;
        return 1;
    }

    // Initialize the data
    vertices = new vertexStruct[nVertices];
    for(int i = 0; i < nVertices; i++){
        fileIn >> id >> vertices[i].xCoordinate >> vertices[i].yCoordinate;
        
        // Output an error if the symbol cannot be read into an int variable
        if(!fileIn.good()){
            cerr << "You must enter an int value for the vertexStruct and/or the coordinates." << endl;
            return 1;
        }

        // Vertices Order Check
        if (id_tracker < id){
            id_tracker = id;
        } else {
            cerr << "TestOracle - Previous read in number '" << id_tracker;
            cerr << "' is higher than current read in number '" << id;
            cerr << "'. This may mean the order of read in data is wrong." << endl;
            return 1;
        }

        // With this condition, the program cannot accept negative coordinates
        if(vertices[i].xCoordinate < 0 || vertices[i].yCoordinate < 0){
            cerr << "TestOracle - Cannot input negative coordinates." << endl;
            return 1;
        }
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

    int row, col;

    // Account for duplicate paths. Since graph is non-directed, store both [i][j] and [j][i] weights.
    for (int i = 0; i < nEdges;i++){
       
        fileIn >> row >> col;

        // Output an error if the symbol cannot be read into an int variable
        if(!fileIn.good()){
            cerr << "TestOracle - You must insert int values only for the edge and/or the weight." << endl;
            return 1;
        }

        // With this condition, the program cannot accept negative edge values
        if(row < 0 || col < 0){
            cerr << "TestOracle - Cannot input negative edge values." << endl;
            return 1;
        }

        if(row > nVertices || col > nVertices){
            cerr << "TestOracle - You cannot insert an edge with a vertexStruct that doesn't exist." << endl;
            return 1;
        }

        // Feed in edge weight afterwards
        fileIn >> edgeWeight[row-1][col-1];

        // With this condition, the program cannot accept negative edge weight
        if(edgeWeight[row-1][col-1] < 0){
            cerr << "Cannot input negative edge weight." << endl;
            return 1;
        }

        row--;
        col--;


        if (edgeWeight[row][col] < edgeWeight[col][row]){
            edgeWeight[col][row] = edgeWeight[row][col];
        } else {
            edgeWeight[row][col] = edgeWeight[row][col];
        }

    }


    // Read start and goal vertexStruct and calculate heuristics for each vertexStruct.
    fileIn >> startVertex >> goalVertex;                                

    // With this condition, the program cannot accept negative start vertexStruct and goal vertexStruct
    if(startVertex < 0 || goalVertex < 0){
        cerr << "Cannot input negative edge start vertexStruct and/or goal vertexStruct." << endl;
        return 1;
    }

    // Output an error if the symbol cannot be read into an int variable
    if(!fileIn.good()){
        cerr << "You must insert int values only for the edge start vertexStruct and/or goal vertexStruct." << endl;
        return 1;
    }

    startVertex--;
    goalVertex--;

    if(fileIn.eof()){ 
        cout << "Haven't reached the end of the file." << endl;
        return 1;
    }
    
    return 0;
}

int TestOracle::run(){
    
    // Run type
    int status = 0;
    status = astar();

    // Report shortest Path information
    if (status == 0){
        cout << "---TestOracle---" << endl;
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

    // 2nd Shortest Path run
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
            nPath2Vertices = 0;
            for(int i = goalVertex; i != startVertex; i = vertices[i].previous){
                path2[nPath2Vertices++] = i;
            }
            path2[nPath2Vertices++] = startVertex;
        }
    }


    if(vertices[goalVertex].length == HUGE_VAL){
        nPath2Vertices = 0;
    }
    
    if(nPath2Vertices > 0){
        cout << "The 2nd shortest path has a length of " << vertices[goalVertex].length << endl;
        cout << " The vertices on this path are: ";
        for(int i = nPath2Vertices; i > 0; i--){
            cout << path2[i-1]+1 << " ";
        }
        cout << endl;
    }


    fileIn.close();
    delete[] vertices;
    for(int i = 0; i < nVertices; i ++){
        delete[] edgeWeight[i];
    }
    delete[] edgeWeight;
    delete[] path;
    delete[] path2;

    return 0;
}

int TestOracle::astar(){
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

void TestOracle::makeheap(int *heap, int heapSize){
    for (int i = heapSize/2; i >= 0; i--){
        siftDown(heap, heapSize, i);
    }
}

void TestOracle::siftUp(int *heap, int i){

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

void TestOracle::siftDown (int *heap, int heapSize, int i){
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