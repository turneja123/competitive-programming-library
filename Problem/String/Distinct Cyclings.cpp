//https://www.spoj.com/problems/CYCLINGS/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 1e9 + 7;
const long long P = 26, Q = 53;
const int N = 1505;

long long modInverse(long long a) {
    long long res = 1;
    long long y = M - 2;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

struct chash {
    long long operator()(pair<long long, long long> x) const { return x.first* M + x.second; }
};

gp_hash_table<pair<long long, long long>, int, chash> mp;

string s[2];

pair<long long, long long> rising[2][N];
pair<long long, long long> falling[2][N];

long long pw_p[N], pw_q[N];
long long inv_p[N], inv_q[N];

int n;

pair<long long, long long> calc_falling(int l, int r, int i, int j) {
    pair<long long, long long> h = falling[i][r], temp;
    if (l == 0) {
        temp = make_pair(0, 0);
    } else {
        temp = falling[i][l - 1];
    }
    h.first = (h.first - temp.first + M) % M;
    h.second = (h.second - temp.second + M) % M;
    if (n - 1 - r - j >= 0) {
        h.first = h.first * inv_p[n - 1 - r - j] % M;
        h.second = h.second * inv_q[n - 1 - r - j] % M;
    } else {
        h.first = h.first * pw_p[j + r + 1 - n] % M;
        h.second = h.second * pw_q[j + r + 1 - n] % M;

    }
    return h;
}

pair<long long, long long> calc_rising(int l, int r, int i, int j) {
    pair<long long, long long> h = rising[i][r], temp;
    if (l == 0) {
        temp = make_pair(0, 0);
    } else {
        temp = rising[i][l - 1];
    }
    h.first = (h.first - temp.first + M) % M;
    h.second = (h.second - temp.second + M) % M;
    if (l - j >= 0) {
        h.first = h.first * inv_p[l - j] % M;
        h.second = h.second * inv_q[l - j] % M;
    } else {
        h.first = h.first * pw_p[j - l] % M;
        h.second = h.second * pw_q[j - l] % M;

    }
    return h;
}

void zigzag(int y, int x, int t, int l, pair<long long, long long> h, int j) {
    while (j < 2 * n) {
        if (j % 2 == 0) {
            int dy = y ^ 1;
            if (l == -1) {
                pair<long long, long long> h_h = calc_falling(0, x, y, j);
                pair<long long, long long> temp = calc_rising(0, x, dy, j + x + 1);
                assert(j + 2 * x + 2 == 2 * n);
                mp[make_pair((h.first + h_h.first + temp.first) % M, (h.second + h_h.second + temp.second) % M)] = 1;
            } else {
                pair<long long, long long> h_h = calc_rising(x, n - 1, y, j);
                pair<long long, long long> temp = calc_falling(x, n - 1, dy, j + n - x);
                assert(j + 2 * n - 2 * x == 2 * n);
                mp[make_pair((h.first + h_h.first + temp.first) % M, (h.second + h_h.second + temp.second) % M)] = 1;
            }
        }
        h.first = (h.first + pw_p[j] * (s[y][x] - 'a' + 1)) % M;
        h.second = (h.second + pw_q[j] * (s[y][x] - 'a' + 1)) % M;
        if (t == 0) {
            y ^= 1;
        } else {
            x += l;
        }
        t ^= 1;
        j++;
    }
    mp[make_pair(h.first, h.second)] = 1;
}

int main() {
	IOS;
	pw_p[0] = 1, pw_q[0] = 1;
	inv_p[0] = 1, inv_q[0] = 1;
	for (int i = 1; i < N; i++) {
        pw_p[i] = pw_p[i - 1] * P % M;
        pw_q[i] = pw_q[i - 1] * Q % M;
        inv_p[i] = modInverse(pw_p[i]);
        inv_q[i] = modInverse(pw_q[i]);
	}
	int t;
	cin >> t;
	while (t--) {
        cin >> n >> s[0] >> s[1];
        long long p_pow = P, q_pow = Q;
        rising[0][0].first = s[0][0] - 'a' + 1;
        rising[0][0].second = s[0][0] - 'a' + 1;
        for (int i = 1; i < n; i++) {
            rising[0][i].first = (rising[0][i - 1].first + p_pow * (s[0][i] - 'a' + 1)) % M;
            rising[0][i].second = (rising[0][i - 1].second + q_pow * (s[0][i] - 'a' + 1)) % M;
            if (i != n - 1) {
                p_pow = p_pow * P % M;
                q_pow = q_pow * Q % M;
            }
        }
        long long p_max = p_pow, q_max = q_pow;
        if (n == 1) {
            p_max = 1, q_max = 1;
        }
        p_pow = P, q_pow = Q;

        rising[1][0].first = s[1][0] - 'a' + 1;
        rising[1][0].second = s[1][0] - 'a' + 1;
        for (int i = 1; i < n; i++) {
            rising[1][i].first = (rising[1][i - 1].first + p_pow * (s[1][i] - 'a' + 1)) % M;
            rising[1][i].second = (rising[1][i - 1].second + q_pow * (s[1][i] - 'a' + 1)) % M;
            if (i != n - 1) {
                p_pow = p_pow * P % M;
                q_pow = q_pow * Q % M;
            }
        }

        falling[0][0].first = p_max * (s[0][0] - 'a' + 1) % M;
        falling[0][0].second = q_max * (s[0][0] - 'a' + 1) % M;
        for (int i = 1; i < n; i++) {
            p_pow = p_pow * inv_p[1] % M;
            q_pow = q_pow * inv_q[1] % M;
            falling[0][i].first = (falling[0][i - 1].first + p_pow * (s[0][i] - 'a' + 1)) % M;
            falling[0][i].second = (falling[0][i - 1].second + q_pow * (s[0][i] - 'a' + 1)) % M;

        }
        p_pow = p_max, q_pow = q_max;
        falling[1][0].first = p_pow * (s[1][0] - 'a' + 1) % M;
        falling[1][0].second = q_pow * (s[1][0] - 'a' + 1) % M;
        for (int i = 1; i < n; i++) {
            p_pow = p_pow * inv_p[1] % M;
            q_pow = q_pow * inv_q[1] % M;
            falling[1][i].first = (falling[1][i - 1].first + p_pow * (s[1][i] - 'a' + 1)) % M;
            falling[1][i].second = (falling[1][i - 1].second + q_pow * (s[1][i] - 'a' + 1)) % M;

        }
        for (int y = 0; y < 2; y++) {
            for (int x = 0; x < n; x++) {
                //left
                int j = 0;
                pair<long long, long long> h = calc_falling(0, x, y, j);
                j += x + 1;
                int dy = y ^ 1;
                pair<long long, long long> temp = calc_rising(0, x, dy, j);
                j += x + 1;
                h.first = (h.first + temp.first) % M;
                h.second = (h.second + temp.second) % M;
                zigzag(dy, x + 1, 0, 1, h, j);
                //right
                j = 0;
                h = calc_rising(x, n - 1, y, j);
                j += n - x;
                temp = calc_falling(x, n - 1, dy, j);
                j += n - x;
                h.first = (h.first + temp.first) % M;
                h.second = (h.second + temp.second) % M;
                zigzag(dy, x - 1, 0, -1, h, j);

            }
        }

        cout << mp.size() << endl;
        mp.clear();
	}

	return 0;
}
