/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
using namespace std;

/*

    function partition (arr[], left, right)
    	pivot <- arr[right]
    	i <- left-1
    	
    	for j from left to right
    		if arr[j] < pivot
    			i++;
    			swap (arr[i], arr[j])
    	
    	swap (arr[i+1], arr[right])
    
    	return i+1;
    
    function quickSort (arr[], left, right)
    	if left >= right
    		return
    	
    	pivotID <- partition (arr, left, right)
    	
    	quickSort (arr, left, pivotID-1)
    	quickSort (arr, pivotID+1, right)

*/

// Hàm phân hoạch của Lomuto
int Partition_Lomuto (int arr[], int left, int right) {
    int piv = arr[right];   // Chọn phần tử cuối cùng làm pivot 
    int i   = left-1;       // i là chỉ số của phần tử nhỏ hơn pivot, duyệt từ left sang
    
    // Duyệt qua các phần tử từ left đến right - 1
    for (int j=left; j<right; j++) {
        if (arr[j] <= piv) {// Nếu phần tử nhỏ hơn hoặc bằng pivot
            i++;            // Tăng i lên
            swap(arr[i], arr[j]); // (swap arr[i] và arr[j])
        }
    }
    
    // Đưa pivot về đúng vị trí (sau các phần tử nhỏ hơn nó)
    swap (arr[i+1], arr[right]);
    
    // Trả về vị trí của pivot sau khi phân hoạch
    return i+1;
}

// Hàm sắp xếp QuickSort đệ quy
void QuickSortL (int arr[], int left, int right) {
    // Trường hợp cơ sở: đoạn con có 0 hoặc 1 phần tử
    if (left >= right) return;
    
    int pivotID = Partition_Lomuto(arr, left, right); // Phân hoạch và lấy chỉ số pivot
    
    // Gọi đệ quy sắp xếp 2 nửa bên trái và bên phải pivot
    QuickSortL(arr, left, pivotID-1);
    QuickSortL(arr, pivotID+1, right);
}

// -------------------------------------------------------------------------------------

/*
    function partition (arr[], left, right)
    	pivot <- arr[left]
    	i <- left-1
    	j <- right+1
    	
    	while(true)
    		while(arr[++i] < pivot)
    		
    		while(arr[++j] > pivot)
    		
    		if i>=j
    			return j
    		
    		swap(arr[i], arr[j])
    
    function quickSort (arr[], left, right0
    	if left>=right
    		return
    
    	pavotID = partition (arr, left, right)
    	
    	quickSort(arr, left, pivotID)
    	quickSort(arr, pivotID+1, right)

*/

int Partition_Hoare (int arr[], int left, int right) {
    int piv = arr[left]; // Chọn pivot là phần tử đầu
    int i   = left - 1;  // duyệt từ trái
    int j   = right + 1; // duyệt từ phải
    
    while(true) {
        // Tăng i đến khi arr[i] < pivot
        do {i++;} while (arr[i] < piv);
        
        // Tăng i đến khi arr[i] > pivot
        do {j--;} while (arr[j] > piv);
        
        // Nếu i >= j thì dừng phân hoạch
        if (i >= j) return j;
        
        // Nếu chưa giao nhau, đổi chỗ phần tử bị sai (cặp nghịch thể)
        swap (arr[i], arr[j]);
    }
}

void QuickSortH (int arr[], int left, int right) {
    // Trường hợp cơ sở: đoạn con có 0 hoặc 1 phần tử
    if (left >= right) return;
    
    int pivotID = Partition_Hoare(arr, left, right); // Phân hoạch và lấy chỉ số pivot
    
    // Gọi đệ quy sắp xếp 2 nửa bên trái và bên phải pivot
    QuickSortH(arr, left, pivotID);
    QuickSortH(arr, pivotID+1, right);
}

// -------------------------------------------------------------------------------------

int main()
{
    int my_arr[7] = {9, 3 , 1 , 2, 4 , 5, -1};
    
    QuickSortL(my_arr, 0, 7);
    
    for (int i=0; i<7; i++){
        cout << my_arr[i] << " ";
    }
    
    // cout << "Hello World" << endl;

    return 0;
}