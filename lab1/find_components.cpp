#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int MAX = 100000;
size_t n, m;
vector<int> edges[MAX];
bool used[MAX];
int color[MAX];
int T = 0;

void dfs(int v) {
    used[v] = true;
    color[v] = T;
    for (size_t i = 0; i < edges[v].size(); ++i) {
        if (!used[edges[v][i]]) {
            dfs(edges[v][i]);
        }
    }
}

#define NAME  //  "/home/liuba/second_year_itmo/algorithms/lads/lab1/components/"

int main() {
    ifstream fin(NAME"components.in");
    ofstream fout(NAME"components.out");

    fin >> n >> m;
    int v1, v2;

    for (size_t i = 0; i < n; ++i) {
        used[i] = false;
    }

    for (size_t i = 0; i < m; ++i) {
        fin >> v1 >> v2;
        edges[v1 - 1].push_back(v2 - 1);
        edges[v2 - 1].push_back(v1 - 1);
    }

    for (size_t i = 0; i < n; ++i) {
        if (!used[i]) {
            T++;
            dfs(i);
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
