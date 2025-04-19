/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath> // Cần thư viện này để sử dụng INFINITY

using namespace std;


void printOptions() {
    cout << endl;
    cout << "------------------------" << endl;
    cout << "0. Quit!" << endl;
    cout << "1. Assignment 1" << endl;
    cout << "2. Assignment 2" << endl;
    cout << "3. Assignment 3" << endl;
    cout << "4. Assignment 4" << endl;
    cout << "5. Assignment 5" << endl;
    cout << endl;
}

// *******************************************************************************
// ------ [ Assignment 1 ] ------

vector<int> read_numbers(string path) {
    /*
        Hàm đọc các số nguyên từ file văn bản tại đường dẫn `path` và lưu vào một vector.
        
        Input:
            - path: đường dẫn đến file văn bản (ví dụ: "numbers.txt")
    
        Trả về:
            - Một vector<int> chứa các số nguyên đọc được từ file.
            - Nếu không mở được file, trả về vector rỗng và in ra thông báo lỗi.
    */
    
    ifstream file(path);  // Mở file
    if (!file) {
        cerr << "Your file is not found!" << endl;
        return {};  // Trả về vector rỗng nếu file không tồn tại
    }

    vector<int> numbers;
    int num;

    // Đọc từng số nguyên từ file và thêm vào vector
    while (file >> num) {
        numbers.push_back(num);
    }

    file.close();  // Đóng file
    return numbers;
}

void bubbleSort(vector<int> &numbers) {
    /*
        Hàm bubbleSort có nhiệm vụ sắp xếp một vector các số nguyên theo thứ tự tăng dần bằng thuật toán sắp xếp nổi bọt (Bubble Sort) có cải tiến.
            - Nếu vector rỗng, in thông báo và thoát khỏi hàm.
            - Dùng 2 vòng lặp lồng nhau để thực hiện các bước so sánh và hoán đổi.
            - Sử dụng biến cờ `flag_swapped` để kiểm tra xem có sự thay đổi nào trong
              một vòng lặp không — nếu không có thì dừng sớm vì mảng đã được sắp xếp.
    
        Input:
            - numbers: vector<int> cần được sắp xếp (tham chiếu & để thay đổi trực tiếp)
        
        Output:
            - mảng đã được sắp xếp
    
        Độ phức tạp thời gian:
            - Trung bình và xấu nhất: O(n²)
            - Trường hợp tốt nhất (đã sắp xếp): O(n)
    */
    
    if (numbers.empty()) {
        cout << "Your arr is empty!" << endl;
        return;
    }

    int num_size = numbers.size();

    for (int i = 0; i < num_size - 1; i++) {
        bool flag_swapped = false; // Dùng để kiểm tra xem có cần tiếp tục sắp xếp không

        for (int j = 0; j < num_size - i - 1; j++) {
            if (numbers[j] > numbers[j + 1]) {
                // Hoán đổi 2 phần tử liền kề nếu sai thứ tự
                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;

                flag_swapped = true; // Đánh dấu là đã có hoán đổi
            }
        }

        // Nếu không có hoán đổi nào thì mảng đã được sắp xếp → thoát sớm
        if (!flag_swapped) break;
    }
}

// *******************************************************************************
// ------ [ Assignment 2 ] ------

vector<vector<int>> read_matrix(string path){
    ifstream file(path);  // Mở file
    if (!file) {
        cerr << "Your file is not found!" << endl;
        return {};  // Trả về vector rỗng nếu file không tồn tại
    }
    
    int rows, cols;
    file >> rows >> cols;
    
    vector<vector<int>> matrix(rows, vector<int>(cols)); // khởi tạo ma trận vector rỗng
    
    for (int r=0; r<rows; r++){
        for (int c=0; c<cols; c++){
            file >> matrix[r][c];
        }
    }
    
    file.close();
    return matrix;
}

void print_matrix(vector<vector<int>> &matrix) {
    for (vector<int> row: matrix) {
        for (int val: row) {
            cout << val << "\t";
        }
        cout << endl;
    }
}

vector<int> getMaxSubMatrix_BruteForce (vector<vector<int>> &matrix) {
    
    if (matrix.empty()) {
        cout << "Your matrix is empty!" << endl;
        return {};
    }
    
    int num_rows= matrix.size();
    int num_cols= matrix[0].size();
    cout << "RxC: " << num_rows << "x" << num_cols << endl;
    
    int sumMax  = -999999;
    vector<int> output = {0, 0, 0, 0, sumMax};
    
    for (int r1=0; r1<num_rows; r1++){ // r1 chạy từ 0 đến num_rows
        for (int c1=0; c1<num_cols; c1++){ // c1 chạy từ 0 đến num_cols
            for (int r2=r1; r2<num_rows; r2++){ // r2 chạy từ r1 đến num_rows
                for (int c2=c1; c2<num_cols; c2++){ // c2 chạy từ c1 đến num_cols
                
                    int sum=0; // khởi tạo sum tạm;
                    
                    // tính sum tạm
                    for (int r=r1; r<=r2; r++){ // r chạy từ r1 đến r2
                        for (int c=c1; c<=c2; c++){ // c chạy từ c1 đến c2
                            sum += matrix[r][c];
                        }
                    }
                    
                    // kiểm tra sum tạm và cập nhật output
                    if (sum > sumMax){
                        sumMax      = sum; // cập nhật sumMax
                        
                        // cập nhật output
                        output[0]   = r1 + 1;
                        output[1]   = c1 + 1;
                        output[2]   = r2 + 1;
                        output[3]   = c2 + 1;
                        output[4]   = sumMax;
                    }
                }
            }
        }
    }
    
    return output;
    
}

