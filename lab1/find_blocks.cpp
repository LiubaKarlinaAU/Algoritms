#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAX = 20000;
size_t n, m;

struct edge {
    int to;
    int number;

    edge(int to, int number) {
        this->to = to;
        this->number = number;
    }

    edge() {
        this->to = -1;
        this->number = -1;
    }
};

vector<edge> edges[MAX];
bool used[MAX];
int up[MAX];
int tin[MAX];
int T = 0;

bool points[MAX];
int color[MAX * 10 + 1];

void dfs(int v, int pr) {
    tin[v] = T;
    up[v] = T++;
    used[v] = true;
    int children = 0;
    for (size_t i = 0; i < edges[v].size(); ++i) {
        int u = edges[v][i].to;
        if (u != pr) {
            if (!used[u]) {
                children++;
                dfs(u, v);
                up[v] = min(up[v], up[u]);
                if (pr != -1 && up[u] >= tin[v]) {
                    points[v] = true;
                }
            } else {
                up[v] = min(up[v], tin[u]);
            }
        }
    }

    if (pr == -1 && children > 1) {
        points[v] = true;
    }
}

int number_of_colors = 0;

void coloring_dfs(int v, int pr, int c) {
    used[v] = false;
    for (size_t i = 0; i < edges[v].size(); ++i) {
        int u = edges[v][i].to;
        int num = edges[v][i].number;
        if (u != pr) {
            if (used[u]) {
                if (up[u] >= tin[v]) {
                    color[num] = ++number_of_colors;
                    coloring_dfs(u, v, number_of_colors);
                } else {
                    color[num] = c;
                    coloring_dfs(u, v, c);
                }
            } else if (tin[u] < tin[v]) {
                color[num] = c;
            }
        }
    }
}


#define NAME  //  "/home/liuba/second_year_itmo/algorithms/lads/lab1/biconv/"

int main() {
    ifstream fin(NAME"biconv.in");
    ofstream fout(NAME"biconv.out");

    fin >> n >> m;
    int v1, v2;

    for (size_t i = 0; i < n; ++i) {
        used[i] = false;
    }

    for (size_t i = 1; i <= m; ++i) {
        fin >> v1 >> v2;
        edges[v1 - 1].push_back(edge(v2 - 1, i));
        edges[v2 - 1].push_back(edge(v1 - 1, i));
    }

    for (size_t i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i, -1);
        }
    }

    for (size_t i = 0; i < n; ++i) {
        if (used[i]) {
            coloring_dfs(i, -1, number_of_colors);
        }
    }

    fout << number_of_colors << endl;
    for (size_t i = 1; i <= m; ++i) {
        fout << color[i] << " ";
    }

    fout << endl;

    fin.close();
    fout.close();

    return 0;
}
