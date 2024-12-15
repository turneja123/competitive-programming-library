//https://atcoder.jp/contests/abc384/tasks/abc384_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

long long a[N];
long long b[N];
long long ans[N];

long long vala[N];
long long valb[N];
int inda[N];
int indb[N];

pair<int, int> compr[N];

struct BIT {
    int n;
    vector<long long> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    BIT(int _n, vector<int> &a) {
        n = _n;
        t.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            t[i] += a[i - 1];
            int j = i + (i & -i);
            if (j <= n) {
                t[j] += t[i];
            }
        }
    }
    void upd(int i, long long val) {
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
        }
    }
    void upd(int l, int r, long long val) {
        upd(l, val);
        upd(r + 1, -val);
    }
    long long query(int i) {
        long long ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
    long long query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

inline int64_t hilbert(int x, int y, int pow, int rot) {
	if (pow == 0) {
		return 0;
	}
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rot) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rot + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = hilbert(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}

bool comp(tuple<int, int, int, int64_t> a, tuple<int, int, int, int64_t> b) {
    int64_t h1 = get<3>(a);
    int64_t h2 = get<3>(b);
    return h1 < h2;
}

tuple<int, int, int, long long> queries[N];

int main() {
    IOS;
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        vala[i] = a[i];
        compr[i] = make_pair(a[i], i);
    }
    sort(compr, compr + n);
    vector<int> sorteda{compr[0].first};
    int ma = 0;
    for (int i = 0; i < n; i++) {
        if (i > 0 && compr[i].first > compr[i - 1].first) {
            sorteda.push_back(compr[i].first);
            ma++;
        }
        a[compr[i].second] = ma;
    }
    ma++;
    BIT cta = BIT(ma), suma = BIT(ma);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        valb[i] = b[i];
        compr[i] = make_pair(b[i], i);
    }
    sort(compr, compr + n);
    vector<int> sortedb{compr[0].first};
    int mb = 0;
    for (int i = 0; i < n; i++) {
        if (i > 0 && compr[i].first > compr[i - 1].first) {
            sortedb.push_back(compr[i].first);
            mb++;
        }
        b[compr[i].second] = mb;
    }
    mb++;
    BIT ctb = BIT(mb), sumb = BIT(mb);
    for (int i = 0; i < n; i++) {
        inda[i] = upper_bound(sortedb.begin(), sortedb.end(), vala[i]) - sortedb.begin();
        indb[i] = upper_bound(sorteda.begin(), sorteda.end(), valb[i]) - sorteda.begin();
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        queries[i] = make_tuple(l, r, i, hilbert(l, r, 21, 0));
    }
    sort(queries, queries + q, comp);
    int l = -1;
    int r = -1;
    long long sum = 0;
    for (int i = 0; i < q; i++) {
        int cur = get<2>(queries[i]);
        int lq = get<0>(queries[i]);
        int rq = get<1>(queries[i]);
        while (r < rq) {
            r++;
            pair<long long, int> lf = make_pair(suma.query(1, indb[r]), cta.query(1, indb[r]));
            sum += valb[r] * lf.second - lf.first;
            pair<long long, int> rt = make_pair(suma.query(indb[r] + 1, ma), cta.query(indb[r] + 1, ma));
            sum += rt.first - valb[r] * rt.second;
            ctb.upd(b[r] + 1, 1);
            sumb.upd(b[r] + 1, valb[r]);
        }
        while (r > rq) {
            pair<long long, int> lf = make_pair(suma.query(1, indb[r]), cta.query(1, indb[r]));
            sum -= valb[r] * lf.second - lf.first;
            pair<long long, int> rt = make_pair(suma.query(indb[r] + 1, ma), cta.query(indb[r] + 1, ma));
            sum -= rt.first - valb[r] * rt.second;
            ctb.upd(b[r] + 1, -1);
            sumb.upd(b[r] + 1, -valb[r]);
            r--;
        }
        while (l < lq) {
            l++;
            pair<long long, int> lf = make_pair(sumb.query(1, inda[l]), ctb.query(1, inda[l]));
            sum += vala[l] * lf.second - lf.first;
            pair<long long, int> rt = make_pair(sumb.query(inda[l] + 1, mb), ctb.query(inda[l] + 1, mb));
            sum += rt.first - vala[l] * rt.second;
            cta.upd(a[l] + 1, 1);
            suma.upd(a[l] + 1, vala[l]);

        }
        while (l > lq) {
            pair<long long, int> lf = make_pair(sumb.query(1, inda[l]), ctb.query(1, inda[l]));
            sum -= vala[l] * lf.second - lf.first;
            pair<long long, int> rt = make_pair(sumb.query(inda[l] + 1, mb), ctb.query(inda[l] + 1, mb));
            sum -= rt.first - vala[l] * rt.second;
            cta.upd(a[l] + 1, -1);
            suma.upd(a[l] + 1, -vala[l]);
            l--;
        }
        ans[cur] = sum;
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
