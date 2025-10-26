//https://dmoj.ca/problem/dmpg16g6
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 270000;
const int SQ = 200;
const int MAGIC = 5;

int a[N];
int tmp[N];
int seen[N];
int restore[N];
ll sum[N / SQ + 5][N / SQ + 5];
int freq_blk[N / SQ + 5][N / MAGIC];
int freq[N];
int tot[N];
int mp[N];
int heavy[N];

vector<int> pos[N];


int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        tot[a[i]]++;
    }
    vector<pair<int, int>> compr;
    for (int i = 0; i < N; i++) {
        if (tot[i]) {
            compr.push_back({-tot[i], i});
        }
    }
    sort(compr.begin(), compr.end());
    for (int i = 0; i < compr.size(); i++) {
        int j = compr[i].second;
        if (-compr[i].first >= MAGIC) {
            heavy[i] = true;
        }
        mp[j] = i;
    }
    for (int i = 0; i < n; i++) {
        a[i] = mp[a[i]];
        pos[a[i]].push_back(i);
    }


    vector<int> op;
    for (int i = 0; i * SQ < n; i++) {
        int idi = i, idj = i;
        ll s = 0;
        for (int j = i * SQ; j < n; j++) {
            if (i == 0) {
                if (!seen[a[j]] && heavy[a[j]]) {
                    seen[a[j]] = 1;
                    op.push_back(a[j]);
                }
            }

            s -= (ll)freq[a[j]] * freq[a[j]];
            freq[a[j]]++;
            s += (ll)freq[a[j]] * freq[a[j]];
            if ((j + 1) % SQ == 0) {
                if (i == 0) {
                    for (int k : op) {
                        freq_blk[idj][k] = freq[k];
                    }
                }
                sum[idi][idj] = s;
                idj++;
            }
        }
        for (int j = i * SQ; j < n; j++) {
            freq[a[j]] = 0;
        }
    }
    for (int k : op) {
        seen[k] = 0;
    }
    int last = 0;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l ^= last, r ^= last;
        int bl = l / SQ;
        if (l % SQ != 0) {
            bl++;
        }
        int br = r / SQ;
        if ((r + 1) % SQ != 0) {
            br--;
        }
        int m = 0;
        ll ans = 0;
        auto f = [&](int l, int r) -> void {
            for (int j = l; j < r; j++) {
                int z = 0;
                if (bl <= br) {
                    if (heavy[a[j]]) {
                        z = freq_blk[br][a[j]] - (bl == 0 ? 0 : freq_blk[bl - 1][a[j]]);
                    } else {
                        for (int &y : pos[a[j]]) {
                            if (y >= bl * SQ && y <= (br + 1) * SQ - 1) {
                                z++;
                            }
                        }
                        //z = upper_bound(pos[a[j]].begin(), pos[a[j]].end(), (br + 1) * SQ - 1) - lower_bound(pos[a[j]].begin(), pos[a[j]].end(), bl * SQ);
                    }
                }
                z += freq[a[j]];
                ans -= (ll)z * z;
                z++;
                freq[a[j]]++;
                ans += (ll)z * z;
                if (!seen[a[j]]) {
                    seen[a[j]] = true;
                    restore[m++] = a[j];
                }
            }
        };
        if (bl > br) {
            f(l, r + 1);
        } else {
            ans = sum[bl][br];
            f(l, bl * SQ);
            f((br + 1) * SQ, r + 1);
        }
        ans %= 1 << 18;
        last = ans;
        cout << ans << endl;
        for (int j = 0; j < m; j++) {
            freq[restore[j]] = 0;
            seen[restore[j]] = 0;
        }
    }


    return 0;
}
