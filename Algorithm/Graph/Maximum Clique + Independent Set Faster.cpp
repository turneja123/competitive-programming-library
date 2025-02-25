//https://judge.yosupo.jp/problem/maximum_independent_set
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 151;

struct Vertex {
    int i, d = 0;
};

struct Clique {
    double lim = 0.025, p = 0;
    vector<Vertex> V;
    vector<bitset<N>> e;
    vector<vector<int>> C;
    vector<int> qmax, q, S, old;

    void init(vector<Vertex> &r) {
        for (auto &v : r) {
            v.d = 0;
            for (auto j : r) {
                v.d += e[v.i][j.i];
            }
        }
        sort(r.begin(), r.end(), [](auto a, auto b) {
            return a.d > b.d;
        });
        int mx = r[0].d;
        for (int i = 0; i < r.size(); i++) {
            r[i].d = min(i, mx) + 1;
        }
    }

    void calc(vector<Vertex> &R, int lev = 1) {
        S[lev] += S[lev - 1] - old[lev];
        old[lev] = S[lev - 1];
        while (R.size()) {
            if (q.size() + R.back().d <= qmax.size()) {
                return;
            }
            q.push_back(R.back().i);
            vector<Vertex> T;
            for (auto v : R) {
                if (e[R.back().i][v.i]) {
                    T.push_back({v.i});
                }
            }
            if (T.size()) {
                if (S[lev]++ / ++p < lim) {
                    init(T);
                }
                int j = 0, mxk = 1, mnk = max((int)qmax.size() - (int)q.size() + 1, 1);
                C[1].clear(), C[2].clear();
                for (auto v : T) {
                    int k = 1;
                    auto f = [&](int i) {
                        return e[v.i][i];
                    };
                    while (any_of(C[k].begin(), C[k].end(), f)) {
                        k++;
                    }
                    if (k > mxk) {
                        mxk = k, C[mxk + 1].clear();
                    }
                    if (k < mnk) {
                        T[j++].i = v.i;
                    }
                    C[k].push_back(v.i);
                }
                if (j > 0) {
                    T[j - 1].d = 0;
                }
                for (int k = mnk; k <= mxk; k++) {
                    for (int i : C[k]) {
                        T[j].i = i, T[j++].d = k;
                    }
                }
                calc(T, lev + 1);
            } else if (q.size() > qmax.size()) {
                qmax = q;
            }
            q.pop_back(), R.pop_back();
        }
    }

    Clique(vector<bitset<N>> g) : e(g), C(e.size() + 1), S(C.size()), old(S) {
        for (int i = 0; i < e.size(); i++) {
            V.push_back({i});
        }
        init(V);
        calc(V);
    }

};

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    vector<bitset<N>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].set(v);
        adj[v].set(u);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            adj[i][j] = !adj[i][j];
        }
    }
    Clique c(adj);
    vector<int> ans = c.qmax;
    cout << ans.size() << endl;
    for (int x : ans) {
        cout << x << " ";
    }


    return 0;
}
