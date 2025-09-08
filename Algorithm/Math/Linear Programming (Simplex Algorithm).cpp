//https://codeforces.com/problemset/problem/375/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

#define MAXC 1010
#define MAXV 1010
#define EPS 1e-13

#define MINIMIZE -1
#define MAXIMIZE +1
#define LESSEQ -1
#define EQUAL 0
#define GREATEQ 1
#define INFEASIBLE -1
#define UNBOUNDED 666

const int N = 1005;

using ld = long double;

//Complexity: O(n^3) or much faster
//MAXV=1e5,MAXC=2 works within 80ms
//MAXV=1e5,MAXC=200 works within 1.5s

namespace lp {
  long double val[MAXV], ar[MAXC][MAXV];
  int m, n, solution_flag, minmax_flag, basis[MAXC], index[MAXV];

  /// nvars = number of variables, f = objective function, flag = MINIMIZE or MAXIMIZE
  inline void init(int nvars, long double f[], int flag){
    solution_flag = 0;
    ar[0][nvars] = 0.0;
    m = 0, n = nvars, minmax_flag = flag;
    for (int i = 0; i < n; i++){
      ar[0][i] = f[i] * minmax_flag; /// Negating sign of objective function when minimizing
    }
  }

  /// C[] = co-efficients of the constraints (LHS), lim = limit in RHS
  /// cmp = EQUAL for C[] = lim, LESSEQ for C[] <= lim, GREATEQ for C[] >= lim
  inline void add_constraint(long double C[], long double lim, int cmp){
    m++, cmp *= -1;
    if (cmp == 0){
      for (int i = 0; i < n; i++) ar[m][i] = C[i];
      ar[m++][n] = lim;
      for (int i = 0; i < n; i++) ar[m][i] = -C[i];
      ar[m][n] = -lim;
    }
    else{
      for (int i = 0; i < n; i++) ar[m][i] = C[i] * cmp;
      ar[m][n] = lim * cmp;
    }
  }

  inline void init(){ /// Initialization
    for (int i = 0; i <= m; i++) basis[i] = -i;
    for (int j = 0; j <= n; j++){
      ar[0][j] = -ar[0][j], index[j] = j, val[j] = 0;
    }
  }

  inline void pivot(int m, int n, int a, int b){ /// Pivoting and exchanging a non-basic variable with a basic variable
    for (int i = 0; i <= m; i++){
      if (i != a){
        for (int j = 0; j <= n; j++){
          if (j != b){
            ar[i][j] -= (ar[i][b] * ar[a][j]) / ar[a][b];
          }
        }
      }
    }
    for (int j = 0; j <= n; j++){
      if (j != b) ar[a][j] /= ar[a][b];
    }
    for (int i = 0; i <= m; i++){
      if (i != a) ar[i][b] = -ar[i][b] / ar[a][b];
    }
    ar[a][b] = 1.0 / ar[a][b];
    swap(basis[a], index[b]);
  }
  inline long double solve(){ /// simplex core
    init();
    int i, j, k, l;
    for (; ;){
      for (i = 1, k = 1; i <= m; i++){
        if ((ar[i][n] < ar[k][n]) || (ar[i][n] == ar[k][n] && basis[i] < basis[k] && (rand() & 1))) k = i;
      }
      if (ar[k][n] >= -EPS) break;

      for (j = 0, l = 0; j < n; j++){
        if ((ar[k][j] < (ar[k][l] - EPS)) || (ar[k][j] < (ar[k][l] - EPS) && index[i] < index[j] && (rand() & 1))){
          l = j;
        }
      }
      if (ar[k][l] >= -EPS){
        solution_flag = INFEASIBLE; /// No solution is possible
        return -1.0;
      }
      pivot(m, n, k, l);
    }
    for (; ;){
      for (j = 0, l = 0; j < n; j++){
        if ((ar[0][j] < ar[0][l]) || (ar[0][j] == ar[0][l] && index[j] < index[l] && (rand() & 1))) l = j;
      }
      if (ar[0][l] > -EPS) break;
      for (i = 1, k = 0; i <= m; i++){
        if (ar[i][l] > EPS && (!k || ar[i][n] / ar[i][l] < ar[k][n] / ar[k][l] - EPS || (ar[i][n] / ar[i][l] < ar[k][n] / ar[k][l] + EPS && basis[i] < basis[k]))){
          k = i;
        }
      }
      if (ar[k][l] <= EPS){
        solution_flag = UNBOUNDED; /// Solution is infinity, no finite solution exists
        return -666.0;
      }
      pivot(m, n, k, l);
    }
    for (i = 1; i <= m; i++){
      if (basis[i] >= 0) val[basis[i]] = ar[i][n];
    }
    solution_flag = 1; /// Successful completion
    return (ar[0][n] * minmax_flag); /// Negate the output for MINIMIZE since the objective function was negated
  }
}
long double obj[N],cons[N];

int black[N];
ll dist[N][N];
int near[N][N];
vector<pair<int, int>> adj[N];

int main() {
    IOS;
    int n, x;
    cin >> n >> x;
    int b = 0;
    for (int i = 0; i < n; i++) {
        cin >> black[i];
        b += black[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = 1e18;
        }
    }
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
        queue<int> q;
        q.push(i);
        while (q.size()) {
            int u = q.front();
            q.pop();
            for (auto [v, wt] : adj[u]) {
                if (dist[i][u] + wt < dist[i][v]) {
                    dist[i][v] = dist[i][u] + wt;
                    q.push(v);
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            near[i][j] = dist[i][j] <= x;
        }
    }
    for (int i = 0; i < n; i++) {
        obj[i] = (ld)1.0 - black[i];
    }
    lp::init(n, obj, MINIMIZE);
    for (int i = 0; i < n; i++) {
        cons[i] = 1.0;
    }
    lp::add_constraint(cons, b, EQUAL);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cons[j] = near[i][j];
        }
        lp::add_constraint(cons, 1.0, GREATEQ);
    }
    ll ans = round(lp::solve());
    if (ans < 0) {
        ans = -1;
    }
    cout << ans;

    return 0;
}
