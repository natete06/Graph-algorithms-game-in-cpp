#include <iostream>
#include <map>
#include <vector>

class Graph{
    public:
        Graph() {}
        void addVertex(int vertex) {
            map_graph[vertex] = {};
        }
        // vector to store neighbors of each vertex
        void addEdge(int Vert1, int Vert2) {
            // creates an equivalence of nodes
            map_graph[Vert1].push_back(Vert2);
            map_graph[Vert2].push_back(Vert1);
        }
        void printGraph() {
            // loops through each key(node) and prints the values from the vector(neighbours) using an iterator object
            for (std::map<int, std::vector<int>>::iterator it = map_graph.begin(); it != map_graph.end(); ++it) {
                //for each key..
                std::cout << "Node " << it->first <<" -> ";
                //for each neighbor..
                for (std::vector<int>::iterator nbr = it->second.begin(); nbr != it->second.end(); ++nbr) {
                    //dereference every vector element
                    std::cout << " " << *nbr;
                     if (nbr + 1 != it->second.end()) {  // avoids trialing comma
                        std::cout << ", ";
                    }
                }
                std::cout << std::endl;
            }
        }

         
    private:
        std::map<int, std::vector<int>> map_graph;

};

int main() {
    Graph g;
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.printGraph();
}