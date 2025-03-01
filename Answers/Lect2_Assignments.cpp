/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
using namespace std;


// *******************************************************************************
// Ass1
void coutAssOptions(){
    cout << endl << endl;
    cout << "------------------------------------------------" << endl;
    cout << "1. Count the number of pairs (i,j)." << endl;
    cout << "2. Singly linked list." << endl;
    cout << "3. Doulby linked list." << endl;
    cout << "4. Queue by linked list." << endl;
    cout << "5. Stack by linked list." << endl;
    cout << "0. Quit!" << endl;
    cout << endl;
}

// *******************************************************************************
// Ass2
struct Node {
    int data;
    Node* next;
    
    // Conductor: khoi tao gia tri mac dinh
    Node (int d_){
        data = d_;
        next = nullptr;
    }
};

class LinkedList {
    public:
    Node* head;
    int len=0;
    
    // Conductor
    LinkedList() {
        head = nullptr;
    }
    
    // Function
    void print() {
        if (head == nullptr){
            cout << "Your LinkedList is empty!" << endl;
        } else {
            Node* temp = head;
            while (temp != nullptr){
                cout << temp->data << ", ";
                temp = temp->next;
            }
        }
        cout << endl;
    }
    
    void append(int x) {
        Node* new_node = new Node(x);
        
        if (head == nullptr){
            head = new_node;
        } else {
            Node* temp = head;
            while (temp->next != nullptr){
                temp = temp->next;
            }
            temp->next = new_node;
        }
        len++;
    }
    
    void insert (int p, int x){
        /*
            Hàm thực hiện nhiệm vụ chèn thêm node là LinkedList dựa trên bị trí
            
            Input:
                int p   vị trị cần chèn dữ liệu
                int x   dữ liệu cần chèn
                
            Output:
                LinkedList đã được chèn
        */
        
        if (p < 0 || p > len) {  // Kiểm tra vị trí không hợp lệ
            cout << "Your position is incorrect!" << endl;
            return;
        }        

        Node* newNode = new Node(x);
        
        // insert vao dau, p=0
        if (p==0) {
            newNode->next = head;
            head = newNode;
        } 
        // insert vi tri bat ky
        else {
            Node* temp=head;
            for (int i=0; i<p-1; i++){
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        } 
        len++;
    }
    
    void del (int p) {
        /*
            Hàm thực hiện nhiệm vụ xóa node trong LinkedList theo vị trí
            
            Input:
                int p   vị trị cần xóa
                
            Output:
                LinkedList đã được xóa
        */
        
        if (head == nullptr) { // Kiểm tra LinkedList rong
            cout << "Your LinkedList is Null" << endl;
            return;
        } else if (p < 0 || p >= len) {  // Kiểm tra vị trí không hợp lệ
            cout << "Your position is incorrect" << endl;
            return;
        }
        
        // Khởi tạo node tạm để lưu head
        Node* temp = head;
        
        // Trường hợp xóa node đầu tiên
        if (p == 0) {
            head = head->next;
        } 
        // Xóa vị trí bất kỳ
        else {
            Node* prev = nullptr;
    
            for (int i = 0; i < p; i++) {
                prev = temp;
                temp = temp->next;
            }
    
            prev->next = temp->next;
        }
    
        delete temp; // giải phóng bộ nhớ
        len--; // Giảm kích thước danh sách
        
    }
};


// *******************************************************************************
// Ass3
struct DNode {
    int data;
    DNode* prev;
    DNode* next;
    
    // Conductor: khoi tao gia tri mac dinh
    DNode (int d_){
        data = d_;
        prev = nullptr;
        next = nullptr;
    }
};

class DLinkedList {
public:
    DNode* head;
    DNode* tail;
    int len=0;
    
    // Conductor
    DLinkedList() {
        head = nullptr;
        tail = nullptr;
    }
    
    // Function
    void append(int value) {
        // Khoi tao node moi
        DNode* newDNode = new DNode(value);
        
        // Nếu DLL rỗng thì gán trực tiếp head và tail = newNode
        if (head == nullptr){
            head = newDNode;
            tail = newDNode;
        } 
        // Nếu DLL không rỗng
        else {
            tail->next = newDNode;
            newDNode->prev = tail;
            tail = newDNode;
        }
        len ++; // cập nhật độ dài mảng
    }
    
    void print() {
        if (head == nullptr){
            cout << "Your Doubly LinkedList is empty!";
            return;
        } else {
            DNode* temp = head;
            while (temp != nullptr){
                cout << temp->data << ", ";
                temp = temp->next;
            }
            cout << endl;
        }
    }
    
    void count_triplets() {
        int ct = 0; // count_triplets
        
        // Kiểm tra nếu danh sách có ít hơn 3 phần tử
        if (len < 3) {
            cout << "DLL count triplets: 0" << endl;
            return;
        }

        int prev_data, curr_data, next_data, sum_triplets;
        DNode* temp = head;
        while (temp != nullptr) {
            if (temp->prev != nullptr && temp->next != nullptr){
                prev_data = temp->prev->data;
                next_data = temp->next->data;
                curr_data = temp->data;
                
                sum_triplets = prev_data + curr_data + next_data;
                if (sum_triplets == 0){
                    ct++;
                }
            }
            temp=temp->next;
        }
        
        cout << "DLL count triplets: " << ct << endl;
    }
};

// *******************************************************************************
// Ass4: Queue
struct QNode {
    int data;
    QNode* next;
    
