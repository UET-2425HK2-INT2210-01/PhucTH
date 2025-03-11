/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <functional>  // Để sử dụng std::function
#include <chrono>  // Thư viện đo thời gian

#define max_size 1000000 // max_size

using namespace std;
using namespace chrono;  // Sử dụng namespace để rút gọn cú pháp


/*Note:
    Đối với cài đặt Queue và Stack
        - Nếu biết trước kích thước: Mảng tĩnh là tốt nhất vì đơn giản và nhanh.
        - Nếu kích thước thay đổi nhiều: Mảng động để tránh lãng phí bộ nhớ.
        - Nếu cần mở rộng linh hoạt mà không cần truy cập nhanh: Danh sách liên kết đơn.
        - Nếu cần hỗ trợ duyệt ngược và linh hoạt: Danh sách liên kết đôi.

*/

// *******************************************************************************
void printOptions() {
    cout << endl;
    cout << "-------------------------------" << endl;
    cout << "1. The order of Big O notation." << endl;
    cout << "2. Calculate the power of 2." << endl;
    cout << "3. Array Queue." << endl;
    cout << "4. Linked list Queue." << endl;
    cout << "5. Array Stack." << endl;
    cout << "6. Linked list Stak." << endl;
    cout << "0. Quit!" << endl;
    cout << endl;
    
}

// Hàm đo thời gian chạy
double measureTime(function<void(int)> func, int n) {
    auto start = high_resolution_clock::now();  // Bắt đầu đo

    func(n);  // Gọi hàm cần đo

    auto end = high_resolution_clock::now();  // Kết thúc đo

    // Tính thời gian chạy (đơn vị mili giây)
    duration<double, milli> duration = end - start;
    return duration.count();  // Trả về thời gian chạy
}

// *******************************************************************************
/* Ass1
    Biến đổi:
    	4nlog(n)+2n = O(nlogn)
    	2^10 = O(1)
    	2^logn = n^log2 = n = O(n)
    	3n+100logn = O(n)
    	4n = O(n)
    	2^n = O(2^n)
    	n^2+10n = O(n^2)
    	n^3 = O(n^3)
    	nlogn = O(nlogn)
    	
    Sắp xếp:
        STT	Big Onotation   Functions
        1	O(1)	        2^10
        2	O(logn)
        3	O(n)	        2^logn; 3n+100logn; 4n; 
        4	O(nlogn)	    4nlog(n)+2n; nlogn
        5	O(n^2)	        n^2+10n, 
        6	O(n^3)	        n^3
        7	O(2^n)	        2^n
        8	O(n!)
*/


// *******************************************************************************
// Ass2
double powerOfTwo_Iterative (int n){
    /*
        ExponentialFunc
        
        Hàm thực hiện nhiệm vụ tính hàm số mũ cơ số 2 (2^n) dựa trên vòng lặp
        Đầu vào:
            int n: số mũ của hàm
        Đầu ra:
            int my_power: kết quả của hàm mũ
    */
    
    double my_power=1;
    
    if (n==0){
        return my_power;
    }
    
    else if (n>0){
        for (int i=0; i<n; i++){
            my_power *= 2;
        }
        return my_power;
    }
        
    else {
        for (int i=0; i>n; i--){
            my_power /= 2;
        }
        return my_power;
    }
    
}

double powerOfTwo_Recursive(int n) {
    /*
        Hàm thực hiện nhiệm vụ tính hàm số mũ cơ số 2 (2^n) dựa trên đệ quy
        
        Ta có tính chất của hàm số mũ như sau:
            2^n = 1, khi n==0
                = 1 * (2^(n/2))^2, khi n>0 chẵn
                = 2 * (2^((n-1)/2))^2, khi n>0 lẻ
                = (2^(n/2))^2 / 1, khi n<0 chẵn
                = (2^((n-1)/2))^2 / 2, khi n<0 lẻ
                
        Đầu vào:
            int n: số mũ của hàm
        Đầu ra:
            int exp_result: kết quả của hàm mũ
    */
    
    if (n == 0) return 1.0;  // 2^0 = 1

    double half_power = powerOfTwo_Recursive(n / 2);

    if (n > 0) {
        if (n % 2 == 0) {
            return 1 * half_power * half_power;
        } else {
            return 2 * half_power * half_power;
        }
    } else {
        if (n % 2 == 0) {
            return half_power * half_power / 1.0;
        } else {
            return (half_power * half_power) / 2.0;
        }
    }
}

