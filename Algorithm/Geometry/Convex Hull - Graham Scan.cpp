//solution for https://open.kattis.com/problems/convexhull
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define f first
#define s second
#define pii pair<int, int>
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int INF = 1e9;

pair<int, int> p0;

int distsq(pii p1, pii p2) {
    return (p1.f - p2.f) * (p1.f - p2.f ) + (p1.s - p2.s) * (p1.s - p2.s);
}

int orientation(pii p1, pii p2, pii p3) {
    int val = (p2.s - p1.s) * (p3.f - p2.f) - (p2.f - p1.f) * (p3.s - p2.s);
    if (val == 0) return 0;
    if (val > 0) return 1;
    if (val < 0) return 2;
}

bool compare(pii p1, pii p2) {
    int o = orientation(p0, p1, p2);
    if (o == 0) {
        int dist1 = distsq(p0, p1);
        int dist2 = distsq(p0, p2);
        if (dist2 >= dist1) {
            return 1;
        } else {
            return 0;
        }
    }
    if (o == 1) return 0;
    if (o == 2) return 1;
}

pii nextToTop(stack<pii> s) {
    pii temp = s.top();
    s.pop();
    pii ret = s.top();
    s.push(temp);
    return ret;
}

int main() {
    IOS;
    while (1) {
        int n;
        cin >> n;
        set<pii> st;
        vector<pii> v;
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            pii pr = {x, y};
            if (st.find(pr) == st.end()) {
                st.insert(pr);
                v.push_back(pr);
            }
        }
        n = v.size();
        if (n < 3) {
            cout << n << endl;
            for (int i = 0; i < n; i++) {
                cout << v[i].f << " " << v[i].s << endl;
            }
            continue;
        }
        pii p[n];
        for (int i = 0; i < n; i++) {
            p[i] = v[i];
        }
        int ymn = INF;
        int xmn = INF;
        int pos = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].s < ymn) {
                ymn = p[i].s;
                xmn = p[i].f;
                pos = i;
            } else if (p[i].s == ymn && p[i].f < xmn) {
                xmn = p[i].f;
                pos = i;
            }
        }
        swap(p[0], p[pos]);
        p0 = p[0];
        sort(p + 1, p + n, compare);
        int m = 1;
        for (int i = 1; i < n ; i++) {
            while (i < n - 1 && orientation(p0, p[i], p[i + 1]) == 0) {
                i++;
            }
            p[m] = p[i];
            m++;
        }
        if (m < 3) {
            cout << 2 << endl;
            cout << p[0].f << " " << p[0].s << endl;
            cout << p[n - 1].f << " " << p[n - 1].s << endl;
            continue;
        }
        stack <pii> s;
        s.push(p[0]);
        s.push(p[1]);
        s.push(p[2]);
        for (int i = 3; i < m; i++) {
            pii _p0 = nextToTop(s);
            pii p1 = s.top();
            pii p2 = p[i];
            while(orientation(_p0, p1, p2) != 2) {
                s.pop();
                _p0 = nextToTop(s);
                p1 = s.top();
            }
            s.push(p[i]);
        }
        vector<pii> out;
        int sz = s.size();
        for (int i = 0; i < sz; i++) {
            out.push_back(s.top());
            s.pop();
        }
        cout << out.size() << endl;
        for (int i = out.size() - 1; i >= 0; i--) {
            cout << out[i].first << " " << out[i].second << endl;
        }
        break;
    }
    return 0;
}
