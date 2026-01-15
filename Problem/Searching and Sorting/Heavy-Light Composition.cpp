//https://dmoj.ca/problem/aaaa1p2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int INF = 1e9 + 5;

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    set<int> st;
    vector<int> a, b;
    for (int i = 0; i < n; i++) {
        int f;
        cin >> f;
        st.insert(f);
        a.push_back(f);
    }
    for (int i = 0; i < m; i++) {
        int f;
        cin >> f;
        if (st.find(f) != st.end()) {
            continue;
        }
        b.push_back(f);
    }
    if (b.empty()) {
        cout << 0;
        return 0;
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    m = b.size();
    int ans = 0;
    for (int i = 0, j = 0; i < m;) {
        while (j < n && a[j] < b[i]) {
            j++;
        }
        vector<int> s;
        while (i < m && b[i] < ((j == n) ? INF : a[j])) {
            s.push_back(b[i++]);
        }

        if (j == 0) {
            ans += a[j] - s[0];
        } else if (j == n) {
            ans += s.back() - a.back();
        } else {
            int best = min(s.back() - a[j - 1], a[j] - s[0]);
            for (int i = 0; i < s.size() - 1; i++) {
                best = min(best, s[i] - a[j - 1] + a[j] - s[i + 1]);
            }
            ans += best;
        }
    }
    cout << ans;
    return 0;
}
