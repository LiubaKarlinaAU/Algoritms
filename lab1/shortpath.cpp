#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAX = 100000;
const long long INF = 1000000001;
size_t n, m;
int s, t;
bool used[MAX];
long long dist[MAX];
vector<int> ans;

struct edge {
    int end;
    long long weight;

    edge(int end, long long weight) {
        this->end = end;
        this->weight = weight;
    }
};

vector<edge> edges[MAX];

void dfs(int v) {
    used[v] = true;
    for (size_t i = 0; i < edges[v].size(); ++i) {
        if (!used[edges[v][i].end]) {
            dfs(edges[v][i].end);
        }
    }

    ans.push_back(v);
}

#define NAME  //  "/home/liuba/second_year_itmo/algorithms/lads/lab1/shortpath/"

int main() {
    ifstream fin(NAME"shortpath.in");
    ofstream fout(NAME"shortpath.out");

    fin >> n >> m >> s >> t;
    --s;
    --t;
    int v1, v2;
    long long w;

    for (size_t i = 0; i < m; ++i) {
        fin >> v1 >> v2 >> w;
        edges[v1 - 1].push_back(edge(v2 - 1, w));
    }

    for (size_t i = 0; i < n; ++i) {
        dist[i] = INF;
        if (!used[i]) {
            dfs(i);
        }
    }

    reverse(ans.begin(), ans.end());

    size_t i = 0;
    while (i < n && ans[i] != s) {
        ++i;
    }

    dist[s] = 0;
    for (; i < n; ++i) {
        int cur = ans[i];
        for (size_t j = 0; j < edges[cur].size(); ++j) {
            edge e = edges[cur][j];
            dist[e.end] = min(dist[e.end], dist[cur] + e.weight);
        }
    }

    if (dist[t] == INF) {
        fout << "Unreachable" << endl;
    } else {
        fout << dist[t] << endl;
    }

    fin.close();
    fout.close();
    return 0;
}
