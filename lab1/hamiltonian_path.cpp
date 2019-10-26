#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int MAX = 100000;
size_t n, m;
vector<int> graph[MAX];
bool used[MAX];
vector<int> ans;

void dfs(int v) {
    used[v] = true;
    for (size_t i = 0; i < graph[v].size(); ++i) {
        if (!used[graph[v][i]]) {
            dfs(graph[v][i]);
        }
    }

    ans.push_back(v);
}

bool exist(int v1, int v2) {
    for (size_t i = 0; i < graph[v1].size(); ++i) {
        if (graph[v1][i] == v2) {
            return true;
        }
    }
    return false;
}

#define NAME ""  //  "/home/liuba/second_year_itmo/algorithms/lads/lab1/hamiltonian/"

int main() {
    ifstream fin(NAME"hamiltonian.in");
    ofstream fout(NAME"hamiltonian.out");

    fin >> n >> m;
    int v1, v2;

    for (size_t i = 0; i < m; ++i) {
        fin >> v1 >> v2;
        graph[v1 - 1].push_back(v2 - 1);
    }

    for (size_t i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i);
        }
    }

    bool flag = true;
    for (size_t i = n - 1; i > 0; --i) {
        if (!exist(ans[i], ans[i - 1])) {
            flag = false;
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
