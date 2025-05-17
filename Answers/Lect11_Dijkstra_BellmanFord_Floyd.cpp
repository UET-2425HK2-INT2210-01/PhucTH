/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
using namespace std;

const long long INF = 1e9; // Giá trị đại diện cho vô cực
const int MAXN = 105; // Số đỉnh tối đa

// Cấu trúc lưu cạnh
struct Edge {
    int u, v, d; // Đỉnh u, v, trọng số d
};

// Hàm tự viết để đảo ngược vector
void reverseVector(vector<int>& vec) {
    int left = 0, right = vec.size() - 1;
    while (left < right) {
        int temp = vec[left];
        vec[left] = vec[right];
        vec[right] = temp;
        left++;
        right--;
    }
}

// Hàm Bellman-Ford tìm đường đi ngắn nhất từ s đến e
void bellmanFord(int n, int s, int e, const vector<Edge>& edges, long long& totalDirty, vector<int>& path) {
    vector<long long> dist(n + 1, INF); // Khoảng cách từ s đến các đỉnh
    vector<int> pred(n + 1, -1); // Lưu đỉnh trước đó để khôi phục đường đi
    dist[s] = 0;

    // Lặp n-1 lần để thư giãn các cạnh
    for (int i = 1; i <= n - 1; ++i) {
        for (const auto& edge : edges) {
            int u = edge.u, v = edge.v;
            long long d = edge.d;
            if (dist[u] != INF && dist[u] + d < dist[v]) {
                dist[v] = dist[u] + d;
                pred[v] = u;
            }
        }
    }

    // Kiểm tra xem có đường đi từ s đến e không
    if (dist[e] == INF) {
        totalDirty = INF;
        return;
    }

    totalDirty = dist[e]; // Tổng mức độ bẩn nhỏ nhất

    // Khôi phục đường đi từ e về s
    path.clear();
    for (int v = e; v != -1; v = pred[v]) {
        path.push_back(v);
    }
    reverseVector(path); // Đảo ngược để được đường đi từ s đến e
}

// Hàm Dijkstra tìm đường đi ngắn nhất từ s đến e
void dijkstra(int n, int s, int e, const vector<vector<pair<int, int>>>& adj, long long& totalDirty, vector<int>& path) {
    vector<long long> dist(n + 1, INF); // Khoảng cách từ s đến các đỉnh
    vector<int> pred(n + 1, -1); // Lưu đỉnh trước đó để khôi phục đường đi
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue; // Bỏ qua nếu đã tìm được đường ngắn hơn

        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pred[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    // Kiểm tra xem có đường đi từ s đến e không
    if (dist[e] == INF) {
        totalDirty = INF;
        return;
    }

    totalDirty = dist[e]; // Tổng mức độ bẩn nhỏ nhất

    // Khôi phục đường đi từ e về s
    path.clear();
    for (int v = e; v != -1; v = pred[v]) {
        path.push_back(v);
    }
    reverseVector(path); // Đảo ngược để được đường đi từ s đến e
}

// Hàm Floyd-Warshall tìm ma trận khoảng cách ngắn nhất
void floydWarshall(int n, vector<vector<long long>>& dist, const vector<Edge>& edges) {
    // Khởi tạo ma trận khoảng cách
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == j) dist[i][j] = 0;
            else dist[i][j] = INF;
        }
    }

    // Cập nhật ma trận từ danh sách cạnh
    for (const auto& edge : edges) {
        dist[edge.u][edge.v] = min(dist[edge.u][edge.v], (long long)edge.d);
    }

    // Floyd-Warshall
    for (int k = 1; k <= n; ++k) {
        cout << "K = " << k << " : ";
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    cout << "(" << i << ", " << j << ", "<< dist[i][j] << "); ";
                }
            }
        }
        cout << endl;
    }
}

int main() {
    // Đọc đầu vào từ file dirty.txt
    ifstream in("dirty.txt");
    int n, m, s, e;
    in >> n >> m >> s >> e;
    vector<Edge> edges(m);
    vector<vector<pair<int, int>>> adj(n + 1); // Danh sách kề cho Dijkstra
    bool hasNegativeWeight = false; // Kiểm tra trọng số âm
    for (int i = 0; i < m; ++i) {
        in >> edges[i].u >> edges[i].v >> edges[i].d;
        adj[edges[i].u].push_back({edges[i].v, edges[i].d});
        if (edges[i].d < 0) hasNegativeWeight = true; // Phát hiện trọng số âm
    }
    in.close();

    // Nhiệm vụ a: Tìm đường đi ngắn nhất từ s đến e
    long long totalDirty;
    vector<int> path;
    if (hasNegativeWeight) {
        bellmanFord(n, s, e, edges, totalDirty, path); // Dùng Bellman-Ford nếu có trọng số âm
    } else {
        dijkstra(n, s, e, adj, totalDirty, path); // Dùng Dijkstra nếu tất cả trọng số dương
    }

    // Nhiệm vụ b: Tìm ma trận khoảng cách ngắn nhất
    vector<vector<long long>>
 dist(n + 1, vector<long long>(n + 1, INF));
    floydWarshall(n, dist, edges);

    // Ghi kết quả ra file dirty.out
    ofstream out("dirty.out");
    if (totalDirty == INF) {
        out << "INF\n";
    } else {
        out << totalDirty << "\n";
        for (size_t i = 0; i < path.size(); ++i) {
            out << path[i];
            if (i < path.size() - 1) out << " ";
        }
        out << "\n";
    }

    // In ma trận khoảng cách
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (dist[i][j] == INF) out << "INF";
            else out << dist[i][j];
            if (j < n) out << " ";
        }
        out << "\n";
    }
    out.close();

    return 0;
}