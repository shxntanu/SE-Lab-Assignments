/*
You have a business with several offices; you want to lease phone lines
to connect them up with each other; and the phone company charges
different amounts of money to connect different pairs of cities. You
want a set of lines that connects all your offices with a minimum total
cost. Solve the problem by suggesting appropriate data structures.
*/

#include<bits/stdc++.h>
using namespace std;

class Graph {
    int **adjMatix;
    int nodeCount;
    map<string, int> cities;

    public:

    Graph(){
        cout<<"Enter number of Nodes: ";
        cin>>nodeCount;
        adjMatix = new int*[nodeCount];
        for (int i = 0; i < nodeCount; i++) {
            adjMatix[ i ] = new int[ nodeCount ];
        }

        cout<<"Add cities in order: "<<endl;
        for(int i = 0; i < nodeCount; i++) {
            string city;
            cin>>city;
            cities.insert(pair<string, int>(city, i));
        }
    }

    void add( string city1, string city2, int dist ) {
        adjMatix[cities[city1]][cities[city2]] = dist;
        adjMatix[cities[city2]][cities[city1]] = dist;
    }

    
};
