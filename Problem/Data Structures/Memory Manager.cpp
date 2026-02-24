//https://judge.beecrowd.com/en/problems/view/1369
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;


int conv(string s) {
    int x, m = 1;
    if (s[s.size() - 2] == 'M') {
        m = 1024;
    } else if (s[s.size() - 2] == 'G') {
        m = 1024 * 1024;
    }
    s.pop_back();
    s.pop_back();
    return stoi(s) * m;
}

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    int val;
    Node* parent;
    int priority;
    int cnt;
    int lazy;
    Node* left;
    Node* right;

    Node(int val) : val(val), parent(nullptr), priority(generator()), cnt(1), lazy(0), left(nullptr), right(nullptr) {}
};

int a[N];
Node* ptr[N];
Node* root;

int get_cnt(Node* node) {
    return node ? node->cnt : 0;
}

void upd_cnt(Node* node) {
    if (node) {
        node->cnt = 1 + get_cnt(node->left) + get_cnt(node->right);
    }
}

void apply(Node* node) {
    if (node && node->lazy != 0) {
        node->val += node->lazy;
        if (node->left) {
            node->left->lazy += node->lazy;
        }
        if (node->right) {
            node->right->lazy += node->lazy;
        }
        node->lazy = 0;
    }
}

void split(Node* node, int k, Node*& left, Node*& right) {
    if (!node) {
        left = right = nullptr;
        return;
    }
    apply(node);
    if (node->val >= k) {
        split(node->left, k, left, node->left);
        if (left) {
            left->parent = nullptr;
        }
        if (node->left) {
            node->left->parent = node;
        }
        right = node;
    } else {
        split(node->right, k, node->right, right);
        if (right) {
            right->parent = nullptr;
        }
        if (node->right) {
            node->right->parent = node;
        }
        left = node;
    }
    upd_cnt(node);
}

Node* merge(Node* left, Node* right) {
    if (!left || !right) {
        return left ? left : right;
    }
    if (left->priority > right->priority) {
        apply(left);
        left->right = merge(left->right, right);
        if (left->right) {
            left->right->parent = left;
        }
        upd_cnt(left);
        return left;
    } else {
        apply(right);
        right->left = merge(left, right->left);
        if (right->left) {
            right->left->parent = right;
        }
        upd_cnt(right);
        return right;
    }
}

void insert(int x, int j) {
    Node *new_node = new Node(x);
    ptr[j] = new_node;
    Node *left, *right;
    split(root, x, left, right);
    root = merge(merge(left, new_node), right);
    if (root) root->parent = nullptr;
}

void erase(int x) {
    Node *a, *b, *c, *d;
    split(root, x, a, b);
    split(b, x + 1, c, d);
    root = merge(a, d);
    if (root) root->parent = nullptr;
}


int dfs(vector<Node*> &v, int i) {
    Node* node = v[i];
    apply(node);
    if (i == v.size() - 1) {
        return node->val;
    }
    if (v[i + 1] == node->left) {
        return dfs(v, i + 1);
    }
    return dfs(v, i + 1);
}

int main() {
    IOS;
    while (1) {
        int n;
        cin >> n;
        if (n == 0) {
            break;
        }
        string s;
        cin >> s;
        int m = conv(s), sum = 0;
        vector<pair<string, int>> queries;

        for (int i = 0; i < n; i++) {
            string t;
            cin >> t;
            if (t == "insere") {
                string nm, sz;
                cin >> nm >> sz;
                queries.push_back({nm, conv(sz)});
            } else if (t == "remove") {
                string nm;
                cin >> nm;
                queries.push_back({nm, -1});
            } else {
                queries.push_back({"", -2});
            }
        }
        set<pair<int, int>> slots;
        set<pair<int, int>> slots_by_x;

        slots.insert({m, 0});
        slots_by_x.insert({0, m});
        map<string, int> mp;
        root = nullptr;
        int ok = 1;

        auto otimiza = [&]() -> void {
            auto it = slots_by_x.begin();
            int mov = 0;
            while (it != slots_by_x.end()) {
                auto [st, len] = *it;
                st -= mov;
                Node *l, *r;
                split(root, st, l, r);
                if (r) {
                    r->lazy -= len;
                }
                root = merge(l, r);
                if (root) root->parent = nullptr;
                mov += len;
                it++;
            }

            slots_by_x.clear();
            slots.clear();
            if (sum < m) {
                slots_by_x.insert({sum, m - sum});
                slots.insert({m - sum, sum});
            }

        };


        for (int i = 0; i < n; i++) {
            auto [t, x] = queries[i];
            if (x > 0) {
                mp[t] = i;
                a[i] = x;
                auto itt = slots.lower_bound({x, -1});
                if (itt == slots.end()) {
                    otimiza();
                }
                auto it = slots.lower_bound({x, -1});

                if (it != slots.end()) {
                    int len = it->first, st = it->second;
                    insert(st, i);
                    slots.erase({len, st});
                    slots_by_x.erase({st, len});
                    if (len - x > 0) {
                        slots.insert({len - x, st + x});
                        slots_by_x.insert({st + x, len - x});
                    }
                } else {
                    ok = 0;
                    break;
                }
                sum += x;
            } else if (x == -1) {
                if (mp.find(t) == mp.end() || mp[t] == -1) {
                    continue;
                }
                int j = mp[t];
                Node* node = ptr[j];
                vector<Node*> v{node};
                while (node != root) {
                    node = node->parent;
                    v.push_back(node);
                    if (node == root) {
                        break;
                    }
                }
                reverse(v.begin(), v.end());
                int x = dfs(v, 0);
                erase(x);



                int st = x, len = a[j];
                sum -= len;
                if (slots_by_x.size()) {
                    auto it = slots_by_x.lower_bound({st, -1});
                    if (it != slots_by_x.begin()) {
                        it--;
                        auto [ST, LEN] = *it;
                        if (ST + LEN == st) {
                            st = ST;
                            len += LEN;
                            slots.erase({LEN, ST});
                            slots_by_x.erase({ST, LEN});
                        }
                    }
                }
                if (slots_by_x.size()) {
                    auto it = slots_by_x.lower_bound({st, -1});
                    if (it != slots_by_x.end()) {
                        auto [ST, LEN] = *it;
                        if (st + len == ST) {
                            len += LEN;
                            slots.erase({LEN, ST});
                            slots_by_x.erase({ST, LEN});
                        }
                    }
                }
                slots.insert({len, st});
                slots_by_x.insert({st, len});
                mp[t] = -1;
            } else {
                otimiza();
            }
        }
        if (!ok) {
            cout << "ERRO: disco cheio" << endl;
            continue;
        }
        vector<int> sizes(8, 0);
        int bl = m / 8;
        for (auto [st, len] : slots_by_x) {
            for (int i = 0; i < 8; i++) {
                int l = max(st, i * bl), r = min(st + len, (i + 1) * bl);
                if (r - l > 0) {
                    sizes[i] += r - l;
                }
            }
        }
        for (int i = 0; i < 8; i++) {
            char c;
            if ((ll)4 * sizes[i] > (ll)3 * bl) {
                c = ' ';
            } else if ((ll)4 * sizes[i] >  bl) {
                c = '-';
            } else {
                c = '#';
            }
            cout << "[" << c << "]";
        }
        cout << endl;

    }


    return 0;
}
