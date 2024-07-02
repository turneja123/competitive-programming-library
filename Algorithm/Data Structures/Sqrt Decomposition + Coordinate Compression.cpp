//https://www.spoj.com/problems/GIVEAWAY/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 6e5 + 5;
const int SQ = 710;

int a[N];
int block[N];

vector<int> v[SQ];

tuple<int, int, int, int> queries[N];
pair<int, int> compr[N];

int main() {
	IOS;
	int n, q;
	cin >> n;
	int sz = sqrt(n), blocks = n / sz + (n % sz != 0);
	for (int i = 0; i < n; i++) {
        cin >> a[i];
        block[i] = i / sz;
        compr[i] = make_pair(a[i], i);
	}
	cin >> q;
	for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        int l, r, k;
        if (t == 0) {
            cin >> l >> r >> k;
            l--, r--;
        } else {
            cin >> l >> k;
            l--;
            r = -1;
        }
        queries[i] = make_tuple(t, l, r, k);
        compr[i + n] = make_pair(k, i + n);
	}
    sort(compr, compr + (n + q));
    int m = 0;
    for (int i = 0; i < n + q; i++) {
        if (i > 0 && compr[i].first > compr[i - 1].first) {
            m++;
        }
        if (compr[i].second < n) {
            a[compr[i].second] = m;
        } else {
            get<3>(queries[compr[i].second - n]) = m;
        }
    }
    m++;
    for (int i = 0; i < n; i++) {
        v[block[i]].push_back(a[i]);
    }
    for (int i = 0; i < blocks; i++) {
        sort(v[i].begin(), v[i].end());
    }

    for (int i = 0; i < q; i++) {
        if (get<0>(queries[i]) == 0) {
            int l = get<1>(queries[i]), r = get<2>(queries[i]), k = get<3>(queries[i]);

            int lb = block[l] + 1, rb = block[r] - 1;
            int ans = 0;
            for (int b = lb; b <= rb; b++) {
                ans += v[b].size() - (lower_bound(v[b].begin(), v[b].end(), k) - v[b].begin());
            }
            for (int j = l; j < min(r, sz * lb); j++) {
                ans += (a[j] >= k);
            }
            for (int j = max(min(r, sz * lb), sz * (rb + 1)); j <= r; j++) {
                ans += (a[j] >= k);
            }
            cout << ans << endl;

        } else {
            int j = get<1>(queries[i]), k = get<3>(queries[i]);
            int b = block[j];
            int pos = lower_bound(v[b].begin(), v[b].end(), a[j]) - v[b].begin();
            v[b][pos] = k;
            a[j] = k;
            sort(v[b].begin(), v[b].end());
        }
    }
	return 0;
}
