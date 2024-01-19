#include <bits/stdc++.h>
using namespace std;

string s;

void sinh_ke_tiep(){
    int i = s.length() - 1;
    while (i >= 0 && s[i] == '1'){
        s[i] = '0';
        i--;
    }
    // nếu không tìm thấy '1' thì thêm '1' vào đầu xâu
    if (i != -1){
        s[i] = '1';
    }
    cout << s << endl;
}

int main (){
    int t;
    cin >> t;
    while (t--){
        cin >> s;
            sinh_ke_tiep();
    }
}