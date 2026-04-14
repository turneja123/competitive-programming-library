//https://dmoj.ca/problem/mmcc15p3
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

/*
-> cnt contains the number of palindromic suffixes of the node
*/
struct PalindromicTree {
  struct node {
    int nxt[26], len, st, en, link, go, cnt, oc;
    vector<int> edges;
  };
  string s;
  vector<node> t;
  vector<ll> val;
  vector<int> lst;
  int sz, last;
  PalindromicTree() {}
  PalindromicTree(int n) {
    s = "";
    t.clear();
    t.resize(n + 9);
    val.clear();
    lst.clear();
    val.push_back(0);
    lst.push_back(2);
    sz = 2, last = 2;
    t[1].len = -1, t[1].link = 1, t[1].go = 1;
    t[2].len = 0, t[2].link = 1, t[2].go = 1;
    t[1].edges.push_back(2);
  }
  int get_link(int cur, int pos) {
    while (1) {
      int curlen = t[cur].len;
      if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
        break;
      }
      int u = t[cur].link;
      curlen = t[u].len;
      if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
        cur = u;
      } else {
        cur = t[cur].go;
      }
    }
    return cur;
  }
  ll extend(char c) {
    s.push_back(c);
    int pos = s.size() - 1;
    int cur = get_link(last, pos);
    int ch = s[pos] - 'a';
    if (t[cur].nxt[ch]) {
      last = t[cur].nxt[ch];
      t[last].oc++;
      lst.push_back(last);
      val.push_back(val.back() + t[last].cnt);
      return val.back();
    }
    sz++;
    last = sz;
    t[sz].oc = 1;
    t[sz].len = t[cur].len + 2;
    t[cur].nxt[ch] = sz;
    t[sz].en = pos;
    t[sz].st = pos - t[sz].len + 1;
    if (t[sz].len == 1) {
      t[sz].link = 2;
      t[sz].go = 1;
      t[sz].cnt = 1;
      t[2].edges.push_back(sz);
      lst.push_back(last);
      val.push_back(val.back() + t[last].cnt);
      return val.back();
    }
    cur = get_link(t[cur].link, pos);
    t[sz].link = t[cur].nxt[ch];
    t[t[cur].nxt[ch]].edges.push_back(sz);
    t[sz].cnt = 1 + t[t[sz].link].cnt;
    int u = t[sz].link;
    if (s[pos - t[u].len] == s[pos - t[t[u].link].len]) {
        t[sz].go = t[u].go;
    } else {
        t[sz].go = t[u].link;
    }
    lst.push_back(last);
    val.push_back(val.back() + t[last].cnt);
    return val.back();
  }
  void backspace() {
    s.pop_back();
    val.pop_back();
    lst.pop_back();
    last = lst.back();
  }
};

PalindromicTree pt;

void Init() {
    pt = PalindromicTree(N);
}

long long Type(char letter) {
    return pt.extend(letter);
}

void Backspace() {
    pt.backspace();
}
