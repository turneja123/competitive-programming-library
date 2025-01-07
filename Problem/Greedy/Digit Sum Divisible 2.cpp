//https://atcoder.jp/contests/abc387/tasks/abc387_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int brute(int n) {
    int s = 0;
    while (n > 0) {
        s += n % 10;
        n /= 10;
    }
    return s;
}


int main() {
    IOS;
    string s;
    cin >> s;
    if (s.size() < 7) {
        int n = stoi(s);
        for (int x = n; x + 1 <= 2 * n; x++) {
            if (x % brute(x) == 0 && (x + 1) % brute(x + 1) == 0) {
                cout << x;
                return 0;
            }
        }
        cout << -1;
        return 0;
    }
    int ct = 0;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            ct++;
        }
    }
    if (s[0] == '1' && ct == n - 1) {
        cout << 1;
        for (int i = 1; i < n - 2; i++) {
            cout << 0;
        }
        cout << 10;
        return 0;
    }
    if (s[0] == '1') {
        cout << 2;
        for (int i = 1; i < n; i++) {
            cout << 0;
        }
        return 0;
    }
    if (s[0] == '2') {
        cout << 3;
        for (int i = 1; i < n - 2; i++) {
            cout << 0;
        }
        cout << 32;
        return 0;
    }
    if (s[0] == '3') {
        cout << 4;
        for (int i = 1; i < n - 2; i++) {
            cout << 0;
        }
        cout << 40;
        return 0;
    }
    if (s[0] == '4') {
        cout << 5;
        for (int i = 1; i < n - 3; i++) {
            cout << 0;
        }
        cout << 120;
        return 0;
    } else if (s[0] == '5') {
        cout << 6;
        for (int i = 1; i < n - 3; i++) {
            cout << 0;
        }
        cout << 200;
        return 0;
    }
    n++;
    cout << 1;
    for (int i = 1; i < n - 2; i++) {
        cout << 0;
    }
    cout << 10;
    return 0;
}
