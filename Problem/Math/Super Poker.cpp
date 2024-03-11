//https://www.beecrowd.com.br/judge/en/problems/view/1353
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 1e9 + 9;
const int K = 15;

int sz;
long long cards = 4;

long long f[K][K];

vector<vector<long long>> mat;
vector<vector<long long>> aux;

long long bin(long long n, long long k) {
    if (!k) {
        return (long long)1;
    }
    long long ans = 1;
    for (long long i = 1; i <= n; i++) {
        ans *= i;
    }
    for (long long i = 1; i <= k; i++) {
        ans /= i;
    }
    for (long long i = 1; i <= n - k; i++) {
        ans /= i;
    }
    return ans;
}

vector<vector<long long>> mul(vector<vector<long long>> base, vector<vector<long long>> m) {
    vector<vector<long long>> ret;
    ret.assign(sz, vector<long long>(sz, 0));
    for (int i = 0; i < sz; i++) {
        for (int p = 0; p < sz; p++) {
            for (int j = 0; j < sz && base[i][p]; j++) {
                ret[i][j] += (base[i][p] * m[p][j]) % M;
                ret[i][j] %= M;
            }
        }
    }
    return ret;
}

void expo(int k) {
    while (k) {
        if (k % 2 == 1) {
            mat = mul(aux, mat);
        }
        aux = mul(aux, aux);
        k /= 2;
    }
}

int main() {
    IOS;
    f[0][0] = 1;
    for (long long i = 1; i < K; i++) {
        for (long long j = 1; j <= i; j++) {
            for (long long k = 0; k <= min(cards, j); k++) {
                f[i][j] += bin(cards, k) * f[i - j][j - k];
                f[i][j] %= M;
            }
        }
    }
    while (1) {
        long long n, k;
        cin >> n >> k;
        if (n == 0 && k == 0) {
            return 0;
        }
        if (n < K) {
            long long ans = 0;
            for (int i = 1; i <= k; i++) {
                ans += f[n][i];
                ans %= M;
            }
            cout << ans << endl;
            continue;
        }

        sz = k * (k + 1);

        mat.assign(k * (k + 1), vector<long long>(k * (k + 1), 0));
        aux.assign(k * (k + 1), vector<long long>(k * (k + 1), 0));

        for (long long i = 0; i < k; i++) {
            for (long long j = 0; j <= k; j++) {
                mat[i * (k + 1) + j][0] = f[k - 1 - i][j];
            }
        }
        for (long long i = 1; i <= k; i++) {
            for (long long j = 0; j <= min(cards, i); j++) {
                aux[i][i * (k + 2) - k - 1 - j] = bin(cards, j);
            }
        }
        for (long long i = 1; i < k; i++) {
            for (long long j = 0; j <= k; j++) {
                aux[i * (k + 1) + j][(i - 1) * (k + 1) + j] = 1;
            }
        }

        expo(n - k + 1);

        long long ans = 0;
        for (int i = 1; i <= k; i++) {
            ans += mat[i][0];
            ans %= M;
        }
        cout << ans << endl;

        mat.clear();
        aux.clear();
    }
    return 0;
}
