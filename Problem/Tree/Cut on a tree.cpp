//https://www.spoj.com/problems/COT6/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using i128 = __int128_t;

const i128 INF = ((i128)1 << 120);

i128 floordiv(i128 a, i128 b){
    i128 q = a / b, r = a % b;
    if(r && ((r > 0) != (b > 0))) --q;
    return q;
}

struct Line{
    mutable i128 k, m, p;

    bool operator < (const Line& o) const{
        return k < o.k;
    }

    bool operator < (const i128& x) const{
        return p < x;
    }
};

struct Hull{
    multiset<Line, less<> > s;

    i128 addS = 0;
    i128 addC = 0;

    using it = multiset<Line, less<> >::iterator;

    bool isect(it x, it y){
        if(y == s.end()){
            x->p = INF;
            return false;
        }

        if(x->k == y->k){
            x->p = (x->m > y->m ? INF : -INF);
        }else{
            x->p = floordiv(y->m - x->m, x->k - y->k);
        }

        return x->p >= y->p;
    }

    void add_line(i128 k, i128 m){
        auto z = s.insert({k, m, 0});
        auto y = z++;
        auto x = y;

        while(isect(y, z)){
            z = s.erase(z);
        }

        if(x != s.begin() && isect(--x, y)){
            isect(x, y = s.erase(y));
        }

        while((y = x) != s.begin() && (--x)->p >= y->p){
            isect(x, s.erase(y));
        }
    }

    i128 query_raw(i128 x) const{
        auto cur = *s.lower_bound(x);
        return cur.k * x + cur.m;
    }

    i128 query(i128 x) const{
        i128 z = x + addS;
        return addC + z * z - query_raw(z);
    }

    int size() const{
        return (int)s.size();
    }

    void reset(){
        s.clear();
        addS = addC = 0;
    }
};

vector<Hull> h(1);
vector<int> free_id;

int new_hull(){
    if(!free_id.empty()){
        int id = free_id.back();
        free_id.pop_back();

        h[id].reset();

        return id;
    }

    h.push_back(Hull());
    return (int)h.size() - 1;
}

void add_state(int id, i128 S, i128 C){
    S -= h[id].addS;
    C -= h[id].addC;

    h[id].add_line(-(2 * S), -(S * S + C));
}

int meld(int a, int b){
    if(!a) return b;
    if(!b) return a;

    if(h[a].size() < h[b].size()){
        swap(a, b);
    }

    while(!h[b].s.empty()){
        Line cur = *h[b].s.begin();
        h[b].s.erase(h[b].s.begin());

        i128 S = (-cur.k) / 2;
        i128 C = -cur.m - S * S;

        S += h[b].addS;
        C += h[b].addC;

        S -= h[a].addS;
        C -= h[a].addC;

        h[a].add_line(-(2 * S), -(S * S + C));
    }

    h[b].addS = h[b].addC = 0;
    free_id.push_back(b);

    return a;
}

int main(){
    IOS;

    int n;
    cin >> n;

    vector<ll> w(n + 1);
    for(int i = 1; i <= n; ++i){
        cin >> w[i];
    }

    vector<int> head(n + 1, -1);
    vector<int> to(2 * max(0, n - 1));
    vector<int> nxt(2 * max(0, n - 1));

    int ec = 0;

    auto add_edge = [&](int u, int v){
        to[ec] = v;
        nxt[ec] = head[u];
        head[u] = ec++;
    };

    for(int i = 1; i < n; ++i){
        int u, v;
        cin >> u >> v;

        add_edge(u, v);
        add_edge(v, u);
    }

    vector<int> par(n + 1, 0), ord;
    vector<int> st;
    st.push_back(1);
    par[1] = -1;

    while(!st.empty()){
        int u = st.back();
        st.pop_back();

        ord.push_back(u);

        for(int e = head[u]; e != -1; e = nxt[e]){
            int v = to[e];

            if(v == par[u]){
                continue;
            }

            par[v] = u;
            st.push_back(v);
        }
    }

    vector<int>().swap(head);
    vector<int>().swap(to);
    vector<int>().swap(nxt);
    vector<int>().swap(st);

    vector<int> rt(n + 1, 0);
    vector<i128> sum(n + 1, 0);

    i128 ans = 0;

    for(int i = n - 1; i >= 0; --i){
        int u = ord[i];
        int id = rt[u];

        if(!id){
            id = new_hull();
        }

        add_state(id, (i128)w[u], 0);

        h[id].addC += sum[u];

        i128 f = h[id].query(0);

        if(u == 1){
            ans = f;
        }else{
            int p = par[u];

            h[id].addS += (i128)w[p];
            h[id].addC -= f;

            sum[p] += f;
            rt[p] = meld(rt[p], id);
        }

        rt[u] = 0;
    }

    cout << (ll)ans << endl;

    return 0;
}
