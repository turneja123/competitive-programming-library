//https://www.spoj.com/problems/CARD/
#include <bits/stdc++.h>
using namespace std;

struct Perm {
    int n;
    vector<int> p;

    Perm(int n_=0): n(n_), p(n_) {
        iota(p.begin(), p.end(), 0);
    }

    static Perm identity(int n){ return Perm(n); }

    bool operator==(const Perm& other) const {
        return n==other.n && p==other.p;
    }
};

static inline Perm compose(const Perm& A, const Perm& B){
    Perm R(A.n);
    for(int i=0;i<A.n;i++) R.p[i] = A.p[B.p[i]];
    return R;
}

static inline Perm inverse_perm(const Perm& P){
    Perm inv(P.n);
    for(int i=0;i<P.n;i++) inv.p[P.p[i]] = i;
    return inv;
}

static inline long long lcm_ll(long long a, long long b){
    return a / __gcd(a,b) * b;
}

static long long order_perm(const Perm& P){
    int n=P.n;
    vector<int> vis(n,0);
    long long ord=1;
    for(int i=0;i<n;i++){
        if(vis[i]) continue;
        int v=i, len=0;
        while(!vis[v]){
            vis[v]=1;
            v=P.p[v];
            len++;
        }
        ord = lcm_ll(ord, len);
    }
    return ord;
}

static Perm pow_perm(const Perm& P, long long e){
    int n=P.n;
    Perm R(n);
    vector<int> vis(n,0);
    for(int i=0;i<n;i++){
        if(vis[i]) continue;
        vector<int> cyc;
        int v=i;
        while(!vis[v]){
            vis[v]=1;
            cyc.push_back(v);
            v=P.p[v];
        }
        int L=(int)cyc.size();
        long long shift = (L==0?0:(e%L));
        for(int j=0;j<L;j++){
            int from = cyc[j];
            int to = cyc[(j + (int)shift) % L];
            R.p[from]=to;
        }
    }
    return R;
}

static bool is_identity(const Perm& P){
    for(int i=0;i<P.n;i++) if(P.p[i]!=i) return false;
    return true;
}

static bool is_transposition(const Perm& P, pair<int,int>& sw){
    int n=P.n;
    vector<int> used(n,0);
    int cnt2=0;
    int a=-1,b=-1;
    for(int i=0;i<n;i++){
        if(used[i]) continue;
        if(P.p[i]==i){
            used[i]=1;
            continue;
        }
        int j=P.p[i];
        if(j<0 || j>=n) return false;
        if(P.p[j]!=i) return false;
        if(i==j) return false;
        used[i]=used[j]=1;
        cnt2++;
        a=i; b=j;
    }
    if(cnt2==1){
        sw={a,b};
        return true;
    }
    return false;
}

struct Segment { bool isA; long long exp; };

static vector<Segment> normalize_word(vector<Segment> w, long long ordA, long long ordB){
    vector<Segment> res;
    for(auto &s : w){
        long long ord = s.isA ? ordA : ordB;
        long long e = s.exp % ord;
        if(e<0) e += ord;
        if(e==0) continue;
        if(!res.empty() && res.back().isA == s.isA){
            res.back().exp = (res.back().exp + e) % ord;
            if(res.back().exp==0) res.pop_back();
        } else {
            res.push_back({s.isA, e});
        }
    }
    return res;
}

static vector<Segment> word_inverse(const vector<Segment>& w, long long ordA, long long ordB){
    vector<Segment> inv;
    inv.reserve(w.size());
    for(int i=(int)w.size()-1;i>=0;i--){
        bool isA = w[i].isA;
        long long ord = isA ? ordA : ordB;
        long long e = w[i].exp % ord;
        if(e<0) e += ord;
        long long ie = (ord - e) % ord;
        if(ie!=0) inv.push_back({isA, ie});
    }
    return normalize_word(std::move(inv), ordA, ordB);
}

static vector<Segment> word_concat(const vector<Segment>& a, const vector<Segment>& b, long long ordA, long long ordB){
    vector<Segment> w;
    w.reserve(a.size()+b.size());
    w.insert(w.end(), a.begin(), a.end());
    w.insert(w.end(), b.begin(), b.end());
    return normalize_word(std::move(w), ordA, ordB);
}

struct PairGraph {
    int n;
    int V;
    vector<int> U, Vv;
    vector<vector<int>> idxOf;
    vector<int> pa, pb;

    int na=0, nb=0;
    vector<int> cidA, posA, cidB, posB;
    vector<vector<int>> cycA, cycB;

