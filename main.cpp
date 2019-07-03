#include <iostream>
#include "header.h"

using namespace std;

int main(){

    ///Create graph
    Graph g;
    for(const auto& p: g.SaveData())
    {
        g.add_node(p.first);
    }
    g.add_edges();
    g.display_Nodes_neighbours(g.vecOfNodes[0]);
}