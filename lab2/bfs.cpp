#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<size_t>> edges;
vector<int> dist;
queue<int> q;
vector<bool> used;

int main() {
    size_t n, m;

    cin >> n >> m;

    edges.resize(n);
    dist.resize(n);
    used.resize(n, false);

    dist[0] = 0;
    used[0] = true;
    q.push(0);

    for (size_t i = 0; i < m; ++i) {
        int v1, v2;
        cin >> v1 >> v2;
        edges[--v1].push_back(--v2);
        edges[v2].push_back(v1);
    }

    while (!q.empty()) {
        int top = q.front();
        q.pop();

        for (int i : edges[top]) {
            if (!used[i]) {
                dist[i] = dist[top] + 1;
                q.push(i);
                used[i] = true;
            }
        }
    }

    for (size_t i = 0; i < n; ++i) {
        cout << dist[i] << " ";
    }

    return 0;
}