    vector<vector<pair<int,int>>> adjBig;

    PairGraph(const Perm& a, const Perm& b){
        n = a.n;
        idxOf.assign(n, vector<int>(n, -1));
        U.clear(); Vv.clear();
        V = n*(n-1)/2;
        U.reserve(V); Vv.reserve(V);
        int idx=0;
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                idxOf[i][j]=idx;
                U.push_back(i);
                Vv.push_back(j);
                idx++;
            }
        }

        pa.assign(V, -1);
        pb.assign(V, -1);
        for(int id=0; id<V; id++){
            int x=U[id], y=Vv[id];
            int ax=a.p[x], ay=a.p[y];
            if(ax>ay) swap(ax,ay);
            pa[id]=idxOf[ax][ay];

            int bx=b.p[x], by=b.p[y];
            if(bx>by) swap(bx,by);
            pb[id]=idxOf[bx][by];
        }

        build_cycles();
        build_big_graph();
    }

    void build_cycles(){
        cidA.assign(V, -1);
        posA.assign(V, -1);
        cycA.clear();
        na=0;
        for(int i=0;i<V;i++){
            if(cidA[i]!=-1) continue;
            vector<int> cyc;
            int v=i;
            while(cidA[v]==-1){
                cidA[v]=na;
                posA[v]=(int)cyc.size();
                cyc.push_back(v);
                v=pa[v];
            }
            cycA.push_back(std::move(cyc));
            na++;
        }

        cidB.assign(V, -1);
        posB.assign(V, -1);
        cycB.clear();
        nb=0;
        for(int i=0;i<V;i++){
            if(cidB[i]!=-1) continue;
            vector<int> cyc;
            int v=i;
            while(cidB[v]==-1){
                cidB[v]=nb;
                posB[v]=(int)cyc.size();
                cyc.push_back(v);
                v=pb[v];
            }
            cycB.push_back(std::move(cyc));
            nb++;
        }
    }

    void build_big_graph(){
        int N = na + nb;
        adjBig.assign(N, {});
        for(int pid=0; pid<V; pid++){
            int aNode = cidA[pid];
            int bNode = na + cidB[pid];
            adjBig[aNode].push_back({bNode, pid});
            adjBig[bNode].push_back({aNode, pid});
        }
    }

    bool connected_big_graph() const {
        int N = na + nb;
        vector<int> vis(N,0);
        deque<int> dq;
        dq.push_back(0);
        vis[0]=1;
        int cnt=1;
        while(!dq.empty()){
            int u=dq.front(); dq.pop_front();
            for(auto [v,pid]: adjBig[u]){
                if(!vis[v]){
                    vis[v]=1;
                    dq.push_back(v);
                    cnt++;
                }
            }
        }
        return cnt==N;
    }

    long long delta_in_cycle(bool isA, int fromPair, int toPair) const {
        if(isA){
            int c = cidA[fromPair];
            int L = (int)cycA[c].size();
            int df = posA[fromPair], dt = posA[toPair];
            int d = dt - df;
            d %= L;
            if(d<0) d += L;
            return d;
        } else {
            int c = cidB[fromPair];
            int L = (int)cycB[c].size();
            int df = posB[fromPair], dt = posB[toPair];
            int d = dt - df;
            d %= L;
            if(d<0) d += L;
            return d;
        }
    }
};

struct BFSTree {
    vector<int> dist;
    vector<int> parent;
    vector<int> parentEdgePair;
};

static BFSTree bfs_tree(const PairGraph& pg, int root){
    int N = pg.na + pg.nb;
    BFSTree t;
    t.dist.assign(N, INT_MAX);
    t.parent.assign(N, -1);
    t.parentEdgePair.assign(N, -1);
    deque<int> dq;
    dq.push_back(root);
    t.dist[root]=0;
    while(!dq.empty()){
        int u=dq.front(); dq.pop_front();
        for(auto [v, pid] : pg.adjBig[u]){
            if(t.dist[v]==INT_MAX){
                t.dist[v]=t.dist[u]+1;
                t.parent[v]=u;
                t.parentEdgePair[v]=pid;
                dq.push_back(v);
            }
        }
    }
    return t;
}

