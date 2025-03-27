//https://cses.fi/problemset/task/2107/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

vector<int> prefix_function(const string &s) {
	int n = s.size();
	vector<int> p(n);
	for (int i = 1, j = 0; i < n; i++) {
		while (j > 0 && s[j] != s[i]) {
            j = p[j - 1];
        }
		if (s[i] == s[j]) {
            j++;
        }
		p[i] = j;
	}
	return p;
}

vector<int> z_function(string &s) {
    int n = s.size();
	vector<int> z(n);
	z[0] = n;
	int l = 0;
	int r = 0;
	for (int i = 1; i < n; i++) {
		z[i] = max(0, min(z[i - l], r - i + 1));
		while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
			l = i;
			r = i + z[i];
			z[i]++;
		}
	}

	return z;
}


int main() {
    IOS;
    string s;
    cin >> s;
    vector<int> p = prefix_function(s), z = z_function(s);
    z[0] = 0;
    for (auto f : z) {
        cout << f << " ";
    }
    cout << endl;
    for (auto f : p) {
        cout << f << " ";
    }
    return 0;
}