double powerOfTwo_LeftShift (int n){
    /*
        Hàm thực hiện nhiệm vụ tính hàm số mũ cơ số 2 (2^n) dựa trên phép dịch bit (Left Shift - <<)
        
        Phép dịch trái x << k có nghĩa là dịch toàn bộ các bit của số x sang trái k lần,
        mỗi lần dịch tương đương với nhân x với 2^k:
            x << k  = x * 2^k
                
        Đầu vào:
            int n: số mũ của hàm
        Đầu ra:
            int exp_result: kết quả của hàm mũ
    */
    
    if (n==0) return 1;
    else if (n>0) return 1 << n;
    else return 1.0/(1<<(-n));
    
}

// *******************************************************************************
// Ass3 - Array Queue
class AQueue{
public:
    int arr[max_size];
    int front, rear;
    int size;
    
    // conductor
    AQueue () {
        front = rear = -1;
        size = 0;
    }
    
    // -------------------------------
    // Functions
    void print() {
        if (size == 0) {
            cout << "Queue is empty!\n";
            return;
        }
        
        for (int i=front; i<rear+1; i++){
            cout << arr[i] << ", ";
        }
        cout << endl;
    }
    
    void enqueue(int val) {
        /*
            Pseudo-code
            
            Function ENQUEUE(val):
                If size == max_size:
                    Print "Your Queue is full!"
                    Return
            
                If front == -1:   // Nếu Queue rỗng, đặt front = 0
                    front = 0
            
                rear = rear + 1   // Tăng rear lên 1
                arr[rear] = val   // Thêm phần tử vào cuối mảng
                size = size + 1   // Tăng kích thước hàng đợi

        */
        
        if (size == max_size){
            cout << "Your Queue is full!" << endl;
            return;
        }
        
        // nếu Queue rỗng, cập nhật front
        if (front == -1) {
            front = 0;
        }
        
        arr[++rear] = val;
        
        size++;
    }
    
    void dequeue(){
        /*
            Pseudo-code
            
            Function DEQUEUE():
                If size == 0:
                    Print "Your Queue is empty!"
                    Return
            
                If front == rear:  // Nếu chỉ có 1 phần tử, reset Queue
                    front = -1
                    rear = -1
                Else:
                    front = front + 1  // Dịch front lên 1
            
                size = size - 1  // Giảm kích thước hàng đợi
        */
        if (size==0) {
            cout << "Your Queue is empty!" << endl;
            return;
        }
        
        // nếu mảng chỉ có 1 phần tử, reset Queue
        if (front == rear){
            front = rear = -1;
        }
        // nếu khong
        else {
            front ++;
        }
        size--;
    }
};

// *******************************************************************************
// Ass4 - Linked list Queue
class LLQueue {
private:
    struct node {
        int data;
        node* next;
        node* prev;
        
        // default conductor
        node () {
            next = prev = nullptr;
        }
        
        // values conductor
        node (int d) {
            data = d;
            next = prev = nullptr;
        }
        
    };
    
public:
    int size;
    node* front;
    node* rear;
    
    // conductor
    LLQueue () {
        size  = 0;
        front = rear = nullptr;
    }
    
    // -------------------------------
    // Functions
    void print() {
        node* temp = front;
        while (temp != nullptr){
            cout << temp->data << ", ";
            temp = temp->next;
        }
        cout << endl;
    }
    