static vector<Segment> word_map_pair(
    const PairGraph& pg,
    int startPair,
    int targetPair,
    const BFSTree& treeA, int rootA,
    const BFSTree& treeB, int rootB,
    long long ordA, long long ordB
){
    int endA = pg.cidA[targetPair];
    int endB = pg.na + pg.cidB[targetPair];

    struct Choice { int dist; int whichTree; int endNode; };
    vector<Choice> cand;
    auto addChoice = [&](int d, int which, int endNode){
        if(d==INT_MAX) return;
        cand.push_back({d, which, endNode});
    };

    addChoice(treeA.dist[endA], 0, endA);
    addChoice(treeA.dist[endB], 0, endB);
    addChoice(treeB.dist[endA], 1, endA);
    addChoice(treeB.dist[endB], 1, endB);

    if(cand.empty()){
        return {};
    }

    auto best = *min_element(cand.begin(), cand.end(), [](const Choice& x, const Choice& y){
        return x.dist < y.dist;
    });

    const BFSTree& T = (best.whichTree==0 ? treeA : treeB);
    int root = (best.whichTree==0 ? rootA : rootB);
    int node = best.endNode;

    vector<int> nodes;
    vector<int> edges;
    int cur=node;
    while(cur!=root){
        edges.push_back(T.parentEdgePair[cur]);
        nodes.push_back(cur);
        cur=T.parent[cur];
        if(cur==-1){
            return {};
        }
    }
    nodes.push_back(root);
    reverse(nodes.begin(), nodes.end());
    reverse(edges.begin(), edges.end());

    vector<Segment> w;
    int curPair = startPair;

    for(size_t i=0;i<edges.size();i++){
        int curNode = nodes[i];
        bool isA = (curNode < pg.na);
        int bridgePair = edges[i];
        long long d = pg.delta_in_cycle(isA, curPair, bridgePair);
        if(d!=0) w.push_back({isA, d});
        curPair = bridgePair;
    }
    bool endIsA = (nodes.back() < pg.na);
    long long dfin = pg.delta_in_cycle(endIsA, curPair, targetPair);
    if(dfin!=0) w.push_back({endIsA, dfin});

    return normalize_word(std::move(w), ordA, ordB);
}

static vector<pair<int,int>> factor_into_transpositions(const Perm& p){
    int n=p.n;
    vector<int> vis(n,0);
    vector<pair<int,int>> trans;
    for(int i=0;i<n;i++){
        if(vis[i]) continue;
        int v=i;
        vector<int> cyc;
        while(!vis[v]){
            vis[v]=1;
            cyc.push_back(v);
            v=p.p[v];
        }
        if((int)cyc.size()<=1) continue;
        int pivot = cyc[0];
        for(int j=1;j<(int)cyc.size();j++){
            trans.push_back({pivot, cyc[j]});
        }
    }
    return trans;
}

static bool commute(const Perm& x, const Perm& y){
    return compose(x,y) == compose(y,x);
}

static long long egcd(long long a, long long b, long long &x, long long &y){
    if(b==0){ x=1; y=0; return a; }
    long long x1,y1;
    long long g=egcd(b, a%b, x1,y1);
    x=y1;
    y=x1 - (a/b)*y1;
    return g;
}

static long long modinv(long long a, long long mod){
    long long x,y;
    long long g=egcd(a,mod,x,y);
    if(g!=1) return -1;
    x%=mod; if(x<0) x+=mod;
    return x;
}

static bool crt_merge(long long a1, long long m1, long long a2, long long m2, long long &a, long long &m){
    long long g = __gcd(m1, m2);
    long long diff = a2 - a1;
    if(diff % g != 0) return false;
    long long m1g = m1 / g;
    long long m2g = m2 / g;
    long long rhs = (diff / g) % m2g;
    if(rhs<0) rhs += m2g;
    long long inv = modinv(m1g % m2g, m2g);
    if(inv==-1) return false;
    long long k = (__int128)rhs * inv % m2g;
    long long l = m1g * m2;
    long long res = a1 + m1 * k;
    res %= l; if(res<0) res += l;
    a=res; m=l;
    return true;
}

