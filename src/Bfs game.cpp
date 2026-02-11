#include <raylib.h>
#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <set>


class Node {
public:
    int id;
    float x, y;
    Vector2 position;
    Color color;
    Node() : id(0), x(0), y(0), position{0, 0}, color(GRAY) {}
    
    Node(int id, float x, float y) : id(id), x(x), y(y), position{x, y}, color(GRAY) {}
    
    char getLabel() { // method to render nodes as letters instead of numbers
        return 'A' + id;
    }
};

class Graph{
    
    protected:
    // Node : neighbours using container nesting
        std::map<int, Node> nodes;
        std::map<int, std::vector<int>> map_graph;

    public:
        Graph() {}
        virtual ~Graph() {}

        void addNode(int id, float x, float y) {
            nodes[id] = Node(id, x, y);
            map_graph[id] = {};
        }

        void drawGraph() {
            // a set of tuples ish of drawn edges
            std::set<std::pair<int, int>> drawnEdges;

            // draw edges first
            for (auto& dict : map_graph) {
                //first node (int version)
                int nodeId = dict.first;
                // node equivalent storing all the properties (reference inorder to edit/change the properties like the color and so..)
                Node& node = nodes[nodeId];

                // iterate through the neighbors(the values of the map, hence the .second)
                for (int nbrId : dict.second) {
                    std::pair<int, int> pairs = {std::min(nodeId, nbrId), std::max(nodeId, nbrId)}; // normalising the edges so 1,2 and 2,1 are interpreted as the same edges
                    if (drawnEdges.find(pairs) == drawnEdges.end()) {

                        //ints used for logic but the node dict is needed for the actual visuals (coordinates, colors.....)
                        Vector2 p1 = node.position;
                        Vector2 p2 = nodes[nbrId].position;

                        DrawLineEx(p1, p2, 2.0f, GRAY); // draws a  line between two points (p1, p2) with thickness 2 and color GRAY.
                        drawnEdges.insert(pairs);

                    }

                }

            }

            for (auto& kvpairs : nodes) {
                //int nodeId = kvpairs.first;
                Node& node = kvpairs.second;

                // draw filled circle at the node position as the center (radius 20)
                DrawCircleV(node.position, 20, node.color);
                // outline with the same radius
                DrawCircleLines(node.position.x, node.position.y, 20, BLACK);

                std::string labelStr(1, node.getLabel());

                int fontSize = 20;

                //expects a C string (const char*)
                int textWidth = MeasureText(labelStr.c_str(), fontSize);

                DrawText(labelStr.c_str(), node.position.x - textWidth/2, node.position.y - fontSize/2, fontSize, BLACK);

            }
        }
        
        // update vector which stores neighbors of each Node
        virtual void addEdge(int Vert1, int Vert2) {
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

/*
class BFSTree : public Graph {
public:
    // overriden methon that only adds connection from source node to child node, not an adjaceny list like in the original graph
    void addEdge(int Parent, int Child) override {
        
        map_graph[Parent].push_back(Child);
        
        // Ensure the child node exists in the map too (even if it has no children yet or at all)
        if (map_graph.find(Child) == map_graph.end()) {
            std::vector<int> empty;
            map_graph[Child] = empty;
        }
    }
};

Graph* BFS(Graph *g, int begin) {
    std::queue<int> bfs_Queue;      
    std::unordered_set<int> visited = {};

    BFSTree *tree = new BFSTree();

    visited.insert(begin);
    bfs_Queue.push(begin);
    tree->addNode(begin);

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

                tree->addNode(neighbors[i]);
                tree->addEdge(current, neighbors[i]);
            }
        }
    }
    return tree;
}
*/

int main() {
    
    Graph g2;

    // 1. CLEAR previous random loop
    // (Delete the for-loop that uses i*50)

    // 2. SETUP NODES (Manual "Puzzle" Placement)
    // Central Ring (The "Trap" - loops back on itself)
    g2.addNode(0, 400, 100); // Start (Top)
    g2.addNode(1, 600, 300); // Right
    g2.addNode(2, 400, 500); // Bottom
    g2.addNode(3, 200, 300); // Left

    // The "Distractions" (Outer nodes that tempt you away)
    g2.addNode(4, 100, 150); // Top Left Wing
    g2.addNode(5, 700, 150); // Top Right Wing
    g2.addNode(6, 100, 450); // Bottom Left Wing
    g2.addNode(7, 700, 450); // Bottom Right Wing

    // The "Bridge" (Connecting distant parts)
    g2.addNode(8, 400, 300); // Dead Center

    // 3. SETUP EDGES (The Logic)
    // Connect the ring
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);
    g2.addEdge(3, 0);

    // Connect the center bridge (Creates short-cuts!)
    g2.addEdge(0, 8);
    g2.addEdge(2, 8);

    // Connect the wings (Dead ends or loops?)
    g2.addEdge(3, 4); // Left -> Wing
    g2.addEdge(4, 6); // Wing -> Wing (Loop on the side)
    g2.addEdge(6, 2); // Wing -> Bottom (Back connection)

    g2.addEdge(1, 5); // Right -> Wing
    g2.addEdge(5, 7);
    g2.addEdge(7, 2);

    std::cout << "--- Graph Structure g2 ---" << std::endl;
    g2.printGraph();

    //std::cout << "\n--- BFS Order (Start: 0) ---" << std::endl;
    //Graph* bfst = BFS(&g2, 0);
    //bfst->printGraph();

    int xval = 400;
    int yval = 400;
    Color idk{230, 99, 102, 255}; // struct with rgb then alpha as args

    InitWindow(800, 800, "Type shiiii");
    // game speed/fps
    SetTargetFPS(60);

    // Game loop, runs until close icon is clicked or if esc is pressed
    while(!WindowShouldClose()) {
        
        BeginDrawing();
        ClearBackground(idk);
        // (coords first 2) radius then color
        DrawCircle(xval, yval, 15, WHITE);

        g2.drawGraph();

        


        EndDrawing();

    }


    CloseWindow();



    return 0;
}