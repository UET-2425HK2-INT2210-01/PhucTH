/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Edge {
    int u, v, weight;
};

void prim(int n, vector<vector<pair<int, int>>>& adj, vector<Edge>& mst, long long& totalCost) {
    vector<bool> visited(n + 1, false);
    vector<int> minWeight(n + 1, 1e9); // Trọng số nhỏ nhất đến mỗi đỉnh
    vector<int> parent(n + 1, -1); // Đỉnh cha trong MST
    
    totalCost = 0;
    mst.clear();
    
    // Bắt đầu từ đỉnh 1
    minWeight[1] = 0;
    
    for (int i = 0; i < n; i++) {
        // Tìm đỉnh chưa thăm có minWeight nhỏ nhất
        int u = -1;
        int minW = 1e9;
        for (int v = 1; v <= n; v++) {
            if (!visited[v] && minWeight[v] < minW) {
                minW = minWeight[v];
                u = v;
            }
        }
        
        if (u == -1) break; // Không còn đỉnh nào để chọn
        
        // Thêm cạnh vào MST
        visited[u] = true;
        if (parent[u] != -1) {
            mst.push_back({parent[u], u, minWeight[u]});
            totalCost += minWeight[u];
        }
        
        // Cập nhật minWeight và parent cho các đỉnh kề
        for (size_t j = 0; j < adj[u].size(); j++) {
            int v = adj[u][j].first;  // Truy cập thủ công
            int w = adj[u][j].second; // Truy cập thủ công
            if (!visited[v] && w < minWeight[v]) {
                minWeight[v] = w;
                parent[v] = u;
            }
        }
    }
}

int main() {
    // Đọc input từ file
    ifstream inp("connection.txt");
    int n, m;
    inp >> n >> m;
    
    // Danh sách kề
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        inp >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // Đồ thị vô hướng
    }
    inp.close();
    
    // Tìm MST
    vector<Edge> mst;
    long long totalCost;
    prim(n, adj, mst, totalCost);
    
    // Kiểm tra liên thông
    if (mst.size() != n - 1) {
        ofstream out("connection.out");
        out << "No MST exists\n";
        out.close();
        return 0;
    }
    
    // Ghi output
    ofstream out("connection.out");
    out << totalCost << '\n';
    for (const Edge& e : mst) {
        out << e.u << ' ' << e.v << ' ' << e.weight << '\n';
    }
    out.close();
    
    return 0;
}