static long long discrete_log_cyclewise(const Perm& g, const Perm& x){
    int n=g.n;
    vector<int> pos(n,-1), cid(n,-1);
    vector<vector<int>> cycles;
    vector<int> vis(n,0);
    for(int i=0;i<n;i++){
        if(vis[i]) continue;
        int v=i;
        vector<int> cyc;
        while(!vis[v]){
            vis[v]=1;
            cid[v]=(int)cycles.size();
            pos[v]=(int)cyc.size();
            cyc.push_back(v);
            v=g.p[v];
        }
        cycles.push_back(std::move(cyc));
    }

    long long a=0, m=1;
    for(auto &cyc : cycles){
        int L=(int)cyc.size();
        if(L==1){
            int v=cyc[0];
            if(x.p[v]!=v) return -1;
            continue;
        }
        int v0=cyc[0];
        int w=x.p[v0];
        if(cid[w]!=cid[v0]) return -1;
        int s = pos[w] - pos[v0];
        s %= L; if(s<0) s += L;

        for(int j=0;j<L;j++){
            int v=cyc[j];
            int expected = cyc[(j+s)%L];
            if(x.p[v]!=expected) return -1;
        }

        long long a2=s, m2=L;
        long long na,nm;
        if(!crt_merge(a,m,a2,m2,na,nm)) return -1;
        a=na; m=nm;
    }

    long long ord = order_perm(g);
    a %= ord;
    return a;
}

static long long primes_not_in_divisor(long long m, long long d){
    long long y = __gcd(m, d);
    long long x = m / y;
    while(true){
        long long z = __gcd(x, y);
        if(z==1) break;
        x /= z;
        y *= z;
    }
    return x;
}

static bool check2_cyclic(const Perm& x, const Perm& y, Perm& gen){
    if(!commute(x,y)) return false;
    long long mx = order_perm(x);
    long long my = order_perm(y);
    long long m = lcm_ll(mx, my);

    long long d1 = m / mx;
    long long d2 = m / my;
    long long d = d1 * d2;

    long long t = primes_not_in_divisor(m, d);

    Perm ypow = pow_perm(y, t);
    Perm g = compose(x, ypow);
    if(order_perm(g) != m) return false;

    gen = g;
    return true;
}

static vector<vector<int>> element_cycles(const Perm& p){
    int n=p.n;
    vector<int> vis(n,0);
    vector<vector<int>> cycles;
    for(int i=0;i<n;i++){
        if(vis[i]) continue;
        int v=i;
        vector<int> cyc;
        while(!vis[v]){
            vis[v]=1;
            cyc.push_back(v);
            v=p.p[v];
        }
        cycles.push_back(std::move(cyc));
    }
    return cycles;
}

static Perm build_random_b(const Perm& a, mt19937_64& rng, int &u, int &v){
    int n=a.n;
    auto cycA = element_cycles(a);

    if((int)cycA.size()>=2){
        uniform_int_distribution<int> distC(0, (int)cycA.size()-1);
        int c1 = distC(rng);
        int c2 = distC(rng);
        while(c2==c1) c2 = distC(rng);

        uniform_int_distribution<int> d1(0, (int)cycA[c1].size()-1);
        uniform_int_distribution<int> d2(0, (int)cycA[c2].size()-1);
        u = cycA[c1][d1(rng)];
        v = cycA[c2][d2(rng)];
    } else {
        uniform_int_distribution<int> dist(0, n-1);
        u = dist(rng);
        v = dist(rng);
        while(v==u) v = dist(rng);
    }

    vector<int> rem;
    rem.reserve(n-2);
    for(int i=0;i<n;i++) if(i!=u && i!=v) rem.push_back(i);
    shuffle(rem.begin(), rem.end(), rng);

    Perm b(n);
    b.p[u]=v; b.p[v]=u;

    if(n%2==1){
        int L=n-2;
        for(int i=0;i<L;i++){
            b.p[rem[i]] = rem[(i+1)%L];
        }
    } else {
        vector<int> odds;
        for(int x=1;x<=n-3;x+=2) odds.push_back(x);
        uniform_int_distribution<int> dist(0, (int)odds.size()-1);
        int l1 = odds[dist(rng)];
        int l2 = (n-2) - l1;
        if(l2<=0 || l2%2==0){
            l1 = 1; l2 = n-3;
        }
        for(int i=0;i<l1;i++){
            b.p[rem[i]] = rem[(i+1)%l1];
        }
        for(int i=0;i<l2;i++){
            b.p[rem[l1+i]] = rem[l1 + (i+1)%l2];
        }
    }

    return b;
}

static Perm build_b_when_a_transposition(int n, int u, int v){
    vector<int> arr;
    arr.reserve(n);
    arr.push_back(u);
    arr.push_back(v);
    for(int i=0;i<n;i++) if(i!=u && i!=v) arr.push_back(i);
    Perm b(n);
    for(int i=0;i<n;i++){
        b.p[arr[i]] = arr[(i+1)%n];
    }
    return b;
}

