//https://basecamp.eolymp.com/en/problems/11862
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int K = 21;

int a[N];
int table[K][N];

void build(int n) {
    for (int i = 1; i <= n; i++) {
        table[0][i] = a[i - 1];
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            table[k][i] = table[k - 1][i] | table[k - 1][i + (1 << (k - 1))];
        }
    }
    return;
}

int query(int l, int r) {
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    return table[k][l] | table[k][r - (1 << k) + 1];
}

map<int, vector<int>> mp;


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        build(n);
        int s = 0;
        for (int i = n - 1; i >= 0; i--) {
            s ^= a[i];
            auto it = mp.find(s);
            if (it == mp.end()) {
                vector<int> v{i};
                mp[s] = v;
            } else {
                it->second.push_back(i);
            }
        }
        for (auto it = mp.begin(); it != mp.end(); it++) {
            sort((it->second).begin(), (it->second).end());
        }
        tuple<int, int, int> ans = {-1,-1,-1};
        s = a[0];
        for (int i = 0; i < n - 2; i++) {
            s &= a[i];
            auto it = mp.find(s);
            if (it == mp.end()) {
                continue;
            }
            int l = i + 1, r = n - 1, spl = -1;
            while (l <= r) {
                int mid = (l + r) / 2;
                int x = query(i + 1, mid);
                if (x >= s) {
                    spl = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            if (spl == -1 || query(i + 1, spl) != s) {
                continue;
            }
            l = i + 1, r = n - 1; int spl2 = -1;
            while (l <= r) {
                int mid = (l + r) / 2;
                int x = query(i + 1, mid);
                if (x <= s) {
                    spl2 = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            int p = upper_bound((it->second).begin(), (it->second).end(), spl) - (it->second).begin();
            if (p != (it->second).size() && (it->second)[p] <= spl2 + 1) {
                ans = {i, (it->second)[p] - 1, s};
                break;
            }
        }
        if (get<0>(ans) == -1) {
            cout << -1 << endl;
        } else {
            auto [l, r, x] = ans;
            cout << l + 1 << " " << r + 1 << " " << x << endl;
        }
        mp.clear();

    }
    return 0;
}
