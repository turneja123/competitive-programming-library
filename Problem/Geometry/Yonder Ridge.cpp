//https://dmoj.ca/problem/hhpc1p3
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e3 + 5;
const int Q = 5e5 + 5;

pair<pair<long long, long long>, long long> lines[N];
long long ans[N];
pair<pair<long long, long long>, pair<int, int>> events[N * N];
pair<long long, pair<int, int>> queries[Q];
long long qans[Q];


int main() {
    IOS;
    long long n, m, q, k, sz = 0;
    cin >> n >> m >> q >> k;
    for (int i = 0; i < n; i++) {
        cin >> lines[i].first.first >> lines[i].first.second >> lines[i].second;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            long long iyl = lines[i].first.first, jyl = lines[j].first.first;
            long long iyr = lines[i].first.second, jyr = lines[j].first.second;
            if (iyl < jyl) {
                ans[i] += lines[j].second;
                if (iyr > jyr && (iyr - iyl) - (jyr - jyl) > 0) {
                    long long x = ((jyl - iyl) * m) / ((iyr - iyl) - (jyr - jyl));
                    long long md = ((jyl - iyl) * m) % ((iyr - iyl) - (jyr - jyl));
                    if (md) {
                        md = 1;
                    }
                    if (x < m) {
                        events[sz++] = make_pair(make_pair(x, md), make_pair(i, j));
                    }
                }
            }
            if (iyl == jyl && i < j) {
                if (iyr < jyr) {
                    ans[i] += lines[j].second;
                } else if (iyr > jyr) {
                    ans[j] += lines[i].second;
                }
            }
        }
    }
    sort(events, events + sz);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].second.first >> queries[i].first;
        queries[i].second.second = i;
    }
    sort(queries, queries + q);
    int il = 0, ir = 0;
    for (int i = 0; i < q; i++) {
        while (ir < sz && events[ir].first.first < queries[i].first + k) {
            ans[events[ir].second.second] += lines[events[ir].second.first].second;
            ir++;
        }
        while (il < sz && events[il].first.first + events[il].first.second <= queries[i].first) {
            ans[events[il].second.first] -= lines[events[il].second.second].second;
            il++;
        }
        qans[queries[i].second.second] = ans[queries[i].second.first - 1];
    }
    for (int i = 0; i < q; i++) {
        cout << qans[i] << endl;
    }


    return 0;
}
