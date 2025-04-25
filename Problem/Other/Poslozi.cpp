//https://dmoj.ca/problem/coci09c2p5
#pragma GCC optimize("Ofast,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 140;

int n, m;
int l[N], r[N];

unordered_map<long long, tuple<int, int, int>> mp_go;

vector<int> from_h(long long h) {
    vector<int> a;
    for (int i = 0; i < n; i++) {
        a.push_back(h % 13);
        h /= 13;
    }
    return a;
}

long long to_h(vector<int> &a) {
    long long h = 0, pw = 1;
    for (int i = 0; i < n; i++) {
        h += (long long)pw * a[i];
        pw *= 13;
    }

    return h;
}


int h1(vector<int> &a) {
    int ct = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ct += a[i] > a[j];
        }
    }
    int d = 1;
    for (int k = 0; k < m; k++) {
        swap(a[l[k]], a[r[k]]);
        int cur = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                cur += a[i] > a[j];
            }
        }
        d = max(d, ct - cur);
        swap(a[l[k]], a[r[k]]);
    }
    return (ct + d - 1) / d;
}

int h2(vector<int> &a) {
    vector<vector<int>> adj(n, vector<int>());
    for (int i = 0; i < m; i++) {
        adj[l[i]].push_back(r[i]);
        adj[r[i]].push_back(l[i]);
    }
    int s = 0, mx = 0;
    for (int i = 0; i < n; i++) {
        vector<int> dist(n, N);
        dist[i] = 0;
        queue<int> q;
        q.push(i);
        while (q.size()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (dist[v] > dist[u] + 1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        s += dist[a[i]];
        mx = max(mx, dist[a[i]]);
    }
    return max(s / 2, mx);
}

int func(vector<int> &a) {
    return max(h1(a), h2(a));
}

int main() {
    IOS;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }
    for (int i = 0; i < m; i++) {
        cin >> l[i] >> r[i];
        l[i]--, r[i]--;
    }
    long long h_start = to_h(a);
    long long h_en = 0, pw = 1;
    for (int i = 0; i < n; i++) {
        h_en += (long long)pw * i;
        pw *= 13;
    }

    priority_queue<tuple<int, int, long long>> pq;
    mp_go[h_start] = make_tuple(func(a), 0, -1);
    pq.push(make_tuple(-func(a), 0, h_start));
    while (pq.size()) {
        auto [f, d, h] = pq.top();
        pq.pop();
        f = -f;
        if (h == h_en) {
            break;
        }
        vector<int> a = from_h(h);
        for (int i = 0; i < m; i++) {
            swap(a[l[i]], a[r[i]]);
            long long h_nx = to_h(a);
            auto it = mp_go.find(h_nx);
            if (it == mp_go.end()) {
                int f = func(a);
                mp_go[h_nx] = make_tuple(f, d + 1, i);
                pq.push(make_tuple(-(f + d + 1), d + 1, h_nx));
            }
            swap(a[l[i]], a[r[i]]);
        }
    }
    while (pq.size()) {
        pq.pop();
    }
    auto it = mp_go.find(h_en);
    if (it != mp_go.end()) {
        vector<int> ans;
        long long h = h_en;
        vector<int> a = from_h(h);
        while (get<2>(mp_go[h]) != -1) {
            int j = get<2>(mp_go[h]);
            ans.push_back(j + 1);
            swap(a[l[j]], a[r[j]]);
            h = to_h(a);
        }
        reverse(ans.begin(), ans.end());
        cout << ans.size() << endl;
        for (int j : ans) {
            cout << j << endl;
        }
        return 0;
    }

    return 0;
}
