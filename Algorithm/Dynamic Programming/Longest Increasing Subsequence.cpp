//solution for https://cses.fi/problemset/task/1145
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];

int BIN(int a[], vector <int> &v, int l, int r, int k) {
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (a[v[m]] >= k) {
            r = m;
        } else {
            l = m;
        }
    }
    return r;
}

int lis(int a[], int n) {
    vector <int> cur(n, 0);
    vector <int> prev(n, -1);
    int len = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] < a[cur[0]]) {
            cur[0] = i;
        } else if (a[i] > a[cur[len - 1]]) {
            prev[i] = cur[len - 1];
            cur[len] = i;
            len++;
        } else {
            int pos = BIN(a, cur, -1, len - 1, a[i]);
            prev[i] = cur[pos - 1];
            cur[pos] = i;
        }
    }
    return len;
}

int main()
{
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cout << lis(a, n);
    return 0;

}
