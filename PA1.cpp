#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <vector>
#include <string>
using namespace std;



struct edge
{
    int Pre; // The tail of edge
    int Post;// The head of edge
};

int Not_Node = 1 << 32 - 1;

bool isDag = true;


// transfer the data from edges to adjacency matrix
vector<vector<int>> Transfer_Adj_Matrix(vector<edge> Edges, int Num_node, vector<vector<int>> G_Matrix)
{
    Num_node++; //0 is not a node. we start from 1
    //cout << Num_node << endl;
    G_Matrix.resize(Num_node);
    //cout << G_Matrix.size()<< endl;
    for(int i = 0; i < Num_node; i++)
    {
        for(int j = 0; j < Num_node; j++)
        {
            G_Matrix[i].push_back(0);
        }
    }
    for(int i = 0; i < Edges.size();i++)
    {
        G_Matrix[Edges[i].Pre][Edges[i].Post] = 1; // if there is a edge between i and j, G_Matrix[i][j] = 1, otherwise G_Matrix[i][j] = 0
    }
    return G_Matrix;
}

//print adjacency matrix
void Show_Matrix(vector<vector<int>> G_Matrix)
{
    for(int i = 1; i < G_Matrix.size(); i++)
    {
        for(int j = 1; j < G_Matrix[i].size(); j++)
        {
            cout << G_Matrix[i][j] << " ";
        }
        cout << endl;
    }
}

//Use DFS method to traverse all edges
void DFS(vector<vector<int>> G_Matrix, int StartNode, vector<int> Stack, vector<int> color)
{
     color[StartNode] = 1;
     Stack.push_back(StartNode);
     for(int i = 0; i < G_Matrix[StartNode].size(); i++)
     {
         if(i != StartNode && G_Matrix[StartNode][i] == 1)
         {
             if(color[i] == 0)
             {
                 DFS(G_Matrix, i, Stack, color);
             }
             else if(color[i] == 1)
             {
                 int k;
                 for(int j = 0; j < Stack.size(); j++)
                 {
                     if(i == Stack[j])
                     {
                         k = j;
                         cout << "Yes, it is a cycle." << endl;
                         while(k < Stack.size())
                         {
                             cout << Stack[k] << ",";
                             k++;
                         }
                         cout << endl;
                         isDag = false;
                         break;
                     }
                 }
             }

         }
     }
     Stack.pop_back();



}


int main(int argc, char **argv)
{


    //Input data
	/////////////////////////////////////////////////
	if(argc!=2)
	{
		cout << "usage: " << argv[0] << " filename" << endl;
		return 0;
	}
	fstream inputFile;
	inputFile.open(argv[1], ios::in);
	if(!inputFile.is_open())
	{
		cout << argv[1] << " not found!" << endl;
		return 0;
	}

	edge Empty_Edges;
	Empty_Edges.Pre = Not_Node;
	Empty_Edges.Post = Not_Node;
	vector<edge> Edges; // Save data in vector
    string line;
    getline(inputFile,line);
    int NodeNum;
    NodeNum = stoi(line);
	string str;
	char flag = ',';
    int lineNumber = 0;
	while(getline(inputFile, line))
	{
		Edges.push_back(Empty_Edges);
		stringstream input(line);
		vector<string> temp_Array;
		while(getline(input, str, flag))
        {
            temp_Array.push_back(str);

        }

        Edges[lineNumber].Pre = stoi(temp_Array[0]);
        if(temp_Array.size() == 2)
        {
            Edges[lineNumber].Post = stoi(temp_Array[1]);

        }
		lineNumber++;
	}
	inputFile.close();

	///////////////////////////////////////////
    /*
    //print input file.
    for(int i = 0; i < Edges.size(); i++)
    {
        cout << Edges[i].Pre << "," << Edges[i].Post << endl;
    }
    */


    vector<vector<int>> G_matrix;
    G_matrix = Transfer_Adj_Matrix(Edges, NodeNum, G_matrix);
    //Show_Matrix(G_matrix);

    vector<int> Stack; // save the nodes of cycle
    vector<int> color; // label of traversed node
    color.resize(G_matrix.size(), 0);

    DFS(G_matrix, 1, Stack, color); // start traverse the graph from 1

    if(isDag == true)
    {
        cout << "Not a cycle" << endl;
    }



	return 0;
}
