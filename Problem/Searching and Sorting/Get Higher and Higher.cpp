//https://www.spoj.com/problems/MAXI/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int l[N], r[N];
long long cum[2][N];
long long ans[N];

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
            r[s.top()] = i - 1;
            s.pop();
        }
        s.push(i);
    }
    while (s.size()) {
        r[s.top()] = n - 1;
        s.pop();
    }
    for (int i = n - 1; i >= 0; i--) {
        while (s.size() && a[s.top()] <= a[i]) {
            l[s.top()] = i + 1;
            s.pop();
        }
        s.push(i);
    }
    while (s.size()) {
        l[s.top()] = 0;
        s.pop();
    }

    for (int i = 0; i < n; i++) {
        int mid = min(i - l[i], r[i] - i) + 1, sz = r[i] - l[i] + 1;
        cum[0][1] += a[i], cum[0][mid + 1] -= a[i];
        cum[1][sz - mid + 1] += a[i], cum[1][sz + 1] -= a[i];
    }
    long long add = 0, sum = 0;
    for (int i = 1; i <= n; i++) {
        add += cum[0][i];
        sum += add;
        ans[i] = sum;
        add -= cum[1][i];
        cout << ans[i] << endl;
    }
    return 0;
}
