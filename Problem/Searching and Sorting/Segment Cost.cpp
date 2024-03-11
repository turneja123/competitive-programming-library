//https://www.hackerearth.com/challenges/competitive/june-circuits-23/algorithm/segment-cost-af31ef0c/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

long long a[N];
long long pref_sum[N];
long long pref_xsum[N];


int main() {
    IOS;
    int n, x, y;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cin >> x >> y;
    x--;
    long long sum = 0, xsum = 0;
    for (int i = x; i < y; i++) {
        sum += a[i];
        xsum ^= a[i];
        pref_sum[i] = sum;
        pref_xsum[i] = xsum;
    }
    if (sum - xsum == 0) {
        cout << x + 1 << " " << x + 1 << endl;
        return 0;

    }
    int r = y - 1, l = x;
    long long t_sum = sum, t_xsum = xsum;

    for (int i = x; i < y - 1 && sum - xsum == t_sum - t_xsum; i++) {
        int j = y - 1;
        sum = t_sum;
        xsum = t_xsum;

        int low = i, high = y - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if ((sum - xsum) == ((pref_sum[mid] - pref_sum[i] + a[i]) - (pref_xsum[mid] ^ pref_xsum[i] ^ a[i]))) {
                j = min(j, mid);
                high = mid - 1;
            } else {
                low = mid + 1;
            }

        }
        if (j - i < r - l) {
            r = j;
            l = i;
        }

        t_sum -= a[i];
        t_xsum ^= a[i];
    }

    cout << l + 1 << " " << r + 1 << endl;
    return 0;
}