    void enqueue (int val){
        /*
            Pseudo-code
            
            Function ENQUEUE(val):
                newnode = new Node(val)  // Tạo một node mới chứa giá trị val
            
                If front == NULL:   // Nếu Queue rỗng, cập nhật front và rear
                    front = newnode
                    rear = newnode
                Else:   // Nếu Queue có ít nhất một phần tử
                    rear.next = newnode  // Liên kết rear với node mới
                    newnode.prev = rear  // Liên kết node mới với rear
                    rear = newnode       // Cập nhật rear
            
                size = size + 1  // Tăng kích thước hàng đợi

        */
        
        node* newnode = new node(val);
        
        // nếu Queue rỗng
        if (front == nullptr){
            front = rear = newnode;
        } 
        
        // nếu Queue có ít nhất 1 phần tử
        else {
            rear->next = newnode;
            newnode->prev = rear;
            rear = newnode;
        }
        size++;
    }
    
    void dequeue (){
        /*
            Pseudo-code
            
            Function DEQUEUE():
                If front == NULL:   // Nếu Queue rỗng
                    Print "Your Queue is empty!"
                    Return
            
                toDel = front  // Lưu node sẽ bị xóa
            
                If front == rear:   // Nếu chỉ có một phần tử, reset Queue
                    front = NULL
                    rear = NULL
                Else:   // Nếu Queue có nhiều hơn một phần tử
                    front = front.next  // Di chuyển front lên node tiếp theo
                    front.prev = NULL   // Ngắt liên kết với node cũ
            
                Delete toDel  // Xóa node đã dequeue
                size = size - 1  // Giảm kích thước hàng đợi
                
        */
        
        if (front == nullptr){
            cout << "Your Queue is empty!" << endl;
            return;
        }
        
        node* toDel = front;
        
        // nếu Queue chỉ có 1 phần tử
        if (front == rear){
            front = rear = nullptr;
        }
        
        // nếu Queue nhiều hơn 1 phần tử
        else {
            front = front->next;
            front->prev = nullptr;
        }
        
        // -----
        delete toDel;
        size--;
    }
    
};

// *******************************************************************************
// Ass5 - Array Stack
class AStack{
public:
    int arr[max_size];
    int top, size;
    
    // default conductor
    AStack () {
        top  = -1;
        size = 0;
    }
    
    // -------------------------------
    // Functions
    void print() {
        if (size == 0) {
            cout << "Stack is empty!\n";
            return;
        }
        
        for (int i = top; i >= 0; i--) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    
    void push(int val){
        /*
            Pseudo-code
            
            Function PUSH(val):
                If size == max_size:   // Kiểm tra nếu stack đầy
                    Print "Your Stack is full!"
                    Return
            
                top = top + 1   // Tăng top lên 1
                arr[top] = val  // Lưu giá trị vào vị trí mới
                size = size + 1 // Tăng kích thước stack

        */
        
        if (size == max_size){
            cout << "Your Stack is full!" << endl;
            return;
        }
        
        arr [++top] = val;
        size ++;
    }
    
    void pop() {
        /*
            Function POP():
                If size == 0:   // Kiểm tra nếu stack rỗng
                    Print "Stack is empty!"
                    Return
            
                top = top - 1   // Giảm top xuống 1
                size = size - 1 // Giảm kích thước stack

        */
        
        if (size == 0) {
            cout << "Stack is empty!\n";
            return;
        }
        
        top--;
        size--;
    }
};

// *******************************************************************************
// Ass6 - Linked list Queue
class LLStack {
private:
    struct node {
        int data;
        node* next;
        
        // default conductor
        node () {
            next = nullptr;
        }
        
        // values conductor
        node (int d) {
            data = d;
            next = nullptr;
        }
        
    };
public:
    int size;
    node* top;
    
    // default conductor
    LLStack (){
        size=0;
        top=nullptr;
    }
    
