/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
Ass8_Exp2_BackscattinC#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
using namespace std;

bool checkSubsetSum (int arr[], int n, int target, int sumCurr=0, int startID=0) {
    if (sumCurr==target) return true;
    
    if (sumCurr>target || startID>=n) return false;
    
    return  checkSubsetSum(arr, n, target, sumCurr+arr[startID], startID+1) ||
            checkSubsetSum(arr, n, target, sumCurr, startID+1);
    
}

bool checkSubsetSumDP (int arr[], int n, int target) {
    /**
        Kiểm tra xem có tồn tại tập con của mảng có tổng bằng target hay không
        Sử dụng phương pháp Quy hoạch động (Dynamic Programming)
    **/    
    
    // Khởi tạo bảng DP với kích thước (n+1) x (target+1)
    bool arr_dp[n+1][target+1];
    
    for (int i=0; i<=n; i++) arr_dp[i][0] = true; // Tổng 0 luôn đạt được bằng tập rỗng
    for (int j=0; j<=target; j++) arr_dp[0][j] = false; // Với tập rỗng, không thể tạo tổng > 0
    
    // Xây dựng bảng DP
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=target; j++) {
            // Nếu phần tử hiện tại lớn hơn tổng j
            // Không thể chọn phần tử này, kết quả giống như không có nó
            if (arr[i-1] > j) arr_dp[i][j] = arr_dp[i-1][j];
            
            // Có thể chọn hoặc không chọn phần tử này
            // Kết quả là OR của 2 trường hợp
            else arr_dp[i][j] = arr_dp[i-1][j] || arr_dp[i-1][j - arr[i-1]];
        }
    }
    
    // Kết quả cuối cùng nằm ở ô arr_dp[n][target]
    return arr_dp[n][target];
    
    /* Truy vết phần tử
    while (i > 0 && j > 0) {
        if (arr_dp[i][j] && !arr_dp[i-1][j]) {
            // Phần tử arr[i-1] phải được chọn
            subset.push_back(arr[i-1]);
            j -= arr[i-1];
        }
        i--;
    }
    */
}

int main()
{
    int n=6;
    int target=10;
    int my_arr[n] = {2, 5, 6, 2, 1, 7};
    
    for (int i=0; i<n; i++){
        cout << my_arr[i] << ", ";
    }
    
    bool my_result = checkSubsetSumDP(my_arr, n, target);
    
    cout << (my_result ? "YES" : "NO");

    return 0;
}