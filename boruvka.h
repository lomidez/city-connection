int find(Subset subsets[], int i);
void Union(Subset subsets[], int x, int y);

vector<vector<int>> Boruvka(Graph* g)
{
    vector<vector<int>> adj_mat(300);
    for(int i=0;i<300;++i)
        adj_mat[i]= vector<int>(300);

    for(int i=0; i<300; ++i)
    {
        for(int j=0; j<300;++j)
            adj_mat[i][j]=0;
    }

    int V = g->V;
    int E = g->E;
    Subset* subsets = new Subset[V];
    int* cheapest = new int[V];

    for (int i=0; i<V; ++i)
    {
        subsets[i].parent = i;
        subsets[i].rank = 0;
        cheapest[i]=-1;
    }

    int numTrees = V;
    int MSTweight = 0;

    while (numTrees > 1)
    {
        // Everytime initialize cheapest array
        for (int v = 0; v < V; ++v)
        {
            cheapest[v] = -1;
        }

        // Traverse through all edges and update
        // cheapest of every component
        for (int i=0; i<E; i++)
        {
            // Find components (or sets) of two corners
            // of current edge
            int set1 = find(subsets,g->edge[i].source);
            int set2 = find(subsets,g->edge[i].dest);

            // If two corners of current edge belong to
            // same set, ignore current edge
            if (set1 == set2)
                continue;

                // Else check if current edge is closer to previous
                // cheapest edges of set1 and set2
            else
            {
                if (cheapest[set1] == -1 ||
                    g->edge[cheapest[set1]].weight > g->edge[i].weight)
                    cheapest[set1] = i;

                if (cheapest[set2] == -1 ||
                    g->edge[cheapest[set2]].weight > g->edge[i].weight)
                    cheapest[set2] = i;
            }
        }

        // Consider the above picked cheapest edges and add them
        // to MST
        for (int i=0; i<V; i++)
        {
            // Check if cheapest for current set exists
            if (cheapest[i] != -1)
            {
                int set1 = find(subsets, g->edge[cheapest[i]].source);
                int set2 = find(subsets, g->edge[cheapest[i]].dest);

                if (set1 == set2)
                    continue;
                MSTweight += g->edge[cheapest[i]].weight;
                adj_mat[g->edge[cheapest[i]].source][g->edge[cheapest[i]].dest] = 1;

                // Do a union of set1 and set2 and decrease number
                // of trees
                Union(subsets, set1, set2);
                numTrees--;
            }
        }

        cout << MSTweight;

//        for(int i=0;i<3;++i)
//        {
//            for(int j=0; j<3;++j)
//                cout << adj_mat[i][j]<<' ';
//            cout << endl;

    }
    return adj_mat;
}

//----------------------------------------------------------------------------------------------------------------------

///Auxiliary methods
int find(Subset subsets[], int i)
{
    // find root and make root as parent of i
    // (path compression)
    if (subsets[i].parent != i)
        subsets[i].parent =
                find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

// A function that does union of two sets of x and y
// (uses union by rank)
void Union(Subset subsets[], int x, int y)
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
