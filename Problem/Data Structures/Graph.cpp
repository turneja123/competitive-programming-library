//https://www.spoj.com/problems/GRAPH2/
#include <bits/stdc++.h>
using namespace std;
#define f(i,b) for(int i=0;i<b;++i)
const int N = 1e5 + 5,SQ = 320;
long long a[2][2],s[N][2],adj_h[SQ][SQ],w;
int z[N],c[N],he[N],id[N],d[N],n,m,q,u,v,h;
vector<pair<int,int>> adj[N];
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n>>m;
    f(i,n){
        cin>>c[i];
        z[i] = i;
    }
    f(i,m){
        cin>>u>>v>>w;
        u--,v--;
        d[u]++,d[v]++;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    sort(z,z+n,[](auto u,auto v){return d[u]>d[v];});
    h=min(SQ,n);
    f(i,n){
        id[z[i]]=i;
    }
    f(i,h){
        he[z[i]]=1;
    }
    f(i,n){
        for (auto[j,w]:adj[i]) {
            if(j>i)continue;
            u=i,v=j;
            if (id[u]<id[v])swap(u,v);
            a[c[u]][c[v]]+=w;
            if (he[u]) {
                adj_h[id[u]][id[v]]+=w;
                adj_h[id[v]][id[u]]+=w;
            } else if(he[v])s[v][c[u]]+=w;
        }
    }
    cin>>q;
    f(i,q) {
        char t;
        cin>>t;
        if (t == 'Q') {
            cin>>u>>v;
            cout<<a[u][v]+(u!=v?a[v][u]:0)<<'\n';
        } else {
            cin>>u;
            u--;
            n=c[u];
            if(he[u]){
                a[n][0]-=s[u][0];
                a[n][1]-=s[u][1];
                a[n^1][0]+=s[u][0];
                a[n^1][1]+=s[u][1];
                int i=id[u];
                f(j,h) {
                    w=adj_h[i][j],v=z[j];
                    a[n][c[v]]-=w;
                    a[n^1][c[v]]+=w;

                }
            }else{
                for (auto[v,w]:adj[u]){
                    a[n][c[v]]-=w;
                    a[n^1][c[v]]+=w;
                    if (he[v]) {
                        s[v][n]-=w;
                        s[v][n^1]+=w;
                    }
                }
            }
            c[u]^=1;
        }
    }

    return 0;
}
