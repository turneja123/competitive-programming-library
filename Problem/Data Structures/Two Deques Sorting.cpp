//https://atcoder.jp/contests/arc221/tasks/arc221_c
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int K = 20;


int prefmn[N], prefmx[N];
int sufmn[N], sufmx[N];

int before[N];
int table[K][N];

void build(int n) {
    for (int i = 1; i <= n; i++) {
        table[0][i] = before[i - 1];
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            table[k][i] = min(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
        }
    }
    return;
}

int query(int l, int r) {
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    return min(table[k][l], table[k][r - (1 << k) + 1]);
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        int best = 0;

        int l = n + 1, r = -1, cur = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] > r) {
                cur++;
            } else if (a[i] < l) {
                cur++;
            } else {
                break;
            }
            l = min(l, a[i]);
            r = max(r, a[i]);
        }
        best = max(best, cur);

        reverse(a.begin(), a.end());
        l = n + 1, r = -1, cur = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] > r) {
                cur++;
            } else if (a[i] < l) {
                cur++;
            } else {
                break;
            }
            l = min(l, a[i]);
            r = max(r, a[i]);
        }
        best = max(best, cur);
        if (a[0] == a.back()) {
            cout << best << endl;
            continue;
        }

        if (a[0] < a.back()) {
            reverse(a.begin(), a.end());
        }
        prefmn[0] = a[0];
        prefmx[0] = a[0];
        for (int i = 1; i < n; i++) {
            prefmn[i] = min(prefmn[i - 1], a[i]);
            prefmx[i] = max(prefmx[i - 1], a[i]);
        }
        sufmn[n - 1] = a.back();
        sufmx[n - 1] = a.back();
        for (int i = n - 2; i >= 0; i--) {
            sufmn[i] = min(sufmn[i + 1], a[i]);
            sufmx[i] = max(sufmx[i + 1], a[i]);
        }

        int suflast = 0;
        l = a.back(), r = a.back();
        before[n - 1] = n;

        for (int i = 0; i < n; i++) {
            if (prefmn[i] <= a.back()) {
                before[n - 1] = i;
                break;
            }
        }

        for (int i = n - 2; i >= 0; i--) {
            if (a[i] > r) {
                //on mora pre prvog veceg s leva
                int L = 0, R = n - 1;
                before[i] = n;
                while (L <= R) {
                    int mid = (L + R) / 2;
                    if (prefmx[mid] >= a[i]) {
                        before[i] = mid;
                        R = mid - 1;
                    } else {
                        L = mid + 1;
                    }
                }

            } else if (a[i] < l) {
                //on mora pre prvog manjeg s leva
                int L = 0, R = n - 1;
                before[i] = n;
                while (L <= R) {
                    int mid = (L + R) / 2;
                    if (prefmn[mid] <= a[i]) {
                        before[i] = mid;
                        R = mid - 1;
                    } else {
                        L = mid + 1;
                    }
                }
            } else {
                suflast = i + 1;
                break;
            }
            l = min(l, a[i]);
            r = max(r, a[i]);
        }
        build(n);
        l = n + 1, r = -1;
        for (int i = 0; i < n; i++) {
            if (a[i] > r) {
                int L = 0, R = n - 1, spl = 0;
                while (L <= R) {
                    int mid = (L + R) / 2;
                    if (sufmx[mid] >= a[i]) {
                        L = mid + 1;
                        spl = mid;
                    } else {
                        R = mid - 1;
                    }
                }
                if (spl >= suflast && query(suflast, spl) <= i) {
                    int L = suflast, R = spl, pos = suflast;
                    while (L <= R) {
                        int mid = (L + R) / 2;
                        if (query(mid, spl) <= i) {
                            L = mid + 1;
                            pos = mid;
                        } else {
                            R = mid - 1;
                        }
                    }
                    suflast = pos + 1;
                }
            } else if (a[i] < l) {
                int L = 0, R = n - 1, spl = 0;
                while (L <= R) {
                    int mid = (L + R) / 2;
                    if (sufmn[mid] <= a[i]) {
                        L = mid + 1;
                        spl = mid;
                    } else {
                        R = mid - 1;
                    }
                }
                if (spl >= suflast && query(suflast, spl) <= i) {
                    int L = suflast, R = spl, pos = suflast;
                    while (L <= R) {
                        int mid = (L + R) / 2;
                        if (query(mid, spl) <= i) {
                            L = mid + 1;
                            pos = mid;
                        } else {
                            R = mid - 1;
                        }
                    }
                    suflast = pos + 1;
                }
            } else {
                break;
            }
            suflast = max(suflast, i + 1);
            best = max(best, i + 1 + n - suflast);
            l = min(l, a[i]);
            r = max(r, a[i]);
        }
        cout << best << endl;

        /*1
        5
        4 3 2 2 1*/
    }
    return 0;
}
