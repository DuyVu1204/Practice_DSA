#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <stack>
#include <algorithm>

#define INF 1000000000

using namespace std;

vector<vector<int>> convertMatrixToList(const string& filename);
vector<vector<int>> convertListToMatrix(const string& filename);
bool isDirected(const vector<vector<int>>& adjMatrix);
int countVertices(const vector<vector<int>>& adjMatrix);
int countEdges(const vector<vector<int>>& adjMatrix);
bool checkNolink(const vector<vector<int>>& adjMatrix, int v);
vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix);
bool isCompleteGraph(const vector<vector<int>>& adjMatrix);
bool isBipartite(const std::vector<std::vector<int>>& adjMatrix);
bool isCompleteBipartite(const vector<vector<int>>& adjMatrix);
vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix);
vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix);
bool isEuler(const vector<vector<int>>& adjMatrix);
vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix);
void dfs(int v, const vector<vector<int>>& adjMatrix, vector<bool>& visited, vector<vector<int>>& treeMatrix);
vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start);
void bfs(int v, const vector<vector<int>>& adjMatrix, vector <bool>& visited, vector<vector<int>>& treeMatrix);
vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start);
bool findWay(int start, int target, const vector<vector<int>>& adjMatrix);
bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix);
vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix);
vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix);

vector<vector<int>> convertMatrixToList(const string& filename)
{
    int n;
    vector<vector<int>> a;
    ifstream infile(filename);
    if (!infile)
    {
        cout << "Error open file!" << endl;
        return a;
    }
    infile >> n;
    for (int i = 0; i < n; i++)
    {
        vector<int> b(1, 0);
        int count = 0;
        for (int j = 0; j < n; j++)
        {
            int x;
            infile >> x;
            if (x != 0)
            {
                b.push_back(j);
                count++;
            }
        }
        b[0] = count;
        a.push_back(b);
    }
    infile.close();
    return a;
}

vector<vector<int>> convertListToMatrix(const string& filename)
{
    int n;
    ifstream infile(filename);
    vector<vector<int>> a;
    if (!infile)
    {
        cout << "Error open file!" << endl;
        return a;
    }
    infile >> n;
    infile.ignore();
    a.resize(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        string line;
        getline(infile, line);
        stringstream ss(line);
        int num;
        ss >> num;
        for (int j = 0; j < num; j++)
        {
            int x;
            ss >> x;
            a[i][x] = 1;
        }
    }
    return a;
}

bool isDirected(const vector<vector<int>>& adjMatrix)
{
    for (int i = 0; i < adjMatrix.size(); i++)
    {
        for (int j = 0; j < adjMatrix[i].size(); j++)
        {
            if (adjMatrix[i][j] != adjMatrix[j][i])// Check for symmetry
                return true; // If different => has direction
        }
    }
    return false; // If all are equal => scalar
}

int countVertices(const vector<vector<int>>& adjMatrix)
{
    return adjMatrix.size();// return size of matrix
}

int countEdges(const vector<vector<int>>& adjMatrix)
{
    int count = 0;
    for (int i = 0; i < adjMatrix.size(); i++)
        for (int j = 0; j < adjMatrix[i].size(); j++)
            if (adjMatrix[i][j])
                count++;// Calculate the edges of graph
    if (isDirected(adjMatrix))
        return count;// If the graph is directed, return the edge.
    else
        return count / 2;// If the graph is undirected, we need to divide by 2.
}

bool checkNolink(const vector<vector<int>>& adjMatrix, int v) {
    for (int i = 0; i < adjMatrix.size(); i++)
    {
        if (adjMatrix[v][i] != 0 || adjMatrix[i][v] != 0)// Check if that vertex has any edges
            return false;
    }
    return true;
}

vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix) {
    vector<int> a;
    for (int i = 0; i < adjMatrix.size(); i++)
    {
        // Iterate over all vertices of the graph using the checkNolink function to add up the count variable.
        if (checkNolink(adjMatrix, i))
        {
            a.push_back(i);
        }
    }
    return a;
}

bool isCompleteGraph(const vector<vector<int>>& adjMatrix) {
    for (int i = 0; i < adjMatrix.size(); i++)
        if (adjMatrix[i].size() != adjMatrix.size())
            return false;

    for (int i = 0; i < adjMatrix.size(); i++)
    {
        if (adjMatrix[i][i] != 0)// Check the ring
            return false;
        for (int j = 0; j < adjMatrix[i].size(); j++)
        {
            if (i != j)
            {
                //Check if that vertex connects edges to other vertices
                if (adjMatrix[i][j] == 0 || adjMatrix[i][j] != adjMatrix[j][i])
                    return false;
            }
        }
    }
    return true;
}

