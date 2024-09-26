//https://atcoder.jp/contests/abc372/tasks/abc372_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;

int a[N];
int ans[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    stack<int> s;
    for (int i = n - 1; i >= 0; i--) {
        ans[i] = s.size();
        while (s.size() && s.top() < a[i]) {
            s.pop();
        }
        s.push(a[i]);
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}
