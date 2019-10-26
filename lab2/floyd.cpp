#include <iostream>
#include <vector>

using namespace std;
const long long INF = numeric_limits<long long>::max();

int main() {
    size_t n, m;
    cin >> n >> m;

    std::vector<std::vector<long long>> matrix;
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

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
