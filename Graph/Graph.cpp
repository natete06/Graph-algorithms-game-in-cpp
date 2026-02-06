#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>

class Graph{
    
    private:
    // Node : neighbours using container nesting
        std::map<int, std::vector<int>> map_graph;

    public:
        Graph() {

        }

        void addNode(int Node) {
            map_graph[Node] = {}; 
        }
        // update vector which stores neighbors of each Node
        void addEdge(int Vert1, int Vert2) {
            // Add the connection
            map_graph[Vert1].push_back(Vert2);
            
            // LEXICOGRAPHIC ORDER 
            std::sort(map_graph[Vert1].begin(), map_graph[Vert1].end());

            // same here
            map_graph[Vert2].push_back(Vert1);
            std::sort(map_graph[Vert2].begin(), map_graph[Vert2].end());
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
        std::vector<int>& GetNbr(int Node) {
            return map_graph[Node];
        }


};

void BFS (Graph *g, int begin) {
    std::queue<int> bfs_Queue;      
    std::unordered_set<int> visited = {};

    visited.insert(begin);
    bfs_Queue.push(begin);

    while (!bfs_Queue.empty()) {
        //store before popping
        int current = bfs_Queue.front();
        std::cout<< "Visiting: " <<current<<std::endl;
        //dequeue current node
        bfs_Queue.pop();
        // neighbors stored for iteration

        const std::vector<int>& neighbors = g->GetNbr(current);
        for (int i = 0; i < neighbors.size(); i++) {
            if (visited.count(neighbors[i]) == 0) {
                bfs_Queue.push(neighbors[i]);
                visited.insert(neighbors[i]);
            }
        }
    }


}

int main() {
    

    std::cout << "\n\n==========================" << std::endl;
    std::cout << "   TESTING GRAPH G2" << std::endl;
    std::cout << "==========================\n" << std::endl;

    Graph g2;

    // 1. Add nodes (using 0-9 to keep it simple but larger)
    for (int i = 0; i < 10; i++) {
        g2.addNode(i);
    }

    // 2. Add "Random" Edges to create a complex web
    // This includes cycles (loops) which will crash your program
    // if the 'visited' set isn't working properly.
    g2.addEdge(0, 1);
    g2.addEdge(0, 4);
    g2.addEdge(1, 2);
    g2.addEdge(1, 3);
    g2.addEdge(1, 4); // Creates a triangle cycle (0-1-4)
    g2.addEdge(2, 5);
    g2.addEdge(3, 6);
    g2.addEdge(4, 5); // Creates a cycle (1-2-5-4)
    g2.addEdge(4, 7);
    g2.addEdge(5, 8);
    g2.addEdge(6, 7); // Creates a path convergence at 7
    g2.addEdge(7, 8); // Creates a cycle (4-5-8-7)
    g2.addEdge(8, 9); // The 'tail' of the graph

    std::cout << "--- Structure of G2 ---" << std::endl;
    g2.printGraph();

    std::cout << "\n--- Running BFS on G2 (Start Node: 0) ---" << std::endl;
    BFS(&g2, 0);
}