#include <bits/stdc++.h>
using namespace std;
// A = 0
// B = 1
int n, ok = 1; 
char a[1001];

void in (){ // in ra từng phần tử của mảng
        for (int i = 0; i < n; i++){
            cout << a[i];
        }
    cout << endl;
}

void sinh (){
    int i = n - 1; // n bit
    while (i >= 0 && a[i] == 'B'){ // khi bit thứ i = 1 thì chuyển bit đó về 0 và lùi 1 bit
        a[i] = 'A';
        i--;
    }
    if (i < 0){
        ok = 0;
    }
    else {
        a[i] = 'B';
    }
}

int main (){
    int t;
    cin >> t;
    while (t--){
            cin >> n;
            ok = 1; // reset ok về 1 để nhập test case
            for (int i = 0; i < n; i++){
                a[i] = 'A'; // khởi tạo
            }
            while (ok){ // kiểm tra điều kiện lặp khi nào đúng
                in ();
                sinh ();
            }
    }
}