/******************************************************************************

function merge (arr[], l, m, r)
	arr_temp
	k = 0
	i = l
	j = m+1
	
	while i<=m && j<=r
		if arr[i] <= arr[j]
			arr_temp[k] = arr[i]
			k++, i++
		else
			arr_temp[k] = arr[j]
			k++, j++
	
	while i<=m
		arr_temp[k] = arr[i]
		k++, i++
	while j<=r
		arr_temp[k] = arr[j]
		k++, j++

	for t from 0 to k
		arr[l+t] = arr_temp[t]

function mergeSort (arr[], l, r)
	if l>=r
		return
	
	m = (l+r)/2
	
	mergeSort (arr, l, m)
	mergeSort (arr, m+1, r)

	merge (arr, l, m, r)

*******************************************************************************/
#include <iostream>
using namespace std;
const int sizeMAX = 100;

void merge (int arr[], int left, int mid, int right) {
    /*
        Hàm thực hiện chức năng gộp 2 mảng đã sắp xếp thành 1 mảng
        Thay vì tạo mảng mới, hàm sắp xếp thứ tự các phần tử trên chính mảng ban đầu
        
        Input:
            - arr (int):    mảng đầu vào
            - left (int):   chỉ số bên trái của mảng con cần sắp xếp (mảng bên trái)
            - mid (int):    chỉ số giữa phân chia 2 mảng con
            - right (int):  chỉ số bên phải của mảng con cần sắp xếp (mảng bên phải)
        
        Output:
            mảng con từ left đến right trong mảng ban đầu đã được sắp xếp
    */
    
    // Khởi tham số
    int arr_temp[sizeMAX]; // mảng tạm để lưu các phần tử được sắp xếp
    int k = 0;      // chỉ số của mảng tạm
    int i = left;   // chỉ số bắt đầu của mảng con bên trái
    int j = mid+1;  // chỉ số bắt đầu của mảng con bên phải
    
    // Sắp xếp các phần tử trong hai mảng con theo thứ tự
    while (i<=mid && j<=right){
        // nếu phần tử bên mảng trái tại i nhỏ hơn bên mảng phải tại j, thì i đi trước
        if (arr[i] <= arr[j]) {
            arr_temp[k] = arr[i];
            k++; i++; // cập nhật index
        }
        // ngược lại, j đi trước
        else {
            arr_temp[k] = arr[j];
            k++; j++; // cập nhật index
        }
    }
    
    // Kiểm tra các phần tử còn lại
    while (i <= mid) { // mảng bên trái
        arr_temp[k] = arr[i];
        k++, i++;
    }
    while (j <= right) { // mảng bên phải
        arr_temp[k] = arr[j];
        k++; j++;
    }
    
    // Chép lại mảng đã sắp xếp vào mảng ban đầu
    for (int t=0; t<k; t++){
        arr[left+t] = arr_temp[t];
    }
}

void mergeSort(int arr[], int left, int right) {
    /*
        Hàm gọi đệ quy mergeSort, điều kiện dừng là duyệt đến khi left và right chạm nhau.
    */
    
    if (left >= right) return;
    
    int mid = (left + right) / 2;
    
    mergeSort(arr, left, mid); // gọi đệ quy bên trái
    mergeSort(arr, mid+1, right); // gọi đệ quy bên phải
    merge(arr, left, mid, right); // gộp 2 mảng đã sắp xếp
}

int main()
{
    const int SIZE = 8;
    int arr[SIZE] = {38, 27, 43, 3, 9, 82, 10, 1};

    cout << "Mang ban dau: ";
    for (int i = 0; i < SIZE; ++i) cout << arr[i] << " ";
    cout << endl;

    mergeSort(arr, 0, SIZE - 1);

    cout << "Mang sau khi sap xep: ";
    for (int i = 0; i < SIZE; ++i) cout << arr[i] << " ";
    cout << endl;

    return 0;
}