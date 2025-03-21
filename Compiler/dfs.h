#include <iostream>
#include <list>
// C++ program to print DFS traversal from
// a given vertex in a  given graph

using namespace std;

// Graph class represents a directed graph
// using adjacency list representation

struct GTY(()) Graph
{
    int V;   // No. of vertices
    int end; // bb2.index
    bool succ;
    int start;
    int find = 0;
    // Pointer to an array containing
    // adjacency lists
    list<int> *adj;

    // int stack
    vector<int> stack;

    // A recursive function used by DFS
    void DFSUtil(int v, bool visited[]);
    // public:
    void init_Graph(int V); // Constructor

    // function to add an edge to graph
    void addEdge(int v, int w);
    bool exist_succ(basic_block bb);
    bool is_succ(basic_block bb1, basic_block bb2);
    // DFS traversal of the vertices
    // reachable from v
    void DFS(int v);
};

void Graph::init_Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}

void Graph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and
    // print it
    visited[v] = true;
    // cout << v << " ";

    // Recur for all the vertices adjacent
    // to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
    {

        if (*i == end)
        {
            succ = true;
        }
        if (!visited[*i])
        {
            if (*i > v)
            {
                stack.push_back(*i);
                DFSUtil(*i, visited);
                if (succ == true)
                {
                    while (stack.size())
                    {
                        stack.pop_back();
                    }
                    return;
                }
                else
                    stack.pop_back();
            }
        }
    }
}

// DFS traversal of the vertices reachable from v.
// It uses recursive DFSUtil()
void Graph::DFS(int v)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // Call the recursive helper function
    // to print DFS traversal

    DFSUtil(v, visited);
}

bool Graph::is_succ(basic_block bb1, basic_block bb2)
{
    stack.clear();
    end = bb2->index;
    succ = false;

    stack.push_back(bb1->index);
    start = bb1->index;
    // fprintf(stderr, "now stack %d\n", bb1->index);
    // fprintf(stderr, "now stack %d\n", bb2->index);
    DFS(bb1->index);
    return succ;
}

bool Graph::exist_succ(basic_block bb)
{
    list<int>::iterator i;
    for (i = adj[bb->index].begin(); i != adj[bb->index].end(); ++i)
    {
        return true;
    }
    return false;
}