vector<int> getMaxSubMatrix_PrefixSum(vector<vector<int>> &matrix) {
    if (matrix.empty()) {
        cout << "Your matrix is empty!" << endl;
        return {};
    }

    int num_rows = matrix.size();
    int num_cols = matrix[0].size();

    // Tạo mảng prefix sum
    vector<vector<int>> prefixSum(num_rows, vector<int>(num_cols, 0));

    for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < num_cols; ++j) {
            prefixSum[i][j] = matrix[i][j];
            if (i > 0) {
                prefixSum[i][j] += prefixSum[i - 1][j];
            }
            if (j > 0) {
                prefixSum[i][j] += prefixSum[i][j - 1];
            }
            if (i > 0 && j > 0) {
                prefixSum[i][j] -= prefixSum[i - 1][j - 1];
            }
        }
    }
    
    cout << "---------" << endl;
    print_matrix(prefixSum);

    int sumMax  = -999999;
    vector<int> output = {0, 0, 0, 0, sumMax};

    for (int r1 = 0; r1 < num_rows; ++r1) {
        for (int c1 = 0; c1 < num_cols; ++c1) {
            for (int r2 = r1; r2 < num_rows; ++r2) {
                for (int c2 = c1; c2 < num_cols; ++c2) {
                    int sum = prefixSum[r2][c2];
                    if (r1 > 0) {
                        sum -= prefixSum[r1 - 1][c2];
                    }
                    if (c1 > 0) {
                        sum -= prefixSum[r2][c1 - 1];
                    }
                    if (r1 > 0 && c1 > 0) {
                        sum += prefixSum[r1 - 1][c1 - 1];
                    }

                    if (sum > sumMax) {
                        sumMax    = sum;
                        output[0] = r1 + 1;
                        output[1] = c1 + 1;
                        output[2] = r2 + 1;
                        output[3] = c2 + 1;
                        output[4] = sumMax;
                    }
                }
            }
        }
    }

    return output;
}
// *******************************************************************************
// ------ [ Assignment 3 ] ------
int getGCD (int x, int y) {

    /*
        Công thức đệ quy (thuật toán Euclid):
        Cho hai số nguyên dương x và y, trong đó x ≥ y:
        
        Công thức: GCD(x, y) = GCD(y, x%y);
        Đk dừng: GCD(x,0) = x
        */    

    // điều kiện dừng
    if (y==0) {
        return x;
    }
    // gọi đệ quy
    return getGCD(y, x%y);
}

// *******************************************************************************
// ------ [ Assignment 4 ] ------

void generateBinary (int n, string my_s="") {
    if (my_s.length() == n) {
        cout << my_s << endl;
        return;
    }
    
    generateBinary (n, my_s + "0");
    generateBinary (n, my_s + "1");
}

// *******************************************************************************
// ------ [ Assignment 5 ] ------

bool used[10];  // Đánh dấu số đã chọn
int perm[10];   // Lưu hoán vị hiện tại

void generatePermutations(int n, int level = 0) {
    if (level == n) {  // Khi đã chọn đủ n số
        for (int i = 0; i < n; i++) cout << perm[i];
        cout << endl;
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {  // Nếu số i chưa được chọn
            used[i] = true;   // Đánh dấu số i đã chọn
            perm[level] = i;  // Lưu số vào vị trí hiện tại
            generatePermutations(n, level + 1); // Gọi đệ quy
            used[i] = false;  // Quay lui: Bỏ chọn số i
        }
    }
}

// *******************************************************************************
int main()
{
    
    int my_option=-1;
    
    while(my_option){
        printOptions();
        cout << "Enter your option: ";
        cin >> my_option; cin.ignore();
        
        switch(my_option){
            case 0: {
                cout << "Bye!" << endl;
                return 0;
            }
            
            case 1: {
                cout << endl << "------ [ Assignment 1 ] ------" << endl;
                
                // đọc file
                vector<int> numbers = read_numbers("numbers.txt");

                for (int n: numbers) cout << n << " "; // in sau đọc
                cout << endl;
                
                // sắp xếp
                bubbleSort(numbers);
                
                for (int n: numbers) cout << n << " "; // in sau sắp xếp
                cout << endl;
                
                break;
            }
            
            case 2: {
                cout << endl << "------ [ Assignment 2 ] ------" << endl;
                
                // đọc file
                vector<vector<int>> matrix = read_matrix("matrix.txt");
                // in sau đọc
                print_matrix(matrix);
                
                // tìm ma trận có tổng lớn nhất
                // vector<int> maxSubMaxtrix = getMaxSubMatrix_BruteForce(matrix);
                vector<int> maxSubMaxtrix = getMaxSubMatrix_PrefixSum(matrix);
                
                // in kết quả khi tìm được
                for (int i: maxSubMaxtrix) cout << i << " ";
                cout << endl;
                
                break;
            }
            
            case 3: {
                cout << endl << "------ [ Assignment 3 ] ------" << endl;
                cout << getGCD(10, 50) << endl;
                break;
            }
            
            case 4: {
                cout << endl << "------ [ Assignment 4 ] ------" << endl;
                generateBinary(5);
                break;
                
            }
            
            case 5: {
                cout << endl << "------ [ Assignment 5 ] ------" << endl;
                generatePermutations(5);
                break;
                
            }
            
            default: {
                cout << "Your option is invalid, try again!" << endl;
                break;
            }
        }
    }
    
    return 0;
}