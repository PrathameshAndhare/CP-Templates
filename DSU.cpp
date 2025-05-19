class DSU{
public:
    vector<int>par, siz;
    DSU(int n){
        par.resize(n + 1, 0);
        siz.resize(n + 1, 1);
        for(int i = 1; i <= n; i ++) par[i] = i;
    }
    int boss(int node){
        if(par[node] == node) return node;
        return par[node] = boss(par[node]);
    }
    void connect(int u, int v){
        u = boss(u);
        v = boss(v);
        if(u == v) return;
        if(siz[u] > siz[v]){
            par[v] = u;
            siz[u] += siz[v];
        }
        else{
            par[u] = v;
            siz[v] += siz[u];
        }
    }
};
