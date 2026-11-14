//https://codeforces.com/gym/105493/problem/B
#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, f, c, d;
    cin >> n >> f >> c >> d;
    string s;
    cin >> s;

    int cur = f;
    int l = 0, r = 1e9, ans = -1;

    vector<int> v(n);
    vector<int> a(n);
    while (l <= r) {
        int mid = (l + r) / 2;
        int cur = f;
        int ok = 1;
        int ct = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'F') {
                ct++;
            }
        }


        for (int i = 0; i < n; i++) {
            if (s[i] == 'T') {
                if (ct == 0) {
                    a[i] = 0;
                } else {
                    a[i] = min(cur + c, mid - (c + 1));
                }
                if (a[i] < 0) {
                    ok = 0;
                    break;
                }
                cur = max(cur, a[i]);
            } else {
                a[i] = cur + c + 1;
                if (a[i] > mid) {
                    ok = 0;
                    break;
                }
                cur -= d;
                if (cur < 0) {
                    ok = 0;
                    break;
                }

                ct--;
            }
        }
        if (ok) {
            r = mid - 1;
            ans = mid;
            v = a;
        } else {
            l = mid + 1;
        }

    }
    if (ans == -1) {
        cout << "NO";
        return 0;
    }
    cout << "YES" << endl;
    cout << ans << endl;
    for (int i = 0; i < n; i++) {
        cout << v[i] << " ";
    }





    return 0;
}
