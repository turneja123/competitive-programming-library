//https://qoj.ac/contest/636/problem/1644
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


int main() {
    IOS;
    string s;
    cin >> s;
    int n = s.size();
    int ct = 0; ll sum = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            ct++;
        }
    }
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            ct--;
        } else {
            sum += ct;
        }
    }
    if (sum % 3 == 0) {
        cout << "Bob";
    } else {
        cout << "Alice";
    }


    return 0;
}
