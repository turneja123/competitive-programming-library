//https://www.spoj.com/problems/MEPPERM/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 66005;
const int SQ = 1000;

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

vector<vector<int>> cyc[N];

int main() {
    IOS;
    int n;
    cin >> n;
    vector<int> p(n), a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    int q;
    cin >> q;
    vector<int> ans(q, 0);
    vector<int> visited(n);
    for (int i = 0; i < n; i++) {
        if (visited[i]) {
            continue;
        }
        vector<int> cur;
        int j = i;
        while (!visited[j]) {
            visited[j] = 1;
            cur.push_back(j);
            j = p[j];
        }
        int L = cur.size();
        cyc[L].push_back(cur);
    }
    for (int L = 1; L <= n; L++) {
        if (cyc[L].empty()) {
            continue;
        }
        vector<int> mx(L, 0);
        for (auto c : cyc[L]) {
            if (L < SQ) {
                for (int j = 0; j < L; j++) {
                    for (int i = 0; i < L; i++) {
                        int ind = i + j;
                        if (ind >= L) {
                            ind -= L;
                        }
                        mx[j] = max(mx[j], a[c[i]] + b[c[ind]]);
                    }
                }
                continue;
            }
            vector<vector<cd>> ffta(17), fftb(17);
            vector<int> marka(17, 0), markb(17, 0);
            vector<vector<cd>> fftans(33);
            int s = 0;
            for (int x = 0; x <= 16; x++) {
                vector<int> A = c, B = c;
                for (int i = 0; i < L; i++) {
                    if (a[c[i]] == x) {
                        A[i] = 1;
                        marka[x] = 1;
                    } else {
                        A[i] = 0;
                    }
                    if (b[c[i]] == x) {
                        B[i] = 1;
                        markb[x] = 1;
                    } else {
                        B[i] = 0;
                    }
                }

                reverse(A.begin(), A.end());
                for (int i = 0; i < L - 1; i++) {
                    int v = B[i];
                    B.push_back(v);
                }
                vector<cd> fa(A.begin(), A.end()), fb(B.begin(), B.end());
                int n = 1;
                while (n < A.size() + B.size()) {
                    n <<= 1;
                }
                s = n;
                fa.resize(n);
                fb.resize(n);

                if (marka[x]) {
                    fft(fa, false);
                    ffta[x] = fa;
                }

                if (markb[x]) {
                    fft(fb, false);
                    fftb[x] = fb;
                }
            }
            for (int w = 32; w >= 0; w--) {
                fftans[w].resize(s);
                for (int x = 0; x <= w; x++) {
                    int y = w - x;
                    if (y > 16 || x > 16 || !marka[x] || !markb[y]) {
                        continue;
                    }
                    for (int i = 0; i < s; i++) {
                        fftans[w][i] += ffta[x][i] * fftb[y][i];
                    }
                }
                fft(fftans[w], true);

                vector<int> result(s);
                for (int i = 0; i < s; i++) {
                    result[i] = round(fftans[w][i].real());
                }
                for (int i = L - 1; i < 2 * L - 1; i++) {
                    if (result[i]) {
                        mx[i - (L - 1)] = max(mx[i - (L - 1)], w);
                    }
                }
                int br = 1;
                for (int i = 0; i < L; i++) {
                    if (mx[i] < w) {
                        br = 0;
                    }
                }
                if (br) {
                    break;
                }
            }
        }
        for (int i = 0, j = 0; i < q; i++, j++) {
            if (j >= L) {
                j -= L;
            }
            ans[i] = max(ans[i], mx[j]);
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}
