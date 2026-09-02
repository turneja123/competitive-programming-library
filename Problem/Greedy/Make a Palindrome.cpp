//https://codeforces.com/contest/2124/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int freq[N];
int add[N];

int is_palindrome(vector<int> v) {
    int n = v.size();
    for (int i = 0; i < n / 2; i++) {
        if (v[i] != v[v.size() - 1 - i]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        k--;
        for (int i = 0; i <= n; i++) {
            freq[i] = 0;
            add[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
            freq[a[i]]++;
        }
        if (k == 0) {
            cout << "YES" << endl;
            continue;
        }
        int j = 0, s = 0;
        while (s <= k) {
            s += freq[j];
            j++;
        }
        j--;
        s -= freq[j];
        int need = k - s;

        int ct = 0;
        vector<int> v;
        for (int i = 0; i < n; i++) {
            if (a[i] < j) {
                v.push_back(a[i]);
                ct++;
            } else if (a[i] == j) {
                add[ct]++;
            }
        }
        if (v.empty()) {
            cout << "YES" << endl;
            continue;
        }
        if (!is_palindrome(v)) {
            cout << "NO" << endl;
            continue;
        }
        int m = v.size();
        if (m % 2 == 0) {
            need -= add[m / 2];
        }

        for (int i = 0; i < m; i++) {
            int j = m - i;
            if (i >= j) {
                break;
            }
            need -= 2 * min(add[i], add[j]);
        }
        if (need <= 0) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }

    }
    return 0;
}
