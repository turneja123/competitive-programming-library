//https://codeforces.com/contest/1219/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    int m;
    cin >> m;
    string s;
    cin >> s;
    int n = s.size();
    if (n % m != 0) {
        n = n / m + 1;
        string a = "1";
        for (int i = 1; i < m; i++) {
            a += '0';
        }
        for (int i = 0; i < n; i++) {
            cout << a;
        }
        return 0;
    }
    string a = "";
    for (int i = 0; i < m; i++) {
        a += s[i];
    }
    int lesser = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] != a[i % m]) {
            if (s[i] < a[i % m]) {
                lesser = 1;
            }
            break;
        }
    }
    auto plus_one = [&](string &x) -> void {
        for (int i = x.size() - 1; i >= 0; i--) {
            if (x[i] == '9') {
                x[i] = '0';
            } else {
                x[i]++;
                break;
            }
        }
    };
    int edge = !lesser;
    for (int i = 0; i < m; i++) {
        if (a[i] != '9') {
            edge = 0;
        }
    }
    if (edge) {
        n = n / m + 1;
        string a = "1";
        for (int i = 1; i < m; i++) {
            a += '0';
        }
        for (int i = 0; i < n; i++) {
            cout << a;
        }
        return 0;
    }

    if (!lesser) {
        plus_one(a);
    }
    for (int i = 0; i < n / m; i++) {
        cout << a;
    }


    return 0;
}
