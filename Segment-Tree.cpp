 // For Sum of values in range [l, r].
class SGT{
public:
    int n;
    vector<int>tree, arr;
    SGT(vector<int>v){
        n = v.size();
        arr.resize(n + 1);
        tree.resize(4 * n + 1);
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

        tree[index] = tree[2 * index] + tree[2 * index + 1];
    }
    void update(int start, int end, int index, int update_index, int update_value){
        if(start == end){
            tree[index] = update_value;
            return; 
        }
        int mid = (start + end) / 2;
        if(update_index <= mid){
            update(start, mid, index * 2, update_index, update_value);
        }
        else{
            update(mid + 1, end, index * 2 + 1, update_index, update_value);
        }

        tree[index] = tree[2 * index] + tree[2 * index + 1];
    }
    int query(int start, int end, int index, int l, int r){
        if(l > end || start > r) return 0;
        if(start >= l && end <= r) return tree[index];

        int mid = (start + end) / 2;
        int left = query(start, mid, index * 2, l, r);
        int right = query(mid + 1, end, 2 * index + 1, l, r);
        return left + right;
    }
};
