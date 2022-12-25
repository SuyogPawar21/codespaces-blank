#include <iostream>
#include <vector>
#include <algorithm>

static const int INFINITY = 999999999;


int findNextVertexToVisit(int distancesFromSourceVertex[], bool visited[], int numVertices) {
    int currentMinimum = INFINITY, potentialVertexToVisit = -1;
    for (int i = 0; i < numVertices; i++) {
        if (!visited[i] && distancesFromSourceVertex[i] < currentMinimum) {
            potentialVertexToVisit = i;
            currentMinimum = distancesFromSourceVertex[i];
        }
    }
    return potentialVertexToVisit;
}

std::string constructPath(int sourceVertex, int terminalVertex,
 int previousVertexInShortestPath[], std::string numberToNameArray[]) {

    int temp = terminalVertex;

    std::string path;

    while (previousVertexInShortestPath[temp] != sourceVertex) {
        path.append(numberToNameArray[temp] + " >- ");
        temp = previousVertexInShortestPath[temp];
    }

    path.append(numberToNameArray[temp] + " >- " + numberToNameArray[sourceVertex]);

    std::reverse(path.begin(), path.end());
    
    return path;
}

void displayDijkstrasResult(int distancesFromSourceVertex[], int previousVertexInShortestPath[],
 int numVertices, int sourceVertex) {

    std::string numberToNameArray[numVertices];

    std::string temp;

    for (int k = 0 ; k < numVertices; k++) {
        std::cout << "Name for " << k << " Vertex: ";
        std::cin >> temp;
        numberToNameArray[k] = temp;
    }

    for (int i = 0; i < numVertices; i++) {

        if (i == sourceVertex) {
            continue;
        }

        std::cout << "Shortest Path from " << numberToNameArray[sourceVertex] <<
         " to " << numberToNameArray[i] << ": ";

        std::cout << constructPath(sourceVertex, i, previousVertexInShortestPath, numberToNameArray)
         << " = "  << distancesFromSourceVertex[i] << std::endl;
    }
}


void dijkstras(std::vector<std::vector<int>> matrix, int numVertices, int sourceVertex) {

    int distancesFromSourceVertex[numVertices];
    int previousVertexInShortestPath[numVertices];
    bool visited[numVertices];
    int numVerticesVisited = 0;

    for (int i = 0; i < numVertices; i++) {
        distancesFromSourceVertex[i] = INFINITY;
        visited[i] = false;
    }

    distancesFromSourceVertex[sourceVertex] = 0;

    while (numVerticesVisited != numVertices) {

        int vertexToVisit = findNextVertexToVisit(distancesFromSourceVertex, visited, numVertices);

        visited[vertexToVisit] = true;

        for (int j = 0; j < numVertices; j++) {

            if (matrix[vertexToVisit][j] != 0 && !visited[j]) {

                if (distancesFromSourceVertex[vertexToVisit] + matrix[vertexToVisit][j] 
                < distancesFromSourceVertex[j]) {

                    distancesFromSourceVertex[j] = distancesFromSourceVertex[vertexToVisit] +
                    matrix[vertexToVisit][j];

                    previousVertexInShortestPath[j] = vertexToVisit;
                }
            }
        }

        numVerticesVisited++;
    }

    displayDijkstrasResult(distancesFromSourceVertex, previousVertexInShortestPath, numVertices, sourceVertex);
}



int main() {
    int numVertices = 5;
    std::vector<std::vector<int>> matrix1 = {


        /*      6
            A--------B
            |       /|\ 5
           1|   2/  2| C
            |/       |/ 5
            D--------E
                1

        */

            /*A*//*B*//*C*//*D*//*E*/
        /*A*/{0,   6,   0,   1,   0},
        /*B*/{6,   0,   5,   2,   2},
        /*C*/{0,   5,   0,   0,   5},
        /*D*/{1,   2,   0,   0,   1},
        /*E*/{0,   2,   5,   1,   0}


    };

    dijkstras(matrix1, numVertices, 0);

    https://www.geeksforgeeks.org/wp-content/uploads/Fig-11.jpg
    
    std::vector<std::vector<int>> matrix2 = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

    dijkstras(matrix2, matrix2[0].size(), 0);
    return 0; 
}
