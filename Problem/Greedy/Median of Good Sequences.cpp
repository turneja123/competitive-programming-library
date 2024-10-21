//https://atcoder.jp/contests/arc183/tasks/arc183_a
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    /*vector<int> v;
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            v.push_back(i);
        }
    }
    do {
        ans.push_back(v);

    } while (next_permutation(v.begin(), v.end()));

    for (int x : ans[(ans.size() - 1) / 2]) {
        cout << x + 1 << " ";
    }*/
    if (n % 2 == 0) {
        int mid = n / 2;
        cout << mid << " ";
        for (int i = n; i >= 1; i--) {
            int j = 0;
            if (i == mid) {
                j = 1;
            }
            for (; j < k; j++) {
                cout << i << " ";
            }
        }
    } else {
        int mid = n / 2 + 1;
        for (int j = 0; j < k; j++) {
            cout << mid << " ";
        }
        if (n != 1) {
            cout << mid - 1 << " ";
        }
        for (int i = n; i >= 1; i--) {
            int j = 0;
            if (i == mid) {
                j = k;
            } else if (i == mid - 1) {
                j = 1;
            }
            for (; j < k; j++) {
                cout << i << " ";
            }
        }
    }
    /*5 2
3 3 2 5 5 4 4 2 1 1*/
    /*4 3
2 4 4 4 3 3 3 2 2 1 1 1*/
    return 0;
}
