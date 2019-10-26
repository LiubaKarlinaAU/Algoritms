#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAX = 20000;
size_t n, m;

vector<int> edges[MAX];
bool used[MAX];
int up[MAX];
int tin[MAX];
int T = 0;

vector<int> ans;


void dfs(int v, int pr) {
    tin[v] = up[v] = T++;
    used[v] = true;
    int children = 0;
    for (size_t i = 0; i < edges[v].size(); ++i) {
        int u = edges[v][i];
        if (u != pr) {
            if (!used[u]) {
                children++;
                dfs(u, v);
                up[v] = min(up[v], up[u]);
                if (pr != -1 && up[u] >= tin[v]) {
                    ans.push_back(v);
                }
            } else {
                up[v] = min(up[v], tin[u]);
            }
        }
    }

    if (pr == -1 && children > 1) {
        ans.push_back(v);
    }
}

#define NAME  //  "/home/liuba/second_year_itmo/algorithms/lads/lab1/bridges/"

int main() {
    ifstream fin(NAME"points.in");
    ofstream fout(NAME"points.out");

    fin >> n >> m;
    int v1, v2;

    for (size_t i = 0; i < n; ++i) {
        used[i] = false;
    }

    for (size_t i = 1; i <= m; ++i) {
        fin >> v1 >> v2;
        edges[v1 - 1].push_back(v2 - 1);
        edges[v2 - 1].push_back(v1 - 1);
    }

    for (size_t i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i, -1);
        }
    }

    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());

    fout << ans.size() << endl;

    for (size_t i = 0; i < ans.size(); ++i) {
        fout << ans[i] + 1 << " ";
    }

    fout << endl;

    fin.close();
    fout.close();
    return 0;
}
