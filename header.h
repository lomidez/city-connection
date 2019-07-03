#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <cmath>

using namespace std;

///code for Graph
struct Node;

struct Link
{
    Node* node;
    double weight;
};

struct Node
{
    string city;
    vector<Link> neighbours;
};

class Graph
{
public:
    vector<pair<string, vector<double>>> SaveData();
    vector<vector<double>> distance_mat();

    vector<Node*> vecOfNodes;
    Node* add_node(string value)
    {
        Node* n = new Node;
        n->city = value;
        vecOfNodes.push_back(n);
    }

    void add_edges()
    {
        for (int j=0;j<vecOfNodes.size();++j)
        {
            for (int i=0;i<vecOfNodes.size();++i)
            {
                if (j != i)
                {
                    Link l;
                    l.node = vecOfNodes[i];
                    l.weight = distance_mat()[j][i];
                    vecOfNodes[j]->neighbours.push_back(l);
                }

            }
        }
    }

    void display_Nodes_neighbours(Node* n)
    {
        for(const auto& p: n->neighbours)
        {
            cout << p.node->city << " "<< p.weight<<endl;
        }
    }


};

//----------------------------------------------------------------------------------------------------------------------

///save data from txt file
vector<pair<string, vector<double>>> Graph::SaveData()
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

//----------------------------------------------------------------------------------------------------------------------
///create distance matrix
vector<vector<double>> Graph::distance_mat() {

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
//----------------------------------------------------------------------------------------------------------------------