//https://www.spoj.com/problems/DELTACA2/
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl "\n"
#define IOS ios::sync_with_stdio(false); cin.tie(nullptr);

using i128 = __int128_t;

struct Z2{ i128 a,b; };

static inline Z2 mulZ(const Z2& x,const Z2& y){ return { x.a*y.a + (i128)2*x.b*y.b, x.a*y.b + x.b*y.a }; }
static inline Z2 U(const Z2& x){ return { (i128)3*x.a + (i128)4*x.b, (i128)2*x.a + (i128)3*x.b }; }
static inline Z2 Ui(const Z2& x){ return { (i128)3*x.a - (i128)4*x.b, -(i128)2*x.a + (i128)3*x.b }; }

static inline int sgn(i128 s,i128 t){
    if(!t) return (s>0)-(s<0);
    if(t>0) return s>=0 ? 1 : (((i128)2*t*t > s*s) - ((i128)2*t*t < s*s));
    return s<=0 ? -1 : ((s*s > (i128)2*t*t) - (s*s < (i128)2*t*t));
}
static inline int cmpZ(const Z2& x,const Z2& y){ return sgn(x.a-y.a,x.b-y.b); }
static inline bool ltZ(const Z2& x,const Z2& y){ return cmpZ(x,y)<0; }
static inline bool leZ(const Z2& x,const Z2& y){ return cmpZ(x,y)<=0; }
static inline bool gtZ(const Z2& x,const Z2& y){ return cmpZ(x,y)>0; }

static inline Z2 redBeta(Z2 x,ll d){
    if(x.a<0) x.a=-x.a,x.b=-x.b;
    Z2 lo{(i128)d,0}, hi{(i128)3*d,(i128)2*d};
    while(ltZ(x,lo)) x=U(x);
    while(!ltZ(x,hi)) x=Ui(x);
    return x;
}
static inline Z2 redAlpha(Z2 x,ll d){
    if(x.a<0) x.a=-x.a,x.b=-x.b;
    Z2 lo{(i128)d,(i128)d}, hi{(i128)7*d,(i128)5*d};
    while(leZ(x,lo)) x=U(x);
    while(gtZ(x,hi)) x=Ui(x);
    return x;
}

static unordered_map<int,pair<int,int>> rep_cache;

static inline pair<int,int> rep_split_prime(int p){
    auto it=rep_cache.find(p);
    if(it!=rep_cache.end()) return it->second;
    int vmax=(int)(sqrtl((long double)p/2.0L)+5);
    for(int v=1; v<=vmax; v++){
        long long t=(long long)p + 2LL*v*v, u=(long long)sqrtl((long double)t);
        while((u+1)*(u+1)<=t) u++;
        while(u*u>t) u--;
        if(u*u==t) return rep_cache[p]={ (int)u, v };
    }
    return rep_cache[p]={0,0};
}

static inline ll powll(ll p,int e){ ll r=1; while(e--) r*=p; return r; }

struct MZ2{ ll a,b; };
static inline ll normm(ll x,ll mod){ x%=mod; if(x<0) x+=mod; return x; }
static inline MZ2 mulM(const MZ2& x,const MZ2& y,ll mod){
    return { (ll)(((i128)x.a*y.a + (i128)2*x.b*y.b)%mod), (ll)(((i128)x.a*y.b + (i128)x.b*y.a)%mod) };
}
static inline MZ2 powM(MZ2 a, unsigned long long e, ll mod){
    MZ2 r{1%mod,0};
    while(e){
        if(e&1ULL) r=mulM(r,a,mod);
        a=mulM(a,a,mod), e>>=1ULL;
    }
    return r;
}

int main(){
    IOS
    int T; cin>>T;
    while(T--){
        unsigned long long n; ll d,m; cin>>n>>d>>m;
        int L; cin>>L;
        vector<pair<int,int>> fac(L);
        for(int i=0;i<L;i++) cin>>fac[i].first>>fac[i].second;

        ll inert=1;
        vector<tuple<int,int,int>> split;

        for(auto [p,e]:fac){
            if(p==2 || p%8==3 || p%8==5) inert*=powll(p,e);
            else{
                auto [u,v]=rep_split_prime(p);
                split.push_back({2*e,u,v});
            }
        }

        vector<Z2> betas={ redBeta({(i128)inert,0},d) };

        for(auto [twoe,u,v]:split){
            vector<Z2> powPi(twoe+1), powPib(twoe+1);
            powPi[0]=powPib[0]={1,0};
            for(int i=1;i<=twoe;i++) powPi[i]=redBeta(mulZ(powPi[i-1],{u,v}),d), powPib[i]=redBeta(mulZ(powPib[i-1],{u,-v}),d);

            vector<Z2> ch(twoe+1);
            for(int k=0;k<=twoe;k++) ch[k]=redBeta(mulZ(powPi[k],powPib[twoe-k]),d);

            vector<Z2> nxt; nxt.reserve(betas.size()*ch.size());
            for(auto &x:betas) for(auto &y:ch) nxt.push_back(redBeta(mulZ(x,y),d));
            betas.swap(nxt);
        }

        vector<Z2> bases; bases.reserve(betas.size());
        for(auto &b:betas) bases.push_back(redAlpha({ b.a + (i128)2*b.b, b.a + b.b }, d));

        sort(bases.begin(),bases.end(),[](const Z2& x,const Z2& y){ return x.a==y.a ? x.b<y.b : x.a<y.a; });
        bases.erase(unique(bases.begin(),bases.end(),[](const Z2& x,const Z2& y){ return x.a==y.a && x.b==y.b; }),bases.end());
        sort(bases.begin(),bases.end(),[](const Z2& x,const Z2& y){ return ltZ(x,y); });

        unsigned long long B=bases.size(), block=(n-1)/B;
        Z2 base=bases[(n-1)%B];

        ll mod2=2*m;
        MZ2 alph{ (ll)normm((ll)(base.a%(i128)mod2),mod2), (ll)normm((ll)(base.b%(i128)mod2),mod2) };
        alph=mulM(alph, powM({3%mod2,2%mod2}, block, mod2), mod2);

        ll x=alph.a, c=alph.b, dd=normm(d,mod2), A=normm(x-dd,mod2)/2%m;
        cout<<A<<" "<<(A + d%m)%m<<" "<<normm(c,m)%m<<endl;
    }
    return 0;
}
