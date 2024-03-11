//solution for https://dmoj.ca/problem/utso21p2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 101;
const int M = 5001;

int a[N];

void construct(int n, int m, int diff) {
    cout << n << endl;
    int j = 0;
    int cur = 0;
    for (int i = n; i > m; i--) {
        cout << 1 << " ";
        j++;
    }
    if (j + diff != n) {
        cout << 2 << " ";
        j++;
    }
    while (diff--) {
        cout << 6 << " ";
        j++;
    }
    for (j; j < n; j++) {
        cout << 3 << " ";
    }
}

int main() {
    IOS;
    int k;
    cin >> k;
    for (int n = 1; n < N; n++) {
        int cur = 0;
        for (int m = n; m > 0; m--) {
            if (cur + m > k) {
                construct(n, m, cur + m - k - 1);
                return 0;
            }
            cur += m;
        }
        if (cur == k) {
            cout << n << endl;
            for (int i = 0; i < n; i++) {
                cout << 1 << " ";
            }
            return 0;
        }
    }
    return 0;
}
