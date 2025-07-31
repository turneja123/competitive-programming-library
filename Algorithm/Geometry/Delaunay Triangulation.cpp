//https://dmoj.ca/problem/cco08p6
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);
#define H(e) e->F(), e->p
#define valid(e) (e->F().cross(H(base)) > 0)

using ld = double;

const ll INF = 1e18;

struct PT {
    ll x, y;
    PT() { x = 0, y = 0; }
    PT(ll x, ll y) : x(x), y(y) {}
    PT operator + (const PT &a) const { return PT(x + a.x, y + a.y); }
    PT operator - (const PT &a) const { return PT(x - a.x, y - a.y); }
    bool operator == (const PT &a) const { return x == a.x && y == a.y; }
    bool operator < (PT a) const { return a.x - x == 0 ? y < a.y : x < a.x; }

    long long norm2() { return x * x + y * y;}
    long long cross(PT p) const { return x * p.y - y * p.x; }
    long long cross(PT a, PT b) const { return (a - *this).cross(b - *this); }
};

struct dPT {
    ld x, y;
    dPT() { x = 0, y = 0; }
    dPT(ld x, ld y) : x(x), y(y) {}
    dPT operator + (const dPT &a) const { return dPT(x + a.x, y + a.y); }
    dPT operator - (const dPT &a) const { return dPT(x - a.x, y - a.y); }
    dPT operator * (const ld a) const { return dPT(x * a, y * a); }

    ld norm2() { return x * x + y * y;}
    ld cross(dPT p) const { return x * p.y - y * p.x; }
    ld cross(dPT a, dPT b) const { return (a - *this).cross(b - *this); }
};

ld dot(dPT a, dPT b) { return a.x * b.x + a.y * b.y; }
ld dist(dPT a, dPT b) { return sqrt(dot(a - b, a - b)); }

dPT rotatecw90(dPT a) { return dPT(a.y, -a.x); }

dPT line_line_intersection(dPT a, dPT b, dPT c, dPT d) {
    ld a1 = a.y - b.y, b1 = b.x - a.x, c1 = a.cross(b);
    ld a2 = c.y - d.y, b2 = d.x - c.x, c2 = c.cross(d);
    ld det = a1 * b2 - a2 * b1;
    return dPT((b1 * c2 - b2 * c1) / det, (c1 * a2 - a1 * c2) / det);
}
ld circle(PT A, PT B, PT C) {
    dPT a(A.x, A.y), b(B.x, B.y), c(C.x, C.y);
    b = (a + b) * 0.5;
    c = (a + c) * 0.5;
    auto p = line_line_intersection(b, b + rotatecw90(a - b), c, c + rotatecw90(a - c));
    return dist(a, p);
}

struct Quad {
    bool mark;
    Quad *o;
    Quad *rot;
    PT p;
    PT F() {
        return r()->p;
    }
    Quad* r() {
        return rot->rot;
    }
    Quad* prev() {
        return rot->o->rot;
    }
    Quad* next() {
        return r()->prev();
    }
};

PT sentinel(INF, INF);

Quad* make_edge(PT st, PT en) {
    Quad *q[] = {new Quad{0, 0, 0, st}, new Quad{0, 0, 0, sentinel}, new Quad{0, 0, 0, en}, new Quad{0, 0, 0, sentinel}};
    for (int i = 0; i < 4; i++) {
        q[i]->o = q[-i & 3];
        q[i]->rot = q[(i + 1) & 3];
    }
    return *q;
}

void splice(Quad *a, Quad *b) {
    swap(a->o->rot->o, b->o->rot->o);
    swap(a->o, b->o);
    return;
}

Quad* connect(Quad *a, Quad *b) {
    Quad *q = make_edge(a->F(), b->p);
    splice(q, a->next());
    splice(q->r(), b);
    return q;
}

bool circ(PT p, PT a, PT b, PT c) {
    __int128 p2 = p.norm2(), A = a.norm2() - p2, B = b.norm2() - p2, C = c.norm2() - p2;
    return p.cross(a, b) * C + p.cross(c, a) * B + p.cross(b, c) * A > 0;
}

pair<Quad*, Quad*> calc(int l, int r, vector<PT> &s) {
    if (r - l + 1 <= 3) {
        Quad *a = make_edge(s[l], s[l + 1]);
        Quad *b = make_edge(s[l + 1], s[r]);
        if (r - l + 1 == 2) {
            return {a, a->r()};
        }
        splice(a->r(), b);
        auto side = s[l].cross(s[l + 1], s[l + 2]);
        Quad *c = side ? connect(b, a) : 0;
        return {side < 0 ? c->r() : a, side < 0 ? c : b->r()};
    }
    Quad *A, *B, *ra, *rb;
    int mid = (l + r) / 2;
    tie(ra, A) = calc(l, mid, s);
    tie(B, rb) = calc(mid + 1, r, s);
    while ((B->p.cross(H(A)) < 0 && (A = A->next())) || (A->p.cross(H(B)) > 0 && (B = B->r()->o)));
    Quad *base = connect(B->r(), A);
    if (A->p == ra->p) {
        ra = base->r();
    }
    if (B->p == rb->p) {
        rb = base;
    }
    for (;;) {
        Quad *e1 = base->r()->o;
        if (valid(e1)) {
            while (circ(e1->o->F(), H(base), e1->F())) {
                Quad *t = e1->o;
                splice(e1, e1->prev());
                splice(e1->r(), e1->r()->prev());
                e1 = t;
            }
        }
        Quad *e2 = base->prev();
        if (valid(e2)) {
            while (circ(e2->prev()->F(), H(base), e2->F())) {
                Quad *t = e2->prev();
                splice(e2, e2->prev());
                splice(e2->r(), e2->r()->prev());
                e2 = t;
            }
        }
        if (!valid(e1) && !valid(e2)) {
            break;
        }
        if (!valid(e1) || (valid(e2) && circ(H(e2), H(e1)))) {
            base = connect(e2, base->r());
        } else {
            base = connect(base->r(), e1->r());
        }
    }
    return {ra, rb};
}

vector<PT> delaunay(vector<PT> p) {
    int n = p.size();
    sort(p.begin(), p.end());
    Quad *e = calc(0, n - 1, p).first;
    vector<Quad*> q = {e};
    int qi = 0;
    while (e->o->F().cross(e->F(), e->p) < 0) {
        e = e->o;
    }
    Quad *c = e;
    do {
        c->mark = 1;
        p.push_back(c->p);
        q.push_back(c->r());
        c = c->next();
    } while (c != e);
    p.clear();
    while (qi < q.size()) {
        if (!(e = q[qi++])->mark) {
            Quad *c = e;
            do {
                c->mark = 1;
                p.push_back(c->p);
                q.push_back(c->r());
                c = c->next();
            } while (c != e);
        }
    }
    return p;
}

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(12);
    int n;
    cin >> n;
    vector<PT> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
    }
    vector<PT> t = delaunay(p);
    ld ans = 0;
    for (int i = 0; i < t.size(); i += 3) {
        ans = max(ans, circle(t[i], t[i + 1], t[i + 2]));
    }
    cout << ans << endl;
    return 0;
}
