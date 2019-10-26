#include <iostream>
#include <vector>

using namespace std;

const long long INF = numeric_limits<long long>::max();
vector<vector<long long>> edges;
vector<long long> dist;
vector<bool> used;

int main() {
    ios_base::sync_with_stdio(false);
    size_t n, s, f;

    cin >> n >> s >> f;

    --s;
    --f;
    edges.resize(n);
    dist.resize(n, INF);
    used.resize(n);

    dist[s] = 0;

    for (size_t i = 0; i < n; ++i) {
        edges[i].resize(n);
        for (size_t j = 0; j < n; ++j) {
            cin >> edges[i][j];
        }
    }

    for (size_t i = 0; i < n; ++i) {
        size_t v = 2001;

        for (size_t j = 0; j < n; ++j) {
            if (!used[j] && (v == 2001 || dist[v] > dist[j])) {
                v = j;
            }
        }

        if (v == 2001 || dist[v] == INF) {
            break;
        }

        used[v] = true;
        if (v == f) {
            cout << dist[f] << endl;
            return 0;
        }

        for (size_t j = 0; j < n; ++j) {
            if (!used[j] && edges[v][j] != -1) {
                if (dist[j] > dist[v] + edges[v][j]) {
                    dist[j] = dist[v] + edges[v][j];
                }
            }
        }
    }


    if (dist[f] == INF) {
        cout << -1 << endl;
    } else {
        cout << dist[f] << endl;
    }

    return 0;
}
