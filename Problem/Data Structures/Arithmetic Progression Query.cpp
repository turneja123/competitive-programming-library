//solution for https://www.spoj.com/problems/UPDTARR/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 100005;
const int SQ = sqrt(N);

int arr[N];
int m[SQ][SQ];

int main() {
    IOS;
    int t, k = 1;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        for (int i = 1; i <= n; i++) {
            arr[i] = 0;
        }
        for (int i = 0; i < SQ; i++) {
            for (int j = 0; j < SQ; j++) {
                m[i][j] = 0;
            }
        }
        for (int i = 0; i < q; i++) {
            int a, b;
            cin >> a >> b;
            if (b >= SQ) {
                for (int j = a % b; j <= n; j += b) {
                    if (j == 0) {
                        continue;
                    }
                    arr[j]++;
                }
            } else {
                m[b][a % b]++;
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j < SQ; j++) {
                arr[i] += m[j][i % j];
            }
        }
        cout << "Case " << k++ << ": ";
        for (int i = 1; i <= n; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
}
