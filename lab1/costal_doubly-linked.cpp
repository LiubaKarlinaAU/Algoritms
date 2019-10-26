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
edge pr[MAX];
int up[MAX];
int tin[MAX];
int T = 0;
int bridges[MAX * 10];
int color[MAX];

void dfs(int v) {
    tin[v] = T;
    up[v] = T++;
    used[v] = true;
    for (size_t i = 0; i < edges[v].size(); ++i) {
        int u = edges[v][i].to;
        if (!used[u]) {
            pr[u].number = edges[v][i].number;
            pr[u].to = v;
            dfs(u);
            up[v] = min(up[v], up[u]);
        } else {
            if (u != pr[v].to) {
                up[v] = min(up[v], tin[u]);
            }
        }
    }

    if (pr[v].to != -1 && up[v] > tin[pr[v].to]) {
        bridges[pr[v].number] = true;
    }
}

int number_of_color = 0;

void color_dfs(int v, int c) {
    color[v] = c;
    used[v] = false;

    for (size_t i = 0; i < edges[v].size(); ++i) {
        int u = edges[v][i].to;
        if (used[u]) {
            color_dfs(u, bridges[edges[v][i].number] ? ++number_of_color : c);
        }
    }
}

#define NAME  

int main() {
    ifstream fin(NAME"bicone.in");
    ofstream fout(NAME"bicone.out");

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
            dfs(i);
        }
    }


    for (size_t i = 0; i < n; ++i) {
        if (used[i]) {
            color_dfs(i, ++number_of_color);
        }
    }

    fout << number_of_color << endl;

    for (size_t i = 0; i < n; ++i) {
        fout << color[i] << " ";
    }

    fout << endl;

    fin.close();
    fout.close();
    return 0;
}
