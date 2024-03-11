//solution for https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=314
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

long double INF = 1e15;

struct Line {
    pair<long double, long double> x;
    pair<long double, long double> y;
};

pair<long double, long double> intersection(Line a, Line b) {
    long double a1 = a.y.second - a.x.second;
    long double b1 = a.x.first - a.y.first;
    long double c1 = a1 * (a.x.first) + b1 * (a.x.second);

    long double a2 = b.y.second - b.x.second;
    long double b2 = b.x.first - b.y.first;
    long double c2 = a2 * (b.x.first) + b2 * (b.x.second);

    long double determinant = a1 * b2 - a2 * b1;
    long double dx = c1 * b2 - c2 * b1;
    long double dy = a1 * c2 - a2 * c1;

    if (determinant == 0 && dx == 0 && dy == 0) {
        cout << "LINE" << endl;
        return {INF * (long double)(10), INF * (long double)(10)};
    }

    if (determinant == 0) {
        cout << "NONE" << endl;
        return {INF * (long double)(10), INF * (long double)(10)};
    }

    long double x = (b2 * c1 - b1 * c2) / determinant;
    long double y = (a1 * c2 - a2 * c1) / determinant;
    cout << "POINT " << x << " " << y << endl;
    return {x, y};

}

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(2);
    cout << "INTERSECTING LINES OUTPUT" << endl;
    int n;
    cin >> n;
    while (n--) {
        Line a, b;
        cin >> a.x.first >> a.x.second >> a.y.first >> a.y.second;
        cin >> b.x.first >> b.x.second >> b.y.first >> b.y.second;
        pair<long double, long double> ans = intersection(a, b);
    }
    cout << "END OF OUTPUT" << endl;
    return 0;
}
