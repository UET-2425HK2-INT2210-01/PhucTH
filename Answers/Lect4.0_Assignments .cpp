/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
using namespace std;

void printOption() {
    cout << endl;
    cout << "----------------" << endl;
    cout << "0. Quit!" << endl;
    cout << "1. Linked List" << endl;
    cout << "2. Priority Queue" << endl;
    cout << "3. Stack" << endl;
    cout << endl;
}

// *******************************************************************************
// Ass1
class LinkedList {
private:
    // khởi tạo node cho LinkedList
    struct node {
        int data;
        node* next;
        // conductor
        node(int d) : data(d), next(nullptr) {}
    };
    
public:
    node* head;
    int size;
    // conductor
    LinkedList() : head(nullptr), size(0) {}
    
    // function
    bool isEmpty() {
        if (head == nullptr) return true;
        else return false;
    }
    
    void print() {
        if (isEmpty()){
            cout << "Your LinkedList is empty!" << endl;
            return;
        }
        
        node* temp = head;
        while(temp != nullptr){
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    
    void append(int newValue) {
        /*
            Trong bài này chỉ yêu cầu nhập phần tử theo thứ tự nên chỉ cần append thay vì insert
        */
        
        node* newNode = new node(newValue);
        
        if (isEmpty()){
            head = newNode;
            size++;
            return;
        }
        
        node* temp = head;
        while(temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = newNode;
        size++;
    }
    
    void search(int value){
        if (isEmpty()){
            cout << "Your LinkedList is empty!" << endl;
            return;
        }
        
        int pos_val= 0;
        node* temp = head;
        
        while(temp != nullptr){
            if (temp->data == value){
                cout << pos_val << endl;
                return;
            } else {
                temp = temp->next;
                pos_val++;
            }
        }
        cout << "NO" << endl;
    }
    
    void reverse() {
        if (isEmpty()){
            cout << "Your LinkedList is empty!" << endl;
            return;
        }
        
        node* prev = nullptr; // Đảm bảo prev khởi tạo đúng
        node* curr = head;
        node* next = nullptr;
        
        while (curr != nullptr){
            next = curr->next;  // Lưu node tiếp theo
            curr->next = prev;  // Đảo ngược liên kết
            prev = curr;        // Dịch prev lên
            curr = next;        // Dịch curr lên
        }
        
        head = prev; // Cập nhật head
        return;
    }
    
    // Hàm đảo ngược danh sách bằng đệ quy
    node* helpRecursive(node* curr) {
        // Điều kiện dừng: nếu danh sách rỗng hoặc chỉ có 1 phần tử
        if (curr == nullptr || curr->next == nullptr) 
            return curr;

        // Đệ quy đảo ngược phần còn lại
        node* newHead = helpRecursive(curr->next);

        // Đảo ngược liên kết
        curr->next->next = curr;
        curr->next = nullptr;

        return newHead;  // Trả về node đầu mới
    }
    
    void reverseRecursive() {
        head = helpRecursive(head);  // Gọi hàm đệ quy với head
    }

};

// *******************************************************************************
// Ass2

class PriorityQueue {
private:
    struct pqnode {
        int data;
        int prio;
        pqnode* prev;
        pqnode* next;
        
        // conductor
        pqnode (int d, int p): data(d), prio(p), prev(nullptr), next(nullptr) {}
    };
    
public:
    pqnode* head;
    pqnode* tail;
    
    // conductor
    PriorityQueue(): head(nullptr), tail(nullptr) {}

    // function
    bool isEmpty() {
        if (head == nullptr) return true;
        else return false;
    }
    
    void print() {
        pqnode* temp = head;
        while (temp != nullptr) {
            cout << "(" << temp->data << ", " << temp->prio << "); ";
            temp = temp->next;
        }
        cout << endl;
    }
    
    void enqueue (int newValue, int newPrio) {
        // khởi tạo node mới
        pqnode* newNode = new pqnode(newValue, newPrio);
        
        // nếu queue rỗng hoặc newNode có prio lớn hơn head thì chèn trực tiếp vào đầu
        if (isEmpty() || head->prio < newPrio) {
            newNode->next = head;
            if (head != nullptr) head->prev = newNode;
            head = newNode;
            if (tail == nullptr) tail = newNode;
        }
        
        // chèn vào giữa hoặc cuối
        else {
            pqnode* temp = head;
            while (temp->next != nullptr && temp->next->prio >= newPrio) {
                temp = temp->next;
            }
            
            newNode->next = temp->next; 
            newNode->prev = temp; 
            
            // nếu newNode không phải node cuối cùng thì cập nhật nhật node cuối chỉ về newNode
            if (temp->next != nullptr) temp->next->prev = newNode;
            
            temp->next = newNode; // chèn newNode sau temp
            
            // nếu newNode là phần tử cuối cùng thì cập nhật tail
            if (newNode->next == nullptr) tail = newNode;
        }
    }
    
    void dequeue() {
        if (isEmpty()) return;
        
        pqnode* temp = head;
        head = head->next;
        
        if (head != nullptr) head->prev = nullptr;
        else tail = nullptr;
        
        delete temp;
    }
};

// *******************************************************************************
// Ass3

class Stack {
private:
    struct snode {
        char data;
        snode* next;
        
        // conductor
        snode(char d): data(d), next(nullptr) {}
    };
    
public:
    snode* top;
    
    // conductor
    Stack(): top(nullptr) {}
    
    // function
    bool isEmpty() {
        return top == nullptr;
    }
    
    void print() {
        snode* temp = top;
        
        while(temp != nullptr) {
            cout << temp->data << ", ";
            temp = temp->next;
        }
        cout << endl;
    }
    
    void push (char newchar) {
        snode* newNode = new snode(newchar);
        newNode->next = top;
        top = newNode;
    }
    
    void pop () {
        if (isEmpty()) return;
        
        snode* temp = top;
        top = top->next;
        
        delete temp;
    }
    
    char getTop() {
        if (isEmpty()) return '\0'; // trả về ký tự null
        return top->data;
    }
};

bool isValidBrackets (const string& myChars) {
    Stack myStack;
    
    for (char c: myChars) {
        // nếu là mở ngoặc thì thêm vào stack
        if (c == '(' || c == '[' || c == '{'){
            myStack.push(c);
        } 
        
        // Nếu là dấu đóng ngoặc thì ktra có khớp với top không?
        else {
            char topChar = myStack.getTop();

            // nếu khớp với top thì pop đi
            if  ((topChar == '(' && c == ')')||
                 (topChar == '[' && c == ']')|| 
                 (topChar == '{' && c == '}')){
            
                myStack.pop();
            }
            // nếu k khớp -> lỗi
            else {
                return false;
            }
        }
    }
    
    // Nếu stack rỗng sau khi duyệt hết chuỗi, trả về true
    return myStack.isEmpty();
}


// *******************************************************************************

int main()
{
    int my_option = -1;
    while (true) {
        printOption();
        cout << "Enter your option: ";
        cin >> my_option; cin.ignore();
        
        switch(my_option){
            case 0: {
                cout << "Bye bye!" << endl;
                return 0;
            }
            
            case 1: {
                LinkedList myLL;
                myLL.print();
                
                int n;
                cin >> n; cin.ignore();
                
                for (int i=0; i<n; i++){
                    int ni; cin >> ni;
                    myLL.append(ni);
                }
            
                myLL.print();
                
                myLL.search(4);
                myLL.search(5);
                
                myLL.reverse();
                myLL.reverseRecursive();
                myLL.print();
                
                break;
            }
            
            case 2: {
                PriorityQueue myPQ;
                
                myPQ.enqueue(10, 0);
                myPQ.enqueue(80, 8);
                myPQ.enqueue(20, 2);
                myPQ.enqueue(100, 1);
                myPQ.enqueue(0, 9);
                myPQ.print();
                
                myPQ.dequeue();
                myPQ.enqueue(-1, 100);
                
                myPQ.print();
                
                break;
            }
            
            case 3: {
                Stack myS;
                
                myS.push('X');
                myS.push('R');
                myS.push('3');
                myS.push('2');
                myS.push('w');
                
                myS.print();
                
                string list_char1 = "{[()]}";
                string list_char2 = "{[(])}";
                string list_char3 = "{{[[(())]]}}";
                
                cout << (isValidBrackets(list_char1) ? "Valid" : "Invalid") << endl;
                cout << (isValidBrackets(list_char2) ? "Valid" : "Invalid") << endl;
                cout << (isValidBrackets(list_char3) ? "Valid" : "Invalid") << endl;
                break;
            }
            
            default: {
                cout << "Your option is invalid, please try again!" << endl;
                break;
            }
        }
    }

    return 0;
}