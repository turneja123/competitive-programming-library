//https://www.spoj.com/problems/ZEROCNT/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

long long dp[64][64][64][3][2]; //i, broj GRUPE, broj obojenih nula, tight, sa cim se zavrsava
int a[2];

long long calc(long long n, int k) {
    vector<int> b;
    while (n > 0) {
        b.push_back(n % 2);
        n /= 2;
    }
    reverse(b.begin(), b.end());
    long long ans = 0;
    dp[0][0][0][2][1] = 1;
    for (int i = 1; i < b.size(); i++) {
        int c = b[i];
        for (int j = 0; j < 64; j++) {
            for (int x = 0; x < 64; x++) {
                dp[i][j][x][0][0] = 0;
                dp[i][j][x][1][0] = 0;
                dp[i][j][x][2][0] = 0;
                dp[i][j][x][0][1] = 0;
                dp[i][j][x][1][1] = 0;
                dp[i][j][x][2][1] = 0;
                if (c == 0) {
                    //dodajem 0
                    if (j != 0) {
                        int add = 0;
                        if ((j - 1) % k == 0) {
                            add = 1;
                        }
                        if (x - add >= 0) {
                            //0 na 0
                            dp[i][j][x][2][0] += dp[i - 1][j][x - add][2][0];
                            dp[i][j][x][1][0] += dp[i - 1][j][x - add][1][0];
                            dp[i][j][x][0][0] += dp[i - 1][j][x - add][0][0];
                            //0 na 1
                            dp[i][j][x][2][0] += dp[i - 1][j - 1][x - add][2][1];
                            dp[i][j][x][1][0] += dp[i - 1][j - 1][x - add][1][1];
                            dp[i][j][x][0][0] += dp[i - 1][j - 1][x - add][0][1];
                        }
                    }

                    //dodajem 1
                    //1 na 0
                    dp[i][j][x][1][1] += dp[i - 1][j][x][2][0] + dp[i - 1][j][x][1][0];
                    dp[i][j][x][0][1] += dp[i - 1][j][x][0][0];
                    //1 na 1
                    dp[i][j][x][1][1] += dp[i - 1][j][x][2][1] + dp[i - 1][j][x][1][1];
                    dp[i][j][x][0][1] += dp[i - 1][j][x][0][1];
                } else {
                    //dodajem 0
                    if (j != 0) {

                        int add = 0;
                        if ((j - 1) % k == 0) {
                            add = 1;
                        }
                        if (x - add >= 0) {
                            //0 na 0
                            dp[i][j][x][0][0] += dp[i - 1][j][x - add][2][0] + dp[i - 1][j][x - add][0][0];
                            dp[i][j][x][1][0] += dp[i - 1][j][x - add][1][0];
                            //0 na 1
                            dp[i][j][x][0][0] += dp[i - 1][j - 1][x - add][2][1] + dp[i - 1][j - 1][x - add][0][1];
                            dp[i][j][x][1][0] += dp[i - 1][j - 1][x - add][1][1];
                        }
                    }
                    //dodajem 1
                    //1 na 0
                    dp[i][j][x][2][1] += dp[i - 1][j][x][2][0];
                    dp[i][j][x][1][1] += dp[i - 1][j][x][1][0];
                    dp[i][j][x][0][1] += dp[i - 1][j][x][0][0];
                    //1 na 1
                    dp[i][j][x][2][1] += dp[i - 1][j][x][2][1];
                    dp[i][j][x][1][1] += dp[i - 1][j][x][1][1];
                    dp[i][j][x][0][1] += dp[i - 1][j][x][0][1];
                }
            }
        }
    }
    for (int i = 1; i < b.size(); i++) {
        for (int j = 1; j < 64; j++) {
            for (int x = 1; x < 64; x++) {
                ans += (dp[i][j][x][0][0] + dp[i][j][x][2][0]) * x;
                ans += (dp[i][j][x][0][1] + dp[i][j][x][2][1]) * x;
                if (i != b.size() - 1) {
                    ans += (dp[i][j][x][1][0]) * x;
                    ans += (dp[i][j][x][1][1]) * x;
                }
            }
        }

    }
    return ans;
}

int main() {
  //  IOS;
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        for(int i = 0; i < 2; i++) {
            iss >> a[i];
        }
        int n = a[0], k = a[1];
        long long ans = calc(n, k);
        cout << ans << endl;
    }
    return 0;
}
