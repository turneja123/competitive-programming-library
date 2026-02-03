//https://codeforces.com/contest/2187/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 31;
const ll INF = 1e18;

ll dp[N][3][3];
tuple<int, int, int, int> go[N][3][3];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> da, db;
        while (n > 0) {
            da.push_back(n % 2);
            n /= 2;
        }
        while (da.size() < 31) {
            da.push_back(0);
        }
        while (m > 0) {
            db.push_back(m % 2);
            m /= 2;
        }
        while (db.size() < 31) {
            db.push_back(0);
        }

        for (int i = 30; i >= 0; i--) {
            for (int ja = 0; ja < 3; ja++) {
                for (int jb = 0; jb < 3; jb++) {
                    dp[i][ja][jb] = INF;
                }
            }
        }
        dp[30][0][0] = 0;
        dp[30][0][1] = 1 << 30;
        dp[30][1][0] = 1 << 30;

        go[30][0][0] = {0, 0, 0, 0};
        go[30][1][0] = {0, 0, 1, 0};
        go[30][0][1] = {0, 0, 0, 1};

        for (int i = 30; i > 0; i--) {
            for (int ja = 0; ja < 3; ja++) {
                for (int jb = 0; jb < 3; jb++) {
                    for (int adda = 0; adda < 2; adda++) {
                        for (int addb = 0; addb < 2; addb++) {
                            if (adda + addb > 1) {
                                continue;
                            }
                            int costa = 0, costb = 0;
                            int ja_nx = ja, jb_nx = jb;
                            if (ja == 0) {
                                if (adda > da[i - 1]) {
                                    ja_nx = 1;
                                    costa = 1 << (i - 1);
                                } else if (adda < da[i - 1]) {
                                    ja_nx = 2;
                                    costa = 1 << (i - 1);
                                }
                            } else if (ja == 1) {
                                costa = (adda - da[i - 1]) * (1 << (i - 1));
                            } else {
                                costa = (da[i - 1] - adda) * (1 << (i - 1));
                            }

                            if (jb == 0) {
                                if (addb > db[i - 1]) {
                                    jb_nx = 1;
                                    costb = 1 << (i - 1);
                                } else if (addb < db[i - 1]) {
                                    jb_nx = 2;
                                    costb = 1 << (i - 1);
                                }
                            } else if (jb == 1) {
                                costb = (addb - db[i - 1]) * (1 << (i - 1));
                            } else {
                                costb = (db[i - 1] - addb) * (1 << (i - 1));
                            }

                            if (dp[i][ja][jb] + costa + costb < dp[i - 1][ja_nx][jb_nx]) {
                                dp[i - 1][ja_nx][jb_nx] = dp[i][ja][jb] + costa + costb;
                                go[i - 1][ja_nx][jb_nx] = {ja, jb, adda, addb};
                            }
                        }
                    }
                }
            }
        }
        ll best = INF;
        int JA, JB;
        for (int ja = 0; ja < 3; ja++) {
            for (int jb = 0; jb < 3; jb++) {
                if (dp[0][ja][jb] < best) {
                    best = dp[0][ja][jb];
                    JA = ja;
                    JB = jb;
                }
            }
        }
        int a = 0, b = 0;
        int i = 0;
        while (i < 31) {

            auto [ja_nx, jb_nx, adda, addb] = go[i][JA][JB];
            a += adda * (1 << i);
            b += addb * (1 << i);
            JA = ja_nx;
            JB = jb_nx;
            i++;
        }

        cout << a << " " << b << endl;

    }


    return 0;
}
