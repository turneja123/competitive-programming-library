//https://atcoder.jp/contests/abc367/tasks/abc367_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];

vector<int> apply(vector<int> a, vector<int> x) {
    int n = a.size();
    vector<int> ans(n, 0);
    for (int i = 0; i < n; i++) {
        ans[i] = a[x[i]];
    }
    return ans;
}

vector<int> expo(vector<int> a, int n, long long y) {
    vector<int> id;
    for (int i = 0; i < n; i++) {
        id.push_back(i);
    }
    while (y > 0) {
        if (y % 2 != 0) {
            id = apply(id, a);
        }
        y /= 2;
        a = apply(a, a);
    }
    return id;
}

int main() {
    IOS;
    int n; long long k;
    cin >> n >> k;
    vector<int> p(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    p = expo(p, n, k);
    for (int i = 0; i < n; i++) {
        cout << a[p[i]] << " ";
    }

    return 0;
}
