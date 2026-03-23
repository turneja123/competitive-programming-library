//https://codeforces.com/contest/1767/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;
const int SQ = 635;
const int S = 10000;


struct Info {
    int la;
    int ra;
    int lb;
    int rb;
    int ind;

};

int a[N];
int freq[N];
int tot[N];
int is_heavy[N];
Info queries[N];
int ans[N];
int bl[SQ][SQ];

int freq_ct[N];
int ct = 0;

bool comp(Info &a, Info &b) {
    if (a.la / S != b.la / S) {
        return a.la / S < b.la / S;
    }
    if (a.ra / S != b.ra / S) {
        return a.ra / S < b.ra / S;
    }
    if (a.lb / S != b.lb / S) {
        return a.lb / S < b.lb / S;
    }
    return a.rb < b.rb;
}

int ord[N];
int sz[N];
int pos[N];
vector<int> adj[N];

int timer = 0;

void dfs(int u, int p) {
    ord[timer] = a[u];
    pos[u] = timer;
    timer++;
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            sz[u] += sz[v];
        }
    }

}

void add(int x) {
    if (freq[x] == ct) {
        ct++;
    }
    freq_ct[freq[x]]--;
    if (!is_heavy[x]) {
        bl[x / SQ][freq[x]]--;
    }
    freq[x]++;
    if (!is_heavy[x]) {
        bl[x / SQ][freq[x]]++;
    }
    freq_ct[freq[x]]++;


}

void rem(int x) {
    if (freq[x] == ct && freq_ct[freq[x]] == 1) {
        ct--;
    }
    freq_ct[freq[x]]--;
    if (!is_heavy[x]) {
        bl[x / SQ][freq[x]]--;
    }
    freq[x]--;
    if (!is_heavy[x]) {
        bl[x / SQ][freq[x]]++;
    }
    freq_ct[freq[x]]++;


}

int main() {
    IOS;
    int n, q;
    cin >> n;
    vector<int> compr;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        compr.push_back(a[i]);
    }
    sort(compr.begin(), compr.end());
    compr.erase(unique(compr.begin(), compr.end()), compr.end());
    for (int i = 0; i < n; i++) {
        a[i] = lower_bound(compr.begin(), compr.end(), a[i]) - compr.begin();
        tot[a[i]]++;
    }
    vector<int> heavy;
    int m = compr.size();
    for (int i = 0; i < m; i++) {
        if (2 * tot[i] >= SQ) {
            heavy.push_back(i);
            is_heavy[i] = 1;
        }
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0);
    cin >> q;
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;

        queries[i] = {pos[u], pos[u] + sz[u] - 1, pos[v], pos[v] + sz[v] - 1, i};
    }
    sort(queries, queries + q, comp);
    int la = 0, ra = -1;
    int lb = 0, rb = -1;
    for (int i = 0; i < q; i++) {
        auto [lqa, rqa, lqb, rqb, cur] = queries[i];
        while (ra < rqa) {
            ra++;
            add(ord[ra]);
        }
        while (la > lqa) {
            la--;
            add(ord[la]);
        }
         while (rb < rqb) {
            rb++;
            add(ord[rb]);
        }
        while (lb > lqb) {
            lb--;
            add(ord[lb]);
        }

        while (ra > rqa) {
            rem(ord[ra]);
            ra--;
        }
        while (la < lqa) {
            rem(ord[la]);
            la++;
        }
        while (rb > rqb) {
            rem(ord[rb]);
            rb--;
        }
        while (lb < lqb) {
            rem(ord[lb]);
            lb++;
        }
        ans[cur] = N;
        for (int j = 0; j < SQ && ct < SQ; j++) {
            if (bl[j][ct]) {
                for (int k = 0; k < SQ && j * SQ + k < m; k++) {
                    if (freq[j * SQ + k] == ct) {
                        ans[cur] = j * SQ + k;
                        break;
                    }
                }
                break;
            }
        }
        for (int k : heavy) {
            if (freq[k] == ct) {
                ans[cur] = min(ans[cur], k);
                break;
            }
        }


    }
    for (int i = 0; i < q; i++) {
        cout << compr[ans[i]] << endl;
    }
    return 0;
}

