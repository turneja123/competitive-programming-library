//https://atcoder.jp/contests/arc185/tasks/arc185_c
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

vector<int> pos[N];

using cd = complex<double>;
const double PI = acos(-1);

int reverse(int num, int lg_n) {
    int res = 0;
    for (int i = 0; i < lg_n; i++) {
        if (num & (1 << i)) {
            res |= 1 << (lg_n - 1 - i);
        }
    }
    return res;
}

void fft(vector<cd>& a, bool invert) {
    int n = a.size();
    int lg_n = 0;
    while ((1 << lg_n) < n) {
        lg_n++;
    }

    for (int i = 0; i < n; i++) {
        if (i < reverse(i, lg_n)) {
            swap(a[i], a[reverse(i, lg_n)]);
        }
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}

vector<int> multiply(vector<int> & a, vector<int> & b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);

    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++) {
        result[i] = round(fa[i].real());
    }
    return result;
}


int main() {
    IOS;
    int n, x;
    cin >> n >> x;
    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        pos[p].push_back(i + 1);
    }
    vector<int> a(N, 0);
    for (int i = 1; i < N; i++) {
        if (pos[i].size() >= 1) {
            a[i] = 1;
        }
        if (pos[i].size() >= 3 && 3 * i == x) {
            vector<int> ans{pos[i][0], pos[i][1], pos[i][2]};
            sort(ans.begin(), ans.end());
            for (int k : ans) {
                cout << k << " ";
            }
            return 0;
        }
        if (pos[i].size() >= 2 && x - 2 * i >= 0 && pos[x - 2 * i].size() >= 1 && x - 2 * i != i) {
            vector<int> ans{pos[i][0], pos[i][1], pos[x - 2 * i][0]};
            sort(ans.begin(), ans.end());
            for (int k : ans) {
                cout << k << " ";
            }
            return 0;
        }
    }
    vector<int> b = multiply(a, a);
    for (int i = 1; i < N; i++) {
        if (a[i]) {
            b[2 * i]--;
        }
        b[i] /= 2;
    }
    for (int i = 1; i < N; i++) {
        if (b[i] && x - i > 0 && a[x - i]) {
            int z = i - (x - i);
            if (b[i] == 1 && a[x - i] && z > 0 && z < N && a[z]) {
                continue;
            }

            for (int j = 1; j < N; j++) {
                if (a[j] && i - j > 0 && a[i - j] && i - j != j) {
                    vector<int> ans{pos[j][0], pos[i - j][0], pos[x - i][0]};
                    sort(ans.begin(), ans.end());
                    for (int k : ans) {
                        cout << k << " ";
                    }
                    return 0;
                }
            }
        }
    }
    cout << -1;


    return 0;
}
