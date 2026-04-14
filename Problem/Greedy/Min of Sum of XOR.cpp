//https://atcoder.jp/contests/arc217/tasks/arc217_a
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);



int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> ans{0};
        for (int i = 1; i < n - 1; i += 2) {
            int a = i, b = i + 1;
            if ((i / 2) % 2 == 0) {
                swap(a, b);
            }
            ans.push_back(a);
            ans.push_back(b);
        }
        if (ans.size() < n) {
            ans.push_back(n - 1);
        }
        for (int x : ans) {
            cout << x + 1 << " ";
        }
        cout << endl;
    }

    return 0;
}
