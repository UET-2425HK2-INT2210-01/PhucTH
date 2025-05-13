/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
using namespace std;

// Hàm tính giá trị lớn nhất của bài toán Knapsack 0/1
int knapsack(int n, int X, int w[], int v[]) {
    // Bảng dp[i][j]: giá trị lớn nhất với i vật phẩm đầu tiên và tổng trọng lượng <= j
    int dp[n + 1][X + 1];
    
    // Khởi tạo: với i=0, không có vật phẩm nào, giá trị = 0
    for (int j = 0; j <= X; j++) {
        dp[0][j] = 0;
    }
    
    // Quy hoạch động
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= X; j++) {
            if (j < w[i-1]) {
                dp[i][j] = dp[i-1][j]; // Không chọn được vật phẩm i
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i-1][j - w[i-1]] + v[i-1]); // Chọn tối ưu
            }
        }
    }
    
    // truy vết
    
    /*
    cout << "Cac vat pham duoc chon (chi so bat dau tu 0): ";
    int i = n, j = X;
    while (i > 0) {
        if (j >= w[i-1] && dp[i][j] == dp[i-1][j - w[i-1]] + v[i-1]) {
            cout << (i-1) << " "; // Vật phẩm i-1 được chọn
            j -= w[i-1]; // Giảm trọng lượng
        }
        i--; // Chuyển sang vật phẩm trước
    }
    cout << endl;
    */
    
    return dp[n][X]; // Trả về giá trị lớn nhất
}

int main() {
    // Khai báo sẵn test case
    int n = 5, X = 10;
    int weights[] = {1, 5, 3, 9, 8};
    int values[] = {2, 4, 1, 6, 10};
    
    cout << knapsack(n, X, weights, values) << endl;
    
    return 0;
}