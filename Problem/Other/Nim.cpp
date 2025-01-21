//https://dmoj.ca/problem/yac9p2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            ans ^= (a == 1 ? 1 : 0);
        }
        if (ans) {
            cout << "Josh" << endl;
        } else {
            cout << "Mike" << endl;
        }
    }
    return 0;
}
