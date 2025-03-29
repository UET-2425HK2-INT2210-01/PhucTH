/******************************************************************************

Ba phương pháp duyệt cây nhị phân như sau:
    Duyệt tiền tự (Preorder Traversal - NLR): Gốc → Trái → Phải
        => Duyệt nút gốc trước, sau đó đến cây con trái, cuối cùng là cây con phải.
    Duyệt trung tự (Inorder Traversal - LNR): Trái → Gốc → Phải
        => Duyệt cây con trái trước, sau đó gốc, rồi đến cây con phải. (Dùng để sắp xếp trong cây tìm kiếm nhị phân - BST).
    Duyệt hậu tự (Postorder Traversal - LRN): Trái → Phải → Gốc
        => Duyệt cây con trái trước, rồi cây con phải, cuối cùng là gốc. (Thường dùng để xóa cây).

*******************************************************************************/
#include <iostream>
using namespace std;

const int NODES_SIZE=1000;

struct treeNode {
    int data;
    treeNode* firstChild; // con cả
    treeNode* nextSibling; // anh chị em của con cả
    
    // conductor
    treeNode(int value): data(value), firstChild(nullptr), nextSibling(nullptr) {}
};

class Tree {
public:
    // Khai báo biến
    treeNode* root; // khởi tạo cây bằng node root
    treeNode* nodeList[NODES_SIZE]; // Mảng lưu trữ các node
    bool isChild[NODES_SIZE]; // Mảng quản lý node con, dùng để tìm node root
    
    // conductor
    Tree(): root(nullptr) {
        for (int i = 0; i < NODES_SIZE; ++i) {
            nodeList[i] = nullptr;
            isChild[i] = false;
        }
    }
    
    // ---------------[ Functions ] ---------------
    // // Hàm để thiết lập nút gốc
    // void setRoot(treeNode* rootNode) {
    //     root = rootNode;
    // }

    // // Hàm để lấy nút gốc
    // treeNode* getRoot() {
    //     return root;
    // }
    
    void updateRoot() {
        for (int i = 0; i < NODES_SIZE; ++i) {
            if (nodeList[i] != nullptr && !isChild[i]) {
                root = nodeList[i];
                return;
            }
        }
    }

    // Thêm con vào node hiện tại
    void addChild (int parent, int child) {
        // kiểm tra xem một node đã tồn tại trong nodeList hay chưa
        if (!nodeList[parent]) nodeList[parent] = new treeNode(parent);
        if (!nodeList[child]) nodeList[child] = new treeNode(child);

        // lấy node từ trong nodeList
        treeNode* parentNode = nodeList[parent];
        treeNode* childNode = nodeList[child];

        // nếu con cả bằng nullptr thì childNode được gán là con cả
        if (parentNode->firstChild == nullptr) {
            parentNode->firstChild = childNode;
        }
        // nếu con cả trong gia đình tồn tại thì thêm anh em vào 
        else {
            // duyệt danh sách các con để add newNode vào cuối
            treeNode* temp = parentNode->firstChild;
            while (temp->nextSibling != nullptr){
                temp = temp->nextSibling;
            }
            temp->nextSibling = childNode; // thêm vào đuôi
        }
        isChild[child] = true;
        updateRoot();
    }
    
    // Hàm tính chiều cao của cây
    int calculateHeight (treeNode* node) {
        // điều kiện dừng của hàm đệ quy
        if (node == nullptr) return 0;
        
        int maxHeight = 0; // khởi tạo biến đếm chiều cao của cây
        
        // duyệt danh sách các con của parent
        treeNode* child = node->firstChild;
        while (child != nullptr) {
            // gọi hàm đệ quy
            int height = calculateHeight(child);
            
            // Nếu chiều cao của cây con hiện tại lớn hơn chiều cao lớn nhất đã tìm thấy trước đó,
            // => cập nhật lại chiều cao lớn nhất.
            if (height > maxHeight) maxHeight = height; 
            
            // next
            child = child->nextSibling;
        }
        
        return maxHeight+1;
    }
    
    int getHeight() {
        return calculateHeight(root) - 1;
    }

