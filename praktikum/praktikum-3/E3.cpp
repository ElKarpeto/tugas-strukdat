#include <bits/stdc++.h>
using namespace std;

struct graph
{
    long vertexCount, edgeCount;
    vector<vector<pair<long, long>>> adjList;
    vector<pair<long, pair<long, long>>> edgeList;

    void init(long v)
    {
        vertexCount = v;
        edgeCount = 0;

        for (int i = 0; i < vertexCount; i++)
        {
            adjList.push_back({}); // inserts V ammount of empty vector
        }
    }

    void add_edge(long vertex1, long vertex2, long weight)
    {
        adjList[vertex1].push_back(make_pair(vertex2, weight));
        adjList[vertex2].push_back(make_pair(vertex1, weight));

        edgeList.push_back(make_pair(weight, make_pair(vertex1, vertex2)));
        edgeCount++;
    }

    void dfs(vector<long> &result, long start)
    {
        vector<bool> visited(vertexCount, false);
        stack<long> st;

        st.push(start);
        visited[start] = true;
        result.push_back(start);

        while (!st.empty())
        {
            long temp = st.top();
            st.pop();

            if (!visited[temp])
            {
                result.push_back(temp);
                visited[temp] = true;
            }

            for (auto vertex : adjList[temp])
            {
                if (!visited[vertex.first])
                    st.push(vertex.first);
            }
        }
    }

    void bfs(vector<long> &result, long start)
    {
        vector<bool> visited(vertexCount, false);
        queue<long> q;

        q.push(start);
        visited[start] = true;
        result.push_back(start);

        while (!q.empty())
        {
            long temp = q.front();
            q.pop();

            for (auto vertex : adjList[temp])
            {
                if (!visited[vertex.first])
                {
                    q.push(vertex.first);
                    visited[vertex.first] = true;
                    result.push_back(vertex.first);
                }
            }
        }
    }

    void dijkstra(vector<long> &result, long start)
    {
        vector<bool> visited(vertexCount, false);
        priority_queue<pair<long, long>,
                       vector<pair<long, long>>,
                       greater<pair<long, long>>>
            pq;
        result = vector<long>(vertexCount, LONG_MAX);

        pq.push(make_pair(0, start));
        result[start] = 0;

        while (!pq.empty())
        {
            auto temp = pq.top();
            pq.pop();

            if (visited[temp.second])
                continue;

            visited[temp.second] = true;

            for (auto vertex : adjList[temp.second])
            {
                long nextVertex = vertex.first;
                long weight = vertex.second;

                if (temp.first + weight < result[nextVertex])
                {
                    result[nextVertex] = temp.first + weight;
                    pq.push(make_pair(result[nextVertex], nextVertex));
                }
            }
        }
    }

    long find_parent(vector<long> &parent, long v)
    {
        if (v == parent[v])
            return v;

        return parent[v] = find_parent(parent, parent[v]);
    }

    void union_set(vector<long> &parent, long vertex1, long vertex2)
    {
        parent[vertex2] = parent[vertex1];
    }

    void kruskal(vector<pair<long, pair<long, long>>> &result)
    {
        vector<long> parent;
        for (int i = 0; i < vertexCount; i++)
            parent.push_back(i);

        sort(edgeList.begin(), edgeList.end());

        for (int i = edgeList.size() - 1; i >= 0; i--)
        {
            long vertex1 = edgeList[i].second.first;
            long vertex2 = edgeList[i].second.second;
            if (find_parent(parent, vertex1) != find_parent(parent, vertex2))
            {
                result.push_back(edgeList[i]);
                union_set(parent, find_parent(parent, vertex1), find_parent(parent, vertex2));
                if (result.size() == vertexCount - 1)
                    return;
            }
        }
    }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    long n, m;

    cin >> n >> m;

    graph G;

    G.init(n);

    long node1, node2, weight;
    for (int i = 0; i < m; i++)
    {
        cin >> node1 >> node2 >> weight;
        G.add_edge(node1, node2, weight);
    }

    vector<pair<long, pair<long, long>>> hasil;

    G.kruskal(hasil);

    long long jumlah = 0;
    for (int i = 0; i < hasil.size(); i++)
    {
        jumlah += hasil[i].first;
    }

    cout << jumlah << endl;
}