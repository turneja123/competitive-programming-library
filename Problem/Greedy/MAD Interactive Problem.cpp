//https://codeforces.com/contest/2159/problem/A
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

//#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


int main() {
    //IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> ans(2 * n, -1);
        vector<int> st, v;
        for (int i = 0; i < 2 * n; i++) {
            cout << "? " << st.size() + 1 << " ";
            for (int j : st) {
                cout << j + 1 << " ";
            }
            cout << i + 1 << " ";
            cout << endl;
            int x;
            cin >> x;
            if (x == 0) {
                st.push_back(i);
            } else {
                ans[i] = x;
                v.push_back(i);
            }
        }
        for (int i = 0; i < 2 * n; i++) {
            if (ans[i] == -1) {
                cout << "? " << v.size() + 1 << " ";
                for (int j : v) {
                    cout << j + 1 << " ";
                }
                cout << i + 1 << " ";
                cout << endl;
                int x;
                cin >> x;
                ans[i] = x;
            }
        }
        cout << "! ";
        for (int i = 0; i < 2 * n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
