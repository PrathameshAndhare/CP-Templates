struct Hash{
public:
    int base1 = 5689, base2 = 8861;
    vector<pair<int, int> >power, hash;
    Hash(string s){
        int n = s.length();
        hash.resize(n + 1, make_pair(0, 0));
        power.resize(n + 1, make_pair(1, 1));
        for(int i = 0; i < n; i ++){
            hash[i + 1].first = (1LL * hash[i].first * base1 + (s[i] - 'a' + 1)) % mod;
            hash[i + 1].second = (1LL * hash[i].second * base2 + (s[i] - 'a' + 1)) % mod;
            power[i + 1].first = (1LL * power[i].first * base1) % mod;
            power[i + 1].second = (1LL * power[i].second * base2) % mod;
        }
    } 
    pair<int, int> get(int l, int r){
        l ++;
        r ++;
        int val1 = (hash[r].first - (1LL * hash[l - 1].first * power[r - l + 1].first) % mod + mod) % mod;
        int val2 = (hash[r].second - (1LL * hash[l - 1].second * power[r - l + 1].second) % mod + mod) % mod;
        return make_pair(val1, val2);
    }
};
