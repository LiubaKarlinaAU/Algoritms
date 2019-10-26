#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int MAX = 100000;
size_t n, m;
vector<int> graph[MAX];
bool used[MAX];
int color[MAX];
bool flag = true;

void dfs(int v, int c) {
    used[v] = true;
    color[v] = c;
    for (size_t i = 0; i < graph[v].size(); ++i) {
        int u = graph[v][i];

        if (!used[u]) {
            dfs(u, 1 - c);
        }

        if (color[u] == c) {
            flag = false;
        }
    }
}

#define NAME  //  "/home/liuba/second_year_itmo/algorithms/lads/lab1/bipartice/"

int main() {
    ifstream fin(NAME"bipartite.in");
    ofstream fout(NAME"bipartite.out");

    fin >> n >> m;

    int v1, v2;

    for (size_t i = 0; i < m; ++i) {
        fin >> v1 >> v2;
        graph[v1 - 1].push_back(v2 - 1);
        graph[v2 - 1].push_back(v1 - 1);
    }

    for (size_t i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i, 0);
        }
    }

    if (flag) {
        fout << "YES" << endl;
    } else {
        fout << "NO" << endl;
    }

    fout << endl;

    fin.close();
    fout.close();
    return 0;
}
