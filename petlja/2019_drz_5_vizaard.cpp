#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

long long a[N];
long long temp;



int main() {
    IOS;
    int n;
    cin >> n;
    long long totxor = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        totxor ^= a[i];
    }
    long long ans = 0;
    long long curxor = 0;
    bool flag = false;
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0) {
            temp = a[i] + 1;
            ans++;
            if (a[i] > 0) {
                flag = true;
            }
        } else {
            temp = a[i];
        }
        curxor ^= temp;
    }
    if (!(flag || curxor)) {
        ans += 2;
    }

    for (long long j = 1; j < 62; j++) {
        long long cur = 0;
        flag = false;
        curxor = 0;
        for (int i = 0; i < n; i++) {
            long long pw = 1ll << j;
            if ((long long)(a[i] & pw) == 0) {
                long long l = pw - (a[i] % pw);
                long long r = a[i] % pw + 1;
                if (a[i] < pw) {
                    r = 1e18;
                }
                if (l < r) {
                    temp = a[i] + l;
                    cur += l;
                } else if (r < l) {
                    temp = a[i] - r;
                    cur += r;
                } else {
                    temp = a[i] + l;
                    cur += l;
                    flag = true;
                }
            } else {
                temp = a[i];
            }
            if (cur >= ans) {
                break;
            }
            curxor ^= temp;
        }
        if (!(flag || curxor)) {
            cur += 1;
        }
        ans = min(ans, cur);
    }
    cout << ans << endl;




    return 0;
}
