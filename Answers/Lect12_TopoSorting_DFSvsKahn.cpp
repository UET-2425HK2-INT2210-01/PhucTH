/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

// hàm in ra danh sách kề
void printAdj(vector<vector<int>> adj_list){
    cout << "Adjacency List:" << endl;
    
    for (int i=1; i<adj_list.size(); i++) {
        cout << i << " : ";
        for (int j: adj_list[i]){
            cout << j << ", ";
        }
        cout << endl;
    }
    cout << endl;
}

void dfs(vector<vector<int>> &adjList, vector<bool> &visitedList, int v, stack<int> &topoStack){
    visitedList[v] = true;
    
    for (int v_next: adjList[v]) {
        if (visitedList[v_next] == false) {
            dfs(adjList, visitedList, v_next, topoStack);
        }
    }
    
    topoStack.push(v);
}

void topoSortingByDFS (vector<vector<int>> &adjList) {

    vector<bool> visitedList(adjList.size(), false);
    stack<int> topoStack;
        
    for (int i=1; i<adjList.size(); ++i) {
        if (visitedList[i] == false)
            dfs(adjList, visitedList, i, topoStack);
    }

    while (!topoStack.empty()) {
        cout << topoStack.top() << " ";
        topoStack.pop();
    }
    cout << endl;
}

void topoSortingByKahn (vector<vector<int>> &adjList, vector<int> &inDegreeList) {
    vector<int> result;
    queue<int> que;
    
    for (int i=1; i<adjList.size(); ++i) {
        if (inDegreeList[i] == 0) {
            que.push(i);
        }
    }
    
    // kahn
    while(!que.empty()) {
        int v = que.front();
        que.pop();
        result.push_back(v);
        
        for (int v_next: adjList[v]) {
            inDegreeList[v_next]--;
            if (inDegreeList[v_next] == 0) {
                que.push(v_next);
            }
        }
    }
    
    for (int i: result) {
        cout << i << " ";
    }
    cout << endl;
}

void topoSortingByKahnPQ(vector<vector<int>> &adjList, vector<int> inDegreeList) {
    int n = adjList.size() - 1;
    vector<int> result;
    priority_queue<int, vector<int>, greater<int>> pq;

    // Sort adjList[u] để ưu tiên các đỉnh nhỏ hơn
    for (int i = 1; i <= n; ++i) {
        sort(adjList[i].begin(), adjList[i].end());
    }

    // Đưa các đỉnh có in-degree = 0 vào hàng đợi
    for (int i = 1; i <= n; ++i) {
        if (inDegreeList[i] == 0) {
            pq.push(i);
        }
    }

    // Thuật toán Kahn
    while (!pq.empty()) {
        int u = pq.top(); pq.pop();
        result.push_back(u);

        for (int v : adjList[u]) {
            inDegreeList[v]--;
            if (inDegreeList[v] == 0) {
                pq.push(v);
            }
        }
    }

    // Kiểm tra chu trình
    if ((int)result.size() != n) {
        cout << "Cycle detected! Topological sort not possible.\n";
        return;
    }

    // In kết quả
    cout << "Topological Sort (Kahn + priority_queue): ";
    for (int i : result) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    
    ifstream FileIn("jobs.txt");
    
    int n, m;
    FileIn >> n >> m;
    
    vector<vector<int>> adjList(n+1);   // Danh sách kề
    vector<int> inDegreeList(n+1, 0); // Danh sách bậc vào của đỉnh
    
    // đọc đồ thị
    for (int i=0; i<m; ++i) {
        int x, y;
        FileIn >> x >> y;
        adjList[x].push_back(y);
        inDegreeList[y]++;
    }
    
    printAdj(adjList);
    
    topoSortingByDFS(adjList);
    topoSortingByKahn(adjList, inDegreeList);
    topoSortingByKahnPQ(adjList, inDegreeList);

    return 0;
}