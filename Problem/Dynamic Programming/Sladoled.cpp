//https://evaluator.hsin.hr/events/coci26_4/tasks/HONI252647sladoled/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;
const int K = 50001;

bitset<K> b[N];

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        b[i][0] = 1;
    }
    for (int i = 0; i < q; i++) {
        int j, x;
        cin >> j >> x;
        j--;
        while (x < K && !b[j][x]) {
            b[j] |= b[j] << x;
            x <<= 1;
        }
        cout << b[j].count() - 1 << endl;
    }

    return 0;
}