static void print_word(const vector<Segment>& w, long long ordA, long long ordB){
    vector<Segment> ww = normalize_word(w, ordA, ordB);
    if(ww.empty()){
        cout << 0 << "\n";
        return;
    }
    if(!ww.front().isA){
        ww.insert(ww.begin(), Segment{true,0});
    }
    vector<long long> r;
    r.reserve(ww.size());
    bool expectedA=true;
    size_t i=0;
    while(i<ww.size()){
        if(ww[i].isA != expectedA){
            r.push_back(0);
            expectedA=!expectedA;
        } else {
            r.push_back(ww[i].exp);
            expectedA=!expectedA;
            i++;
        }
    }
    cout << r.size();
    for(long long x: r) cout << " " << x;
    cout << "\n";
}


static string perm_key(const Perm& p){
    string s;
    s.resize(p.n);
    for(int i=0;i<p.n;i++) s[i] = (char)p.p[i];
    return s;
}

struct WordStep { bool isA; int delta; };

static vector<Segment> steps_to_segments(const vector<WordStep>& steps, long long ordA, long long ordB){
    vector<Segment> w;
    for(const auto &st: steps){
        if(st.delta==0) continue;
        long long ord = st.isA ? ordA : ordB;
        long long e = st.delta;
        e %= ord;
        if(e<0) e += ord;
        if(e==0) continue;
        w.push_back({st.isA, e});
    }
    return normalize_word(std::move(w), ordA, ordB);
}

