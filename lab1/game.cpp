#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int MAX = 100000;
size_t n, m, s;
vector<int> graph[MAX];
bool used[MAX];
bool color[MAX];

void dfs(int v) {
    used[v] = true;
    bool type = false;
    for (size_t i = 0; i < graph[v].size(); ++i) {
        size_t u = graph[v][i];
        if (!used[u]) {
            dfs(u);
        }
        if (!color[u]) {
            type = true;
        }
    }

    color[v] = type;
}

#define NAME ""  //  "/home/liuba/second_year_itmo/algorithms/lads/lab1/game/"

int main() {
    ifstream fin(NAME"game.in");
    ofstream fout(NAME"game.out");

    fin >> n >> m >> s;
    --s;
    int v1, v2;

    for (size_t i = 0; i < m; ++i) {
        fin >> v1 >> v2;
        graph[v1 - 1].push_back(v2 - 1);
    }

    dfs(s);

    if (color[s]) {
        fout << "First player wins" << endl;
    } else {
        fout << "Second player wins" << endl;
    }

    fout << endl;

    fin.close();
    fout.close();
    return 0;
}
