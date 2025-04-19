/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
using namespace std;

// 1. Tính tổng từ 1 đến n
int getsum(int n){
    if (n==0) return 0;
    
    return n + getsum(n-1);
}

// 2. Tính giai thừa
int getFactorial (int n){
    if (n==0) return 1;
    
    return n * getFactorial(n-1);
}

// 3. Dãy Fibonacci
int getFibonacci(int n){
    if (n==0) return 0;
    else if (n==1) return 1;
    
    return getFibonacci(n-1) + getFibonacci(n-2);
}

// 4. Lũy thừa
int getPower (int x, int n){
    if (n==0) return 1;
    
    return x*getPower(x,n-1);
}

// 5. Đếm số chữ số của một số nguyên
long long countDigits (long long n ){
    if (n<10) return 1;
    
    return 1 + countDigits(n/10);
}

// 6. Tổng các chữ số của một số nguyên
int sumDigits(long long n){
    if (n<10) return n;
    
    return n%10 + sumDigits(n/10);
}

// 7. Đảo ngược một số nguyên
int reverseNumber(int n, int revNum=0){
    if (n==0) return revNum;
    
    return reverseNumber(n/10, revNum*10 + n%10);
}


int main()
{
    cout << getsum(3) << endl;
    cout << getFactorial(5) << endl;
    
    for (int i=0; i < 10; i++)
        cout << getFibonacci(i) << ", ";
    cout << endl;
    
    
    cout << getPower(4, 2) << endl;
    
    cout << countDigits(100000000000) << endl;
    cout << sumDigits(9999) << endl;
    
    cout << reverseNumber(-1234) << endl;
    
    
    return 0;
}
