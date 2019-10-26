#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int MAX = 200000;
size_t n, m;
vector<int> edges[MAX];
vector<int> reverse_edges[MAX];
bool used[MAX/10];
int color[MAX/10];
vector<int> top_sort;
int T = 0;

void dfs(int v) {
    used[v] = true;
    for (size_t i = 0; i < edges[v].size(); ++i) {
        if (!used[edges[v][i]]) {
            dfs(edges[v][i]);
        }
    }
    top_sort.push_back(v);
}

void dfs2(int v) {
    used[v] = false;
    color[v] = T;
    for (size_t i = 0; i < reverse_edges[v].size(); ++i) {
        if (used[reverse_edges[v][i]]) {
            dfs2(reverse_edges[v][i]);
        }
    }
}

#define NAME "/home/liuba/second_year_itmo/algorithms/lads/lab1/condencation/"

int main() {
    ifstream fin(NAME"cond.in");
    ofstream fout(NAME"cond.out");

    fin >> n >> m;
    int v1, v2;

    for (size_t i = 0; i < n; ++i) {
        used[i] = false;
    }

    for (size_t i = 0; i < m; ++i) {
        fin >> v1 >> v2;
        edges[v1 - 1].push_back(v2 - 1);
        reverse_edges[v2 - 1].push_back(v1 - 1);
    }

    for (size_t i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i);
        }
    }

    for (size_t i = 1; i <= n; i ++) {
        int v = top_sort[n - i];
        if (used[v]) {
            T++;
            dfs2(v);
        }
    }

    fout << T << endl;

    for (size_t i = 0; i < n; ++i) {
        fout << color[i] << " ";
    }

    fout << endl;

    fin.close();
    fout.close();
    return 0;
}
