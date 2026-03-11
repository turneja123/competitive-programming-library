//https://www.spoj.com/problems/TWOCIR/
#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;

int sign(double x) { return (x > eps) - (x < -eps); }

struct PT {
    double x, y, z;
    PT() { x = y = z = 0; }
    PT(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
    PT operator + (const PT &a) const { return PT(x + a.x, y + a.y, z + a.z); }
    PT operator - (const PT &a) const { return PT(x - a.x, y - a.y, z - a.z); }
    PT operator * (const double a) const { return PT(x * a, y * a, z * a); }
    friend PT operator * (const double &a, const PT &b) { return PT(a * b.x, a * b.y, a * b.z); }
    PT operator / (const double a) const { return PT(x / a, y / a, z / a); }
};

inline double dot(PT a, PT b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

inline PT cross(PT a, PT b) {
    return PT(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

struct circle3 { PT o, n; double r2; };

circle3 get_circle(PT A, PT B, PT C) {
    PT a = B - A, b = C - A, n = cross(a, b);
    PT o = A + (cross(b, n) * dot(a, a) + cross(n, a) * dot(b, b)) / (2.0 * dot(n, n));
    return {o, n, dot(o - A, o - A)};
}

bool linked_one_way(const circle3 &A, const circle3 &B) {
    PT d = cross(A.n, B.n);
    double dd = dot(d, d);
    if (sign(dd) == 0) return 0;
    PT p0 = (cross(B.n, d) * dot(A.n, A.o) + cross(d, A.n) * dot(B.n, B.o)) / dd;
    PT m = p0 - B.o;
    double Aq = dd, Bq = 2.0 * dot(d, m), Cq = dot(m, m) - B.r2, disc = Bq * Bq - 4.0 * Aq * Cq;
    if (sign(disc) <= 0) return 0;
    double s = sqrt(max(0.0, disc));
    int in = 0;
    in += (sign(dot((p0 + d * ((-Bq - s) / (2.0 * Aq))) - A.o, (p0 + d * ((-Bq - s) / (2.0 * Aq))) - A.o) - A.r2) < 0);
    in += (sign(dot((p0 + d * ((-Bq + s) / (2.0 * Aq))) - A.o, (p0 + d * ((-Bq + s) / (2.0 * Aq))) - A.o) - A.r2) < 0);
    return in & 1;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        long long x1,y1,z1,x2,y2,z2,x3,y3,z3;
        cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;
        PT A1(x1,y1,z1), B1(x2,y2,z2), C1(x3,y3,z3);
        cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;
        PT A2(x1,y1,z1), B2(x2,y2,z2), C2(x3,y3,z3);
        cout << (linked_one_way(get_circle(A1,B1,C1), get_circle(A2,B2,C2)) ? "YES\n" : "NO\n");
    }
    return 0;
}