    // Conductor
    QNode (int d_){
        data = d_;
        next = nullptr;
    }
};

class Queue {
public:
    // int len=0; // Queue k cần cái này vì chỉ cần vào và đợi thôi, k quan tâm số lượng

    QNode* front; // head
    QNode* rear; // tail
    
    // Conductor
    Queue () {
        front = nullptr;
        rear = nullptr;
    }
    
    // Function
    void print(){
        QNode* temp = front;
        while(temp != nullptr){
            cout << temp->data << ", ";
            temp = temp->next;
        }
        cout << endl;
    }
    
    void enqueue(int value) {
        /*
            Hàm thực hiện chức năng insert value vào cuối hàng (tail - rear)
        */
        
        QNode* newQNode = new QNode(value);
        if (rear == nullptr){ // Nếu queue rỗng
            front = rear = newQNode;
        } else {
            rear->next = newQNode;
            rear = newQNode;
        }
    }
    
    void dequeue() {
        /*
            Hàm thực hiện chức năng delete value ở đầu hàng (head - front)
        */
        
        if (front == nullptr) {
            cout << "Your Queue is empty!" << endl;
            return;
        }
        
        QNode* temp = front;
        front = front->next;
        
        if (front == nullptr){ // Nếu xóa xong mà queue rỗng
            rear = nullptr;
        }
        delete temp;
    }
};

// *******************************************************************************
// Ass5: Stack
struct SNode {
    // B1: khoi tao tham so
    int data;
    SNode* next;
    
    // B2: khoi tao Conductor
    SNode (int d_){
        data = d_;
        next = nullptr;
    }
};

class Stack {
public:
    // B1: khoi tao tham so
    SNode* top;
    
    // B2: khoi tao Conductor
    Stack() {
        top = nullptr;
    }
    
    // B3: Cai dat ham
    void print(){
        if (top == nullptr) {  // Kiểm tra stack rỗng
            cout << "Stack is empty!" << endl;
            return;
        }
        
        SNode* temp = top; // Duyệt từ đỉnh stack xuống
        while (temp != nullptr){
            cout << temp->data << ", ";
            temp = temp->next;
        }
        cout << endl;
    }

    void printReverseHelper(SNode* node) {
        if (node == nullptr) return;  // Dừng khi đến cuối danh sách
        printReverseHelper(node->next);  // Đệ quy trước khi in
        cout << node->data << " ";  // In dữ liệu sau khi gọi đệ quy
    }

    void printReverse() {
        if (top == nullptr) {
            cout << "Stack is empty!" << endl;
            return;
        }
        // cout << "Stack (bottom to top): ";
        printReverseHelper(top);
        cout << endl;
    }
    
    void push(int value) {
        /*
            Hàm thêm phần tử vào stack
            Ở đây k cần check gì cả vì khi thêm mới thì luôn đặt lên đầu, k quan trọng stack có null hay k
        */
        SNode* newSNode = new SNode(value);
        
        newSNode-> next = top;
        top = newSNode;
    }
    
    void pop () {
        /*
            Hàm thực hiện chức năng lấy phần tử khỏi stack
            Ở đây phải check xem stack có rỗng hay không
        */
        if (top == nullptr){
            cout << "Your Stack is empty!" << endl;
            return;
        } else {
            SNode* temp = top;
            top = top->next;
            delete temp;
        }
    }
};

// *******************************************************************************
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
                cout << "-------------" << endl;
                
                int n;
                cout << "Enter n: ";
                cin >> n;
                
                cout << "Enter array of " << n << " number: ";
                int arr[n];
                for (int i=0; i<n; i++){
                    cin >> arr[i];
                }
                
                int countPairNum=0;
                for (int i=0; i<n-1; i++){
                    for (int j=i+1; j<n; j++){
                        if (arr[i] == arr[j]){
                            countPairNum++;
                        }
                    }
                }
                
                cout << "countPairNum: " << countPairNum << endl;
                break;
            }
            
            case 2:{
                cout << "-------------" << endl;
                
                LinkedList myll;
                // myll.append(3);
                // myll.append(2);
                // myll.append(1);
                
                int n; // n_operations
                cin >> n;
                
                for (int i=0; i<n; i++){
                    string command_i; // operation_i
                    cin >> command_i;
    
                    if (command_i == "insert"){
                        int p, x;
                        cin >> p >> x;
                        myll.insert(p,x);
                    } else if (command_i == "delete") {
                        int p;
                        cin >> p;
                        myll.del(p);
                    }
                }
                myll.print();
                break;
            }
            
            case 3:{
                DLinkedList mydll;
                
                mydll.append(5);
                mydll.append(-3); 
                mydll.append(-2); 
                mydll.append(2); 
                mydll.append(9); 
                mydll.append(-11); 
                mydll.print();
                
                mydll.count_triplets();
                break;
            }
            
            case 4:{
                Queue myQ;
                
                myQ.enqueue(1);
                myQ.enqueue(2);
                myQ.enqueue(3);
                myQ.enqueue(4);
                myQ.dequeue();
                myQ.dequeue();
                myQ.enqueue(5);
                
                myQ.print();
                
                break;
            }
            
            case 5:{
                Stack myS;
                
                myS.push(1);
                myS.push(2);
                myS.push(3);
                myS.push(4);
                myS.pop();
                myS.pop();
                myS.push(100);
                myS.push(5);
                myS.pop();
                
                myS.print();
                myS.printReverse();
                break;
            }
        
            default:{
                cout << "Invalid option. Please try again!" << endl;
            }
        }
    }
}