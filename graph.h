#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <cmath>


using namespace std;

struct Edge
{
    string source;
    string dest;
    int weight;
};

struct Subset
{
    string parent;
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

//    for(int i=0; i<dist_matrix.size();++i)
//    {
//        for (int j=0; j<dist_matrix[0].size();++j)
//        {
//            cout << dist_matrix[i][j] << ' ';
//        }
//        cout << endl;
//    }

    return dist_matrix;
}

Graph* createGraph(int v,int e)
{
    Graph* graph = new Graph;
    graph->V = v;
    graph->E = e;
    graph->edge = new Edge[e];
    return graph;

}