bool isBipartite(const std::vector<std::vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> color(n, -1);// Uncolored, for vertices color is -1
    for (int i = 0; i < n; i++)
    {
        if (color[i] == -1)// If the vertex is not colored then start iterating over it.
        {
            queue<int> q;
            q.push(i);
            color[i] = 1;// Give it color 1
            while (!q.empty())
            {
                int v = q.front();
                q.pop();
                for (int j = 0; j < n; j++)
                {
                    if (adjMatrix[v][j] != 0)
                    {
                        if (color[j] == -1)
                        {
                            q.push(j);
                            color[j] = 1 - color[v];// Iterate over the adjacent vertices, if not colored, set the color to 0
                        }
                        else if (color[j] == color[v])// If adjacent to each other and have the same color, return false
                            return false;
                    }
                }
            }
        }
    }
    return true;
}

bool isCompleteBipartite(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> color(n, -1);
    for (int i = 0; i < n; i++)
    {
        if (color[i] == -1)
        {
            queue<int> q;
            q.push(i);
            color[i] = 1;
            while (!q.empty())
            {
                int v = q.front();
                q.pop();
                for (int j = 0; j < n; j++)
                {
                    if (adjMatrix[v][j] != 0)
                    {
                        if (color[j] == -1)
                        {
                            q.push(j);
                            color[j] = 1 - color[v];
                        }
                        else if (color[j] == color[v])
                            return false;
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j == i)
                continue;
            if (color[i] == color[j])
            {
                if (adjMatrix[i][j] != 0)// If same color then 2 edges are not adjacent
                    return false;
            }
            else
            {
                if (adjMatrix[i][j] == 0) // If different colors must be adjacent to each other
                    return false;
            }
        }
    }
    return true;
}

vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<vector<int>> copyMatrix(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (adjMatrix[i][j] != 0)// if that cell is not 0
            {
                // Set the values ​​in those cells symmetrically across the main diagonal to 1.
                copyMatrix[i][j] = 1;
                copyMatrix[j][i] = 1;
            }
        }
    }
    return copyMatrix;
}

vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<vector<int>> complementMatrix(n, vector<int>(n, 1));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                if (adjMatrix[i][j] != 0)
                {
                    complementMatrix[i][j] = 0;// Set cells with non-zero values ​​to 0 to make adjacent cells non-adjacent.
                }
            }
            else
            {
                complementMatrix[i][j] = 0;// vertices without a ring
            }
        }
    }

    return complementMatrix;
}

bool isEuler(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    queue<int> q;

    // Find the first non-zero degree vertex to start BFS
    int start = -1;
    for (int i = 0; i < n; ++i)
    {
        int deg = 0;
        for (int j = 0; j < n; ++j)
            deg += adjMatrix[i][j];
        if (deg > 0)
        {
            start = i;
            break;
        }
    }
    if (start == -1)
        return true; // No edges

    // BFS
    q.push(start);

    visited[start] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = 0; v < n; ++v)
        {
            if ((adjMatrix[u][v] > 0 || (!isDirected(adjMatrix) && adjMatrix[v][u] > 0)) && !visited[v])
            {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    // Check that all vertices with degree > 0 have been visited.
    for (int i = 0; i < n; ++i)
    {
        int deg = 0;
        for (int j = 0; j < n; ++j)
            deg += adjMatrix[i][j] + (!isDirected(adjMatrix) ? adjMatrix[j][i] : 0);
        if (deg > 0 && !visited[i])
            return false;
    }

    return true;
}

vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> cycle;

    if (!isEuler(adjMatrix))
        return {};

    bool directed = isDirected(adjMatrix);

    if (directed) // Check the condition of a directed graph
    {
        vector<int> in(n, 0), out(n, 0);
        for (int u = 0; u < n; ++u)
            for (int v = 0; v < n; ++v)
                if (adjMatrix[u][v])
                {
                    out[u] += adjMatrix[u][v];
                    in[v] += adjMatrix[u][v];
                }
        for (int i = 0; i < n; ++i)
            if (in[i] != out[i]) return {};
    }
    else // Check the condition of an undirected graph
    {
        for (int i = 0; i < n; ++i)
        {
            int deg = 0;
            for (int j = 0; j < n; ++j)
                deg += adjMatrix[i][j];
            if (deg % 2 != 0)
                return {};
        }
    }

    vector<vector<int>> copyMatrix = adjMatrix;

    // Find the starting vertex with edge
    int start = -1;
    for (int i = 0; i < n; ++i)
    {
        int deg = 0;
        for (int j = 0; j < n; ++j)
            deg += adjMatrix[i][j];
        if (deg > 0)
        {
            start = i;
            break;
        }
    }
    if (start == -1) return {};

    stack<int> s;
    s.push(start);

    while (!s.empty())
    {
        int u = s.top();
        bool found = false;
        for (int v = 0; v < n; ++v)
        {
            if (copyMatrix[u][v])
            {
                s.push(v);
                copyMatrix[u][v]--;
                if (!directed)
                    copyMatrix[v][u]--;
                found = true;
                break;
            }
        }
        if (!found)
        {
            cycle.push_back(u);
            s.pop();
        }
    }


    reverse(cycle.begin(), cycle.end());

    return cycle;
}

