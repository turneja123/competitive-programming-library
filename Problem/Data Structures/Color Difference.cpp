//https://www.codechef.com/problems/COLDIF
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int a[N];
int freq[N];
int sz;
tuple<int, int, int> queries[N];
long long ans[N];

int ct[N];
int timer[N];

bool comp(tuple<int, int, int> a, tuple<int, int, int> b) {
    int block1 = get<0>(a) / sz;
    int block2 = get<0>(b) / sz;
    if (block1 != block2) {
        return block1 < block2;
    }
    int r1 = get<1>(a);
    int r2 = get<1>(b);
    return r1 < r2;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        sz = sqrt(n);
        if (sz * sz != n) {
            sz++;
        }
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
            timer[i] = q, freq[i] = 0, ans[i] = 0, ct[i] = 0;
        }
        for (int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            queries[i] = make_tuple(l, r, i);
        }
        sort(queries, queries + q, comp);
        int l = 0;
        int r = -1;
        for (int i = 0; i < q; i++) {
            int cur = get<2>(queries[i]);
            int lq = get<0>(queries[i]);
            int rq = get<1>(queries[i]);
            while (r < rq) {
                r++;
                freq[a[r]]++;
                if (freq[a[r]] == 1) {
                    timer[a[r]] = i;
                }
            }
            while (r > rq) {
                freq[a[r]]--;
                if (freq[a[r]] == 0) {
                    ct[a[r]] += i - timer[a[r]];
                    timer[a[r]] = q;
                }
                r--;
            }
            while (l < lq) {
                freq[a[l]]--;
                if (freq[a[l]] == 0) {
                    ct[a[l]] += i - timer[a[l]];
                    timer[a[l]] = q;
                }
                l++;
            }
            while (l > lq) {
                l--;
                freq[a[l]]++;
                if (freq[a[l]] == 1) {
                    timer[a[l]] = i;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            ct[i] += q - timer[i];
            freq[i] = 0;
        }
        l = 0, r = -1; long long sum = 0;
        for (int i = 0; i < q; i++) {
            int cur = get<2>(queries[i]);
            int lq = get<0>(queries[i]);
            int rq = get<1>(queries[i]);
            while (r < rq) {
                r++;
                freq[a[r]]++;
                if (freq[a[r]] == 1) {
                    sum += q - ct[a[r]];
                }
            }
            while (r > rq) {
                freq[a[r]]--;
                if (freq[a[r]] == 0) {
                    sum -= q - ct[a[r]];
                }
                r--;
            }
            while (l < lq) {
                freq[a[l]]--;
                if (freq[a[l]] == 0) {
                    sum -= q - ct[a[l]];
                }
                l++;
            }
            while (l > lq) {
                l--;
                freq[a[l]]++;
                if (freq[a[l]] == 1) {
                    sum += q - ct[a[l]];
                }
            }
            ans[cur] = sum;
        }

        for (int i = 0; i < q; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
    return 0;
}

