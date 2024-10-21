//https://codeforces.com/contest/2024/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

pair<int, int> a[N];

int calc_val(pair<int, int> a) {
    int val = 0;
    val += a.first;
    val += a.second;
    return val;
}

bool comp(pair<int, int> a, pair<int, int> b) {
    return calc_val(a) < calc_val(b);
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i].first >> a[i].second;
        }
        sort(a, a + n, comp);
        for (int i = 0; i < n; i++) {
            cout << a[i].first << " " << a[i].second << " ";
        }
        cout << endl;
    }


    return 0;
}
