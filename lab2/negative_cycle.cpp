#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct edge {
    long long weight;
    unsigned int v1, v2;

    edge(unsigned int vertex1, unsigned int vertex2, long long weight) {
        this->weight = weight;
        this->v1 = vertex1;
        this->v2 = vertex2;
    }
};

typedef long long ll;

const ll INF = 10e9;
size_t n, t;
vector<edge> edges;
vector<ll> dist;
vector<unsigned int> pr;
vector<unsigned int> cycle;

int main() {
    cin >> n;

    dist.resize(n);
    pr.resize(n, 300);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            long long w;
            cin >> w;
            if (w != INF) {
                edges.push_back(edge(i, j, w));
            }
        }
    }

    unsigned int anka = 300;
    for (size_t i = 0; i < n; ++i) {
        anka = 300;
        for (edge e : edges) {
            if (dist[e.v2] > dist[e.v1] + e.weight) {
                dist[e.v2] = dist[e.v1] + e.weight;
                pr[e.v2] = e.v1;
                anka = e.v2;
            }
        }
    }

    if (anka == 300) {
        cout << "NO" << endl;
        return 0;
    }

    cout << "YES" << endl;

    for (size_t i = 0; i < n; ++i) {
        anka = pr[anka];
    }

    for (unsigned int k = anka;; k = pr[k]) {
        cycle.push_back(k);
        if (k == anka && cycle.size() > 1)
            break;
    }

    unsigned int m = cycle.size();
    cout << m << endl;

    for (size_t i = 0; i < m; ++i) {
        cout << cycle[m - 1 - i] + 1 << " ";
    }

    return 0;
}

