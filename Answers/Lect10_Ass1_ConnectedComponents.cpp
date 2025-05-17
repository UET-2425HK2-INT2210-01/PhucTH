/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

void printAdj (vector<vector<int>> adj_matrix) {
    cout << endl << "Your adjacency matrix:" << endl;
    
    for (int i=1; i<adj_matrix.size(); ++i){
        cout << i << ": ";
        for (int j: adj_matrix[i]){
            cout << j << ", ";
        }
        cout << endl;
    }
}

// ở đây phải truyền vector visited theo kiểu tham chiếu để lưu các thay đổi vào vector gốc
void dfs(const vector<vector<int>>& adj_matrix, int v, vector<bool>& visited) { // v = vertice
    visited [v] = true;
    
    for (int neighbor: adj_matrix[v]){
        if (neighbor<adj_matrix.size() && visited[neighbor]==false) {
            dfs(adj_matrix, neighbor, visited);
        }
    }
}

void getConnectedComponents(const vector<vector<int>>& adj_matrix) {
    vector<bool> visited(adj_matrix.size(), false);
    
    int components = 0;
    for (int i = 1; i < adj_matrix.size(); ++i) {
        if (!visited[i]) {
            dfs(adj_matrix, i, visited);
            components++;
        }
    }
    
    cout << "The components: " << components << endl;
}

int main() {
    int n, m;
    cin >> n >> m;
    
    if (n <= 0 || m < 0) {
        cout << "Invalid input!" << endl;
        return 1;
    }
    
    // Khởi tạo ma trận kề với n+1 phần tử (trong bài 1 đỉnh bắt đầu từ 1)
    vector<vector<int>> adj_matrix(n+1);
    
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        adj_matrix[x].push_back(y);
        adj_matrix[y].push_back(x); // vì là đồ thị vô hướng
    }
    
    printAdj(adj_matrix);
    getConnectedComponents(adj_matrix);

    return 0;
}
