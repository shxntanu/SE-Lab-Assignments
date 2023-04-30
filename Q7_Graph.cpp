/*
You have a business with several offices; you want to lease phone lines
to connect them up with each other; and the phone company charges
different amounts of money to connect different pairs of cities. You
want a set of lines that connects all your offices with a minimum total
cost. Solve the problem by suggesting appropriate data structures.
*/

//#include<bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
const int max = INT_MAX;

class Graph {
    int **adjMatix;
    int nodeCount;
    int edgeCount;
    map<string, int> cities;
    map<int, string> inv_cities;

    public:

    Graph(){
        cout<<"Enter number of Nodes: ";
        cin>>nodeCount;
        cout<<"Enter number of edges: ";
        cin>>edgeCount;
        
        adjMatix = new int*[nodeCount];
        for (int i = 0; i < nodeCount; i++) {
            adjMatix[ i ] = new int[ nodeCount ];
        }
        
        for(int i=0; i<nodeCount; i++) {
            for(int j=0; j<nodeCount; j++) {
                adjMatix[i][j] = 0;
            }
        }

        cout<<"Add cities in order: "<<endl;
        for(int i = 0; i < nodeCount; i++) {
            string city;
            cin>>city;
            cities.insert(pair<string, int>(city, i));
            inv_cities.insert(pair<int, string>(i, city));
        }
        
        for(auto i: cities) {
            cout << i.first << " \t\t " << i.second << endl;
        }
        
        for(int i=0; i<edgeCount; i++) {
            string u,v;
            int d;
            cout<<"City 1: ";
            cin>>u;
            cout<<"City 2: ";
            cin>>v;
            cout<<"Distance: ";
            cin>>d;
            add(u, v, d);
        }
        
        for(int i=0; i<nodeCount; i++) {
            for(int j=0; j<nodeCount; j++) {
                cout<<adjMatix[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    void add( string city1, string city2, int dist ) {
        adjMatix[cities[city1]][cities[city2]] = dist;
        adjMatix[cities[city2]][cities[city1]] = dist;
    }
    
//    int selectMinVertex(vector<int>& value,vector<bool>& setMST, Graph g)
//    {
//        int minimum = INT_MAX;
//        int vertex = -1;
//        for(int i=0;i<g.nodeCount;++i)
//        {
//            if(setMST[i]==false && value[i]<minimum)
//            {
//                vertex = i;
//                minimum = value[i];
//            }
//        }
//        return vertex;
//    }
    
    int minimum_key(int k[], int mst[])
    {
        int minimum  = INT_MAX, min,i;
          
        /*iterate over all vertices to find the vertex with minimum key-value*/
        for (i = 0; i < nodeCount; i++)
            if (mst[i] == 0 && k[i] < minimum )
                minimum = k[i],min = i;
        return min;
    }
    
    void prim(Graph g) {
        int n = g.nodeCount;
        int parent[n];
        int k[n];
        int mst[n];
        
        for (int i = 0; i < n; i++)
        {
            k[i] = INT_MAX;
            mst[i] = 0;
        }
        
        k[0] = 0;
        parent[0] = -1;
        
        for (int count = 0; count < n-1; count++)
        {
            /*select the vertex having minimum key and that is not added in the MST yet from the set of vertices*/
            int edge = minimum_key(k, mst);
            mst[edge] = 1;
            for (int v = 0; v < n; v++)
            {
                if (g.adjMatix[edge][v] && mst[v] == 0 && g.adjMatix[edge][v] <  k[v])
                {
                    parent[v]  = edge;
                    k[v] = g.adjMatix[edge][v];
                }
            }
         }
        
        cout<<"MST of given graph is: \n"<<endl;
        cout<<"\nEdge \t Weight\n";
        for(int i=1; i<n; i++) {
            cout<<inv_cities[parent[i]]<<" <-> "<<inv_cities[i]<<" \t "<<g.adjMatix[i][parent[i]]<<endl;
        }
    }
};

int main() {
    
    Graph g;
    g.prim(g);
    
    return 0;
}
