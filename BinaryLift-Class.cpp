class BinaryLift{
public:
    int n, LOG = 20; // root = 1;
    vector<vector<int>>tree, ancestors;
    vector<int>depth;
    BinaryLift(vector<vector<int>>&v){
        n = v.size() - 1;
        tree = v;
        depth.resize(n + 1, 0);
        ancestors = vector<vector<int>>(n + 1, vector<int>(LOG, 0));
        initialize(1, 0);
    }
    void initialize(int node, int par){
        depth[node] = depth[par] + 1;
        ancestors[node][0] = par;
        for(int i = 1; i < LOG; i ++){
            int mid = ancestors[node][i - 1];
            ancestors[node][i] = ancestors[mid][i - 1];
        }
        for(int adj : tree[node]){
            if(adj != par){
                initialize(adj, node);
            }
        }
    }
    int LCA(int u, int v){
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
    }
    int distance(int x, int y){
        int lca = LCA(x, y);
        int dif = abs(depth[x] - depth[y]);
        int mn = min(depth[x], depth[y]);
        dif += 2 * (mn - depth[lca]);
        return dif;
    }
};
