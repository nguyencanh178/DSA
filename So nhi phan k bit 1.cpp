#include <bits/stdc++.h>

using namespace std;

int n, ok = 1;
int a[1001];
int k;

void in (){
    for (int i = 0; i < n; i++){
        cout << a[i]; 
    }
    cout << endl;
}

void sinh (){
    int i = n - 1;
    while (i >= 0 && a[i] == 1){
        a[i] = 0;
        i--;
    }
    if (i < 0){
        ok = 0;
    }
    else {
        a[i] = 1;
    }
}

bool check (){
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum += a[i];
    }
    return sum == k;
}

int main (){
    int t;
    cin >> t;
    while (t--){
        ok = 1;
        cin >> n >> k;
        for (int i = 0; i < n; i++){
            a[i] = 0;
        }
        while (ok){
            if (check()){
                in ();
            }
            sinh ();
        }
    }
}