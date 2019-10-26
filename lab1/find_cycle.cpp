#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <algorithm>

using namespace std;

size_t n, m;
vector<vector<int>> graph;
vector<int> color;
vector<int> ans;
stack<int> st;
bool cycle = false;
size_t finded;

void dfs1(int v) {
    color[v] = 1;
    for (size_t u : graph[v]) {
        if (!color[u]) {
            dfs1(u);
        } else if (color[u] == 1) {
            cycle = true;
            finded = u;
        }
    }

    color[v] = 2;
}

bool dfs2(int v) {
    st.push(v);
    color[v] = 1;

    bool on_cycle = false;

    for (size_t u : graph[v]) {
        if (!color[u]) {
            if (dfs2(u)) {
                on_cycle = true;
            }
        } else if (u == finded) {
            on_cycle = true;
        }
    }

    color[v] = 2;
    if (on_cycle) {
        ans.push_back(v);
        return true;
    } else {
        st.pop();
        return false;
    }
}


#define NAME  //  "/home/liuba/second_year_itmo/algorithms/lads/lab1/cycle/"
//  #define FILE_NAME "cycle"


int main() {
    ifstream fin(NAME"cycle.in");
    ofstream fout(NAME"cycle.out");

    fin >> n >> m;
    int v1, v2;

    graph.resize(n);
    color.resize(n);

    for (size_t i = 0; i < m; ++i) {
        fin >> v1 >> v2;
        graph[v1 - 1].push_back(v2 - 1);
    }

    for (size_t i = 0; i < n; ++i) {
        if (!color[i]) {
            dfs1(i);
        }
    }


    if (!cycle) {
        fout << "NO" << endl;
        return 0;
    }

    color.assign(n, 0);
    dfs2(finded);

    fout << "YES" << endl;

    reverse(ans.begin(), ans.end());
    for (size_t i : ans) {
        fout << i + 1 << " ";
    }

    fout << endl;

    fin.close();
    fout.close();
    return 0;
}
