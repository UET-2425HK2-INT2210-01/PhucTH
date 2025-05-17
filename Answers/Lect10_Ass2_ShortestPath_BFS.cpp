/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// hàm in ra danh sách kề
void printAdj(vector<vector<int>> adj_list){
    cout << "Your adjacency matrix:" << endl;
    
    for (int i=1; i<adj_list.size(); i++) {
        cout << i << " : ";
        for (int j: adj_list[i]){
            cout << j << ", ";
        }
        cout << endl;
    }
    cout << endl;
}

void dfs(const vector<vector<int>>& adj_list, vector<bool>& visited, int v=1){
    /*
        Hàm đệ quy thực hiện chức năng duyệt đồ thị theo chiều sâu (Depth-First Search)
        
        Đầu vào
            - adj_list (vector<vector<int>>)    : danh sách kề lưu chứa đồ thị
            - visited (vector<bool>)            : danh sách các đỉnh để duyệt đồ thị
                                                  do đây là hàm đệ quy nên mảng visited cần được tạo bên ngoài
            - v (int)                           : đỉnh bắt đầu duyệt đồ thị (mặc định = 1)
            
        Đầu ra:
            - In ra danh sách các đỉnh của đồ thị được duyệt theo trình tự dfs
    */
    
    // gán đỉnh đang được duyệt bằng true
    visited[v] = true;
    cout << v << ", "; // ịn ra đỉnh
    
    // gọi vòng for đi thăm các đỉnh lân cận của v
    for (int v_next: adj_list[v]) {
        // nếu đỉnh lân cận (v_next) chưa được thăm
        if (visited[v_next] == false) {
            dfs(adj_list, visited, v_next); // thì gọi đệ quy để duyệt tiếp v_next
        }
    }
}

void bfs (const vector<vector<int>>& adj_list, int start=1) {
    /*
        Hàm thực hiện chức năng duyệt đồ thị theo chiều rộng (Breadth-First Search)
        
        Đầu vào:
            - adj_list (vector<vector<int>>)    : danh sách kề lưu chứa đồ thị
            - start (int)                       : đỉnh bắt đầu duyệt đồ thị (mặc định = 1)
            
        Đầu ra:
            - In ra danh sách các đỉnh của đồ thị được duyệt theo trình tự bfs
    */
    
    // khởi tạo mảng visited để đánh dấu các đỉnh đã duyệt (false là chưa được duyệt)
    vector<bool> visited(adj_list.size(), false);
    queue<int> q; // hàng đợi hỗ trợ duyệt đồ thị
    
    // bắt đầu duyệt từ start
    q.push(start);
    visited[start] = true;
    
    // bắt đầu vòng while để duyệt đồ thị cho tới khi hàng đợi empty
    cout << "bfs: ";
    while (!q.empty()) {
        // in ra đỉnh đang được duyệt - bắt đầu với đỉnh start
        int v = q.front(); // lấy đỉnh đầu của queue
        q.pop(); // duyệt xong rồi thì bỏ đỉnh này khỏi hàng đợi
        cout << v << ", ";
        
        // gọi vòng for để duyệt đỉnh lân cận của v là v_next
        for (int v_next: adj_list[v]) {
            // nếu v_next chưa được duyệt thì 
            if (visited[v_next] == false) {
                visited[v_next] = true; // đánh dấu v_next
                q.push(v_next); // thêm v_next vào hàng đợi để in ra ở trên
            }
        }
    }
    cout << endl << endl;
}

vector<int> getDistByBFS (const vector<vector<int>>& adj_list, int start=1) {
    /*
        Hàm tính khoảng cách từ đỉnh start tới các cạnh còn lại dựa trên BFS
        
        Đầu vào:
            - adj_list (vector<vector<int>>)    : danh sách kề lưu chứa đồ thị
            - start (int)                       : đỉnh bắt đầu duyệt đồ thị (mặc định = 1)
    */
    // khởi tạo mảng tính khoảng cách, -1 có nghĩa là 2 đỉnh k có cạnh chung
    vector<int> distances(adj_list.size(), -1);
    // khởi tạo mảng visited để đánh dấu các đỉnh đã duyệt (false là chưa được duyệt)
    vector<bool> visited(adj_list.size(), false);
    queue<int> q; // hàng đợi hỗ trợ duyệt đồ thị
    
    // bắt đầu duyệt từ start
    q.push(start);
    visited[start] = true;
    distances[start] = 0; // khoảng cách start đến chính nó bằng 0
    
    while (!q.empty()) {
        // in ra đỉnh đang được duyệt - bắt đầu với đỉnh start
        int v = q.front(); // lấy đỉnh đầu của queue
        q.pop(); // duyệt xong rồi thì bỏ đỉnh này khỏi hàng đợi
        
        // gọi vòng for để duyệt đỉnh lân cận của v là v_next
        for (int v_next: adj_list[v]){
            if (visited[v_next] == false){
                visited[v_next] = true; // đánh dấu v_next
                q.push(v_next); // thêm v_next vào hàng đợi để duyệt tiếp
                distances[v_next] = distances[v] + 1; // khoảng cách từ start đến v_next tăng 1
            }
        }
    }
    
    return distances;
    
    // // In ra danh sách distances
    // cout << "BFS distances from " << start << ": " << endl;
    // for (int i=1; i<adj_list.size(); ++i) {
    //     cout << i << " : " << distances[i] << endl;
    // }
    // cout << endl;
}

void getDistXtoY (const vector<vector<int>>& adj_list, int X, int Y){
    /*
        Hàm thực hiện chức năng tìm đường đi ngắn nhất từ X đến Y dựa trên trình tự BFS
    */
    // Gọi hàm tính distances từ X đến các đỉnh còn lại
    vector<int> distances = getDistByBFS(adj_list, X);
    
    // In ra danh sách distances
    cout << "BFS distances from " << X << ": " << endl;
    for (int i=1; i<adj_list.size(); ++i) {
        cout << i << " : " << distances[i] << endl;
    }

    cout << "Shortest path from " << X << " to " << Y << ": " << distances[Y] << endl;
    cout << endl;    
}

int main()
{
    int n, m, X, Y;
    cin >> n >> m >> X >> Y;
    
    vector<vector<int>> adj_list(n+1);
    
    for (int i=0; i<m; ++i) {
        int x, y;
        cin >> x >> y;
        
        adj_list[x].push_back(y);
        adj_list[y].push_back(x);
    }
    
    cout << endl;
    printAdj(adj_list);
    
    cout << "dfs: ";
    vector<bool> visited(adj_list.size(), false);
    dfs(adj_list, visited);
    cout << endl;
    
    bfs(adj_list);
    
    
    getDistXtoY(adj_list, X, Y);
    
    return 0;
}