struct MiddleElement{
    multiset<int>left, right;
    int leftSum = 0, rightSum = 0;
    void balance(){
        while(left.size() < right.size()){
            leftSum += *right.begin();
            rightSum -= *right.begin();
            left.insert(*right.begin());
            right.erase(right.find(*right.begin()));
        }
        while(left.size() > right.size() + 1){
            rightSum += *left.rbegin();
            leftSum -= *left.rbegin();
            right.insert(*left.rbegin());
            left.erase(left.find(*left.rbegin()));
        }
    }
    void insert(int x){
        if(left.empty() || *left.rbegin() >= x){
            leftSum += x;
            left.insert(x);
        }
        else{
            rightSum += x;
            right.insert(x);
        }
        balance();
    }
    void erase(int x){
        if(left.find(x) != left.end()){
            leftSum -= x;
            left.erase(left.find(x));
        }
        else {
            rightSum -= x;
            right.erase(right.find(x));
        }
        balance();
    }
    int get(){
        int median = *left.rbegin();
        int leftSz = left.size() - 1, rightSz = right.size();
        int prefix = leftSum - median, suffix = rightSum;
        return median * leftSz - prefix + suffix - median * rightSz;
    }
};

void bol_bacchan() {
    int n, k;
    cin >> n >> k;
    vector<int>v(n), ans;
    for(int i = 0; i < n; i ++) cin >> v[i];
    int l = 0, r = 0;
    MiddleElement mde;
    while(r < k - 1){
        mde.insert(v[r]);
        r ++;
    }
    while(r < n){
        mde.insert(v[r]);
        cout << mde.get() << ' ';
        mde.erase(v[l]);
        l ++;
        r ++;
    }
    for(int i : ans) cout << i << ' ';
    cout << endl;
}
