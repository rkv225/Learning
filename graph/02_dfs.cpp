/*
Time Complexity: O(V + E)
Space Complexity: O(V)
*/

#include<iostream>
#include<vector>

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define NIL -999999
#define INF 999999

using namespace std;

class node
{
public:
	int value;
	int color;
	int discovery;
	int finished;
	int parent;
	node(int v, int c, int d, int f, int p)
	{
		value = v;
		color = c;
		discovery = d;
		finished = f;
		parent = p;
	}
};

class Graph
{
private:
	int n;
	int time;
	vector<node> Vertices;
	vector<vector<int>> Adj;
	vector<int> Traversal;
public:
	Graph(int x)
	{
		n = x;
		for (int i = 0; i < n; i++)
			Vertices.push_back(node(i, WHITE, INF, INF, NIL));
		Adj.resize(n);
	}
	void AddEdge(int u, int v) // u ---> v
	{
		Adj[u].push_back(v);
	}
	void DFSVisit(int u)
	{
		time++;
		Vertices[u].discovery = time; // time of discovery
		Vertices[u].color = GRAY; // paint gray as this is now discovered
		Traversal.push_back(u);
		for (vector<int>::iterator it = Adj[u].begin(); it != Adj[u].end(); it++)
		{
			if (Vertices[(*it)].color == WHITE) // we'll only visit undiscovered nodes
			{
				Vertices[(*it)].parent = u; // set the parent 
				DFSVisit(*it); // visit the undiscovered node
			}
		}
		Vertices[u].color = BLACK; // when all adjacent nodes are traversed, mark node as black
		time++;
		Vertices[u].finished = time; // store finishing time 
	}
	void ComputeDFS()
	{
		time = 0;
		for (vector<node>::iterator it = Vertices.begin(); it != Vertices.end(); it++) // go for each node once in graph
		{
			if ((*it).color == WHITE)
				DFSVisit((*it).value);
		}
	}
	void print_traversal()
	{
		cout << "DFS Traversal:" << endl;
		for (vector<int>::iterator it = Traversal.begin(); it != Traversal.end(); it++)
			cout << *it << "(" << Vertices[(*it)].discovery << "/" << Vertices[(*it)].finished << ")" << endl;
	}
};

int main()
{
	Graph g(6);
	g.AddEdge(0, 1);
	g.AddEdge(0, 3);
	g.AddEdge(1, 2);
	g.AddEdge(1, 4);
	g.AddEdge(2, 4);
	g.AddEdge(2, 5);
	g.AddEdge(3, 1);
	g.AddEdge(4, 3);
	g.AddEdge(5, 5);
	g.ComputeDFS();
	g.print_traversal();
	return 0;
}