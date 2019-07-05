#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


using namespace std;

struct Edge
{
    int src, dest;
    double weight;
};

struct Subset
{
    int parent;
    int rank;
};


class Graph
{
public:
    int V, E;
    Edge* edge;
    //vector<Node*> vecOfNodes;

    //vector<pair<string, vector<double>>> SaveData();
    //vector<vector<double>> distance_mat();
    //Graph* createGraph(int v,int e);


};

//----------------------------------------------------------------------------------------------------------------------
/*This part is definition of methods defined above*/

///save data from txt file
vector<pair<string, vector<double>>> SaveData()
{


    ifstream inFile("C:\\Users\\msalm\\Desktop\\file.txt");
    vector<pair<string, vector<double>>> all_info;

    string city;
    double shirota, dolgota;


    while(inFile >> city >> shirota >> dolgota)
    {
        pair<string, vector<double>> p;
        vector<double> coordinates;
        coordinates.push_back(shirota);
        coordinates.push_back(dolgota);
        p = make_pair(city, coordinates);
        all_info.push_back(p);
        //cout << city << ' '<<shirota << ' '<<dolgota;
    }

//    for(auto a: all_info)
//        cout << a.first << ' ';
//    cout << endl;

    return all_info;
}

vector<pair<string, vector<double>>> info = SaveData();

///create distance matrix
vector<vector<double>> distance_mat() {

    vector<vector<double>> dist_matrix;
    for(int j=0; j<SaveData().size();++j)
    {
        vector<double> v;
        for(int i=0; i<SaveData().size();++i)
        {
            double distance;
            if (j==i)
                distance = 0;
            distance = sqrt(pow(SaveData()[i].second[0]-SaveData()[j].second[0],2)+pow(SaveData()[i].second[1]-SaveData()[j].second[1],2));
            v.push_back(distance);
        }
        dist_matrix.push_back(v);
    }
    return dist_matrix;
}



struct Graph* createGraph(int v,int e)
{
    Graph* graph = new Graph;
    graph->V = v;
    graph->E = e;
    graph->edge = new Edge[e];
    return graph;

}
struct subset
{
    int parent;
    int rank;
};

// A utility function to find set of an element i
// (uses path compression technique)
int find(struct subset subsets[], int i)
{
    // find root and make root as parent of i
    // (path compression)
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

// A function that does union of two sets of x and y
// (uses union by rank)
void Union(struct subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    // Attach smaller rank tree under root of high
    // rank tree (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;

        // If ranks are same, then make one as root and
        // increment its rank by one
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Compare two edges according to their weights.
// Used in qsort() for sorting an array of edges
int myComp(const void* a, const void* b)
{
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight > b1->weight;
}

// The main function to construct MST using Kruskal's algorithm
vector<vector<int>> KruskalMST(struct Graph* graph) {

    vector<vector<int>> adj_mat(300);
    for (int i = 0; i < 300; ++i)
        adj_mat[i] = vector<int>(300);

    for (int i = 0; i < 300; ++i) {
        for (int j = 0; j < 300; ++j)
            adj_mat[i][j] = 0;
    }
    int MSTweight = 0;


    int V = graph->V;
    struct Edge result[V];  // Tnis will store the resultant MST
    int e = 0;  // An index variable, used for result[]
    int i = 0;  // An index variable, used for sorted edges

    // Step 1:  Sort all the edges in non-decreasing
    // order of their weight. If we are not allowed to
    // change the given graph, we can create a copy of
    // array of edges
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);

    // Allocate memory for creating V ssubsets
    struct subset *subsets =
            (struct subset *) malloc(V * sizeof(struct subset));

    // Create V subsets with single elements
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Number of edges to be taken is equal to V-1
    while (e < V - 1 && i < graph->E) {
        // Step 2: Pick the smallest edge. And increment
        // the index for next iteration
        struct Edge next_edge = graph->edge[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge does't cause cycle,
        // include it in result and increment the index
        // of result for next edge
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
        // Else discard the next_edge
    }

    // print the contents of result[] to display the
    // built MST
    for (i = 0; i < e; ++i) {
        MSTweight += result[i].weight;
        adj_mat[result[i].src][result[i].dest] = 1;
        //cout << result[i].src << " " << result[i].dest << " " << result[i].weight << endl;
    }
    //cout << MSTweight;
    return adj_mat;
}
