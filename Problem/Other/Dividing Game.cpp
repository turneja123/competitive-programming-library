//https://atcoder.jp/contests/abc368/tasks/abc368_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

bool composite[N];
int x[N];


int main() {
    IOS;
    for (int i = 2; i < N; i++) {
        if (!composite[i]) {
            x[i]++;
            for (int j = 2 * i; j < N; j += i) {
                composite[j] = true;
                int t = j;
                while (t % i == 0) {
                    x[j]++;
                    t /= i;
                }
            }
        }
    }
    int n;
    cin >> n;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        sum ^= x[a];
    }
    if (sum > 0) {
        cout << "Anna";
    } else {
        cout << "Bruno";
    }

    return 0;
}
