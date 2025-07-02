//https://www.codechef.com/problems/SHOPGAMEEZ
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const long long M = 1e9 + 7;

int a[N];
bool taken[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        string s;
        cin >> s;
        reverse(s.begin(), s.end());
        int e = 0;
        while (e < k && s[e] == s[0]) {
            e++;
        }
        if (s[0] == '0') {
            reverse(a, a + n);
        }
        set<pair<int, int>> st;
        for (int i = 0; i < n; i++) {
            st.insert({a[i], i});
            if (st.size() > k) {
                st.erase(st.begin());
            }
        }
        long long sum = 0;
        for (auto [x, i] : st) {
            sum += x;
            taken[i] = true;
        }
        int j = -1, f = 0;
        for (int i = 0; i < k - e + 1; i++) {
            if (!taken[i]) {
                f = 1;
            }
            if (taken[i] && (j == -1 || a[i] < a[j])) {
                j = i;
            }
        }
        if (f) {
            cout << sum % M<< endl;
        } else {
            sum -= a[j];
            j = -1;
            for (int i = k - e + 1; i < n; i++) {
                if (!taken[i] && (j == -1 || a[i] > a[j])) {
                    j = i;
                }
            }
            sum += a[j];
            cout << sum % M << endl;
        }
        for (int i = 0; i < n; i++) {
            taken[i] = 0;
        }
    }
    return 0;
}
