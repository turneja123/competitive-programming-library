//https://qoj.ac/contest/2511/problem/14112
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
	IOS;
	deque<int> a, b, c;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.push_front(x);
	}
	vector<pair<int, int>> ans;
	while (1) {
        for (int i = 0; i < n; i++) {
            if (c.empty() || c.front() > a.front()) {
                ans.push_back({1, 3});
                c.push_front(a.front());
                a.pop_front();
            } else if (b.empty() || b.front() > a.front()) {
                ans.push_back({1, 2});
                b.push_front(a.front());
                a.pop_front();
            } else {
                while (b.size() && c.size()) {
                    if (c.front() < b.front()) {
                        ans.push_back({3, 1});
                        a.push_front(c.front());
                        c.pop_front();
                    } else {
                        ans.push_back({2, 1});
                        a.push_front(b.front());
                        b.pop_front();
                    }
                }
                while (c.size()) {
                    ans.push_back({3, 1});
                    a.push_front(c.front());
                    c.pop_front();
                }
                while (b.size()) {
                    ans.push_back({2, 1});
                    a.push_front(b.front());
                    b.pop_front();
                }

                break;
            }
        }
        if (a.empty() && c.size() == n) {
            break;
        }
        while (b.size() && c.size()) {
            if (c.front() < b.front()) {
                ans.push_back({3, 1});
                a.push_front(c.front());
                c.pop_front();
            } else {
                ans.push_back({2, 1});
                a.push_front(b.front());
                b.pop_front();
            }
        }
        while (c.size()) {
            ans.push_back({3, 1});
            a.push_front(c.front());
            c.pop_front();
        }
        while (b.size()) {
            ans.push_back({2, 1});
            a.push_front(b.front());
            b.pop_front();
        }
	}
    cout << ans.size() << endl;
    for (auto [l, r] : ans) {
        cout << l << " " << r << endl;
    }
	return 0;
}