    // Hàm duyệt cây theo thứ tự tiền tự (Preorder Traversal - NLR)
    // Quy tắc duyệt: Gốc → Trái → Phải
    void getPreorderTraversal(treeNode* node) {
        // Điều kiện dừng: Nếu node là nullptr (cây rỗng hoặc duyệt hết cây con), thoát khỏi hàm
        if (!node) return;

        // 1. Xử lý node hiện tại trước (N - Node)
        cout << node->data << " ";

        // 2. Duyệt qua danh sách các con của node hiện tại (L - Left)
        treeNode* child = node->firstChild;
        while (child) {
            getPreorderTraversal(child);  // Gọi đệ quy để duyệt từng cây con
            child = child->nextSibling;   // Chuyển sang anh chị em tiếp theo (R - Right)
        }
    }

    // Hàm gọi duyệt cây theo Preorder
    void preorderTraversal() {
        getPreorderTraversal(root);
        cout << endl;
    }

    // Hàm duyệt cây theo thứ tự hậu tự (Postorder Traversal - LRN)
    // Quy tắc duyệt: Trái → Phải → Gốc
    void getPostorderTraversal(treeNode* node) {
        // Điều kiện dừng: Nếu node là nullptr, thoát khỏi hàm
        if (!node) return;

        // 1. Duyệt danh sách cây con trước (L - Left)
        treeNode* child = node->firstChild;
        while (child) {
            getPostorderTraversal(child);
            child = child->nextSibling; // Chuyển sang anh chị em tiếp theo (R - Right)
        }

        // 2. Xử lý node hiện tại (N - Node)
        cout << node->data << " ";
    }

    // Hàm gọi duyệt cây theo Postorder từ gốc
    void postorderTraversal() {
        getPostorderTraversal(root);
        cout << endl;
    }

    bool checkBinaryTree(treeNode* node) {
        /*
            true: là cây nhị phân
            false: không phải cây nhị phân
        */
        // điều kiện dừng của hàm đệ quy, nếu node rỗng thì trả về true 
        if (node == nullptr) return true;
        
        treeNode* child = node->firstChild;
        int childCount = 0;
        
        while (child != nullptr) {
            childCount++; /// đếm số lượng con của node hiện tại
            
            // nhiều hơn 2 con thì k phải cây nhị phân
            if (childCount > 2) return false;
            
            // kiểm tra đệ quy các anh chị và con của child
            if (checkBinaryTree(child) == false) return false;
            
            child = child->nextSibling;
        }
        return true; // nếu k trả về false thì nó là cây nhị phân
    }
    
    bool isBinaryTree(){
        return checkBinaryTree(root);
    }
    
    // Hàm duyệt cây theo thứ tự trung tự (Inorder Traversal)
    // Quy tắc duyệt: Trái -> Gốc → Phải
    void getInorderTraversal(treeNode* node){
        // Điều kiện dừng: Nếu node là nullptr, thoát khỏi hàm
        if (!node) return;
        
        // đi thẳng đến con cả lá đầu tiên - bên trái
        if (node->firstChild != nullptr){
            getInorderTraversal(node->firstChild);
        }
        
        // xử lý node hiện tại - gốc
        cout << node->data << " ";
        
        // duyệt đến node nextSibling tiếp theo - bên phải
        if ((node->firstChild != nullptr) && (node->firstChild->nextSibling != nullptr)) {
            getInorderTraversal(node->firstChild->nextSibling);
        }
    }
    
    void inorderTraversal () {
        if (isBinaryTree() == true) {
            getInorderTraversal(root);
            cout << endl;
        }
        else {
            cout << "NOT BINARY TREE" << endl;
            return;
        }
    }
    
};

int main() {
    
    int N, M;
    cin >> N >> M; cin.ignore();
    
    Tree myTree; // khai báo cây
    treeNode* nodeList[N] = {nullptr}; // Mảng lưu trữ các node
    bool isChild[N] = {false}; // Mảng đánh dấu các node con

    
    // Đọc input và xây dựng cây
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        myTree.addChild(u, v);
    }
    
    cout << myTree.getHeight() << endl;
    
    myTree.preorderTraversal();
    myTree.postorderTraversal();
    myTree.inorderTraversal();
    
    return 0;
}
