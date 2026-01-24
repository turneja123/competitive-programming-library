//https://qoj.ac/contest/2694/problem/15629
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

struct Op {
    int d;
    int i;
    int j;
    vector<int> from;
};

int main() {
    IOS;
    map<vector<int>, Op> dist;
    vector<int> a(5);
    iota(a.begin(), a.end(), 0);
    dist[a] = {0, 0, 0, a};
    queue<vector<int>> q;
    q.push(a);
    int ct = 0;
    while (q.size()) {
        auto a = q.front();
        int d = dist[a].d;
        q.pop();
        for (int i = 0; i + 2 < 5; i++) {
            vector<int> tmp = a;
            int x = a[i], y = a[i + 1], z = a[i + 2];
            tmp.erase(tmp.begin() + i);
            tmp.erase(tmp.begin() + i);
            tmp.erase(tmp.begin() + i);


            for (int j = 0; j <= tmp.size(); j++) {
                vector<int> tmp2 = tmp;
                tmp2.insert(tmp2.begin() + j, z);
                tmp2.insert(tmp2.begin() + j, y);
                tmp2.insert(tmp2.begin() + j, x);
                auto it = dist.find(tmp2);
                if (it == dist.end()) {
                    dist[tmp2] = {d + 1, i, j, a};
                    q.push(tmp2);
                }
            }
        }
    }
    int n;
    cin >> n;
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        b[i]--;
    }
    vector<pair<int, int>> ans;
    for (int i = 0; i + 5 < n; i++) {
        int p = 0;
        for (int j = 0; j < n; j++) {
            if (b[j] == i) {
                p = j;
                break;
            }
        }
        if (p == n - 1) {
            int x = b[n - 4], y = b[n - 3], z = b[n - 2];
            b.erase(b.begin() + n - 4);
            b.erase(b.begin() + n - 4);
            b.erase(b.begin() + n - 4);
            b.insert(b.begin() + n - 3, z);
            b.insert(b.begin() + n - 3, y);
            b.insert(b.begin() + n - 3, x);
            ans.push_back({n - 4, n - 3});
        } else if (p == n - 2) {
            int x = b[n - 5], y = b[n - 4], z = b[n - 3];
            b.erase(b.begin() + n - 5);
            b.erase(b.begin() + n - 5);
            b.erase(b.begin() + n - 5);
            b.insert(b.begin() + n - 3, z);
            b.insert(b.begin() + n - 3, y);
            b.insert(b.begin() + n - 3, x);
            ans.push_back({n - 5, n - 3});
        }
        for (int j = 0; j < n; j++) {
            if (b[j] == i) {
                p = j;
                break;
            }
        }

        int x = b[p], y = b[p + 1], z = b[p + 2];
        b.erase(b.begin() + p);
        b.erase(b.begin() + p);
        b.erase(b.begin() + p);
        b.insert(b.begin() + i, z);
        b.insert(b.begin() + i, y);
        b.insert(b.begin() + i, x);
        ans.push_back({p, i});
    }
    vector<int> c(5);
    for (int i = n - 5; i < n; i++) {
        c[i - (n - 5)] = b[i] - (n - 5);
    }
    while (c != a) {
        auto it = dist[c];
        ans.push_back({it.j + n - 5, it.i + n - 5});
        c = it.from;
    }
    cout << ans.size() << endl;
    for (auto [i, j] : ans) {
        cout << i + 1 << " " << j + 1 << endl;
    }
    return 0;
}
