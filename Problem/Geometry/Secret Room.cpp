//solution for https://dmoj.ca/problem/secret
#pragma GCC target ("avx")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 55;

const long double INF = 1e10;

struct Line {
    pair<long double, long double> x;
    pair<long double, long double> y;

};

Line l[N];

vector<tuple<long double, long double, long double>> bisectors;

long double ans = 0;
long double e = 1e-7;
long double n, m, z = 0; int q;

long double dist(pair<long double, long double> a, Line li) {
    long double x0 = a.first, y0 = a.second, x1 = li.x.first, y1 = li.x.second, x2 = li.y.first, y2 = li.y.second;
    long double d = ((x2 - x1) * (y1 - y0) - (x1 - x0) * (y2 - y1)) / (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
    return abs(d);

}

pair<long double, long double> intersection(Line a, Line b) {
    long double a1 = a.y.second - a.x.second;
    long double b1 = a.x.first - a.y.first;
    long double c1 = a1 * (a.x.first) + b1 * (a.x.second);

    long double a2 = b.y.second - b.x.second;
    long double b2 = b.x.first - b.y.first;
    long double c2 = a2 * (b.x.first) + b2 * (b.x.second);

    long double determinant = a1 * b2 - a2 * b1;

    if (determinant == 0) {
        return {INF * (long double)(10), INF * (long double)(10)};
    }

    long double x = (b2 * c1 - b1 * c2) / determinant;
    long double y = (a1 * c2 - a2 * c1) / determinant;

    return {x, y};
}

pair<long double, long double> biintersection(tuple<long double, long double, long double> a, tuple<long double, long double, long double> b) {
    long double a1 = get<0>(a);
    long double b1 = get<1>(a);
    long double c1 = get<2>(a);

    long double a2 = get<0>(b);
    long double b2 = get<1>(b);
    long double c2 = get<2>(b);

    long double determinant = a1 * b2 - a2 * b1;

    if (determinant == 0) {
        return {INF * (long double)(10), INF * (long double)(10)};
    }

    long double x = (b2 * c1 - b1 * c2) / determinant;
    long double y = (a1 * c2 - a2 * c1) / determinant;

    return {x, y};
}

void pushBisectors(Line a, Line b) {
    long double a1 = a.y.second - a.x.second;
    long double b1 = a.x.first - a.y.first;
    long double c1 = a1 * (a.x.first) + b1 * (a.x.second);
    long double d1 = sqrt(a1 * a1 + b1 * b1);

    long double a2 = b.y.second - b.x.second;
    long double b2 = b.x.first - b.y.first;
    long double c2 = a2 * (b.x.first) + b2 * (b.x.second);
    long double d2 = sqrt(a2 * a2 + b2 * b2);
    bisectors.push_back(make_tuple(a1 / d1 + a2 / d2, b1 / d1 + b2 / d2, c1 / d1 + c2 / d2));
    bisectors.push_back(make_tuple(a1 / d1 - a2 / d2, b1 / d1 - b2 / d2, c1 / d1 - c2 / d2));

}

void solve(Line a, Line b, Line c, bool par) {
    if (!par) {
        pushBisectors(a, b);
        pushBisectors(a, c);
        pushBisectors(b, c);
    } else {
        pushBisectors(a, c);
        pushBisectors(b, c);
    }
    for (int i = 0; i < 6; i++) {
        for (int j = i; j < 6; j++) {
            if (i == j) {
                continue;
            }
            pair<long double, long double> center = biintersection(bisectors[i], bisectors[j]);
            long double radius = min(min(dist(center, a), dist(center, b)), dist(center, c));

            if (center.first - radius < 0 || center.first + radius > n || center.second - radius < 0 || center.second + radius > m) {
                continue;
            }
            if (radius < ans) {
                continue;
            }

            bool flag = true;
            for (int k = 0; k < q + 4; k++) {
                long double d = dist(center, l[k]);
                if (d < radius) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                ans = max(ans, radius);
            }
        }
    }
    bisectors.clear();
}

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(5);

    cin >> n >> m >> q;
    l[0].x = {z, z};
    l[0].y = {n, z};
    l[1].x = {z, z};
    l[1].y = {z, m};
    l[2].x = {z, m};
    l[2].y = {n, m};
    l[3].x = {n, z};
    l[3].y = {n, m};

    for (int i = 4; i < q + 4; i++) {
        pair<long double, long double> a, b;
        cin >> a.first >> a.second >> b.first >> b.second;
        if (a.first > b.first) {
            swap(a, b);
        }
        l[i].x = a;
        l[i].y = b;
    }


    for (int i = 0; i < q + 4; i++) {
        for (int j = 0; j < q + 4; j++) {
            for (int k = 0; k < q + 4; k++) {
                if (i == j || i == k || j == k) {
                    continue;
                }
                Line a = l[i], b = l[j], c = l[k];
                if (intersection(a, b).first > INF && intersection(a, c).first > INF) {
                    continue;
                }
                if (intersection(a, b).first > INF) {
                    solve(a, b, c, true);
                } else if (intersection(a, c).first > INF) {
                    solve(a, c, b, true);
                } else if (intersection(b, c).first > INF) {
                    solve(b, c, a, true);
                } else {
                    solve(a, b, c, false);
                }

            }
        }
    }
    cout << ans << endl;
    return 0;
}
