//solution for https://dmoj.ca/problem/xor
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int calcxor(int l, int r) {
    int ret = 0;
    for (int i = 1; i < 31; i++) {
        int cur = 1 << i;
        int sum = 0;
        if (r < cur) {
            break;
        }
        if ((int)(l & cur) != 0) {
            int d = l / cur;
            sum += cur * (d + 1) - l;
        }
        if ((int)(r & cur) != 0) {
            int d = r / cur;
            sum += r - d * cur + 1;
        }

        if (sum % 2 == 1) {
            ret += cur;
        }
    }
    int ct = 0;
    if (l == r){
        if (l % 2 == 1)
            ct++;
    } else {
        if (l % 2 == 1) {
            ct++;
            l++;
        }
        if (r % 2 == 1) {
            ct++;
            r--;
        }
        ct += (r - l) / 2;
    }
    if (ct % 2 == 1) {
        ret++;
    }

    return ret;

}
int main()
{
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int l, r;
        cin >> l >> r;
        cout << calcxor(l, r) << endl;
    }
    return 0;

}
