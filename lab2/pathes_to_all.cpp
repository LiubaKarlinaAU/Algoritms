#include <iostream>
#include <vector>

using namespace std;
const int64_t INF = numeric_limits<int64_t>::max();

int main() {
    //  ios_base::sync_with_stdio(false);
    size_t n, m, s;
    cin >> n >> m >> s;
    --s;

    std::vector<std::vector<int64_t>> matrix;
    matrix.resize(n);

    for (size_t i = 0; i < n; ++i) {
        matrix[i].resize(n, INF);
        matrix[i][i] = 0;
    }

    for (size_t j = 0; j < m; ++j) {
        unsigned int v1, v2;
        cin >> v1 >> v2;
        cin >> matrix[--v1][--v2];
    }

    for (size_t k = 0; k < n; ++k) {
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (matrix[i][k] != INF && matrix[k][j] != INF) {
                    matrix[i][j] = std::min(matrix[i][j], matrix[i][k] + matrix[k][j]);
                }
            }
        }
    }

    for (size_t j = 0; j < n; ++j) {
        for (size_t t = 0; t < n; ++t) {
            if (matrix[s][t] < INF && matrix[t][t] < 0 && matrix[t][j] < INF) {
                matrix[s][j] = -INF;
            }
        }
    }


    for (size_t i = 0; i < n; ++i) {
        int64_t dist = matrix[s][i];
        if (dist >= INF) {
            cout << "*\n";
        } else if (dist == -INF) {
            cout << "-\n";
        } else {
            cout << dist << "\n";
        }
    }

    return 0;
}
