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

    auto dist = [&](int x, int y)->int{
        int lca = LCA(x, y);
        int dif = abs(depth[x] - depth[y]);
        int mn = min(depth[x], depth[y]);
        dif += 2 * (mn - depth[lca]);
        return dif;
    };

    int mx_depth = 0, num1 = 0;
    for(int i = 1; i <= n; i ++){
        if(depth[i] > mx_depth){
            mx_depth = depth[i];
            num1 = i;
        }
    }

    vector<int>depth2(n + 1);
     auto dfs = [&](int node, int par, auto&& F)->void{
        depth2[node] = depth2[par] + 1;
        for(int adj : tree[node]){
            if(adj != par){
                F(adj, node, F);
            }
        }
     };
     dfs(num1, 0, dfs);

     mx_depth = 0;
     int num2 = 0;
     for(int i = 1; i <= n; i ++){
        if(depth2[i] > mx_depth){
            mx_depth = depth2[i];
            num2 = i;
        }
    }

    for(int i = 1; i <= n; i ++){
        int dist1 = dist(i, num1);
        int dist2 = dist(i, num2);
        cout << max(dist1, dist2) << ' ';
    }
    cout << endl;

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
