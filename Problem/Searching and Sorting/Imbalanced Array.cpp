//https://codeforces.com/problemset/problem/817/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int a[N];
int l_big[N], r_big[N];
int l_small[N], r_small[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    stack<int> s;
    for (int i = 0; i < n; i++) {
        while (s.size() && a[s.top()] < a[i]) {
            r_big[s.top()] = i - 1;
            s.pop();
        }
        s.push(i);
    }
    while (s.size()) {
        r_big[s.top()] = n - 1;
        s.pop();
    }
    for (int i = n - 1; i >= 0; i--) {
        while (s.size() && a[s.top()] <= a[i]) {
            l_big[s.top()] = i + 1;
            s.pop();
        }
        s.push(i);
    }
    while (s.size()) {
        l_big[s.top()] = 0;
        s.pop();
    }

    for (int i = 0; i < n; i++) {
        while (s.size() && a[s.top()] > a[i]) {
            r_small[s.top()] = i - 1;
            s.pop();
        }
        s.push(i);
    }
    while (s.size()) {
        r_small[s.top()] = n - 1;
        s.pop();
    }
    for (int i = n - 1; i >= 0; i--) {
        while (s.size() && a[s.top()] >= a[i]) {
            l_small[s.top()] = i + 1;
            s.pop();
        }
        s.push(i);
    }
    while (s.size()) {
        l_small[s.top()] = 0;
        s.pop();
    }

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += (long long)a[i] * (i - l_big[i] + 1) * (r_big[i] - i + 1) - (long long)a[i] * (i - l_small[i] + 1) * (r_small[i] - i + 1);
    }
    cout << ans << endl;

    return 0;
}
