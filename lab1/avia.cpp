#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct edge {
    size_t vertex;
    long long weight;

    edge(size_t vertex, long long weight) {
        this->vertex = vertex;
        this->weight = weight;
    }
};

size_t n, m;
vector<vector<edge>> edges;
vector<vector<edge>> reverse_edges;
vector<bool> used;
vector<int> color;
vector<int> top_sort;
int T;
long long current_weight;

void dfs(int v) {
    used[v] = true;
    for (edge e : edges[v]) {
        if (!used[e.vertex] && e.weight <= current_weight) {
            dfs(e.vertex);
        }
    }
    top_sort.push_back(v);
}

void dfs2(int v) {
    used[v] = false;
    color[v] = T;
    for (edge e : reverse_edges[v]) {
        if (used[e.vertex] && e.weight <= current_weight) {
            dfs2(e.vertex);
        }
    }
}

bool is_one_component() {
    T = 0;
    top_sort.clear();
    used.assign(n, false);
    color.assign(n, 0);

    for (size_t i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i);
        }
    }

    for (size_t i = 1; i <= n; i++) {
        int v = top_sort[n - i];
        if (used[v]) {
            T++;
            if (T > 1) {
                return false;
            }
            dfs2(v);
        }
    }

    return true;
}

#define NAME  //  "/home/liuba/second_year_itmo/algorithms/lads/lab1/avia/"

int main() {
    ifstream fin(NAME"avia.in");
    ofstream fout(NAME"avia.out");

    fin >> n;
    edges.resize(n);
    reverse_edges.resize(n);
    used.resize(n);
    color.resize(n);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            long long w;
            fin >> w;
            edges[i].push_back(edge(j, w));
            reverse_edges[j].push_back(edge(i, w));
        }
    }

    long long l = -1, r = 1000000000;

    while (l + 1 < r) {
        current_weight = (l + r) / 2;
        if (is_one_component()) {
            r = current_weight;
        } else {
            l = current_weight;
        }
    }

    fout << r << endl;

    fin.close();
    fout.close();
    return 0;
}
