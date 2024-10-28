//https://codeforces.com/contest/2026/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;

bool b[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        stack<int> zero, one, need;
        for (int i = 1; i <= n; i++) {
            if (s[i - 1] == '0') {
                zero.push(i);
            }
            need.push(i);
        }
        for (int i = n; i >= 0; i--) {
            if (s[i - 1] == '1') {
                one.push(i);
            }
        }
        long long ans = 0;
        for (int i = n; i >= 1; i--) {
            if (s[i - 1] == '0') {
                continue;
            }
            while (zero.size() && zero.top() >= i) {
                zero.pop();
            }
            while (zero.size() && b[zero.top()]) {
                zero.pop();
            }
            while (need.size() && need.top() > i) {
                need.pop();
            }
            while (need.size() && b[need.top()]) {
                need.pop();
            }
            if (zero.size() && need.size()) {
                int x = zero.top(), y = need.top();
                b[x] = true, b[y] = true;
                zero.pop(), need.pop();
                ans += x;
            } else if (one.size() && need.size() && one.top() < need.top()) {
                int x = one.top(), y = need.top();
                b[x] = true, b[y] = true;
                one.pop(), need.pop();
                ans += x;
            }
        }
        for (int i = 1; i <= n; i++) {
            if (!b[i]) {
                ans += i;
            } else {
                b[i] = false;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
