//https://www.spoj.com/problems/TUPLEDIV/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXN = 10005;
const int MAXM = 12;
const long long INF_LL = 1e18;

int N, M;
int C[MAXM];
int val[MAXN][MAXM];

struct VectorCost {
    long long v[MAXM];

    VectorCost() {
        for(int i=0; i<MAXM; ++i) v[i] = 0;
    }

    void set_val(int dim, int val) {
        for(int i=0; i<MAXM; ++i) v[i] = 0;
        if(dim >= 0 && dim < MAXM) v[dim] = val;
    }

    VectorCost operator+(const VectorCost& other) const {
        VectorCost res;
        for(int i=0; i<M; ++i) res.v[i] = v[i] + other.v[i];
        return res;
    }

    VectorCost operator-(const VectorCost& other) const {
        VectorCost res;
        for(int i=0; i<M; ++i) res.v[i] = v[i] - other.v[i];
        return res;
    }

    bool operator<(const VectorCost& other) const {
        for(int i=0; i<M; ++i) {
            if(v[i] != other.v[i]) return v[i] < other.v[i];
        }
        return false;
    }

    bool operator>(const VectorCost& other) const {
        return other < *this;
    }

    bool operator==(const VectorCost& other) const {
        for(int i=0; i<M; ++i) if(v[i] != other.v[i]) return false;
        return true;
    }

    bool operator!=(const VectorCost& other) const {
        return !(*this == other);
    }
};

struct EdgeData {
    VectorCost cost;
    int tuple_idx;

    bool operator>(const EdgeData& other) const {
        return cost > other.cost;
    }
};

int current_group[MAXN];
int group_count[MAXM];

priority_queue<EdgeData, vector<EdgeData>, greater<EdgeData>> heaps[MAXM + 1][MAXM + 1];
VectorCost potentials[MAXM + 1];
VectorCost dist[MAXM + 1];
int parent_node[MAXM + 1];
int trans_tuple[MAXM + 1];
bool visited[MAXM + 1];

VectorCost get_tuple_cost(int tuple_idx, int group_idx) {
    VectorCost c;
    if (group_idx < M) {
        c.set_val(group_idx, -val[tuple_idx][group_idx]);
    }
    return c;
}

void solve() {
    cin >> N >> M;

    int total_needed = 0;
    for (int i = 0; i < M; ++i) {
        cin >> C[i];
        total_needed += C[i];
        group_count[i] = 0;
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> val[i][j];
        }
        current_group[i] = M;
    }

    for(int i=0; i<=M; ++i) {
        for(int j=0; j<=M; ++j) {
            while(!heaps[i][j].empty()) heaps[i][j].pop();
        }
        potentials[i] = VectorCost();
    }

    for(int i=1; i<=N; ++i) {
        for(int j=0; j<M; ++j) {
            VectorCost cost = get_tuple_cost(i, j);
            heaps[M][j].push({cost, i});
        }
    }

    int items_processed = 0;

    while(items_processed < total_needed) {
        for(int i=0; i<=M; ++i) {
            dist[i].v[0] = INF_LL;
            visited[i] = false;
            parent_node[i] = -1;
        }

        dist[M] = VectorCost();

        while(true) {
            int u = -1;
            for(int i=0; i<=M; ++i) {
                if(!visited[i] && dist[i].v[0] != INF_LL) {
                    if(u == -1 || dist[i] < dist[u]) {
                        u = i;
                    }
                }
            }

            if(u == -1) break;
            visited[u] = true;

            for(int v=0; v<M; ++v) {
                if(u == v) continue;

                while(!heaps[u][v].empty()) {
                    if(current_group[heaps[u][v].top().tuple_idx] != u) {
                        heaps[u][v].pop();
                    } else {
                        break;
                    }
                }

                if(!heaps[u][v].empty()) {
                    EdgeData best_edge = heaps[u][v].top();
                    VectorCost reduced = best_edge.cost + potentials[u] - potentials[v];

                    if(dist[u] + reduced < dist[v]) {
                        dist[v] = dist[u] + reduced;
                        parent_node[v] = u;
                        trans_tuple[v] = best_edge.tuple_idx;
                    }
                }
            }
        }

        int best_sink = -1;
        VectorCost best_sink_dist;
        best_sink_dist.v[0] = INF_LL;

        for(int j=0; j<M; ++j) {
            if(group_count[j] < C[j] && dist[j].v[0] != INF_LL) {
                VectorCost potential_adjusted = dist[j] + potentials[j];

                if(best_sink == -1 || potential_adjusted < best_sink_dist) {
                    best_sink = j;
                    best_sink_dist = potential_adjusted;
                }
            }
        }

        if(best_sink == -1) break;

        int curr = best_sink;
        while(curr != M) {
            int prev = parent_node[curr];
            int item = trans_tuple[curr];

            current_group[item] = curr;

            for(int next=0; next<M; ++next) {
                if(next == curr) continue;
                VectorCost c_curr = get_tuple_cost(item, curr);
                VectorCost c_next = get_tuple_cost(item, next);
                heaps[curr][next].push({c_next - c_curr, item});
            }

            curr = prev;
        }

        group_count[best_sink]++;
        items_processed++;

        for(int i=0; i<=M; ++i) {
            if(dist[i].v[0] != INF_LL) {
                potentials[i] = potentials[i] + dist[i];
            }
        }
    }

    long long final_scores[MAXM];
    for(int i=0; i<M; ++i) final_scores[i] = 0;

    for(int i=1; i<=N; ++i) {
        if(current_group[i] < M) {
            final_scores[current_group[i]] += val[i][current_group[i]];
        }
    }

    for(int i=0; i<M; ++i) {
        cout << final_scores[i] << (i == M - 1 ? "" : " ");
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
