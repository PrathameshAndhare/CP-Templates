class SGT{
public:
    int n;
    vector<int>tree, arr, lazy;
    SGT(vector<int>&v){
        n = v.size();
        arr.resize(n + 1);
        tree.resize(4 * n + 1);
        lazy.resize(4 * n + 1, 0);
        for(int i = 0; i < n; i ++){
            arr[i + 1] = v[i];
        }
        build(1, n, 1);
    }
    void build(int start, int end, int index){
        if(start == end) {
            tree[index] = arr[start];
            return;
        }

        int mid = (start + end) / 2;
        build(start, mid, 2 * index);
        build(mid + 1, end, 2 * index + 1);

        tree[index] = tree[2 * index] ^ tree[2 * index + 1];
    }
    void push(int start, int end, int index){
        if(lazy[index] != 0){
            tree[index] += (end - start + 1) * lazy[index];
            if(start != end){
                lazy[2 * index] += lazy[index];
                lazy[2 * index + 1] += lazy[index];
            }
            lazy[index] = 0;
        }
    };
    void update(int start, int end, int index, int l, int r, int val){
        push(start, end, index);
        if(l > end || start > r) return;
        if(start >= l && end <= r){
            lazy[index] += val;
            push(start, end, index);
            return;
        }

        int mid = (start + end) / 2;
        update(start, mid, index * 2, l, r, val);
        update(mid + 1, end, index * 2 + 1, l, r, val);

        tree[index] = tree[2 * index] + tree[2 * index + 1];
    }
    int query(int start, int end, int index, int x){
        push(start, end, index);
        if(start == end) return tree[index];

        int mid = (start + end) / 2;
        if(x <= mid){
            return query(start, mid, index * 2, x);
        }
        else return query(mid + 1, end, 2 * index + 1, x);
    }
};
