//https://qoj.ac/contest/2509/problem/14098
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

set<int> a, b, c;

int main() {
	IOS;
	int n;
	cin >> n;
	n *= 2;
	string s;
	cin >> s;
	int j = 0;
	for (int i = 0; i < n; i++) {
        if (s[i] == 'A') {
            a.insert(i);
            j--;
        } else if (s[i] == 'B') {
            b.insert(i);
            j++;
        } else {
            c.insert(i);
            j++;
        }
	}
	j /= 2;
	vector<pair<int, int>> ans;
	for (int i = 0, z = 0; i < n && z < j; i++) {
        if (s[i] == 'C') {
            if (b.size() && *b.begin() < i) {
                ans.push_back({*b.begin(), i});
                b.erase(b.begin());
                c.erase(i);
                z++;
            }
        }
	}
	for (int i = 0; i < n; i++) {
        if (s[i] == 'A') {
            if (b.size() && c.size()) {
                if (*b.begin() < *c.begin()) {
                    if (*b.begin() < i) {
                        cout << "NO";
                        return 0;
                    }
                    ans.push_back({i, *b.begin()});
                    b.erase(b.begin());
                    a.erase(i);

                } else {
                    if (*c.begin() < i) {
                        cout << "NO";
                        return 0;
                    }
                    ans.push_back({i, *c.begin()});
                    c.erase(c.begin());
                    a.erase(i);
                }
            } else if (b.size()) {
                if (*b.begin() < i) {
                    cout << "NO";
                    return 0;
                }
                ans.push_back({i, *b.begin()});
                b.erase(b.begin());
                a.erase(i);
            } else if (c.size()) {
                if (*c.begin() < i) {
                    cout << "NO";
                    return 0;
                }
                ans.push_back({i, *c.begin()});
                c.erase(c.begin());
                a.erase(i);
            } else {
                cout << "NO";
                return 0;
            }

        }
	}
	if (ans.size() != n / 2) {
        cout << "NO";
        return 0;
	}
	cout << "YES" << endl;
	for (auto [l, r] : ans) {
        cout << l + 1 << " " << r + 1 << endl;
	}


	return 0;
}
