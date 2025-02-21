/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <string>
#include <math.h> // cho round
#include <vector> // ass5

using namespace std;

// *******************************************************************************
// Ass1
void reverse_sentence(string &sent){
    for (int i=sent.length()-1; i>=0; i--){
        cout << sent[i];
    }
};

// *******************************************************************************
// Ass2
class Point{
public:
    double y;
    double x;

    // khai báo các hàm trong lớp Point
    Point(double x_=0, double y_=0){
        x=x_;
        y=y_;
    }
    
    // Hien thi diem
    void print() {
        cout << "[" << x << ", " << y << "]" << endl;
    }
    
    // Import Point
    void import() {
        cin >> x; cin >> y;
    }
};

class Line{
    /*
        Phuong trinh duong thang qua 2 diem A(x1, x2) va B(y1, y2) 
        co dang y = ax + b
        a = y1 - y2
        b = x2 - x1
        
    */

public:
    double a;
    double b;
    
    // Khai bao ham

    void print(){
        cout << "y = " << a << "x + " << b << endl;
    }    

    Line(Point &A, Point &B) {
        if (A.x == B.x) { // Đường thẳng thẳng đứng
            cout << "Vertical line: x = " << A.x << endl;
            a = INFINITY; // Độ dốc vô hạn
            b = A.x;      // Chỉ cần lưu giá trị x
            return;
        }
        // Tính hệ số a và b cho các trường hợp khác
        a = (B.y - A.y) / (B.x - A.x);
        b = A.y - a * A.x;
    
        a = round(a * 100) / 100;
        b = round(b * 100) / 100;
    }
};

void findIntersectionPoint(Line &AB, Line &CD) {
    if (AB.a == CD.a) { // Kiểm tra nếu hai đường thẳng song song hoặc trùng nhau
        if (AB.b == CD.b) {
            cout << "MANY" << endl; // Trùng nhau
        } else {
            cout << "NO" << endl; // Song song
        }
        return;
    }
    // Tính điểm giao nhau
    double x = (CD.b - AB.b) / (AB.a - CD.a);
    double y = AB.a * x + AB.b; // Hoặc y = CD.a * x + CD.b;

    x = round(x * 100) / 100;
    y = round(y * 100) / 100;
    
    cout << x << " " << y << endl;
}

// *******************************************************************************
// Ass3
// Hàm tìm ước chung lớn nhất (GCD) sử dụng thuật toán Euclid
int gcd(int a, int b) {
    /*
        GCD của a và b được tính bằng cách liên tục thay a bởi b và b bởi a%b (phần dư)
        Quá trình này kết thúc khi b=0, khi đó gcd=a
    */
    
    while (b != 0) {
        int remain = a % b; // Tính số dư
        a = b;                 // Đổi giá trị a
        b = remain;         // Đổi giá trị b
    }
    return a;
}

// *******************************************************************************
// Ass4 - 
void bubble_sort(int arr[], int n){
    for (int i=0; i<n-1; i++){
        for (int j=0; j<n-i-1; j++){
            if (arr[j] > arr[j+1]){
                // Đổi chỗ nếu phần tử trước lớn hơn phần tử sau
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// *******************************************************************************
// Ass5
void getSumGS (vector<int> &arr){
    /*
        calculate the sum of the greatest number and the smallest number
    */
    
    int n = arr.size();
    int tempG = arr[0];
    int tempS = arr[0];
    
    for (int i=0; i<n; i++){
        
        if (arr[i] > tempG){
            tempG = arr[i];
        }
        
        if (arr[i] < tempS){
            tempS = arr[i];
        }
    }
    
    cout << tempS + tempG << endl;

}

void coutAssOptions(){
    cout << endl;
    cout << "------------------------------------------------" << endl;
    cout << "1. Reverse sentence." << endl;
    cout << "2. Determine the intersection of the lines." << endl;
    cout << "3. Find greatest common divisor." << endl;
    cout << "4. Ascending Sort." << endl;
    cout << "5. Calculate the sum of the greatest number and the smallest number.";
    cout << "0. Quit!" << endl;
    cout << endl;
}

int main(){
    int my_option=-1;

    while (true){
        
        // Hiển thị menu và nhập lựa chọn
        coutAssOptions();
        cout << "Enter your option: ";
        cin >> my_option;
        cin.ignore();
        
        // Thực hiện các tùy chọn
        switch (my_option){
            
            case 0:{
                cout << endl;
                cout << "Good bye!" << endl;
                return 0;
            }
            
            case 1:{
                cout << endl;
                
                string my_sentence;
                
                cout << "Enter your sentence: ";
                getline(cin, my_sentence);
                
                reverse_sentence(my_sentence);
                break;
            }
            
            case 2:{
                while (true){
                    cout << "------------------------" << endl;
                    Point A, B, C, D;
                    A.import();
                    B.import();
                    C.import();
                    D.import();
                    
                    Line AB (A, B);
                    Line CD (C, D);
                    AB.print();
                    CD.print();
                    
                    findIntersectionPoint(AB, CD);
                }
            }
            
            case 3:{
                while (true){
                    int a, b;
                    cin >> a >> b;
                    
                    cout << gcd(a,b) << endl;
                }
            }
            
            case 4:{
                while (true){
                    int n;
                    cin >> n;
                    
                    int arr[n];
                    // có thể sử dụng vector<int> arr(n); khi đó n trong hàm = arr.size(), #include <vector>
                    
                    for (int i=0; i<n; i++){
                        cin >> arr[i];
                    }
                    
                    bubble_sort(arr, n);
                    
                    for (int i=0; i<n; i++){
                        cout << arr[i] << " ";
                    }
                    
                    cout << endl;
                    cin.ignore();
                }
            }
            
            case 5:{
                while(true){
                        int n;
                        cin >> n;
                        
                        vector<int> arr(n);
                        
                        for (int i=0; i<n; i++){
                            cin >> arr[i];
                        }
                        
                        getSumGS(arr);
                }
                
            }
        
            default:{
                cout << "Invalid option. Please try again!" << endl;
            }
        }
    }
}