static void brute_small(int n, const Perm& a, const vector<Perm>& cs, Perm& bestB, vector<vector<Segment>>& bestWords){
    long long ordA = order_perm(a);
    vector<int> base(n);
    iota(base.begin(), base.end(), 0);

    int k = (int)cs.size();
    int bestCount=-1;

    Perm aInv = inverse_perm(a);

    do {
        Perm b(n);
        b.p = base;
        long long ordB = order_perm(b);
        Perm bInv = inverse_perm(b);

        unordered_map<string,int> id;
        vector<Perm> elems;
        vector<int> par;
        vector<WordStep> step;

        auto add = [&](const Perm& p, int parent, WordStep st){
            string key = perm_key(p);
            auto it=id.find(key);
            if(it!=id.end()) return it->second;
            int idx=(int)elems.size();
            id.emplace(key, idx);
            elems.push_back(p);
            par.push_back(parent);
            step.push_back(st);
            return idx;
        };

        deque<int> dq;
        int root = add(Perm::identity(n), -1, {true,0});
        dq.push_back(root);

        vector<pair<Perm,WordStep>> gens = {
            {a, {true, +1}},
            {aInv, {true, -1}},
            {b, {false, +1}},
            {bInv, {false, -1}}
        };

        while(!dq.empty()){
            int cur = dq.front(); dq.pop_front();
            for(auto &g : gens){
                Perm nxt = compose(g.first, elems[cur]);
                string key = perm_key(nxt);
                if(id.find(key)==id.end()){
                    int nx = add(nxt, cur, g.second);
                    dq.push_back(nx);
                }
            }
        }

        int cnt=0;
        vector<int> cid(k,-1);
        for(int i=0;i<k;i++){
            auto it=id.find(perm_key(cs[i]));
            if(it!=id.end()){
                cnt++;
                cid[i]=it->second;
            }
        }

        if(cnt>bestCount){
            bestCount=cnt;
            bestB=b;
            bestWords.assign(k, {});
            for(int i=0;i<k;i++){
                if(cid[i]==-1){
                    bestWords[i].clear();
                    continue;
                }
                vector<WordStep> steps;
                int v=cid[i];
                while(v!=root){
                    steps.push_back(step[v]);
                    v=par[v];
                }
                reverse(steps.begin(), steps.end());
                bestWords[i] = steps_to_segments(steps, ordA, ordB);
            }
        }

    } while(next_permutation(base.begin(), base.end()));
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if(!(cin>>n)) return 0;

    Perm a(n);
    for(int i=0;i<n;i++){
        int x;cin>>x; a.p[i]=x-1;
    }
    int k;cin>>k;
    vector<Perm> cs(k, Perm(n));
    for(int i=0;i<k;i++){
        for(int j=0;j<n;j++){
            int x;cin>>x; cs[i].p[j]=x-1;
        }
    }

    long long ordA = order_perm(a);
    pair<int,int> aSwap;
    bool aIsTrans = is_transposition(a, aSwap);

    if(is_identity(a)){
        Perm bestB = Perm::identity(n);
        int bestCnt = -1;

        int totalMasks = 1<<k;
        for(int mask=0; mask<totalMasks; mask++){
            bool ok=true;
            Perm gen = Perm::identity(n);
            bool has=false;
            for(int i=0;i<k;i++) if(mask&(1<<i)){
                if(!has){ gen = cs[i]; has=true; }
                else {
                    Perm newGen(n);
                    if(!check2_cyclic(gen, cs[i], newGen)) { ok=false; break; }
                    gen = newGen;
                }
            }
            if(!ok) continue;
            Perm b = has ? gen : Perm::identity(n);
            int cnt=0;
            for(int i=0;i<k;i++){
                if(discrete_log_cyclewise(b, cs[i]) != -1) cnt++;
            }
            if(cnt>bestCnt){
                bestCnt=cnt;
                bestB=b;
            }
        }

        for(int i=0;i<n;i++){
            if(i) cout << ' ';
            cout << bestB.p[i]+1;
        }
        cout << "\n";

        for(int i=0;i<k;i++){
            long long e = discrete_log_cyclewise(bestB, cs[i]);
            if(e==-1){
                cout << -1 << "\n";
            } else if(e==0){
                cout << 0 << "\n";
            } else {
                cout << 2 << " " << 0 << " " << e << "\n";
            }
        }
        return 0;
    }

    if(n<=4){
        Perm bestB(n);
        vector<vector<Segment>> words;
        brute_small(n, a, cs, bestB, words);

        long long ordB = order_perm(bestB);

        for(int i=0;i<n;i++){
            if(i) cout << ' ';
            cout << bestB.p[i]+1;
        }
        cout << "\n";

        for(int i=0;i<k;i++){
            if(words[i].empty() && !is_identity(cs[i])){
                cout << -1 << "\n";
            } else {
                print_word(words[i], ordA, ordB);
            }
        }
        return 0;
    }

    mt19937_64 rng((uint64_t)chrono::high_resolution_clock::now().time_since_epoch().count());

    Perm b(n);
    int base_u=-1, base_v=-1;
    vector<Segment> tWord;

    for(int attempt=0; attempt<20000; attempt++){
        if(aIsTrans){
            base_u=aSwap.first;
            base_v=aSwap.second;
            b = build_b_when_a_transposition(n, base_u, base_v);
        } else {
            b = build_random_b(a, rng, base_u, base_v);
        }
        PairGraph pg(a, b);
        if(pg.connected_big_graph()){
            break;
        }
    }

    long long ordB = order_perm(b);

    if(aIsTrans){
        tWord = {{true, 1}};
    } else {
        tWord = {{false, ordB/2}};
    }
    tWord = normalize_word(tWord, ordA, ordB);

    for(int i=0;i<n;i++){
        if(i) cout << ' ';
        cout << b.p[i]+1;
    }
    cout << "\n";

    PairGraph pg(a, b);

    int i0=min(base_u, base_v);
    int j0=max(base_u, base_v);
    int basePair = pg.idxOf[i0][j0];

    int rootA = pg.cidA[basePair];
    int rootB = pg.cidB[basePair] + pg.na;
    BFSTree treeA = bfs_tree(pg, rootA);
    BFSTree treeB = bfs_tree(pg, rootB);

    vector<vector<Segment>> transWordCache(pg.V);
    vector<char> transReady(pg.V, 0);

    auto get_trans_word = [&](int x, int y)->const vector<Segment>&{
        int u=min(x,y), v=max(x,y);
        int pid = pg.idxOf[u][v];
        if(transReady[pid]) return transWordCache[pid];

        vector<Segment> w = word_map_pair(pg, basePair, pid, treeA, rootA, treeB, rootB, ordA, ordB);
        vector<Segment> wInv = word_inverse(w, ordA, ordB);
        vector<Segment> temp = word_concat(wInv, tWord, ordA, ordB);
        vector<Segment> full = word_concat(temp, w, ordA, ordB);

        transWordCache[pid] = std::move(full);
        transReady[pid] = 1;
        return transWordCache[pid];
    };

    for(int idx=0; idx<k; idx++){
        const Perm& c = cs[idx];
        if(is_identity(c)){
            cout << 0 << "\n";
            continue;
        }
        vector<pair<int,int>> trans = factor_into_transpositions(c);
        vector<Segment> word;
        for(auto [x,y] : trans){
            const vector<Segment>& tw = get_trans_word(x,y);
            word = word_concat(word, tw, ordA, ordB);
        }
        print_word(word, ordA, ordB);
    }

    return 0;
}