    // -------------------------------
    // Functions
    void print() {
        node* temp = top;
        while (temp != nullptr){
            cout << temp->data << ", ";
            temp = temp->next;
        }
        cout << endl;
    }
    
    void push (int val){
        /*
            Function PUSH(val):
                newnode = new Node(val)   // Tạo một node mới chứa giá trị val
            
                newnode.next = top  // Liên kết node mới với top hiện tại
                top = newnode       // Cập nhật top thành node mới
            
                size = size + 1  // Tăng kích thước stack

        */
        
        node* newnode = new node(val);
        
        newnode->next = top;
        top = newnode;
        
        size++;
    }
    
    void pop() {
        /*
            Function POP():
                If top == NULL:   // Kiểm tra nếu stack rỗng
                    Print "Stack is empty!"
                    Return
            
                toDel = top      // Lưu node sẽ bị xóa
                top = top.next   // Cập nhật top lên node tiếp theo
            
                Delete toDel  // Xóa node đã pop
                size = size - 1  // Giảm kích thước stack

        */
        
        // nếu stack rỗng
        if (top == nullptr){
            cout << "Stack is empty!" << endl;
            return;
        }
        
        node* toDel = top;
        top = top->next;
        
        delete toDel;
        size--;
    }
    
    
};


// *******************************************************************************
int main()
{
    int your_choice = -1;
    
    while(true){
        
        printOptions();
        cout << "Enter your choice: ";
        cin >> your_choice; cin.ignore();
        
        switch(your_choice){
            case 0:
                cout << "Bye!" << endl;
                return 0;
            case 1:
                cout << "Read the assignment address in the source above!" << endl;
                break;
            case 2: {
                int n;
                cin >> n;
                
                cout << powerOfTwo_Iterative(n) << ", " << powerOfTwo_Recursive(n) << ", " << powerOfTwo_LeftShift(n) << endl;
                
                cout << measureTime(powerOfTwo_Iterative, n) << ", " << measureTime(powerOfTwo_Recursive, n) << ", " << measureTime(powerOfTwo_LeftShift, n) << endl;
                
                break;
            }
            case 3: {
                AQueue myAQ;
                
                myAQ.enqueue(1);
                myAQ.enqueue(2);
                myAQ.enqueue(3);
                myAQ.enqueue(5);
                myAQ.enqueue(22);
                myAQ.enqueue(32);
                myAQ.enqueue(52);
                myAQ.print();
                
                myAQ.dequeue();
                myAQ.dequeue();
                myAQ.dequeue();
                myAQ.dequeue();
                
                myAQ.print();
                
                break;
            }
            case 4: {
                LLQueue myLLQ;
                
                myLLQ.enqueue(1);
                myLLQ.enqueue(2);
                myLLQ.enqueue(3);
                myLLQ.enqueue(5);
                myLLQ.enqueue(22);
                myLLQ.enqueue(32);
                myLLQ.enqueue(52);
                myLLQ.print();
                
                myLLQ.dequeue();
                myLLQ.dequeue();
                myLLQ.dequeue();
                myLLQ.dequeue();
                
                myLLQ.print();
                
                break;
            }
            case 5: {
                AStack myAT;
                
                myAT.push(1);
                myAT.push(2);
                myAT.push(3);
                myAT.push(5);
                myAT.push(22);
                myAT.push(32);
                myAT.push(52);
                myAT.print();
                
                myAT.pop();
                myAT.pop();
                myAT.pop();
                myAT.pop();
                
                myAT.print();
                break;
            }
            case 6: {
                AStack myLLT;
                
                myLLT.push(1);
                myLLT.push(2);
                myLLT.push(3);
                myLLT.push(5);
                myLLT.push(22);
                myLLT.push(32);
                myLLT.push(52);
                myLLT.print();
                
                myLLT.pop();
                myLLT.pop();
                myLLT.pop();
                myLLT.pop();
                
                myLLT.print();
                break;
            }
            default:
                cout << "Invalid options, try againt!" << endl;
                break;
        }
    }

    return 0;
}