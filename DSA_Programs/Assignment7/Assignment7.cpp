#include <iostream>
#include <vector>
#include <algorithm>


class UnionFind {
    private:
        int* parents;
        int* ranks;

    public:
        UnionFind(int numVertices) {
            parents = new int[numVertices];
            ranks = new int[numVertices];

            for (int i = 0; i < numVertices; i++) {
                parents[i] = i;
                ranks[i] = 0;
            }
        }

        ~UnionFind() {
            delete parents;
            delete ranks;
        }

        int findParent(int vertex) {
            if (vertex == parents[vertex]) {
                return vertex;
            }
            else {
                while (vertex != parents[vertex]) {
                    vertex = parents[vertex];
                }
                return vertex;
            }
        }


        void merge(int vertex1, int vertex2) {
            int pVertex1 = findParent(vertex1);
            int pVertex2 = findParent(vertex2);
            if (pVertex1 != pVertex2) {
                if (ranks[pVertex1] == ranks[pVertex2]) {
                    parents[pVertex2] = pVertex1;
                    ranks[pVertex1]++;
                }
                else if (ranks[pVertex1] < ranks[pVertex2]) {
                    parents[vertex1] = pVertex2;
                }
                else {
                    parents[vertex2] = pVertex1;
                }
            } 
        }
};


class Graph {
    private:
        std::vector<std::vector<int>> edgeList;
        std::vector<std::string> numberToNameArray;
        int numVertices;

        int minDistance(bool included[], int distance[]) {
            int minVertex, minDistance = 999999;
            for (int i = 0; i < numVertices; i++) {
                if (!included[i] && distance[i] < minDistance) {
                    minDistance = distance[i];
                    minVertex = i;
                }
            }
            return minVertex;
        }

    public:
        Graph(int numVertices) {
            this->numVertices = numVertices;
            std::string temp;
            for (int i = 0; i < numVertices; i++) {
                std::cout << "Name of " << i << " vertex: ";
                std::cin >> temp;
                numberToNameArray.push_back(temp);
            }
        }

        void addEdge(int vertex1, int vertex2, int weight) {
            if (vertex1 != vertex2) {
                edgeList.push_back({weight, vertex1, vertex2});
            }
        }

        void kruskalMST() {
            int totalWeight = 0, weight, vertex1, vertex2;
            std::sort(edgeList.begin(), edgeList.end());
            UnionFind* unionfind = new UnionFind(numVertices);
            std::cout << "MST\n";
            for (auto edge: edgeList) {
                weight = edge[0];
                vertex1 = edge[1];
                vertex2 = edge[2];

                if (unionfind->findParent(vertex1) != unionfind->findParent(vertex2)) { 
                    unionfind->merge(vertex1, vertex2);
                    totalWeight += weight;
                    std::cout << numberToNameArray[vertex1] << " --- "
                    << numberToNameArray[vertex2] << " = " << weight << "\n";
                }
            }
            std::cout << "Total Weight of MST: " << totalWeight << "\n";
            delete unionfind;
        }

        void primsMST(std::vector<std::vector<int>> matrix) {

            bool included[numVertices];
            int distance[numVertices];
            int parent[numVertices];
            int numEdgesIncluded = 0;

            for (int i = 0; i < numVertices; i++) {
                included[i] = false;
                distance[i] = 99999;
            }

            distance[0] = 0;
            parent[0] = -1;

            while (numEdgesIncluded != numVertices - 1) {

                int vertexToVisit = minDistance(included, distance);

                included[vertexToVisit] = true;

                for (int i = 0; i < numVertices; i++) {
                    if (matrix[vertexToVisit][i] != 0 && !included[i] && 
                    matrix[vertexToVisit][i] < distance[i]) {
                        parent[i] = vertexToVisit;
                        distance[i] = matrix[vertexToVisit][i];    
                    }
                }

                numEdgesIncluded++;

            }

            std::cout << "\nMST Edges\n";
            int totalWeight = 0;
            for (int i = 1; i < numVertices; i++) {
                std::cout << numberToNameArray[parent[i]] << " --- " << numberToNameArray[i] << " = "
                << matrix[i][parent[i]] << " \n";
                totalWeight += matrix[i][parent[i]];
            }
            std::cout << "Total Weight of MST: " << totalWeight << "\n";
        }
};


int main() {
    
    Graph graph(5);
    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 2, 4);
    graph.addEdge(0, 3, 1);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 3, 2);
    graph.addEdge(3, 4, 1);
    graph.kruskalMST();
    std::vector<std::vector<int>> matrix = {
        {0,5,4,1,0},
        {5,0,2,0,0},
        {4,2,0,2,0},
        {1,0,2,0,1},
        {0,0,0,1,0}};
    graph.primsMST(matrix);
}