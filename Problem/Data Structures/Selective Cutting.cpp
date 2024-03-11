//https://dmoj.ca/problem/dmopc14c2p6
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int ans[N];
int seg[2 * N];

void update(int pos, int val, int n) {
    pos += n;
    seg[pos] = val;
    while (pos > 1) {
        pos /= 2;
        seg[pos] = seg[2 * pos] + seg[2 * pos + 1];
    }
}

int rsq(int l, int r, int n) {
    l += n;
    r += n;
    int sum = 0;
    while (l < r) {
        if (r % 2 == 1) {
            sum += seg[--r];
        }
        if (l % 2 == 1) {
            sum += seg[l++];
        }
        l /= 2;
        r /= 2;
    }
    return sum;
}

map<int, vector<int>> mp;
vector<array<int, 4>> queries(N);

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        mp[a].push_back(i);
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> queries[i][2] >> queries[i][3] >> queries[i][0];
        queries[i][1] = i;
    }
    sort(queries.begin(), queries.begin() + q);
    reverse(queries.begin(), queries.begin() + q);
    auto it = mp.rbegin();
    bool flag = false;

    for (int i = 0; i < q; i++) {
        int q = queries[i][0];
        int ind = queries[i][1];
        int l = queries[i][2];
        int r = queries[i][3];
        while (!flag && it->first >= q) {
            for (int j = 0; j < it->second.size(); j++) {
                update(it->second[j], it->first, n);
            }
            ++it;
            if (it == mp.rend()) {
                flag = true;
                break;
            }
        }
        ans[ind] = rsq(l, r + 1, n);
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }


    return 0;
}
