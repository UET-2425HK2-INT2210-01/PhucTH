/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
using namespace std;

class MinHeap {
private:
    int* heap;      // khởi tạo mảng động lưu trữ Min heap
    int maxSize;    // dung lượng tối đa của mảng
    int size;       // kích thước hiện tại của mảng

    // lấy chỉ số của cha của node tại i
    int getParentID (int i) {
        return (i-1)/2;
    }
    
    // lấy chỉ số con trái của node hiện tại
    int getLeftChildID (int i) {
        return 2*i+1;
    }
    
    // lấy chỉ số con phải của node hiện tại
    int getRightChildID (int i) {
        return 2*i+2;
    }
    
    // hoán đổi 2 phần tử trong mảng
    void swap (int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }
    
    // Hàm cập nhật Min Heap sau khi insert -> dịch chuyển phần tử lên trên
    void heapifyUp (int i) {
        /*
            Hàm thực hiện chức năng đưa phần tử mới chèn về đúng vị trí theo quy tắc của Min Heap (cha nhỏ hơn con).
            Nếu phần tử mới nhỏ hơn cha của nó thì hoán đổi và tiếp tục kiểm tra lên trên (up).
            
            Input:
                - i (int)   : index của phần tử vừa mới được chèn vào mảng
            
            Output:
                - mảng đã được cập nhật
        */
        
        while (
                i > 0 && // kiểm tra đến con của gốc
                heap[getParentID(i)] > heap[i] // nếu phần tử mới nhỏ hơn cha của nó
            ) {
            // dịch chuyển phần tử đó lên trên lên trên - hoán đổi 2 cha con
            swap(heap[i], heap[getParentID(i)]);
            
            // dịch chuyển i lên để duyệt tiếp
            i = getParentID(i); 
        }
    }
    
    // Hàm cập nhật Min Heap sau khi delete -> dịch chuyển phần tử xuống dưới
    void heapifyDown (int i) {
        /*
            Hàm thực hiện chức năng update lại Min Heap sau khi xóa phần i.
            Tìm con nhỏ hơn (trái hoặc phải) sau đó hoán đổi dần xuống bên dưới.
            
            Input:
                - i (int)   : index của phần tử vừa được hoán đổi để xóa
            
            Output:
                - mảng đã được cập nhật
        */
        
        int smallestID  = i; // giả sử i nhỏ nhất
        int leftID      = getLeftChildID(i);
        int rightID     = getRightChildID(i);
        
        // cập nhật con bên trái
        if (leftID < size && heap[leftID] < heap[smallestID]) smallestID  = leftID;
        
        // cập nhật con bên phải
        if (rightID < size && heap[rightID] < heap[smallestID]) smallestID  = rightID;
        
        if (smallestID != i) { // nếu i không phải nhỏ nhất 
            swap(heap[i], heap[smallestID]); // đổi vị trí i và smallestID
            heapifyDown(smallestID); // gọi đệ quy tiếp xuống dưới
        }
    }
    
public:
    // constructor
    MinHeap(int sizeInput): heap(new int[sizeInput]), maxSize(sizeInput), size(0) {}
    
    // Functions
    // Thêm phần tử vào cây
    void insert(int value) {
        if (size == maxSize){
            cout << "Your heap is full!" << endl;
            return;
        }
        
        // 1. trực tiếp insert value vào cuối mảng
        heap[size] = value;
        
        // 2. cập nhật heap tree sau khi insert vào cuối
        heapifyUp(size);
        size++; // 3. cập nhật số lượng phần tử trong mảng
    }
    
    // Xóa phần tử bất kỳ khỏi heap
    void del(int value) {
        bool check=false; // biến kiểm tra phần tử có trong mảng
        
        // duyệt mảng để tìm phần tử cần xóa
        for (int i=0; i<size; i++) {
            // tìm phần tử cần xóa
            if (heap[i] == value) {
                check = true; // đã tìm thấy value
                
                // nếu tìm thấy thì xóa phần tử đó
                heap[i] = heap[size-1];
                size--; // giảm kích thước sau xóa
                
                heapifyDown(i); // cập nhật sau xóa
                break;
            }
        }
        
        if (check == false){
            cout << "Your value is not found!" << endl;
            return;
        }
    }
    
    // Xây dựng heap từ mảng ban đầu - O(nlogn)
    void buildHeap(int arr[], int n) {
        for (int i = 0; i < n; i++) {
            insert(arr[i]);
        }
    }
    
    // Xây dựng heap từ mảng ban đầu - O(n)
    // void buildHeap(int arr[], int n) { 
    //     for (int i = 0; i < n; i++) {
    //         heap[i] = arr[i];
    //     }
    //     size = n;
    //     // Heapify từ các node cha cuối cùng trở lên
    //     for (int i = (n / 2) - 1; i >= 0; i--) {
    //         heapifyDown(i);
    //     }
    // }
    
    // In mảng lưu Min Heap
    void print() {
        for (int i = 0; i < size; i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }

    // Duyệt cây theo Preorder (NLR - Node, Left, Right)
    void preorderTraversal(int i = 0) {
        if (i >= size) return; // Nếu vị trí i vượt quá số phần tử, dừng lại
        
        cout << heap[i] << " ";  // 1. In giá trị nút hiện tại
        preorderTraversal(getLeftChildID(i));  // 2. Duyệt con trái
        preorderTraversal(getRightChildID(i)); // 3. Duyệt con phải
    }

    // Duyệt cây theo Preorder 
    void inorderTraversal(int i = 0) {
        if (i >= size) return; // Nếu vị trí i vượt quá số phần tử, dừng lại
        
        inorderTraversal(getLeftChildID(i));  // 1. Duyệt con trái
        cout << heap[i] << " ";  // 2. In giá trị nút hiện tại
        inorderTraversal(getRightChildID(i)); // 3. Duyệt con phải
    }

    // Duyệt cây theo Postorder 
    void postorderTraversal(int i = 0) {
        if (i >= size) return; // Nếu vị trí i vượt quá số phần tử, dừng lại
        
        postorderTraversal(getLeftChildID(i));  // 1. Duyệt con trái
        postorderTraversal(getRightChildID(i)); // 2. Duyệt con phải
        cout << heap[i] << " ";  // 3. In giá trị nút hiện tại
    }

};

int main() {

    // Danh sách số nguyên ban đầu
    int arr[]   = {2, 1, 10, 6, 3, 8, 7, 13, 20};
    int n       = sizeof(arr) / sizeof(arr[0]);

    // Tạo Min Heap và xây dựng từ danh sách ban đầu
    MinHeap heap(n+100); // Cấp phát lớn hơn để có chỗ chèn thêm
    heap.buildHeap(arr, n);
    heap.print();

    cout << "Preorder: ";
    heap.preorderTraversal();
    cout << endl;

    cout << "Inorder: ";
    heap.inorderTraversal();
    cout << endl;

    cout << "Postorder: ";
    heap.postorderTraversal();
    cout << endl;

    // Chèn các giá trị mới: 14, 0, 35
    heap.insert(14);
    heap.insert(0);
    heap.insert(35);
    heap.print();

    // Xóa các phần tử: 6, 13, 35
    heap.del(6);
    heap.del(13);
    heap.del(35);
    heap.print();    

    return 0;
}