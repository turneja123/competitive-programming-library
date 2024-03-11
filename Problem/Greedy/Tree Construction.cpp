//solution for
//https://www.hackerearth.com/practice/algorithms/graphs/depth-first-search/practice-problems/approximate/tree-construction-7b3cb288/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;


int main() {
    IOS;
    ll n, m;
    cin >> n >> m;
    if (n == 1) {
        if (m != 1) {
            cout << -1;
        }
        return 0;
    }
    if (m < 1 + 2 * (n - 1) || m > n * (n + 1) / 2) {
        cout << -1;
        return 0;
    }
    ll sum = 1;
    cout << "1 2" << endl;
    for (int i = 2; i < n; i++) {
        sum += i;
        if (m > sum + (i + 1) * (n - i)) {

            cout << i << " " << i + 1 << endl;
            continue;
        }
        ll cur = sum + i * (n - i);
        int ct = 0;
        for (int j = i + 1; j <= n; j++) {
            if (cur + ct == m) {
                break;
            }
            ct++;
        }
        int v = i + 1;
        for (int j = 0; j < ct; j++) {
            cout << i << " " << v << endl;
            v++;
        }
        for (int j = 0; j < n - i - ct; j++) {
            cout << i - 1 << " " << v << endl;
            v++;
        }
        return 0;
    }
}
