#include <iostream>
#include <vector>
#include <fstream>
#include <set>

using namespace std;

const int64_t INF = numeric_limits<long long>::max();

struct edge {
    int64_t weight;
    unsigned int vertex;

    edge(int64_t weight, unsigned int vertex) {
        this->weight = weight;
        this->vertex = vertex;
    }

    bool operator<(edge const &obj) const {
        if (this->weight != obj.weight) {
            return this->weight < obj.weight;
        }
        return this->vertex < obj.vertex;
    }

    bool operator==(edge const &obj) const {
        return this->weight == obj.weight && this->vertex == obj.vertex;
    }
};

vector<vector<edge>> edges;
vector<int64_t> dist;
set<edge> set1;

int main() {
    size_t n, m;

    cin >> n >> m;

    edges.resize(n);
    dist.resize(n, INF);

    dist[0] = 0;
    set1.insert(edge(dist[0], 0));

    for (size_t i = 0; i < m; ++i) {
        unsigned int v1, v2;
        int64_t w;
        cin >> v1 >> v2 >> w;
        edges[--v1].push_back(edge(w, --v2));
        edges[v2].push_back(edge(w, v1));
    }

    while (!set1.empty()) {
        size_t v = set1.begin()->vertex;
        set1.erase(set1.begin());

        for (edge e : edges[v]) {
            if (dist[e.vertex] > dist[v] + e.weight) {
                set1.erase(edge(dist[e.vertex], e.vertex));
                dist[e.vertex] = dist[v] + e.weight;
                set1.insert(edge(dist[e.vertex], e.vertex));
            }
        }
    }

    for (size_t i = 0; i < n; ++i) {
        cout << dist[i] << " ";
    }

    return 0;
}
