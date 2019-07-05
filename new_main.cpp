#include <iostream>
#include "boruvka.h" //здесь поменять на свой хэдер

using namespace std;

int main(){

    ///Create graph
    Graph* g = createGraph(300,44850);

//    vector<vector<int>> v = {{0,2,3},{2,0,6},{3,6,0}};
//
//    for(int i=0;i<3;++i)
//    {
//        for(int j=0;j<3;++j)
//            cout << v[i][j]<<" ";
//        cout <<endl;
//    }

    int index = 0;

    //info.size()-1, info.size()
    for(int i=0; i<info.size()-1;++i)
    {
        for (int j=i+1; j<info.size();++j)
        {
            g->edge[index].source = i;
            g->edge[index].dest = j;
            g->edge[index].weight = distance_mat()[i][j];
            ++index;
        }
    }

    Boruvka(g); //здесь на свой поменять

}
