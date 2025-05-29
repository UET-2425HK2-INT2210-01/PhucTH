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

// Hàm hoán đổi hai cạnh
void swap(Edge& a, Edge& b) {
    Edge temp = a;
    a = b;
    b = temp;
}

// Hàm quick sort để sắp xếp cạnh theo trọng số
int partition(vector<Edge>& arr, int low, int high) {
    int pivot = arr[high].weight;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].weight <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<Edge>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Disjoint Set Union
class DSU {
    vector<int> parent;
public:
    DSU(int n) : parent(n + 1) {
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]); // Path compression
        }
        return parent[u];
    }
    
    bool unite(int u, int v) {
        int pu = find(u), pv = find(v);
        if (pu == pv) return false;
        parent[pu] = pv; // Hợp nhất ngẫu nhiên
        return true;
    }
};

void kruskal(int n, vector<Edge>& edges, vector<Edge>& mst, long long& totalCost) {
    // Sắp xếp cạnh theo trọng số
    if (!edges.empty()) {
        quickSort(edges, 0, edges.size() - 1);
    }
    
    DSU dsu(n);
    totalCost = 0;
    mst.clear();
    
    for (const Edge& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            mst.push_back(e);
            totalCost += e.weight;
        }
    }
}

int main() {
    // Đọc input từ file
    ifstream inp("connection.txt");
    int n, m;
    inp >> n >> m;
    
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        inp >> edges[i].u >> edges[i].v >> edges[i].weight;
    }
    inp.close();
    
    // Tìm MST
    vector<Edge> mst;
    long long totalCost;
    kruskal(n, edges, mst, totalCost);
    
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