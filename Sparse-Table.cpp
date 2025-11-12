struct SparseTable {
    int n, LOG;
    vector<int> arr, log_table;
    vector<vector<int>> sparse;
    SparseTable(vector<int>&v) {
        n = v.size();
        LOG = log2(2 * n);
        arr.resize(2 * n);
        log_table.resize(2 * n + 1);
        sparse.resize(LOG + 1, vector<int>(2 * n));
        for (int i = 0; i < n; i ++) {
            arr[i] = v[i];
            arr[n + i] = v[i];
        }
        build();
    }
    void build() {
        log_table[1] = 0;
        for (int i = 2; i <= 2 * n; i++){
            log_table[i] = log_table[i / 2] + 1;
        }
        for (int i = 0; i < 2 * n; i ++){
            sparse[0][i] = arr[i];
        }
        for (int level = 1; level <= LOG; level ++) {
            for (int i = 0; i + (1 << level) <= 2 * n; i++) {
                sparse[level][i] = gcd(
                    sparse[level - 1][i],
                    sparse[level - 1][i + (1 << (level - 1))]
                );
            }
        }
    }
    int query(int l, int r) {
        int len = r - l + 1;
        int p = log_table[len];
        return __gcd(sparse[p][l], sparse[p][r - (1 << p) + 1]);
    }
};
