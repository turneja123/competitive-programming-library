//https://www.spoj.com/problems/HISTOGRA/
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

int main() {
    IOS;
    int n;
    cin >> n;
    while (n != 0) {
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        stack<int> s;
        for (int i = 0; i < n; i++) {
            while (s.size() && a[s.top()] > a[i]) {
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
            while (s.size() && a[s.top()] > a[i]) {
                l[s.top()] = i + 1;
                s.pop();
            }
            s.push(i);
        }
        while (s.size()) {
            l[s.top()] = 0;
            s.pop();
        }
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, (long long)a[i] * (r[i] - l[i] + 1));
        }
        cout << ans << endl;
        cin >> n;
    }
    return 0;
}
