//solution for http://algoge.com/problem/karantin_2_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;

int s[N];
int a[N];
int seg[2 * N];
vector<int> pos[N];

void build(int n) {
    for (int i = 0; i < n; i++) {
        seg[i + n] = a[i];
    }
    for (int i = n - 1; i > 0; i--) {
        seg[i] = max(seg[2 * i], seg[2 * i + 1]);
    }
}

void update(int ind, int val, int n) {
    ind += n;
    seg[ind] = val;
    while (ind > 1) {
        ind /= 2;
        seg[ind] = max(seg[2 * ind], seg[2 * ind + 1]);
    }
}

int rmq(int l, int r, int n) {
    l += n;
    r += n;
    int mx = 0;
    while (l < r) {
        if (r % 2 == 1) {
            mx = max(mx, seg[--r]);
        }
        if (l % 2 == 1) {
            mx = max(mx, seg[l++]);
        }
        l /= 2;
        r /= 2;
    }
    return mx;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        pos[s[i]].push_back(i);
    }
    for (int i = 0; i < n; i++) {
        a[i] = pos[s[i]][pos[s[i]].size() - 1];
    }
    build(n);
    bool flag = false;
    pair<int, int> ans = {1e9, 1e9};
    for (int e = 0; e < N; e++) {
        if (pos[e].size() < 2) {
            continue;
        }
        for (int i = 1; i < pos[e].size(); i++) {
            rep:;
            int q = rmq(pos[e][0] + 1, pos[e][i], n);
            if (q > pos[e][i]) {
                int b = s[q];
                ans = min(ans, {e, b});
                flag = true;
                for (int j = 0; j < pos[b].size(); j++) {
                    update(pos[b][j], -1, n);
                }
                goto rep;
            }
            update(pos[e][i], -1, n);
        }
        if (flag) {
            break;
        }
        for (int i = 1; i < pos[e].size(); i++) {
            update(pos[e][i], *pos[e].rbegin(), n);
        }
    }
    if (!flag) {
        cout << -1 << endl;
    } else {
        cout << ans.first << " " << ans.second << endl;
    }

    return 0;
}
