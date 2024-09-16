//https://dmoj.ca/problem/bts24p5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 5e5 + 5;
const int SQ = 600;

int a[N];
int ans[N];
int val[N];
int block[N];
int iter[N];

vector<int> pos[N];
vector<int> heavy;

vector<tuple<int, int, int>> light_queries[SQ];
vector<tuple<int, int, int, int>> heavy_queries;


int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        pos[a[i]].push_back(i);
    }
    for (int i = 0; i < n; i++) {
        if (pos[i].size() >= SQ) {
            heavy.push_back(i);
        }
    }
    for (int i = 0; i < q; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        l--, r--;
        if (k < SQ) {
            light_queries[k].push_back(make_tuple(l, r, i));
        } else {
            heavy_queries.push_back(make_tuple(l, r, k, i));
        }
    }
    for (int k = 1; k < SQ; k++) {
        if (light_queries[k].size() == 0) {
            continue;
        }
        for (int i = 0; i < n / SQ + 5; i++) {
            block[i] = N;
        }
        for (int i = 0; i < n; i++) {
            val[i] = N;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < pos[i].size(); j++) {
                if (j + k - 1 >= pos[i].size()) {
                    break;
                }
                val[pos[i][j]] = pos[i][j + k - 1];
                int ind = pos[i][j] / SQ;
                block[ind] = min(block[ind], pos[i][j + k - 1]);
            }
        }
        for (int i = 0; i < light_queries[k].size(); i++) {
            int l = get<0>(light_queries[k][i]), r = get<1>(light_queries[k][i]);

            int lb = l / SQ + 1, rb = r / SQ - 1;
            int mn = N;
            for (int b = lb; b <= rb; b++) {
                mn = min(mn, block[b]);
            }
            if (block[l / SQ] <= r) {
                for (int j = l; j < min(r, SQ * lb); j++) {
                    mn = min(mn, val[j]);
                }
            }
            if (block[r / SQ] <= r) {
                for (int j = max(min(r, SQ * lb), SQ * (rb + 1)); j <= r; j++) {
                    mn = min(mn, val[j]);
                }
            }
            if (mn > r) {
                mn = -2;
            }
            ans[get<2>(light_queries[k][i])] = mn;
        }

    }
    sort(heavy_queries.begin(), heavy_queries.end());

    int j = 0;
    for (int i = 0; i < heavy_queries.size(); i++) {
        int l = get<0>(heavy_queries[i]), r = get<1>(heavy_queries[i]), k = get<2>(heavy_queries[i]);
        while (j < l) {
            iter[a[j]]++;
            j++;
        }
        int mn = N;
        for (int p = 0; p < heavy.size(); p++) {
            int e = heavy[p], ind = iter[e] + k - 1;
            if (ind < pos[e].size()) {
                mn = min(mn, pos[e][ind]);
            }
        }
        if (mn > r) {
            mn = -2;
        }
        ans[get<3>(heavy_queries[i])] = mn;
    }
    for (int i = 0; i < q; i++) {
        if (ans[i] == -2) {
            cout << -1 << endl;
        } else {
            cout << a[ans[i]] + 1 << endl;
        }
    }
    return 0;
}
