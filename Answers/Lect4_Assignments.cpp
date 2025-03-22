/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
using namespace std;

const int STUDENTLIST_SIZE = 11;

void printOptions() {
    cout << endl;
    cout << "-----------------------" << endl;
    cout << "0. Quit!" << endl;
    cout << "1. Ex1" << endl;
    cout << "2. Ex2" << endl;
    cout << "3. Ex3" << endl;
    cout << "4. Ex4 - Chaining" << endl;
    cout << "5. Ex4 - Linear probing" << endl;
}

// *******************************************************************************
// Ex4 - Chaining
class StudentListLL {
private:
    struct node {
        int ID;
        string name;
        string clsname;
        node* next;
        
        // Constructor mặc định
        node(): ID(-1), name("nan"), clsname("nan"), next(nullptr) {}
    
        // Constructor có tham số
        node(int id, string n, string c): ID(id), name(n), clsname(c), next(nullptr) {}
    };

    int hashFunc (int ID){
        return ID % STUDENTLIST_SIZE;
    }
    
public:
    node* table[STUDENTLIST_SIZE];  // Mảng cố định chứa con trỏ đầu danh sách liên kết

    // conductor
    StudentListLL() {
        for (int i=0; i<STUDENTLIST_SIZE; i++) {
            table[i] = nullptr;
        }
    }
    
    // function
    void print() {
        cout << "-----------------------" << endl;
        cout << "Your hash table: " << endl;
        
        for (int i=0; i<STUDENTLIST_SIZE; i++) {
            
            cout << i << "\t: ";
            
            node* temp = table[i];
            if (temp == nullptr) {
                cout << "Empty"; // Nếu không có phần tử nào
            } 
            
            else {
                while (temp != nullptr) {
                    cout << "[" << temp->ID << ", " << temp->name << ", " << temp->clsname << "] → ";
                    temp = temp->next;
                }
                cout << "NULL"; // Kết thúc danh sách liên kết
            }
            cout << endl;
        }
    }
    
    
    void insert(int id, string name, string clsname) {
        node* newNode   = new node(id, name, clsname); // tạo node mới 
        int hashIndex   = hashFunc(id); // tính toán index của node mới
        
        // chèn vào đầu linkedlist
        newNode->next   = table[hashIndex];
        table[hashIndex]= newNode;
    }
    
    void del(int id) {
        int hashIndex   = hashFunc(id);
        
        // kiểm tra linked list tại i, nếu nó rỗng thì trả về luôn
        if (table[hashIndex] == nullptr) {
            cout << "Your linked list at " << hashIndex << " is empty";
            return;
        } 
        
        // nếu nó không rỗng thì tìm kiếm id trong danh sách liên kết
        else {
            node* curr = table[hashIndex];
            node* prev = nullptr;
            
            // Duyệt danh sách liên kết
            while (curr != nullptr){
                // kiểm tra nếu gặp id thì ...
                if (curr->ID == id){
                    // nếu id ngay đầu linkedlist, cập nhật lại head
                    if (prev == nullptr) {
                        table[hashIndex] = curr->next;
                    }
                    // nếu id không ở đầu
                    else {
                        prev->next = curr->next;
                    }
                }
                
                // nếu không gặp id thì duyệt tiếp
                prev = curr;
                curr = curr->next;
            }
        }
    }
    
    void infor(int id) {
        int hashIndex   = hashFunc(id);
        
        // kiểm tra linked list tại i, nếu nó rỗng thì trả về luôn
        if (table[hashIndex] == nullptr) {
            cout << "Your linked list at " << hashIndex << " is empty" << endl;
            return;
        }
        
        // duyệt linked list tìm id
        node* temp = table[hashIndex];
        while(temp != nullptr) {
            if (temp->ID == id){
                cout << "[" << temp->ID << ", " << temp->name << ", " << temp->clsname << "]" << endl;
                return;
            }
            temp = temp->next;
        }
        
        cout << "Your ID is not found!" << endl;
        return;
    }
};

// *******************************************************************************
// Ex4 - Linear probing

class StudentListA {
private:
    struct Student {
        int ID;
        string name;
        string clsname;
        
        // Constructor mặc định
        Student(): ID(-1), name("-"), clsname("-") {}
    
        // Constructor có tham số
        Student(int id, string n, string c): ID(id), name(n), clsname(c) {}
    };

    Student StudentList[STUDENTLIST_SIZE]; // cài đặt mảng cố định
    