void dfs(int v, const vector<vector<int>>& adjMatrix, vector<bool>& visited, vector<vector<int>>& treeMatrix) {
    int n = adjMatrix.size();
    visited[v] = true;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && adjMatrix[v][i] != 0)
        {
            treeMatrix[v][i] = 1;
            treeMatrix[i][v] = 1;
            dfs(i, adjMatrix, visited, treeMatrix);
        }
    }
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    vector<vector<int>> treeMatrix(n, vector<int>(n, 0));
    if (start < 0 || start >= n) return treeMatrix;
    dfs(start, adjMatrix, visited, treeMatrix);
    return treeMatrix;
}

void bfs(int v, const vector<vector<int>>& adjMatrix, vector <bool>& visited, vector<vector<int>>& treeMatrix) {
    int n = adjMatrix.size();
    queue<int> q;
    q.push(v);
    visited[v] = true;
    while (!q.empty())
    {
        int x = q.front();
        q.pop();

        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && adjMatrix[x][i] != 0)
            {
                q.push(i);
                visited[i] = true;
                treeMatrix[x][i] = 1;
                treeMatrix[i][x] = 1;
            }

        }
    }
}

vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    vector<vector<int>> treeMatrix(n, vector<int>(n, 0));
    bfs(start, adjMatrix, visited, treeMatrix);
    return treeMatrix;
}

bool findWay(int start, int target, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (u == target)
            return true;

        for (int v = 0; v < n; ++v)
        {
            if (adjMatrix[u][v] != 0 && !visited[v])
            {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    return false;
}

bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix) {
    if (u == v) return true;  // Same top is always connected

    if (!isDirected(adjMatrix))
    {
        // Undirected graph, just check 1 direction is enough
        return findWay(u, v, adjMatrix);
    }
    else {
        // Directed graph, connected if u->v or v->u has a path
        return findWay(u, v, adjMatrix) || findWay(v, u, adjMatrix);
    }
}

vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> d(n, INF);// distance
    vector<bool> visited(n, false);// visited vertex
    vector<int> parent(n, -1);// parent of vertex

    d[start] = 0;

    for (int i = 0; i < n - 1; i++)
    {
        int u = -1;
        int mind = INF;
        for (int j = 0; j < n; j++)
        {
            if (!visited[j] && d[j] < mind)
            {
                mind = d[j];
                u = j;
            }
        }

        if (u == -1)
            break;
        visited[u] = true;

        for (int k = 0; k < n; k++)
        {
            if (adjMatrix[u][k] != INF && !visited[k])
            {
                if (d[u] + adjMatrix[u][k] < d[k])
                {
                    d[k] = d[u] + adjMatrix[u][k];
                    parent[k] = u;
                }
            }
        }
    }

    vector<int> path;

    if (d[end] == INF)
        return path;

    for (int v = end; v != -1; v = parent[v])
    {
        path.push_back(v);
    }

    reverse(path.begin(), path.end());

    return path;
}

vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> d(n, INF);
    vector<int> parent(n, -1);

    d[start] = 0;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (adjMatrix[j][k] != INF && d[j] != INF && d[j] + adjMatrix[j][k] < d[k])
                {
                    d[k] = d[j] + adjMatrix[j][k];
                    parent[k] = j;
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (adjMatrix[i][j] != INF && d[i] != INF && d[i] + adjMatrix[i][j] < d[j])
            {
                return {};
            }
        }
    }

    vector<int> path;

    if (d[end] == INF)
        return path;

    for (int v = end; v != -1; v = parent[v])
    {
        path.push_back(v);
    }

    reverse(path.begin(), path.end());
    return path;
}
