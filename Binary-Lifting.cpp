#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007

void bol_bacchan() {
    int n, LOG = 20;
    cin >> n;
    vector<int>depth(n + 1, 0);
    vector<vector<int>>tree(n + 1);
    for(int i = 1; i < n; i ++){
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    vector<vector<int>>ancestors(n + 1, vector<int>(LOG, 0));

    auto binary_lift = [&](int node, int par, auto&& F)->void{
        depth[node] = depth[par] + 1;
        ancestors[node][0] = par;
        for(int i = 1; i < LOG; i ++){
            int mid = ancestors[node][i - 1];
            ancestors[node][i] = ancestors[mid][i - 1];
        }
        for(int adj : tree[node]){
            if(adj != par){
                F(adj, node, F);
            }
        }
    };
    binary_lift(1, 0, binary_lift);

    auto LCA = [&](int u, int v)->int{
        if(depth[u] < depth[v]) swap(u, v);
        int dif = depth[u] - depth[v];

        for(int i = 0; i < LOG; i ++){
            if((1 << i) & dif){
                u = ancestors[u][i];
            }
        }

        for(int i = LOG - 1; i >= 0; i --){
            if(ancestors[u][i] != ancestors[v][i]){
                u = ancestors[u][i];
                v = ancestors[v][i];
            }
        }
        return u == v ? u : ancestors[u][0];
    };

    auto kth_ancestor = [&](int x, int k) -> int {
        for (int i = 0; i < LOG; i++) {
            if (k & (1 << i)) {
                x = ancestors[x][i];
                if (x == 0) break;
            }
        }
        return x == 0 ? -1 : x;
    };

    auto dist = [&](int x, int y)->int{
        int lca = LCA(x, y);
        int dif = abs(depth[x] - depth[y]);
        int mn = min(depth[x], depth[y]);
        dif += 2 * (mn - depth[lca]);
        return dif;
    };
}

signed main() {
    
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL); cout.tie(NULL);

    init();
    
    int test = 1; 
    cin >> test;
    while (test--) {
        bol_bacchan();
    }
}