    int hashfunc(int id) {
        return id%STUDENTLIST_SIZE;
    }
    
public:
    // conductor
    StudentListA () {
        for(int i=0; i<STUDENTLIST_SIZE; i++) {
            StudentList[i].ID = -1;
        }
    }
    
    
    // function
    void print() {
        cout << "-----------------------" << endl;
        cout << "Your hash table: " << endl;
        
        for (int i=0; i<STUDENTLIST_SIZE; i++) {
            
            cout << i << "\t: ";
            
            // if (StudentList[i].ID == -1) {
            //     cout << " -" << endl;
            // } else {
            //     cout << "[ " << StudentList[i].ID << ", " << StudentList[i].name << ", " << StudentList[i].clsname << " ]" << endl;
            // }
            cout << "[ " << StudentList[i].ID << ", " << StudentList[i].name << ", " << StudentList[i].clsname << " ]" << endl;
        }
    }
    
    void insert(int id, string name, string clsname) {
        int index   = hashfunc(id);
        int startIndex = index; // cần lưu lại cái index ban đầu để dừng vòng while
        
        // tìm index với 2 điều kiện: chỗ đó trống và id không trùng với ID có sẵn
        while (StudentList[index].ID != -1 && StudentList[index].ID != id) {
            index = (index+1) % STUDENTLIST_SIZE;
            
            // nếu duyệt 1 vòng về lại cái index ban đầu tức là bảng đầy
            if (index == startIndex) {
                cout << "Your table is full!" << endl;
                return;
            }
        }
        
        // nếu tìm thấy chỗ trống thì insert vào bảng
        StudentList[index] = {id, name, clsname};
    }
    
    void del(int id) {
        int index       = hashfunc(id);
        int startIndex  = index; // cần lưu lại cái index ban đầu để dừng vòng while
        
        while (StudentList[index].ID != -1) {
            // Kiểm tra phần tử cần xóa
            if (StudentList[index].ID == id){
                StudentList[index] = Student(); // xóa phần tử nến tìm được
                cout << "Delete ID: " << id << " done!" << endl;
                return;
            }
            
            // dịch chuyển index
            index = (index+1) % STUDENTLIST_SIZE;
            
            // nếu duyệt hết mảng mà k tìm được
            if (index == startIndex) {
                cout << "Your ID not found" << endl;
                return;
            }
            
        }
    }
    
    void getInfo(int id) {
        int index = hashfunc(id);
        int startIndex = index;

        while (StudentList[index].ID != -1) {
            if (StudentList[index].ID == id) {
                cout << "[ " << StudentList[index].ID << ", " << StudentList[index].name << ", " << StudentList[index].clsname << " ]" << endl;
                return;
            }
            
            index = (index + 1) % STUDENTLIST_SIZE;
            
            // nếu duyệt hết mảng mà k tìm được
            if (index == startIndex) {
                cout << "Your ID not found" << endl;
                return;
            }
        }
        cout << "NA,NA" << endl;
    }
};

int main()
{
    int my_option = -1;
    
    while(true) {
        printOptions();
        cout << "Enter your option: ";
        cin >> my_option; cin.ignore();
        
        cout << "-----------------------" << endl;
        
        switch(my_option) {
            case 0: {
                cout << "Bye!" << endl;
                return 0;
            }
            
            case 1: {
                cout << "case 1" << endl;
                break;
            }
            
            case 2: {
                cout << "case 2" << endl;
                break;
            }
            
            case 3: {
                cout << "case 3" << endl;
                break;
            }
            
            case 4: {
                
                StudentListLL mySL;
                
                mySL.insert(1004, "HTP1004", "1004");
                mySL.insert(200, "HTP200", "1004");
                mySL.insert(31, "31", "1004");
                mySL.insert(12, "12", "1004");
                mySL.insert(3131, "3131", "1004");
                mySL.insert(331, "H331TP", "1004");
                mySL.insert(111, "HT331P", "1004");
                
                mySL.infor(111);
                mySL.infor(000);
                
                mySL.print();
                
                mySL.del(12);
                mySL.del(31);
                mySL.del(331);
                
                mySL.infor(331);
                
                mySL.print();
                
                break;
            }
            
            case 5: {
                StudentListA mySLA;
                
                mySLA.insert(1004, "HTP1004", "1004");
                mySLA.insert(200, "HTP200", "1004");
                mySLA.insert(31, "31", "1004");
                mySLA.insert(12, "12", "1004");
                mySLA.insert(3131, "3131", "1004");
                mySLA.insert(331, "H331TP", "1004");
                mySLA.insert(111, "HT331P", "1004");
                mySLA.print();
                
                mySLA.getInfo(331);
                
                mySLA.del(12);
                mySLA.del(31);
                mySLA.print();

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